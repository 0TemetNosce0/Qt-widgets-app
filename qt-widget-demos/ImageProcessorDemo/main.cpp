#include "imgprocessor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImgProcessor w;
    w.resize(1430, 320);
    w.show();

    return a.exec();
}
