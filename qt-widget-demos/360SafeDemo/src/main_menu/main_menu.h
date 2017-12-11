/**
* @�ļ���   main_menu.h
* @�汾��Ϣ copyright  2012-2013 Sugon. All rights reserved.
* @��������
*           MainMenu��������˵�����Ҫ�������������ǡ��˳���
* @����     ����<wangliang@sugon.com>
* @����     2012-01-07
*/

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMenu>

class MainMenu : public QMenu
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);

    void translateActions();

signals:
    void showSettingDialog();
    void showNewCharacter();
    void showAboutUs();

private:
    void createActions();

private:
    QAction *action_setting;        //����
    QAction *action_new_character;  //�°�����
    QAction *action_check_update;   //������
    QAction *action_change_company; //�л�Ϊ��ҵ��
    QAction *action_help_online;    //���߰���
    QAction *action_platform_help;  //��̳����
    QAction *action_login_home;     //360��վ
    QAction *action_protect;        //��˽����
    QAction *action_about_us;       //��������
};

#endif //MAINMENU_H
