#include "Process.h"

#include <QMessageBox>
#include <QSettings>
#include <QDir>

#include <stdlib.h>
#include <stdio.h>
//#include <unistd.h>

#if defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
#include <signal.h>
#include <sys/wait.h>
#include "cthreadkillconnection.h"
#endif

#if defined(Q_OS_WIN)
#include <Windows.h>
#include <psapi.h>
#endif

#include <QDebug>

Process::Process(){

}

void Process::killProcess(QString pid)
{
    if (pid=="" || pid.toInt()==0)
    {
        QMessageBox::critical(0,"KillProcess",QObject::tr("You cannot kill this process"));
        return;
    }

#if defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
    if (kill(pid.toInt(),SIGTERM))
    {
        QMessageBox::critical(0,"KillProcess",QObject::tr("kill process was not successful"));
    }
#elif defined(Q_OS_WIN)
    HANDLE tmpHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid.toInt());
    if (NULL != tmpHandle)
    {
        TerminateProcess(tmpHandle, 0);
    }
#else
    QMessageBox::critical(0,"KillProcess",QObject::tr("Your OS is not support killProcess"));
#endif

}


void Process::closeConnection(QString from, QString to)
{
    QSettings conf(QDir::homePath()+"/.config/qnetstatview/qnetstatview.ini", QSettings::IniFormat);
    conf.setPath(QSettings::IniFormat, QSettings::UserScope, QDir::currentPath());

    QString utiliteProcKill=conf.value("General/prockill","").toString();

    if (utiliteProcKill=="")
    {
        #if defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
            QString filter="";
            QStringList fromList = from.split(":");
            QStringList toList = to.split(":");
            filter="host "+fromList.at(0)+" and host "+toList.at(0)+" and port "+fromList.at(1)+" and port "+toList.at(1);

            cThreadKillConnection *cc = new cThreadKillConnection();
            cc->init("eth0",filter);
            cc->start();
        #elif defined(Q_OS_WIN)
            QMessageBox::critical(0,"closeConnection",QObject::tr("Your OS is not support closeConnection"));
        #else
            QMessageBox::critical(0,"closeConnection",QObject::tr("Your OS is not support closeConnection"));
        #endif
    }
    else
    {
        QStringList fromList = from.split(":");
        QStringList toList = to.split(":");

        utiliteProcKill.replace("%LOCAL_IP%",fromList.at(0));
        utiliteProcKill.replace("%LOCAL_PORT%",fromList.at(1));
        utiliteProcKill.replace("%REMOTE_IP%",toList.at(0));
        utiliteProcKill.replace("%REMOTE_PORT%",toList.at(1));

        system(utiliteProcKill.toStdString().c_str());
    }

}
