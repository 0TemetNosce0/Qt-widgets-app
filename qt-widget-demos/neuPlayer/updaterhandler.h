#ifndef UPDATERHANDLER_H
#define UPDATERHANDLER_H

#include <QObject>
#include <QProcess>

class UpdaterHandler : public QObject
{
    Q_OBJECT
public:
    explicit UpdaterHandler(QObject *parent = 0);
    void start(QString appName, QString currentVersion, QString urlLatestVersion, QString urlLatestExe, QString showMessageIfNoUpdate);
private slots:
    void on_newInfosFromProc();
private:
    QProcess a_updateprocess;
};

#endif // UPDATERHANDLER_H
