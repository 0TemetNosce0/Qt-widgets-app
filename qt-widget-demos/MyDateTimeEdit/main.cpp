#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator tran;
    tran.load("D:/GCR/trunk/Glodon/src/GLD/GLD_zh_CN.qm");
    a.installTranslator(&tran);
    MainWindow w;
    w.show();

    return a.exec();
}
