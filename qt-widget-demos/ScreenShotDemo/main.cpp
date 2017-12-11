#include "screenshotwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScreenShotWindow w;
    w.show();

    return a.exec();
}
