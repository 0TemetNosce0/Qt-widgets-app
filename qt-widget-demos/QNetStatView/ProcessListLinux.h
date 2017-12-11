#ifndef PROCCESSLISTLINUX_H
#define PROCCESSLISTLINUX_H

#include <QString>
#include <QStringList>
#include <QMap>
#include "Process.h"


class ProcessListLinux{
    public:
        ProcessListLinux();
        int initProccessList();
        sProccess getProc(QString inode);

    private:
        QStringList getSockets(QString pid);
        QString getProgram(QString pid);
        QString getCmdline(QString pid);

        QMap<QString,sProccess>  proclist;


};

#endif // PROCCESSLIST_H
