#include "lcomponent.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LComponent w;
    w.showMaximized();

    return a.exec();
}
