
//TODO:move to levena.c
//ibus.hにはibusengine.hやらglibc.hやらがincludeされてる
#include<ibus.h>
#include<stdio.h>
// prototype declaration

#define IS_ALPHA(c) (((c)>=IBUS_a && (c)<=IBUS_z) || ((c)>=IBUS_A && (c)<=IBUS_Z))

void print_handler (const gchar* message) { 
    gchar *commandline; 
    commandline = g_strdup_printf ("zenity --info --text=%s", message); 
    g_spawn_command_line_sync (commandline, NULL, NULL, NULL, NULL); 
    g_free (commandline); 
} 

void registerComponent(IBusBus *);
gboolean ibus_levena_engine_process_key_event(IBusEngine *,guint ,guint ,guint ,gpointer );
void ibus_levena_engine_property_activate(IBusEngine*,const gchar* ,guint);//create panel
//void ibus_levena_engine_focus_in(IBusLevenaEngine*);//create panel
//I will migrate to levena.h

#define IBUS_TYPE_LEVENA_ENGINE (ibus_levena_engine_get_type())
GType ibus_levena_engine_get_type(void);
//GType型システムに登録する。TODO:もっと詳しく

typedef struct tagIBusLevenaEngine IBusLevenaEngine;
typedef struct tagIBusLevenaEngineClass IBusLevenaEngineClass;

//インスタンス変数等を登録する。
struct tagIBusLevenaEngine{
    IBusEngine parent;
    GString *preedit;
    gint cursor_pos;
    IBusLookupTable *table;
    IBusPropList *proplist;//create panel
};

//こっちはメソッドやらクラス変数を登録する。
struct tagIBusLevenaEngineClass{
    IBusEngineClass parent;
};
//上記２つは公開している。protectedやprivateじゃない。

//TODO:if understand ibus_obuject_get_type implemnt,delete and test
G_DEFINE_TYPE(IBusLevenaEngine,ibus_levena_engine,IBUS_TYPE_ENGINE)

static void ibus_levena_engine_create_property_list(IBusLevenaEngine *levena){//create panel
    IBusProperty* prop;
        levena->proplist = ibus_prop_list_new();
        g_object_ref_sink(levena->proplist);

///create proplist
IBusText* label,* tooltip;
    label = ibus_text_new_from_static_string("hellloooo");
        tooltip = ibus_text_new_from_static_string("hehehe!!"); // ?
        gchar *name="gcharname";
        prop = ibus_property_new(name,
                                 PROP_TYPE_RADIO,
                                 label,
                                 "",
                                 tooltip,
                                 FALSE,
                                 TRUE,
                                 PROP_STATE_UNCHECKED,
                                 NULL);
        if (ibus_prop_list_update_property(levena->proplist, prop) == FALSE)
            ibus_prop_list_append(levena->proplist, prop);
            ibus_warning("function create property list is end!!!!");
}//create panel

//インスタンス化された時に呼び出される。コンストラクタ。
//https://documents.mikeforce.net/glib-2.18.x-refs/gobject/html/gtype-instantiable-classed.html#gtype-instantiable-classed-init-done
void ibus_levena_engine_init(IBusLevenaEngine *klass){
    ibus_warning("levena-engine init!");
    klass->preedit=g_string_new("");
    klass->cursor_pos=0;
    klass->table=ibus_lookup_table_new(9,0,TRUE,TRUE);
}

void ibus_levena_engine_focus_in(IBusLevenaEngine *klass){//create panel
    ibus_warning("signal_focusin");
    ibus_levena_engine_create_property_list(klass);
    ibus_warning("proplist created!");
    ibus_engine_register_properties((IBusEngine *)klass,klass->proplist);
    ibus_warning("proplist registered!!");
}//create panel

void ibus_levena_engine_class_init(IBusLevenaEngineClass *klass){
    ibus_warning("levena-engine init! in class");
    IBusEngineClass *iec=IBUS_ENGINE_CLASS (klass);
    iec->process_key_event=ibus_levena_engine_process_key_event;
    iec->property_activate = ibus_levena_engine_property_activate;//create panel
    iec->focus_in=ibus_levena_engine_focus_in;//create panel
}


static gboolean ibus_levena_engine_update_lookup_table(IBusLevenaEngine *klass){
    klass->table=ibus_lookup_table_new(9,0,TRUE,TRUE);//TODO:????
    if(klass->preedit->len == 0){
        //ibus_lookup_table_clear(klass->table);
        ibus_engine_hide_lookup_table((IBusEngine *)klass);
        //ibus_engine_update_lookup_table((IBusEngine *)klass,klass->table,TRUE);
        ibus_warning("ret");
        return FALSE;
    }else{
        ibus_lookup_table_clear(klass->table);
        IBusText *text;
        text=ibus_text_new_from_string("test");
        //TODO: write engine function
        ibus_lookup_table_append_candidate(klass->table,text);
        ibus_warning("e");
        ibus_engine_update_lookup_table((IBusEngine *)klass,klass->table,TRUE);
        ibus_warning("f");
    }
    ibus_warning("signal_update_lookup_table");
    return TRUE;
}

