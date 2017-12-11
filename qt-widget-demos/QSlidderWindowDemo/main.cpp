#include "qsliderwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font("ZYSong18030",12);
    a.setFont(font);

    QSliderWidget w;
    w.show();

    return a.exec();
}
