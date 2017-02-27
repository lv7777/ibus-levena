
//TODO:move to levena.c
//ibus.hにはibusengine.hやらglibc.hやらがincludeされてる
#include<ibus.h>
#include<stdio.h>
// prototype declaration


void print_handler (const gchar* message) { 
gchar *commandline; 
commandline = g_strdup_printf ("zenity --info --text=%s", message); 
g_spawn_command_line_sync (commandline, NULL, NULL, NULL, NULL); 
g_free (commandline); 
} 

void registerComponent(IBusBus *);
gboolean ibus_levena_engine_process_key_event(IBusEngine *,guint ,guint ,guint ,gpointer );
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
    g_print("levena-engine init!");

}

void ibus_levena_engine_class_init(IBusLevenaEngineClass *klass){
    g_print("levena-engine init! in class");

   IBusEngineClass *iec=IBUS_ENGINE_CLASS (klass);
iec->process_key_event=ibus_levena_engine_process_key_event;
}

void ibus_levena_engine_destroy(IBusLevenaEngine *klass){
    g_print("signal_destroy");
}

void ibus_levena_engine_update_lookup_table(IBusLevenaEngine *klass){
    g_print("signal_update_lookup_table");
}

void ibus_levena_engine_update_preedit(IBusLevenaEngine *klass){
    g_print("signal_update_preedit");
}

void ibus_levena_engine_commit_preedit(IBusLevenaEngine *klass){
    g_print("signal_commit_preedit");
}

static void ibus_levena_engine_commit_string (IBusLevenaEngine *klass, const gchar *string){
    g_print("signal_commit_string");
    IBusText *text;
    text = ibus_text_new_from_static_string (string);
    ibus_engine_commit_text ((IBusEngine *)klass, text);
}

static void
ibus_levena_engine_update (IBusLevenaEngine *klass)
{
    g_print("signal_update");
    //ibus_enchant_engine_update_preedit (enchant);
    //ibus_engine_hide_lookup_table ((IBusEngine *)enchant);
}


//catch the process-key-event signal from ibus_init
gboolean ibus_levena_engine_process_key_event(IBusEngine *ie,guint keyval,guint keycode,guint state,gpointer user_data){
g_print ("ok?"); 
printf("process-key-event signal recieved!! : %x",keycode);
gboolean ret=0;
return TRUE;
}


int main(int argc,char **argv){

g_set_print_handler (print_handler);
g_print ("g_set_print_handler\n"); 
//gchar *dbg="test"
//ibus_warning("%s",dbg );
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

registerComponent(bus);




//最後にして至高の一撃、ibus_main()
ibus_main();
}

void registerComponent(IBusBus *bus){
    gchar *filepath="/home/levena/levena/levena.xml";
    IBusComponent *component;
    component=ibus_component_new_from_file(filepath);
    if(!component){
        g_print("error! file isn't loading!");
    }
    //ok!(if doing test,you should comment out ibus_main();)
    //printf(ibus_component_get_version(component));
    ibus_bus_register_component (bus, component);
}