#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/1680_1050_4714.jpg");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();

    MainWindow w;
    w.show();
    splash.finish(&w);

    return a.exec();
}
