#include "stretchdemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StretchDemo w;
    w.show();

    return a.exec();
}
