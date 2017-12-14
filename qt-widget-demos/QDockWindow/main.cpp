#include <QApplication>
#include "mainwindow.h"
/*
 made by www.hnmade.com
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.resize(800,500);
    w.show();

    return a.exec();
}
