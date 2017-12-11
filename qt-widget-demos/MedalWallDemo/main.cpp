#include "mainwindow.h"
#include <QApplication>
#include "medalwallwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MedalWallWidget w;
    w.show();

    return a.exec();
}