void ibus_levena_engine_update_preedit(IBusLevenaEngine *klass){
    IBusText *  text;
    text = ibus_text_new_from_static_string (klass->preedit->str);
    ibus_warning("signal_update_preedit: %s ,cursor_pos: %d",klass->preedit,klass->cursor_pos);
    ibus_engine_update_preedit_text ((IBusEngine *)klass,
                                    text,
                                    ibus_text_get_length(text),
                                    TRUE);
    //ibus_engine_update_preedit_text();
}

static gboolean ibus_levena_engine_commit_preedit(IBusLevenaEngine *klass){
    ibus_warning("signal_commit_preedit");
    if((klass->cursor_pos) == 0){
        return FALSE;
    }
    IBusText *text;
    text=ibus_text_new_from_static_string(klass->preedit->str);
    ibus_engine_commit_text((IBusEngine*)klass,text);
    g_string_assign(klass->preedit,"");
    klass->cursor_pos=0;
    ibus_levena_engine_update_preedit(klass);
    return TRUE;
}

static void ibus_levena_engine_commit_string (IBusLevenaEngine *klass, const gchar *string){
    ibus_warning("signal_commit_string");
    IBusText *text;
    text = ibus_text_new_from_static_string (string);
    ibus_engine_commit_text ((IBusEngine *)klass, text);
}

static gboolean ibus_levena_engine_delete_left (IBusLevenaEngine *klass){
    if(klass->preedit->len == 0){
        return FALSE;
    }else if(klass->cursor_pos > 0){
        klass->cursor_pos--;
	g_string_erase(klass->preedit, klass->cursor_pos, 1);
	return ibus_levena_engine_commit_preedit(klass);
    }
    return FALSE;
}

static void
ibus_levena_engine_update (IBusLevenaEngine *klass)
{
    ibus_warning("signal_update");
    //ibus_levena_engine_update_preedit (enchant);//process key event is direct called
    //ibus_engine_hide_lookup_table ((IBusEngine *)enchant);
}


//catch the process-key-event signal from ibus_init
gboolean ibus_levena_engine_process_key_event(IBusEngine *ie,guint keyval,guint keycode,guint state,gpointer user_data){

    IBusLevenaEngine *levenaengine=(IBusLevenaEngine *)ie;
    //g_print ("ok?"); 
    ibus_warning("\nkeycode :%x, is_release :%d, is_modify:%d ,using ctrl:%d,shift:%d",keycode,state&IBUS_RELEASE_MASK,state&IBUS_MOD1_MASK,state&IBUS_CONTROL_MASK,state&IBUS_SHIFT_MASK);
    //ibus_warning("process-key-event signal recieved!! : %x",keycode);
    if (state&IBUS_RELEASE_MASK){
        // releaseは当然無視
        ibus_warning("is_release");
        return FALSE;
    }

    if(state&IBUS_CONTROL_MASK){
        ibus_warning("is_control");
        //controlが押されている時は特殊動作
        //TODO:
        return FALSE;
    }
    if(state&IBUS_MOD1_MASK){
        ibus_warning("is mod1");
        //mod1(alt)key
        return FALSE;
    }

//アルファベットの場合
    if(IS_ALPHA(keyval)){
        ibus_warning("is_alpha");
        g_string_insert_c(levenaengine->preedit,levenaengine->cursor_pos,keyval);
        levenaengine->cursor_pos++;
        ibus_levena_engine_update_preedit(levenaengine);
        return TRUE;
    }else if(keyval == IBUS_Return){
        //enter
        return ibus_levena_engine_commit_preedit(levenaengine);
    }else if(keyval == IBUS_space){
        //space//convert lookup
        ibus_warning("lookup");
        return ibus_levena_engine_update_lookup_table(levenaengine);
    }else if(keyval == IBUS_BackSpace){
        // backspace(delete left)
        ibus_warning("backspace");
	return ibus_levena_engine_delete_left(levenaengine);
    }

    ibus_warning("end");
    //release event

    //enabled ctrl or modify key
    //

    gboolean ret=0;
    return TRUE;
}

void ibus_levena_engine_property_activate(IBusEngine* engine,const gchar* prop_name,guint prop_state){//create pannel

ibus_warning("process-key-event signal recieved!! : %s",prop_name);
}//create pannel

int main(int argc,char **argv){

//g_set_print_handler (print_handler);
//g_print ("g_set_print_handler\n"); 
//gchar *dbg="test"
ibus_warning("main func");
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
    gchar *filepath="./levena.xml";
    IBusComponent *component;
    component=ibus_component_new_from_file(filepath);
    if(!component){
        ibus_warning("error! file isn't loading!");
    }
    //ok!(if doing test,you should comment out ibus_main();)
    //printf(ibus_component_get_version(component));
    ibus_bus_register_component (bus, component);
}
