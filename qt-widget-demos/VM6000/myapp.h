#ifndef MYAPP_H
#define MYAPP_H

class QString;

class myApp
{
public:
    static QString AppPath;                 //Ӧ�ó���·��
    static int DeskWidth;                   //������ÿ��
    static int DeskHeight;                  //������ø߶�

    static QString AppTitle;                //�������
    static QString NVRType;                 //Ӳ��¼�������
    static QString IPCType;                 //�������������
    static QString AppStyle;                //������ʽ
    static int VideoDelayTime;              //��Ƶ������Ӧ��ʱʱ��
    static bool UseVideoOffLineCheck;       //��Ƶ���߼��
    static int VideoOffLineCheckInterval;   //��Ƶ���߼����
    static int RtspType;                    //��������
    static bool AutoRun;                    //�����Զ�����
    static bool AutoPoll;                   //�Զ���ѯ
    static int PollType;                    //��ѯ������
    static int PollInterval;                //��ѯ���
    static int PollSleep;                   //��ѯ��ʱ
    static QString RtspAddr16;              //16��ͨ����Ӧrtsp��ַ
    static QString VideoType;               //��ǰ����չʾ����
    static QString LastConfig;              //������������Ϣ

    static void ReadConfig();               //��ȡ�����ļ�
    static void WriteConfig();              //д�������ļ�

};

#endif // MYAPP_H
