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
    void initTray();                    //初始化托盘
    void initLayout();
    void closeEvent(QCloseEvent *);    //在关闭窗口时候要重写该函数，为了最小化到托盘，而不是退出程序
    void showMessageBox();             //像是托盘图表的messagebox();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Dialog *ui;
    QSystemTrayIcon *tray;
    QTimer *timer;         //用于闪烁ICON的定时器
    int TimerCount;      //用于计算定时器超时次数，单数显示图标，双数不显示  并且为0时候表示没有消息

private slots:
    void menuExit();       //右键菜单退出
    void showNormal();     //正常显示
    void iconIsActived(QSystemTrayIcon::ActivationReason); //托盘图表活动，无论是鼠标悬浮，或者双击，或者单击
    void showClickMsg();  //点击了消息框后的响应函数
    void qq_msg_com();
    void updateIcon();    //定时器刚
};

#endif // DIALOG_H
