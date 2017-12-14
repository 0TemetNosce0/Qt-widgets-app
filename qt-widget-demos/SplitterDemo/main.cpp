#include "splitter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    splitter w;
    w.setWindowTitle(QObject::tr("Splitter"));
    w.show();

    return a.exec();
}
