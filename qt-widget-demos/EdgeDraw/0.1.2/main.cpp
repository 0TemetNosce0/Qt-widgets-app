#include <QApplication>

#include "GLDMaskBox.h"
#include "CustomDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    float iR = 50;
//    float oR = 100;

//    Donut *d = new Donut(QPoint(), iR, oR);
//    d->show();

    Dialog w;
    w.show();

    return a.exec();
}
