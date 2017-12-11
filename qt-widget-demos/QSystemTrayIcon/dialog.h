#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSystemTrayIcon>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void initTimer();
    void initTray();                    //��ʼ������
    void initLayout();
    void closeEvent(QCloseEvent *);    //�ڹرմ���ʱ��Ҫ��д�ú�����Ϊ����С�������̣��������˳�����
    void showMessageBox();             //��������ͼ���messagebox();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Dialog *ui;
    QSystemTrayIcon *tray;
    QTimer *timer;         //������˸ICON�Ķ�ʱ��
    int TimerCount;      //���ڼ��㶨ʱ����ʱ������������ʾͼ�꣬˫������ʾ  ����Ϊ0ʱ���ʾû����Ϣ

private slots:
    void menuExit();       //�Ҽ��˵��˳�
    void showNormal();     //������ʾ
    void iconIsActived(QSystemTrayIcon::ActivationReason); //����ͼ�����������������������˫�������ߵ���
    void showClickMsg();  //�������Ϣ������Ӧ����
    void qq_msg_com();
    void updateIcon();    //��ʱ����
};

#endif // DIALOG_H
