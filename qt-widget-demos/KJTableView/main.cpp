#include "mainwindow.h"
#include <QApplication>
#include <QTableView>
#include <QHeaderView>

#include "kjmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
