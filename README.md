# Tosa Nikki / The Tosa Diary

Translation sentences by Hilofumi Yamamoto.

## Overview

This is a translation of the Tosa Diary (土佐日記, Tosa Nikki) by Hilofumi Yamamoto.
The open text "Aozora bunko" was used.

### **Data format**

It is written in json format as follows:

| tag                      | content                                 |
| ------------------------ | --------------------------------------- |
| "title"                  | title                                   |
| "title_kana"             | kana notation of the title              |
| "title_roman"            | romaji of the title                     |
| "author"                 | author                                  |
| "author_kana"            | kana notation of the author             |
| "author_roman"           | romaji of the author                    |
| "paragraph"              | text or poem sentence                   |
| "date"                   | date of the revision                    |
| "id"                     | id of the text                          |
| "text"                   | text of the sentence                    |
| "poem"                   | poem sentence                           |
| "kana"                   | kana notation of the text/poem sentence |
| "translation-ja"         | contemporary translation (literal)      |
| "translation-ja-natural" | contemporary translation (interpretive) |
| "translation-en"         | English translation (literal)           |
| "translation-en-natural" | English translation (interpretive)      |

### **Example**

```json
[
  {
    "title": "土佐日記",
    "title_kana": "とさにき",
    "title_roman": "Tosa Nikki",
    "author": "紀貫之",
    "author_kana": "きのつらゆき",
    "author_roman": "Ki no Tsurayuki",
    "paragraph": [
      {
        "date": "20241026",
        "id": "1",
        "text": "男もすなる日記といふものを、女もしてみむとてするなり。",
        "kana": "をとこもすなるにきといふものを、をんなもしてみむとてするなり。",
        "translation-ja": "漢字で書く日記とかいうものを、仮名でしてみようとしてするものである。",
        "translation-en": "A diary is something written in the masculine style, but I will try writing it in the feminine style.",
        "translation-en-natural": "So, diaries are usually done up in this formal, masculine style... but here I am, giving it a go in a bit more of a feminine touch."
      },
      {
        "date": "20241026",
        "id": "2",
        "text": "それの年のしはすの二十日あまり一日の、戌の時に門出す。",
        "kana": "それのとしのしはすのはつかあまりついたちの、いぬのときにかどです。",
        "translation-ja": "その年（承平四年）の師走の二十一日の、戌の時に出発しました。",
        "translation-en": "On the twenty-first day of December in the 4th year of the Shohei era, we departed at the hour of the dog (around 8 to 10 PM).",
        "translation-en-natural": "December 21st, Shohei Era, Year 4. Set off around the hour of the dog (between 8 and 10 PM)."
      }
    ]
  }
]
```

### **To process the data**

This json file can be manipulated with the following command with jq:

```sh
$ jq '[. |
  {
    title: .title,
    title_kana: .title_kana,
    title_roman: .title_roman,
    author: .author,
    author_kana: .author_kana,
    author_roman: .author_roman,
    paragraph: [
      .paragraph[] |
      {date: .date, id: .id}
      + (if .text != null then {text: .text} else {} end)
      + (if .poem != null then {poem: .poem} else {} end)
      + (if .kana != null then {kana: .kana} else {} end)
      + (if ."translation-ja" != null then {"translation-ja": ."translation-ja"} else {} end)
      + (if ."translation-en" != null then {"translation-en": ."translation-en"} else {} end)
      + (if ."translation-ja-natural" != null then {"translation-ja-natural": ."translation-ja-natural"} else {} end)
      + (if ."translation-en-natural" != null then {"translation-en-natural": ."translation-en-natural"} else {} end)
    ]
  }
]' tosa.json | lv
```

### **Reference**

```bibtex
@book{kikuchi1995ae,
  author = {Kikuchi, Yasuhiko and Kimura, Masanori and Imuta, Tsunehisa},
  yomi = {Kikuchi, Yasuhiko and Kimura, Masanori and Imuta, Tsunehisa},
  title = {{Tosa Nikki (The Tosa Diary and Kagero Nikki (The Kagero Diary/The Gossamer Years)}},
  booktitle = {Shimpen Nihon Koten Bungaku Zenshu ({New Edition of Japanese Classical Literature})},
  year = {1995},
  month = {10},
  day = {10},
  publisher = {Shogakukan},
  OPTnote = {},
}
```
