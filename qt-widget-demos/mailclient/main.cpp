#include "mailclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mailclient w;
    w.show();

    return a.exec();
}
