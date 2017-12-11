#include "listwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListWidget w;
    w.show();

    return a.exec();
}
