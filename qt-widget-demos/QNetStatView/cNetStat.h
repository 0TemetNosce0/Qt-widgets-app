#ifndef CNETSTAT_H
#define CNETSTAT_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QTime>
#include <QThread>

#include "Process.h"

#if defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
#include "ProcessListLinux.h"
#endif
#if defined(Q_OS_WIN)
#include "ProcessListWindows.h"
#endif

class cNetStat : public QThread {
    Q_OBJECT
    public:
        cNetStat();
        QVector<sNetStat> getNetStat();
        void run();

    private:
        QString convAddress(QString address, QString ipv);
        QVector<sNetStat> getTable();
        void writeLog(QString str);


        QVector<sNetStat> save_netstat;

    signals:
        void endReadStat(QVector<sNetStat>);
};

#endif // CNETSTAT_H
