#include <QApplication>
#include "chatwindow.h"
#include <QtGui>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatWindow w;
    w.showMaximized();

    return a.exec();
}
