#include "mainwindow.h"
#include "logindialog.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog Check;
    if (QDialog::Rejected == Check.exec())
        return 0;//ͨ���ļ���д��ʽ������Ϣ

    MainWindow w;

    w.show();

    return a.exec();
}

