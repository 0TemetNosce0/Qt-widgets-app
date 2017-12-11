#include "mytableview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTableView w;
    w.show();

    return a.exec();
}
