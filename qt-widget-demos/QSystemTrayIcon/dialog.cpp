#include "dialog.h"
#include "ui_dialog.h"

#include <QMenu>
#include <QTimer>
#include <QCloseEvent>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    initTimer();
    initTray();
    initLayout();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::changeEvent(QEvent *e)
{
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }

    QDialog::changeEvent(e);
}

/**
 * @brief Dialog::InitUi
 * 初始化总结
 */
void Dialog::initTimer()
{
    timer = new QTimer(this);
    TimerCount = 0;
}

/**
 * @brief Dialog::initTray
 * 初始化托盘
 */
void Dialog::initTray()
{
    QMenu *contexmenu = new QMenu(this);           //注意右键菜单的父对象，在窗口销毁后要把菜单也销毁掉
    QAction *shut = new QAction(QStringLiteral("退出"),this);                  //菜单中两个动作
    QAction *openNomal = new QAction(QStringLiteral("正常显示"),this);
    QAction *qqmsg = new QAction(QStringLiteral("QQ消息"),this);
    contexmenu->addAction(openNomal);
    contexmenu->addSeparator();
    contexmenu->addAction(qqmsg);
    contexmenu->addSeparator();
    contexmenu->addAction(shut);
    connect(shut, SIGNAL(triggered()), this, SLOT(menuExit()));          //点击了这两个菜单
    connect(openNomal, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect(qqmsg, SIGNAL(triggered()), this, SLOT(qq_msg_com()));
    tray = new QSystemTrayIcon(this);
    tray->setToolTip("try to click");   //放在图表上时候显示
    tray->setContextMenu(contexmenu);
    tray->setIcon(QIcon(":/image/icon.png"));
    tray->show();

    connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
    connect(tray, SIGNAL(messageClicked()), this, SLOT(showClickMsg()));  //模拟QQ消息到来时候的闪烁图表
}

/**
 * @brief Dialog::InitLayout
 * 初始化布局
 */
void Dialog::initLayout()
{

}

/**
 * @brief Dialog::closeEvent
 * @param event
 * 关闭窗口消息函数
 */
void Dialog::closeEvent(QCloseEvent *event)
{
    if(tray->isVisible())
    {
        QMessageBox::about(this,QStringLiteral("最小化"),QStringLiteral("最小化到托盘"));
        this->hide();
        event->ignore();
    }

}

/**
 * @brief Dialog::ShowNormal
 * 响应右键菜单正常显示
 */
void Dialog::showNormal()
{
    timer->stop();
    tray->setIcon(QIcon(":/image/icon.png"));   //正常显示时候恢复原有图标，防止定时器在无显示图表时候被终止
    this->show();
}

/**
 * @brief Dialog::MenuExit
 * 响应右键菜单 关闭程序
 */
void Dialog::menuExit()
{
    exit(0);
}

/**
 * @brief Dialog::iconIsActived
 * @param reason
 * 托盘图标活动
 */
void Dialog::iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::DoubleClick:
        showNormal();
        break;
    case QSystemTrayIcon::Trigger:
        showMessageBox();
        break;
    case QSystemTrayIcon::Unknown:
        QMessageBox::about(this, "unkown", "unkown activation");
        break;
    default:
        break;
    }
}

void Dialog::showMessageBox()
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(1);  //设置图表是标准的系统托盘信息
    tray->showMessage("you click", "hello,tray", icon, 10000);
}

/**
 * @brief Dialog::ShowClickMsg
 * 点击了消息框后的要响应的函数
 */
void Dialog::showClickMsg()
{
    QMessageBox::about(0, "click", "you click the messagebox");
}

/**
 * @brief Dialog::qq_msg_com
 * 模拟QQ消息到来时候，托盘图表闪动
 */
void Dialog::qq_msg_com()
{
    timer->start(500);  //每500ms都刷新一次
    timer->setSingleShot(false);  //如果为真,表示只重复一次,为假表示无限次循环
    connect(timer, SIGNAL(timeout()), this, SLOT(updateIcon()));
}

/**
 * @brief Dialog::updateIcon
 * 刷新托盘图标
 */
void Dialog::updateIcon()
{
    TimerCount++;

    if(TimerCount%2)
    {
        tray->setIcon(QIcon(":/image/null.png"));   //实际上没有这个图标,然后会显示没有图表
    }
    else
    {
        tray->setIcon(QIcon(":/image/icon.png"));
    }
}
