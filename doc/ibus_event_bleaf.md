# ibus event and signal explanation

signal is fired by ibus.

So, if you want to calling signal, you need to regist function to ibus.

follow example is aim to regist function in ibus-levena.

```
void ibus_levena_engine_class_init(IBusLevenaEngineClass *klass){
    ibus_warning("levena-engine init! in class");

    IBusEngineClass *iec=IBUS_ENGINE_CLASS (klass);
    iec->process_key_event=ibus_levena_engine_process_key_event;
}
```

other implement(e.g ibus-tmpl) seemed 

# ibusのイベントやシグナル等の説明

シグナルはibusによってime側に送信される。

そのため、**もしあなたがシグナルをibusから呼んで欲しい場合、imeで実装されてる関数をibusに登録する必要がある。**

以下はibus-levenaで関数をibusに登録するためのコード例である。


```
void ibus_levena_engine_class_init(IBusLevenaEngineClass *klass){
    ibus_warning("levena-engine init! in class");

    IBusEngineClass *iec=IBUS_ENGINE_CLASS (klass);
    iec->process_key_event=ibus_levena_engine_process_key_event;
}
```

*他の実装(例：ibus-tmpl)ではibusに登録していなくてもibusから発火されるように思えるが、実際にはimeで実装されてるものが呼んでいるだけである。*

(例えば,ibus-tmplではibus-tmpl-engine-process-key-eventが発生した後にibus-tmpl-updateなどが発火されており筆者は困惑したがこれは単にprocess-key-eventから呼ばれているだけだった)

ibus-XXX-engineの接頭辞をつけて、[ここ](http://ibus.github.io/docs/ibus-1.5/IBusEngine.html)にある関数(ibus_engine_update_property等)を宣言しても**呼ばれるわけではない**
