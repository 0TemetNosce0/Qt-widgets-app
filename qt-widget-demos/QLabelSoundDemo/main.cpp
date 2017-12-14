#include "labelsound.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LabelSound w;
    w.show();

    return a.exec();
}
