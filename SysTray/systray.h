#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QSystemTrayIcon>

namespace Ui { class SysTray; }

class SysTray : public QDialog
{
    Q_OBJECT

public:
    explicit SysTray(QWidget *parent = 0);
    ~SysTray();

public:
    void create_traymenu();
    void create_trayicon();

public slots:
    void tray_action(QSystemTrayIcon::ActivationReason reason);

private:
    QAction* max_size_action;
    QAction* mini_size_action;
    QAction* restorewin_action;
    QAction* quit_action;
    QMenu* m_tray_menu;
    QSystemTrayIcon* m_tray_icon;

private:
    Ui::SysTray *ui;
};

#endif // SYSTRAY_H
