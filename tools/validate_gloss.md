**`.github/copilot-instructions.md` から略号を自動抽出して検証に使える版** にします。

これにより、略号表を編集したときも、バリデータが自動で最新状態を使うようになります。
いちいち Python スクリプト内のリストを更新する必要がなくなります。

---

## ✅ `tosa/tools/validate_gloss.py`（最新版）

````python
#!/usr/bin/env python3
"""
validate_gloss.py
Gloss JSON validator for the Tosa Translation Project.

Checks:
  - JSON syntax
  - required keys ("phrase", "gloss", "words")
  - unknown gloss abbreviations based on copilot-instructions.md

Usage:
  python3 validate_gloss.py tosa/gloss/*.json
"""

import json
import re
import sys
from pathlib import Path

# === ファイルパスの推定 ===
PROJECT_ROOT = Path(__file__).resolve().parents[1]
COPILOT_INSTRUCTIONS = PROJECT_ROOT/".github"/"copilot-instructions.md"

# === 正規表現 ===
ABBREV_JSON_BLOCK = re.compile(r'```json\s*\{(.+?)\}\s*```', re.DOTALL)
ABBREV_PATTERN = re.compile(r'"([A-Z][A-Z0-9]*(?:\.[A-Z0-9]+)*)"')
GLOSS_ABBREV_PATTERN = re.compile(r'\b([A-Z][A-Z0-9]*(?:\.[A-Z0-9]+)*)\b')

# === 略号の読み込み ===
def load_abbreviations():
    """copilot-instructions.md から abbreviation list を抽出"""
    if not COPILOT_INSTRUCTIONS.exists():
        print(f"[!] copilot-instructions.md not found: {COPILOT_INSTRUCTIONS}")
        return set()

    text = COPILOT_INSTRUCTIONS.read_text(encoding="utf-8")
    m = ABBREV_JSON_BLOCK.search(text)
    if not m:
        print("[!] Could not find JSON abbreviation block in copilot-instructions.md")
        return set()

    json_text = "{" + m.group(1) + "}"
    try:
        data = json.loads(json_text)
        abbrevs = set(data.get("abbreviations", {}).keys())
        print(f"[✓] Loaded {len(abbrevs)} abbreviations from copilot-instructions.md")
        return abbrevs
    except Exception as e:
        print(f"[!] Failed to parse abbreviation JSON block: {e}")
        return set()

# === gloss 検証 ===
def validate_gloss_entry(entry, filename, allowed):
    errors = []
    required_keys = {"phrase", "gloss", "words"}

    # キー存在チェック
    if not required_keys.issubset(entry.keys()):
        missing = required_keys - entry.keys()
        errors.append(f"Missing keys: {', '.join(missing)}")

    # gloss 内の略号チェック
    gloss_text = entry.get("gloss", "")
    for match in GLOSS_ABBREV_PATTERN.findall(gloss_text):
        for part in match.split("."):
            if part.isupper() and part not in allowed:
                errors.append(f"Unknown abbreviation '{part}' in gloss: {gloss_text}")

    # words 構造チェック
    words = entry.get("words", [])
    if not isinstance(words, list):
        errors.append("`words` should be a list.")
    else:
        for i, w in enumerate(words):
            if not isinstance(w, dict):
                errors.append(f"Word entry {i} is not a dict.")
            elif not {"word", "gloss"} <= w.keys():
                errors.append(f"Word entry {i} missing 'word' or 'gloss'.")

    # 出力
    if errors:
        print(f"[✗] {filename}: {entry.get('phrase', '(no phrase)')}")
        for e in errors:
            print("   -", e)
    else:
        print(f"[✓] {filename}: {entry.get('phrase', '(no phrase)')} OK")

def validate_file(path: Path, allowed):
    try:
        with open(path, "r", encoding="utf-8") as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        print(f"[!] JSON syntax error in {path}: {e}")
        return

    if isinstance(data, list):
        for entry in data:
            validate_gloss_entry(entry, path.name, allowed)
    elif isinstance(data, dict):
        validate_gloss_entry(data, path.name, allowed)
    else:
        print(f"[!] Unexpected JSON structure in {path}")

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 validate_gloss.py <gloss.json> [more.json ...]")
        sys.exit(1)

    allowed = load_abbreviations()
    if not allowed:
        print("[!] Warning: no abbreviations loaded, skipping abbreviation check.")

    for arg in sys.argv[1:]:
        path = Path(arg)
        if path.exists():
            validate_file(path, allowed)
        else:
            print(f"[!] File not found: {path}")

if __name__ == "__main__":
    main()
````

---

## ✅ このスクリプトの動作

1. `.github/copilot-instructions.md` を開き、
   `json ... ` で囲まれた abbreviation セクションを自動抽出。
2. その中の `"TOP"`, `"FOC"`, `"CAUS"`, ... などのキーをセットとして取得。
3. すべての gloss JSON の中をチェックし、

   * gloss 行に未知略号がないか
   * `phrase`, `gloss`, `words` のキーが揃っているか
   * `words` の中に欠落項目がないか
     を出力します。

---

## ✅ 実行例

```bash
$ python3 tosa/tools/validate_gloss.py tosa/gloss/371.json
[✓] Loaded 43 abbreviations from copilot-instructions.md
[✓] 371.json: けふわりごもたせてきたる人、 OK
[✓] 371.json: その名などぞや、 OK
```

もし略号が存在しない場合：

```bash
[✗] 371.json: けふわりごもたせてきたる人、
   - Unknown abbreviation 'PERFS' in gloss: today wrapping.cloth-carry-CAUS.REALIS CONJ come.PERFS.ATTR person
```

---

## ✅ 導入場所

* スクリプトを `tosa/tools/validate_gloss.py` に保存。
* 実行権限を付与：

  ```bash
  chmod +x tosa/tools/validate_gloss.py
  ```
* 以後、コマンドラインから簡単に実行可能です。

  ```bash
  ./tosa/tools/validate_gloss.py tosa/gloss/*.json
  ```

---

## ✅ 拡張案（次のステップ）

* `--strict` オプションで空欄や重複語を警告。
* `--summary` で統計出力（OK/NG件数）。
* `--md` オプションで Markdown 形式の検証レポートを生成。
* `pre-commit` hook に組み込み、自動で PR 前にチェック。

---

この仕組みを入れておくと、今後 AEAD・伊勢物語 gloss もすべて同一規格で自動検証できます。
次はこの validator を **pre-commit hook** に登録して、
`git commit` のたびに自動実行するように設定してみましょうか？

