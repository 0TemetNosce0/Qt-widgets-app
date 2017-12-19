//#include "mainwindow.h"
#include <QApplication>
#include "mywidget.h"
#include "uiwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();

    return a.exec();
}
