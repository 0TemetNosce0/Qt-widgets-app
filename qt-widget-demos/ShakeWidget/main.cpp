#include "shakewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShakeWidget w;
    w.show();

    return a.exec();
}
