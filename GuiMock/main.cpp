#include <QApplication>

#include "dragwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DragWidget window;
    window.show();

    return a.exec();
}
