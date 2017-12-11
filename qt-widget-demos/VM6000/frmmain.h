#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>

class QMenu;
class QLabel;
class QModelIndex;

namespace Ui
{
    class frmMain;
}

class frmMain : public QDialog
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void change_style();            //�л���ʽ

    void screen_full();             //ȫ��ģʽ
    void screen_normal();           //��ͨģʽ

    void delete_video_one();        //ɾ����ǰ��Ƶ
    void delete_video_all();        //ɾ��������Ƶ
    void snapshot_video_one();      //��ͼ��ǰ��Ƶ
    void snapshot_video_all();      //��ͼ������Ƶ

    void show_video_1();            //�л���1����
    void show_video_4();            //�л���4����
    void show_video_9();            //�л���9����
    void show_video_16();           //�л���16����

    void on_btnMenu_Close_clicked();
    void on_btnMenu_Min_clicked();
    void on_treeMain_doubleClicked(const QModelIndex &index);

private:
    Ui::frmMain *ui;

    QMenu *menuStyle;               //��ʽ�˵�
    QMenu *menu;                    //����Ҽ��˵�����
    QLabel *tempLab;                //��ʱ������Ƶ�ı�ǩ
    bool video_max;                 //ͨ���Ƿ������

    QList<QLabel *> VideoLab;       //ͨ����ʾ��Ƶlab����
    QList<QLayout *> VideoLay;      //ͨ����Ƶ����lab��layout

    void InitStyle();               //��ʼ���ޱ߿���
    void InitForm();                //��ʼ����������
    void InitVideo();               //��ʼ����Ƶ������������
    void LoadVideo();               //������������
    void LoadNVRIPC();              //����NVR��IPC����

    void removelayout();            //�Ƴ����в���
    void change_video_1(int index); //�ı�1���沼��
    void change_video_4(int index); //�ı�4���沼��
    void change_video_9(int index); //�ı�9���沼��
    void change_video_16(int index);//�ı�16���沼��

    QString GetNVRID(QString NVRIP);//��ȡNVR���

    void ChangeVideoLayout();       //�ı�ͨ������

    //��Ӧ�ı�ͨ��rtsp��ַ
    void ChangeRtspAddr(int ch, QString rtspAddr);

    //��ȡ�������������������ַ
    void GetRtspAddr(QString NVRID, QString IPCIP,
                     QString &IPCRtspAddrMain, QString &IPCRtspAddrSub);

};

#endif // FRMMAIN_H
