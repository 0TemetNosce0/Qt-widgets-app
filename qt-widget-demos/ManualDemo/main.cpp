#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;

    if(!QFile("../manual/manualdata.db3").exists())//�ж����ݿ��ļ��Ƿ����
    {
        QMessageBox::critical(0, QStringLiteral("�޷������ݿ�"), QStringLiteral("���ݿ��ļ������ڣ�"));//���ݿ��ļ�����������ʾ��ʾ��
        return 0;
    }

    mainWindow.show();

    return app.exec();
}
