#include <QApplication>
#include <QStyleFactory>

#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //a.setStyle(QStyleFactory::create("Windows"));
    //a.setStyle(QStyleFactory::create("Plastique"));

    Dialog w;
    w.show();
    w.resize(1200, 600);

    return a.exec();
}
