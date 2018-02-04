# ibusのテキストイベント(lookuptable以外)の流れ

ibusはpreeditで貯めてcommitで発火という感じ。

TODO:画像例(ibus-levenaのpreeditからcommitの挙動gif)

大体のimeの挙動は(日本語入力モードになっている時に)a~z、A〜Zの文字列(以降is\_alpha)が来た場合、ibus\_xxx\_engineに実装しているpreedit(文字のqueue)にためてEnterキーで確定(commit)する感じ。

TODO:画像例(preeditに溜まっているところのgif)

preeditはあくまで内部状態なので表示の状態を変えるにはsorroundテキストとかを使用しないといけないっぽい。(多分)

また、enterを押したときにpreeditをcommitするだけの挙動をしていてはバギーなので(preeditを確定するだけとエンターキー本来の挙動)preeditがあるかどうかによって挙動を変える。

TODO:変換候補を確定するだけの挙動と普通にエンターを押したときの挙動のgif

preeditイベントやcommitイベントはibusから呼ばれるわけではないので、自力でprocess-key-eventから呼ぶ必要がある。

また、preeditを扱う時はcursor_pos(カーソルキーの位置)も一緒に保持しておく必要がある。

## ibus-cannaやibus-tmplのそのへんの実装

* ibus-tmpl

* ibus-canna

g_insert_cの説明とか

* ibus-levena

## 変換テーブル候補の挙動

変換テーブル関係はlookup系の関数で行う。

preeditが0の時の挙動は当然スペースキー本来の挙動（空白）なのでこれも挙動を変える必要がある。

## ibus-levenaの実装
