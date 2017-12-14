#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;

    if(!QFile("../manual/manualdata.db3").exists())//判断数据库文件是否存在
    {
        QMessageBox::critical(0, QStringLiteral("无法打开数据库"), QStringLiteral("数据库文件不存在！"));//数据库文件不存在则显示提示框
        return 0;
    }

    mainWindow.show();

    return app.exec();
}
