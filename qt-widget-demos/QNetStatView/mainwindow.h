#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QHostInfo>
#include <QVector>

#include "cNetStat.h"
#include "about.h"
#include "setupUtiliteKill.h"


//qRegisterMetaType("QVector<sNetStat>");

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void initPopupMenu();
    QString resolve(QString ipaddr, QString prot);

    QTimer *timerUpdate;
    cNetStat *netstat;
    QMenu *menu;

    int sortcol;

    QMap<QString,QString> DNSCache;
    QMap<QString,QString> ServicesCache;


private slots:
    void popupCustomMenu( const QPoint &pos );
    void killProcess();
    void closeConnection();

    void timerUpdate_timeout();
    void drawTable(QVector<sNetStat> newNetStat);

    void CopyToClipboard();
    void CopyToFile();
    void restartAsRoot();

    void tableWidget_sectionVerticalResized( int logicalIndex, int oldSize, int newSize);
    void tableWidget_sectionHorizontalResized( int logicalIndex, int oldSize, int newSize);
    void tableWidget_sectionClicked(int col);

    void Resolve_Addresses();
    void lookedUp(const QHostInfo &host);

    void timer_speed1();
    void timer_speed3();
    void timer_speed5();
    void timer_pause();

    void showAbout();
    void showSetupKill();
};

#endif // MAINWINDOW_H
