#include <QApplication>
#include "colorwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ColorWidget w;
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

    return a.exec();
}
