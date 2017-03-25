# ibus-levena

ドキュメントとコメントに重きをおいた参考実装用ibus-ime．

このプロジェクトは[ibus-katari](https://github.com/WhiteHawk-taka/katari)にインスパイアされて作られました。

主にibus-katariのテスト機能の実装とかに使います。

# about

設定画面，入力モードの切り替えの部分（prop），変換テーブル等の機能が一通り揃ってます．

ただし中身は作られていません．

# compile

`gcc levena.c $(pkg-config ibus-1.0 --cflags --libs)`

そのうちでかくなったらMakefile書くかもしれません。

# author

lv7777