#ifndef CTHREADKILLCONNECTION_H
#define CTHREADKILLCONNECTION_H

#include <QThread>
#include "tcpkill/tcpkill.h"

class cThreadKillConnection : public QThread {
    public:
        cThreadKillConnection();
        void run();
        void init(QString intf, QString param);

    private:
        QString intf;
        QString param;

};

#endif // CTHREADKILLCONNECTION_H
