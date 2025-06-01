# Gloss Design Guidelines

この文書は、Tosa Nikki 翻訳・注釈プロジェクト、およびその他 gloss 記録プロジェクトにおける gloss 設計方針を定めたものです。

## Last change: 2025/06/01-10:38:29.

## ✅ 基本原則

1. **gloss は常に1語に統一する**

   - 主たる意味・代表的な英語1語を選ぶ。
   - 意味が複数ある場合でも、複数の候補（例：attach / affix）は記載しない。
   - 例：
     ✅ `{ "word": "つく", "gloss": "attach" }`
     ❌ `{ "word": "つく", "gloss": "attach / affix" }`

2. **用語の専門性は中庸に保つ**

   - 難解な学術用語（例：affix、approach、convey）よりも、日常英語で理解できる語（例：attach、go、say）を優先する。
   - 特別な理由がない限り、専門用語や文語調は避ける。

3. **Leipzig Glossing Rules（LGR）の略語は定義リストで管理する**

   - `glossary-abbreviations` セクションに使った略語のみを記録。
   - 不要な略語や使っていない略語は出力に含めない。

4. **phrase-gloss の phrase は意味単位を基準に分ける**

   - 単語単位ではなく、語句・構文・意味のまとまり単位で分割。
   - 例：
     ✅ 「そのよしいさゝか」＝1つの phrase（意味的まとまり）
     ❌ 「その」「よし」「いさゝか」で個別に phrase を作る。

---

## ✅ 出力形式の統一例

```json
"phrase-gloss": [
  {
    "phrase": "ものにかきつく",
    "gloss": "write down",
    "words": [
      { "word": "もの", "gloss": "thing" },
      { "word": "に", "gloss": "LOC" },
      { "word": "かき", "gloss": "write" },
      { "word": "つく", "gloss": "attach" }
    ]
  }
]
```

---

## ✅ gloss-notes の英語側方針

- gloss-notes-en では日本語補記（例：「書き付く」など）は記載しない。
- 英語のみで簡潔・明快に説明する。

---

## ✅ 将来的な拡張

- gloss-linter（自動整備ツール）を導入する場合、本ガイドラインを標準仕様として組み込む。
- 用語集（master glossary）を作成し、全ての gloss 候補を統一管理する。

---

必要に応じて、このガイドラインは随時更新する。
