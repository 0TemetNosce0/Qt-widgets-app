#include <QApplication>
#include "donut.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    float iR = 50;
    float oR = 100;

    Donut *d = new Donut(QPoint(), iR, oR);
    d->show();

    return a.exec();
}
