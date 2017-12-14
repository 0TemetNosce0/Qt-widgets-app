#include "gldmaskwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GLDMaskWidget w;
    w.show();

    return a.exec();
}
