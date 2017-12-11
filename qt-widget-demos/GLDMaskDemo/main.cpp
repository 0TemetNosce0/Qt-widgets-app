#include <QApplication>

#include "vld.h"
#include "GLDMaskBox.h"
#include "CustomDialog.h"
#include "LogoinWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LogoinWidget w;
    w.show();

    return a.exec();
}
