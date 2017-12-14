#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TreeView treeView;
    treeView.show();

    return a.exec();
}
