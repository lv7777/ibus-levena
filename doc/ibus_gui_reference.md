このドキュメントでは，ibusのgui関係，特にpreferenceとプロパティについて説明する．

# about preferences

ibus-setupで設定ボタンを開くとime独自の設定画面が開かれるはず．これがpreference．

このことからguiを実際に作るのは分かるがどこで設定をするのか分からなかったがアレはibusのメインエンジンとは独立して作ることができる．

mozc.xmlやcanna.xmlなどのengineセクションにnameセクションがある．

ibus-setup-"nameセクションの名前"というプログラムを独自で(エンジンとは別に)作り，それを/usr/lib\*/に置く．

/usr/lib\*というのは例えば/usr/lib/ibus/ibus-setup-XXXのような感じ．

自分はここに置いといたら動いたし他のエンジンもここに置いているのでまぁここでいいんじゃね？

実際にconfig組むのはgtkでやる．

e.g.

levena.xmlではengine以下nameセクションでは`ibus-levena`となっている．

この場合は/usr/lib/ibus/ibus-setup-ibus-levenaとする．

まぁconfigはそっち側でibus.hでも呼び出してconfig service使えば良さそう．

んでengine側ではibus起動時にibusconfig的なの読み出しておk．

