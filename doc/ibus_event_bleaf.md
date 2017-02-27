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
//TODO:delete the statement
hokano jissou ha ibus ni touroku sinakutemo ugoku youni omoeruga, jissainiha process_key_event kara yobareta kannsuudearu

other implement(e.g ibus-tmpl) seemed 