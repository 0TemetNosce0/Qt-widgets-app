#include "iconeditor.h"
#include <QIcon>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QImage icon(":/images/mouse.png");
    IconEditor w;
    w.setIconImage(icon);
    w.show();

    return a.exec();
}
