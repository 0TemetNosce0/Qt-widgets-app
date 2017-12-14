#include "ProcessListLinux.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QTextStream>


ProcessListLinux::ProcessListLinux()
{

}


int ProcessListLinux::initProccessList()
{
    // Получение списка процессов
    sProccess proc;
    QMap<QString,sProccess> result;

    QRegExp rx_digit("^\\d+$");

    QDir dir = QDir("/proc");
    dir.setFilter(QDir::AllDirs);
    QFileInfoList pidList = dir.entryInfoList();
    for (int i=0;i<pidList.size();i++)
    {
        QString pid = pidList.at(i).fileName();

        if (!rx_digit.exactMatch(pid))
        {
            continue;
        }

        proc.pid = pid;
        proc.sockets = getSockets(pid);
        proc.program = getProgram(pid);
        proc.cmdline = getCmdline(pid);

        result[pid] = proc;
    }

    proclist=result;

    return 1;
}



sProccess ProcessListLinux::getProc(QString inode)
{
    QMapIterator<QString, sProccess> i(proclist);
    while (i.hasNext())
    {
        i.next();
        for (int p=0;p<i.value().sockets.size();p++)
        {
            if (i.value().sockets.at(p) == inode)
            {
                return i.value();
            }
        }
    }

    return sProccess();
}


QString  ProcessListLinux::getProgram(QString pid)
{
    QFile file("/proc/"+pid+"/exe");
    return file.symLinkTarget();
}

QString  ProcessListLinux::getCmdline(QString pid)
{
    QFile file("/proc/"+pid+"/cmdline");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return "";
    QTextStream in(&file);
    QString result = in.readAll();
    file.close();

    for (int i = 0;i < result.size();i++)
    {
        if (result[i].unicode() == 0)
        {
            result=result.mid(0,i) + " " + result.mid(i+1);
        }

    }

    return result;
}

QStringList ProcessListLinux::getSockets(QString pid)
{
    QStringList result;

    QRegExp rx("(.*)socket:\\[(.*)\\]");

    QDir dir = QDir("/proc/"+pid+"/fd/");
    dir.setFilter(QDir::AllDirs);
    QFileInfoList fdList = dir.entryInfoList();
    for (int i = 0;i < fdList.size();i++)
    {
        QString link = fdList.at(i).symLinkTarget();
        if (rx.exactMatch(link))
        {
            result.append(rx.cap(2));
        }
    }

    return result;
}
