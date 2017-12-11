#include "widgetscale.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetScale w;
    w.show();

    return a.exec();
}
