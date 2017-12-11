#include "systray.h"
#include "ui_systray.h"

SysTray::SysTray(QWidget *parent) : QDialog(parent), ui(new Ui::SysTray)
{
    ui->setupUi(this);
    create_traymenu();
    create_trayicon();
}

SysTray::~SysTray()
{
    delete ui;
}

void SysTray::create_traymenu()
{
    max_size_action = new QAction("最大化(&M)", this);
    mini_size_action = new QAction("最小化(&N)", this);
    restorewin_action = new QAction("还原(&R)", this);
    quit_action = new QAction("退出(&R)", this);

    connect(mini_size_action, SIGNAL(triggered()), this, SLOT(hide()));
    connect(max_size_action, SIGNAL(triggered()), this, SLOT(showMaximized()));
    connect(restorewin_action, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect(quit_action, SIGNAL(triggered()), this, SLOT(quit()));

    m_tray_menu = new QMenu((QWidget*)QApplication::desktop());
    m_tray_menu->addAction(mini_size_action);
    m_tray_menu->addAction(max_size_action);
    m_tray_menu->addAction(restorewin_action);
    m_tray_menu->addSeparator();
    m_tray_menu->addAction(quit_action);
}

void SysTray::create_trayicon()
{
    if(!QSystemTrayIcon::isSystemTrayAvailable())
        return ;

    m_tray_icon = new QSystemTrayIcon(this);
    m_tray_icon->setIcon(QIcon("../icon/tray_icon.ico"));
    m_tray_icon->setContextMenu(m_tray_menu);
    m_tray_icon->setToolTip("系统托盘图标 V1.0");
    m_tray_icon->show();

    connect(m_tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(tray_action(QSystemTrayIcon::ActivationReason)));
}

void SysTray::tray_action(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::DoubleClick:
        showNormal();
        break;

    case QSystemTrayIcon::MiddleClick:
        m_tray_icon->showMessage("系统托盘图标", "middle is click", QSystemTrayIcon::Information, 10000);
        break;

    default:
        break;
    }
}

































































