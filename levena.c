
//TODO:move to levena.c
//ibus.hにはibusengine.hやらglibc.hやらがincludeされてる
#include<ibus.h>

typedef struct tagIBusLevenaEngine IBusLevenaEngine;
typedef struct tagIBusLevenaEngineClass IBusLevenaEngineClass;

struct tagIBusLevenaEngine{

};

struct tagIBusLevenaEngineClass{

};

int main(int argc,char **argv){

//必要なibus_系の宣言
IBusBus *bus;
IBusFactory *factory;
gchar *IMEname="levena";

bus=ibus_bus_new();
factory=ibus_factory_new(ibus_bus_get_connection(bus));
ibus_factory_create_engine(factory,IMEname);
}