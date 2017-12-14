#include "myapp.h"
#include "myhelper.h"

QString myApp::AppPath = "";
int myApp::DeskWidth = 1024;
int myApp::DeskHeight = 768;

QString myApp::AppTitle = QStringLiteral("��Ƶ���ƽ̨");
QString myApp::NVRType = "���;��ѧ;����;̩��;���;����;����;��;����;�ά;����";
QString myApp::IPCType = "̩��;����;����;����;��;����";
QString myApp::AppStyle = ":/image/silvery.css";

int  myApp::VideoDelayTime = 300;
bool myApp::UseVideoOffLineCheck = true;
int  myApp::VideoOffLineCheckInterval = 30;
int  myApp::RtspType = 1;

bool myApp::AutoRun = false;
bool myApp::AutoPoll = false;
int  myApp::PollType = 1;
int  myApp::PollInterval = 30;
int  myApp::PollSleep = 0;

//Ĭ��16��ͨ��ȫ����ʾ
QString myApp::VideoType = "16";
//16��ͨ����Ӧrtsp��ַ,�������������Զ�����
QString myApp::RtspAddr16 = "|||||||||||||||";
//���������Ϣ,������
QString myApp::LastConfig = "1";

//��ȡ�����ļ�
void myApp::ReadConfig()
{
    QString fileName = myApp::AppPath + "config.txt";
    //��������ļ�������,���Գ�ʼֵ��������
    if (!myHelper::FileIsExist(fileName))
    {
        //��Ӧ����ת����ȷ�ı���
        myApp::AppTitle = myApp::AppTitle.toLatin1();
        myApp::NVRType = myApp::NVRType.toLatin1();
        myApp::IPCType = myApp::IPCType.toLatin1();
        return;
    }

    QSettings *set = new QSettings(fileName, QSettings::IniFormat);

    set->beginGroup("AppConfig");
    myApp::AppTitle = set->value("AppTitle").toString();
    myApp::NVRType = set->value("NVRType").toString();
    myApp::IPCType = set->value("IPCType").toString();
    myApp::AppStyle = set->value("AppStyle").toString();
    myApp::VideoDelayTime = set->value("VideoDelayTime").toInt();
    myApp::UseVideoOffLineCheck = set->value("UseVideoOffLineCheck").toBool();
    myApp::VideoOffLineCheckInterval = set->value("VideoOffLineCheckInterval").toInt();
    myApp::RtspType = set->value("RtspType").toInt();
    myApp::AutoRun = set->value("AutoRun").toBool();
    myApp::AutoPoll = set->value("AutoPoll").toBool();
    myApp::PollType = set->value("PollType").toInt();
    myApp::PollInterval = set->value("PollInterval").toInt();
    myApp::PollSleep = set->value("PollSleep").toInt();
    myApp::VideoType = set->value("VideoType").toString();
    myApp::RtspAddr16 = set->value("RtspAddr16").toString();
    myApp::LastConfig = set->value("LastConfig").toString();
    set->endGroup();
}

//д�������ļ�
void myApp::WriteConfig()
{
    QString fileName = myApp::AppPath + "config.txt";
    QSettings *set = new QSettings(fileName, QSettings::IniFormat);

    set->beginGroup("AppConfig");
    set->setValue("AppTitle", myApp::AppTitle);
    set->setValue("NVRType", myApp::NVRType);
    set->setValue("IPCType", myApp::IPCType);
    set->setValue("AppStyle", myApp::AppStyle);
    set->setValue("VideoDelayTime", myApp::VideoDelayTime);
    set->setValue("UseVideoOffLineCheck", myApp::UseVideoOffLineCheck);
    set->setValue("VideoOffLineCheckInterval", myApp::VideoOffLineCheckInterval);
    set->setValue("RtspType", myApp::RtspType);
    set->setValue("AutoRun", myApp::AutoRun);
    set->setValue("AutoPoll", myApp::AutoPoll);
    set->setValue("PollType", myApp::PollType);
    set->setValue("PollInterval", myApp::PollInterval);
    set->setValue("PollSleep", myApp::PollSleep);
    set->setValue("VideoType", myApp::VideoType);
    set->setValue("RtspAddr16", myApp::RtspAddr16);
    set->setValue("LastConfig", myApp::LastConfig);
    set->endGroup();
}

