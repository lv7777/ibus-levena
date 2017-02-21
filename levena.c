
//TODO:move to levena.c
//ibus.hにはibusengine.hやらglibc.hやらがincludeされてる
#include<ibus.h>

// prototype declaration

void registerComponent(IBusBus *);

//I will migrate to levena.h

#define IBUS_TYPE_LEVENA_ENGINE (ibus_levena_engine_get_type())
GType ibus_levena_engine_get_type(void);
//GType型システムに登録する。TODO:もっと詳しく

typedef struct tagIBusLevenaEngine IBusLevenaEngine;
typedef struct tagIBusLevenaEngineClass IBusLevenaEngineClass;

//インスタンス変数等を登録する。
struct tagIBusLevenaEngine{
    IBusEngine parent;
};

//こっちはメソッドやらクラス変数を登録する。
struct tagIBusLevenaEngineClass{
    IBusEngineClass parent;
};
//上記２つは公開している。protectedやprivateじゃない。

//TODO:if understand ibus_obuject_get_type implemnt,delete and test
G_DEFINE_TYPE(IBusLevenaEngine,ibus_levena_engine,IBUS_TYPE_ENGINE)

//インスタンス化された時に呼び出される。コンストラクタ。
//https://documents.mikeforce.net/glib-2.18.x-refs/gobject/html/gtype-instantiable-classed.html#gtype-instantiable-classed-init-done
void ibus_levena_engine_init(IBusLevenaEngine *klass){
    g_printf("levena-engine init!");
}

void ibus_levena_engine_class_init(IBusLevenaEngineClass *klass){
    g_printf("levena-engine init! in class");
}

void ibus_levena_engine_destroy(IBusLevenaEngine *klass){
    g_printf("end!!");
}

//TODO:return value no haaku
// GType ibus_levena_engine_get_type(){

// }


//catch the process-key-event signal from ibus_init
gboolean levena_process_key_event(IBusEngine *ie,guint keyval,guint keycode,guint state,gpointer user_data){

printf("process-key-event signal recieved!! : %x",keycode);
gboolean ret=0;
return TRUE;
}


int main(int argc,char **argv){

ibus_init();//絶対必要っぽい。忘れてた。

//必要なibus_系の宣言
IBusBus *bus;
IBusFactory *factory;
//component: imeエンジンの説明、作者、バージョン等。通常xmlから読み込む
IBusComponent *component;

//カスタムIMEのエンジンの追加。こいつをIBusEngineClassに変換する。
IBusLevenaEngineClass *levenaengine;
//process_key_event登録用のエンジンクラス。詳細不明
IBusEngineClass *iec;
gchar *IMEname="ibus-levena";


bus=ibus_bus_new();
factory=ibus_factory_new(ibus_bus_get_connection(bus));
//todo:下の理解。ime側エンジンを作成する。addするわkではない。例えばstructとかの宣言とかを省けるんじゃないかな？
//とりあえずibus_factory_create_engineとibus_factory_add_engineは違う。
//ibus_factory_create_engine(factory,IMEname);
//TODO:engineタイプの追加。
ibus_factory_add_engine(factory,IMEname,IBUS_TYPE_LEVENA_ENGINE);

iec=IBUS_ENGINE_CLASS (levenaengine);
iec->process_key_event=levena_process_key_event;

//最後にして至高の一撃、ibus_main()
ibus_main();
}

void registerComponent(IBusBus *bus){
    IBusComponent
}