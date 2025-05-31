# Tosa Nikki / The Tosa Diary

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.15563257.svg)](https://doi.org/10.5281/zenodo.15563257)

Translation sentences
by Hilofumi Yamamoto Ph.D.
Institute of Science Tokyo

## Overview

This is a translation of the Tosa Diary (土佐日記, Tosa Nikki) by Hilofumi Yamamoto.
The open text "Aozora bunko" was used.

### **Data format**

It is written in json format as follows:

| tag                      | content                                          |
| ------------------------ | ------------------------------------------------ |
| "title"                  | title                                            |
| "title_kana"             | kana notation of the title                       |
| "title_roman"            | romaji of the title                              |
| "author"                 | author                                           |
| "author_kana"            | kana notation of the author                      |
| "author_roman"           | romaji of the author                             |
| "paragraph"              | text or poem sentence                            |
| "date"                   | date of the revision                             |
| "id"                     | id of the text                                   |
| "text"                   | text of the sentence                             |
| "poem"                   | poem sentence                                    |
| "kana"                   | kana notation of the text/poem sentence          |
| "translation-ja"         | contemporary translation (literal)               |
| "translation-en"         | English translation (literal)                    |
| "phrase-gloss"           | Gloss by each phrase                             |
| "gloss-notes-ja"         | Gloss notes in Japanese                          |
| "gloss-notes-en"         | Gloss notes in English                           |
| "glossary-abbreviations" | Glossary abbreviations                           |
| "translation-ja-natural" | contemporary Japanese translation (interpretive) |
| "translation-en-natural" | English translation (interpretive)               |
| "notes-ja"               | Notes in Japanese                                |
| "notes-en"               | Notes in English                                 |
| "commentary-ja"          | Related Notes in Japanese                        |
| "commentary-en"          | Related Notes in English                         |

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
        "translation-ja-natural": "男の書き方で書くという日記を、女の書き方で書いてみようと思って書いているのです。",
        "translation-en-natural": "So, diaries are usually done up in this formal, masculine style... but here I am, giving it a go in a bit more of a feminine touch."
      },
      {
        "date": "20241026",
        "id": "2",
        "text": "それの年のしはすの二十日あまり一日の、戌の時に門出す。",
        "kana": "それのとしのしはすのはつかあまりついたちの、いぬのときにかどです。",
        "translation-ja": "その年（承平四年）の師走の二十一日の、戌の時に出発しました。",
        "translation-en": "On the twenty-first day of December in the 4th year of the Shohei era, we departed at the hour of the dog (around 8 to 10 PM).",
        "translation-ja-natural": "その年（承平四年）の十二月二十一日、戌の刻に出発しました。",
        "translation-en-natural": "December 21st, Shohei Era, Year 4. Set off around the hour of the dog (between 8 and 10 PM)."
      }
    ]
  }
]
```

### **To process the data**

This json file can be manipulated with the following command with jq:

```sh
#!/bin/bash
jq '[. |
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
      + (if ."koutei-yamagen" != null then {"koutei-yamagen": ."koutei-yamagen"} else {} end)
      + (if ."translation-ja" != null then {"translation-ja": ."translation-ja"} else {} end)
      + (if ."translation-en" != null then {"translation-en": ."translation-en"} else {} end)

      + (if ."phrase-gloss" != null then {"phrase-gloss": ."phrase-gloss"} else {} end)
      + (if ."gloss-notes-ja" != null then {"gloss-notes-ja": ."gloss-notes-ja"} else {} end)
      + (if ."gloss-notes-en" != null then {"gloss-notes-en": ."gloss-notes-en"} else {} end)
      + (if ."glossary-abbreviations" != null then {"glossary-abbreviations": ."glossary-abbreviations"} else {} end)
      + (if ."translation-ja-natural" != null then {"translation-ja-natural": ."translation-ja-natural"} else {} end)
      + (if ."translation-en-natural" != null then {"translation-en-natural": ."translation-en-natural"} else {} end)
      + (if ."notes-ja" != null then {"notes-ja": ."notes-ja"} else {} end)
      + (if ."notes-en" != null then {"notes-en": ."notes-en"} else {} end)
#      + (if ."commentary-ja" != null then {"commentary-ja": ."commentary-ja"} else {} end)
#      + (if ."commentary-en" != null then {"commentary-en": ."commentary-en"} else {} end)
    ]
  }
]' $1
```

### **Reference**

```
底本：「國文大觀　日記草子部」明文社
　　　1906（明治39）年1月30日初版発行
　　　1909（明治42）年10月12日再版発行
※このファイルは、日本文学等テキストファイル（http://www.let.osaka-u.ac.jp/~okajima/bungaku.htm）で公開されたものを、青空文庫形式にあらためて作成しました。
※校正には、「國文大觀　日記草子部」板倉屋書房、1903（明治36）年10月27日発行を使用しました。
※割り注を（）に入れました。
※「現在通行字体の〈し〉」「志に由来する変体仮名」ともに、「し」で入力しました。
※「楫」と「<img src="tosanikki_files/1-86-21.png" alt="※(「楫＋戈」、第3水準1-86-21)" class="gaiji">」の混在については底本通りにしました。
※監修者、編纂者の没年は以下の通りです。
監修者　本居豊穎　（1913（大正2）年2月15日没）
同　　　木村正辭　（1913（大正2）年4月10日没）
同　　　小杉榲邨　（1910（明治43）年3月30日没）
同　　　井上頼圀　（1914（大正3）年7月3日没）
同　　故落合直文　（1903（明治36）年12月16日没）
編纂者　丸岡　桂　（1919（大正8）年2月12日没）
同　　　松下大三郎（1935（昭和10）年5月2日没）
松下以外の没年月日は講談社学術文庫『大日本人名辞書』による。
松下の没年月日は徳田正信『近代文法図説』（明治書院）による。
編纂者等の著作権は消失している。
入力：岡島昭浩
校正：小林繁雄
2004年7月6日作成
2011年4月29日修正
青空文庫作成ファイル：
このファイルは、インターネットの図書館、<a href="http://www.aozora.gr.jp/">青空文庫（http://www.aozora.gr.jp/）</a>で作られました。入力、校正、制作にあたったのは、ボランティアの皆さんです。
```

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
