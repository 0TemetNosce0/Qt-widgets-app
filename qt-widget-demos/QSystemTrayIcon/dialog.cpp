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
 * ��ʼ���ܽ�
 */
void Dialog::initTimer()
{
    timer = new QTimer(this);
    TimerCount = 0;
}

/**
 * @brief Dialog::initTray
 * ��ʼ������
 */
void Dialog::initTray()
{
    QMenu *contexmenu = new QMenu(this);           //ע���Ҽ��˵��ĸ������ڴ������ٺ�Ҫ�Ѳ˵�Ҳ���ٵ�
    QAction *shut = new QAction(QStringLiteral("�˳�"),this);                  //�˵�����������
    QAction *openNomal = new QAction(QStringLiteral("������ʾ"),this);
    QAction *qqmsg = new QAction(QStringLiteral("QQ��Ϣ"),this);
    contexmenu->addAction(openNomal);
    contexmenu->addSeparator();
    contexmenu->addAction(qqmsg);
    contexmenu->addSeparator();
    contexmenu->addAction(shut);
    connect(shut, SIGNAL(triggered()), this, SLOT(menuExit()));          //������������˵�
    connect(openNomal, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect(qqmsg, SIGNAL(triggered()), this, SLOT(qq_msg_com()));
    tray = new QSystemTrayIcon(this);
    tray->setToolTip("try to click");   //����ͼ����ʱ����ʾ
    tray->setContextMenu(contexmenu);
    tray->setIcon(QIcon(":/image/icon.png"));
    tray->show();

    connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
    connect(tray, SIGNAL(messageClicked()), this, SLOT(showClickMsg()));  //ģ��QQ��Ϣ����ʱ�����˸ͼ��
}

/**
 * @brief Dialog::InitLayout
 * ��ʼ������
 */
void Dialog::initLayout()
{

}

/**
 * @brief Dialog::closeEvent
 * @param event
 * �رմ�����Ϣ����
 */
void Dialog::closeEvent(QCloseEvent *event)
{
    if(tray->isVisible())
    {
        QMessageBox::about(this,QStringLiteral("��С��"),QStringLiteral("��С��������"));
        this->hide();
        event->ignore();
    }

}

/**
 * @brief Dialog::ShowNormal
 * ��Ӧ�Ҽ��˵�������ʾ
 */
void Dialog::showNormal()
{
    timer->stop();
    tray->setIcon(QIcon(":/image/icon.png"));   //������ʾʱ��ָ�ԭ��ͼ�꣬��ֹ��ʱ��������ʾͼ��ʱ����ֹ
    this->show();
}

/**
 * @brief Dialog::MenuExit
 * ��Ӧ�Ҽ��˵� �رճ���
 */
void Dialog::menuExit()
{
    exit(0);
}

/**
 * @brief Dialog::iconIsActived
 * @param reason
 * ����ͼ��
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
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(1);  //����ͼ���Ǳ�׼��ϵͳ������Ϣ
    tray->showMessage("you click", "hello,tray", icon, 10000);
}

/**
 * @brief Dialog::ShowClickMsg
 * �������Ϣ����Ҫ��Ӧ�ĺ���
 */
void Dialog::showClickMsg()
{
    QMessageBox::about(0, "click", "you click the messagebox");
}

/**
 * @brief Dialog::qq_msg_com
 * ģ��QQ��Ϣ����ʱ������ͼ������
 */
void Dialog::qq_msg_com()
{
    timer->start(500);  //ÿ500ms��ˢ��һ��
    timer->setSingleShot(false);  //���Ϊ��,��ʾֻ�ظ�һ��,Ϊ�ٱ�ʾ���޴�ѭ��
    connect(timer, SIGNAL(timeout()), this, SLOT(updateIcon()));
}

/**
 * @brief Dialog::updateIcon
 * ˢ������ͼ��
 */
void Dialog::updateIcon()
{
    TimerCount++;

    if(TimerCount%2)
    {
        tray->setIcon(QIcon(":/image/null.png"));   //ʵ����û�����ͼ��,Ȼ�����ʾû��ͼ��
    }
    else
    {
        tray->setIcon(QIcon(":/image/icon.png"));
    }
}
