# Tosa Nikki / The Tosa Diary

Translation sentences by Hilofumi Yamamoto.

## Overview

This is a translation of the Tosa Diary (土佐日記, Tosa Nikki) by Hilofumi Yamamoto.
The open text "Aozora bunko" was used.

### **Data format**

It is written in json format as follows:

| tag              | content                                 |
| ---------------- | --------------------------------------- |
| "title"          | title                                   |
| "title_kana"     | kana notation of the title              |
| "title_roman"    | romaji of the title                     |
| "author"         | author                                  |
| "author_kana"    | kana notation of the author             |
| "author_roman"   | romaji of the author                    |
| "paragraph"      | text or poem sentence                   |
| "date"           | date of the revision                    |
| "id"             | id of the text                          |
| "text"           | text of the sentence                    |
| "poem"           | poem sentence                           |
| "kana"           | kana notation of the text/poem sentence |
| "translation-ja" | contemporary translation                |
| "translation-en" | English translation                     |

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
    ]
  }
]' tosanikki.json | lv
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
