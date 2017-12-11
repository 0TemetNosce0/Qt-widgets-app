#include "simplelistwidget.h"
#include "filesystem.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    SimpleListWidget widget;
//    widget.resize(640, 480);
//    widget.show();

    FileSystemView w;
    w.resize(640, 480);
    w.show();

    return a.exec();
}
