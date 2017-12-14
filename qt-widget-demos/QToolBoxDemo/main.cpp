#include "dialog.h"
#include "drawer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Drawer drawer;
    drawer.show();

    return a.exec();
}
