#ifndef SYSYTEMTRAY_H
#define SYSYTEMTRAY_H

#include <QSystemTrayIcon>

class QMenu;
class QAction;

class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit SystemTray(QWidget *parent = 0);
    ~SystemTray();
    void translateLanguage();

private:
    void createAction();

private:
    QMenu *tray_menu; //���̲˵�

    QAction *action_open; //��360��ȫ��ʿ
    QAction *action_help_center; //��������
    QAction *action_kill_mummy; //��ɱľ��
    QAction *action_clear; //��������
    QAction *action_optimize; //һ���Ż�
    QAction *action_fireproof; //������
    QAction *action_show_speed; //��ʾ������
    QAction *action_soft_manage; //����ܼ�
    QAction *action_safe_notice; //��ȫ֪ͨ
    QAction *action_rise; //����
    QAction *action_login; //360�û���¼
    QAction *action_separate; //����ɳ��
    QAction *action_logout; //�˳�

};

#endif //SYSYTEMTRAY_H
