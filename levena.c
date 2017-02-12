
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

}