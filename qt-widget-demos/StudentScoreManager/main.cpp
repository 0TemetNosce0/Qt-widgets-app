#include "mainwindow.h"
#include "logindialog.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog Check;
    if (QDialog::Rejected == Check.exec())
        return 0;//通过文件读写方式传递信息

    MainWindow w;

    w.show();

    return a.exec();
}

