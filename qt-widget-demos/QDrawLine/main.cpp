#include "paintwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    paintWidget w;
    w.show();

    return a.exec();
}
