#include "../include/ViewerWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ViewerWindow w;
    w.show();

    return a.exec();
}
