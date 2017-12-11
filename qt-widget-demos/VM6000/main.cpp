#include <QApplication>
#include "myhelper.h"
#include "frmmain.h"
#include "myapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("VM");         //����Ӧ�ó�������
    a.setApplicationVersion("V201412"); //����Ӧ�ó���汾
    myHelper::SetUTF8Code();            //���ó������ΪUTF-8
    myHelper::SetChinese();             //���ó���Ϊ�����ֿ�

    //��ֵ��ǰӦ�ó���·���������ȸ߶�
    myApp::AppPath = QApplication::applicationDirPath() + "/";
    myApp::DeskWidth = qApp->desktop()->availableGeometry().width();
    myApp::DeskHeight = qApp->desktop()->availableGeometry().height();

    //�������ʱ�ȼ�������������Ϣ
    myApp::ReadConfig();

    //���غ�Ӧ����ʽ
    myHelper::SetStyle(myApp::AppStyle);

    //���������ڴ�,�ж��Ƿ��Ѿ����г���
    QSharedMemory mem("VM");
    if (!mem.create(1))
    {
        myHelper::ShowMessageBoxError(QStringLiteral("����������,������Զ��ر�!"));
        return 1;
    }

    //�жϵ�ǰ���ݿ��ļ��Ƿ����(������ݿ��ʧ������ֹӦ�ó���)
    if (!myHelper::FileIsExist(myApp::AppPath + "VM.db"))
    {
        myHelper::ShowMessageBoxError(QStringLiteral("���ݿ��ļ�������,�����Զ��ر�!"));
        return 1;
    }

    QSqlDatabase DbConn;
    DbConn = QSqlDatabase::addDatabase("QSQLITE");
    DbConn.setDatabaseName(myApp::AppPath + "VM.db");

    //�������ݿ����Ӳ���(������ݿ��ʧ������ֹӦ�ó���)
    if (!DbConn.open())
    {
        myHelper::ShowMessageBoxError(QStringLiteral("�����ݿ�ʧ��,�����Զ��رգ�"));
        return 1;
    }

    frmMain w;
    w.show();
    w.setGeometry(qApp->desktop()->availableGeometry());

    return a.exec();
}
