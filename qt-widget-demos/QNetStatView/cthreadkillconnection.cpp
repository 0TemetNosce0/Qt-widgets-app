#include "cthreadkillconnection.h"

cThreadKillConnection::cThreadKillConnection(){

}

void cThreadKillConnection::run(){    
#if defined(USE_LIBNET)
    tcpkill(intf,param);
#endif
}

void cThreadKillConnection::init(QString intf,QString param){
    this->intf=intf;
    this->param=param;
}
