#include "rubber.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Rubber w;
    w.show();

    return a.exec();
}
