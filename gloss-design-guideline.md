# Gloss Design Guidelines

この文書は、Tosa Nikki 翻訳・注釈プロジェクト、およびその他 gloss 記録プロジェクトにおける gloss 設計方針を定めたものです。

## Last change: 2025/06/03-13:50:54.

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

# 自然訳の方針メモ

このドキュメントは、翻訳作業における自然訳（translation-ja-natural / translation-en-natural）の方針を記録したものです。

---

## ✅ 基本方針

- 原文に書いてあることを最大限拾う。
- 原文に書かれていない補足（語り手の感情、伝聞、推測、背景説明）は自然訳に入れない。
- 現代語として不自然にならないように、語順・表現は整える。

---

## ✅ 具体例

- 「けり」→ **過去の事実としてのみ表現**（例：「〜だった」「〜があった」）。
- 「そうだ」「〜と伝えられている」などの補足的伝聞表現は付けない。
- 英語でも "it is said" などを付けず、直接表現する。

---

## ✅ 厳密訳と自然訳の役割分担

| 項目           | 厳密訳（translation-ja/en） | 自然訳（translation-ja-natural/en-natural）  |
| -------------- | --------------------------- | -------------------------------------------- |
| 文の忠実さ     | 原文構造を正確に再現        | 原文内容を拾いながら自然な語順・表現にする   |
| 補足情報の扱い | 一切付けない                | 付けない（ただし文の自然さのための整形はOK） |
| 文体           | である調（常体）            | である調（常体）、和歌のみですます調         |

---

✅ Gloss 記述ルールメモ
1️⃣ 語幹と活用を明示的に分ける

    語幹部分は意味 gloss（例：elegance, beauty, strength）。

    活用部分は文法 gloss（例：ATTR, ADV.F, PAST）。

例：
「おもしろき」 →
{ "word": "おもしろ", "gloss": "elegance" }, { "word": "き", "gloss": "ATTR" }
※ただし通常はまとめて
{ "word": "おもしろき", "gloss": "elegance.ATTR" } としてOK。
2️⃣ 格助詞の gloss は必ず助詞単体につける

    格助詞が決める文の格は、その助詞自体に gloss をつける。

    語幹や活用側に格（ACC, DAT, GEN など）を含めない。

例：
「おもしろきを」 →
{ "word": "おもしろき", "gloss": "elegance.ATTR" }, { "word": "を", "gloss": "ACC" }
3️⃣ まとめ書きは避ける

    語の内部と文法的接続の gloss を一語に統合しない。

    例外は助詞などが一語に縮約している場合（例：じゃ＝では、だに＝すら）。

4️⃣ 意味分類 gloss と文法 gloss はピリオドで区切る

    複合 gloss は 意味.文法 の順。

    例：elegance.ATTR, strength.ADV.F

5️⃣ 全体 gloss（phrase-gloss）は単語間をスペース、単語内をピリオドで区切る

    例：
    phrase gloss: elegance.ATTR ACC praise

✅ このルールの適用例

文：

    この殿のおもしろきをほむる歌よむ

gloss（単語ごと）：

[
{ "word": "この", "gloss": "this" },
{ "word": "殿", "gloss": "lord.GEN" },
{ "word": "の", "gloss": "GEN" },
{ "word": "おもしろき", "gloss": "elegance.ATTR" },
{ "word": "を", "gloss": "ACC" },
{ "word": "ほむる", "gloss": "praise.ATTR" },
{ "word": "歌", "gloss": "song" },
{ "word": "よむ", "gloss": "compose" }
]

---

# Gloss 記述ルールメモ

---

## 1️⃣ 語幹と活用を明示的に分ける

- 語幹部分は意味 gloss（例：`elegance`, `beauty`, `strength`）。
- 活用部分は文法 gloss（例：`ATTR`, `ADV.F`, `PAST`）。

例：
「おもしろき」 →
`おもしろ` → `elegance`
`き` → `ATTR`
→ まとめる場合は：`elegance.ATTR`

---

## 2️⃣ 格助詞の gloss は必ず助詞単体につける

- 格助詞が決める文の格（`ACC`, `DAT`, `GEN` など）は、その助詞自体に gloss をつける。
- 語幹や活用側に格情報を含めない。

例：
「おもしろきを」 →
`{ "word": "おもしろき", "gloss": "elegance.ATTR" }, { "word": "を", "gloss": "ACC" }`

---

## 3️⃣ まとめ書きは避ける

- 語の内部と文法的接続の gloss を一語に統合しない。
- 例外は助詞などが一語に縮約している場合（例：`じゃ`＝`では`、`だに`＝`すら`）。

---

## 4️⃣ 意味分類 gloss と文法 gloss はピリオドで区切る

- 複合 gloss は `意味.文法` の順に書く。
- 例：`elegance.ATTR`, `strength.ADV.F`

---

## 5️⃣ 全体 gloss（phrase-gloss）は単語間をスペース、単語内をピリオドで区切る

- 例：
  phrase gloss: `elegance.ATTR ACC praise`

---

### ✅ 適用例

文：
この殿のおもしろきをほむる歌よむ

単語ごとの gloss：

```json
[
  { "word": "この", "gloss": "this" },
  { "word": "殿", "gloss": "lord.GEN" },
  { "word": "の", "gloss": "GEN" },
  { "word": "おもしろき", "gloss": "elegance.ATTR" },
  { "word": "を", "gloss": "ACC" },
  { "word": "ほむる", "gloss": "praise.ATTR" },
  { "word": "歌", "gloss": "song" },
  { "word": "よむ", "gloss": "compose" }
]
```

---
