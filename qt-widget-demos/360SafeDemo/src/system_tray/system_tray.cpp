#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QSystemTrayIcon>

#include "system_tray.h"

SystemTray::SystemTray(QWidget *parent)
    : QSystemTrayIcon(parent)
{
    this->createAction();
    this->translateLanguage();
}

SystemTray::~SystemTray()
{

}

void SystemTray::translateLanguage()
{
    //��������ͼ����ʱ����ʾ
    this->setToolTip(tr("360 safe"));

    action_open->setText(tr("open"));
    action_help_center->setText(tr("help center"));
    action_kill_mummy->setText(tr("kill mummy"));
    action_clear->setText(tr("clear"));
    action_optimize->setText(tr("optimize"));
    action_fireproof->setText(tr("fireproof"));
    action_show_speed->setText(tr("show speed"));
    action_soft_manage->setText(tr("soft manage"));
    action_safe_notice->setText(tr("safe notice"));
    action_rise->setText(tr("rise"));
    action_login->setText(tr("login"));
    action_separate->setText(tr("separate"));
    action_logout->setText(tr("logout"));
}

void SystemTray::createAction()
{
    this->setIcon(QIcon(":/img/safe"));

    tray_menu = new QMenu();
    action_open = new QAction(this);
    action_help_center = new QAction(this);
    action_kill_mummy = new QAction(this);
    action_clear = new QAction(this);
    action_optimize = new QAction(this);
    action_fireproof = new QAction(this);
    action_show_speed = new QAction(this);
    action_soft_manage = new QAction(this);
    action_safe_notice = new QAction(this);
    action_rise = new QAction(this);
    action_login = new QAction(this);
    action_separate = new QAction(this);
    action_logout = new QAction(this);

    //��Ӳ˵���
    tray_menu->addAction(action_open);
    tray_menu->addAction(action_help_center);
    tray_menu->addSeparator();
    tray_menu->addAction(action_kill_mummy);
    tray_menu->addAction(action_clear);
    tray_menu->addSeparator();
    tray_menu->addAction(action_optimize);
    tray_menu->addAction(action_fireproof);
    tray_menu->addAction(action_show_speed);
    tray_menu->addAction(action_soft_manage);
    tray_menu->addSeparator();
    tray_menu->addAction(action_safe_notice);
    tray_menu->addAction(action_rise);
    tray_menu->addAction(action_login);
    tray_menu->addAction(action_separate);
    tray_menu->addAction(action_logout);

    //�����ź�����
    /*QObject::connect(action_show, SIGNAL(triggered(bool)), this, SIGNAL(showWidget()));
    QObject::connect(action_quit, SIGNAL(triggered(bool)), this, SIGNAL(logoutWidget()));
    QObject::connect(action_setting, SIGNAL(triggered(bool)), this, SIGNAL(setUp()));
    QObject::connect(action_about, SIGNAL(triggered(bool)), this, SIGNAL(aboutUs()));
    QObject::connect(action_login_home, SIGNAL(triggered(bool)), MenuAction::getInstance(), SLOT(openLoginHome()));
    QObject::connect(action_help, SIGNAL(triggered(bool)), MenuAction::getInstance(), SLOT(openHelpMe()));
    QObject::connect(action_check_update, SIGNAL(triggered(bool)), MenuAction::getInstance(), SLOT(openCheckUpdate()));*/

    connect(action_logout, SIGNAL(triggered()), qApp, SLOT(quit()));
    this->setContextMenu(tray_menu);
}
