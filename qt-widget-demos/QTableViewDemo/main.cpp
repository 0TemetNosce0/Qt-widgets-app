#include "mainwindow.h"
#include <QApplication>
#include <QTableView>
#include "proxystyle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

//    w.ptableView->edit(w.ptableView->model()->index(0, 2));

    return a.exec();
}
