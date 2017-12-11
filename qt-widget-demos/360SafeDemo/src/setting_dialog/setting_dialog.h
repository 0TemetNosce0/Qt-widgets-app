#ifndef SETTINGDIALOG_H 
#define SETTINGDIALOG_H

#include <QDialog>
#include "../push_button/push_button.h"

class QLabel;
class QGroupBox;
class QCheckBox;
class QTabWidget;
class QHBoxLayout;
class QRadioButton;

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();
    void translateLanguage();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    void initTitle();
    void initCenter();
    void initBottom();
    void initTab1();
    void initTab2();
    void initTab3();
    void initTab4();
    void initTab5();
    void initTab6();

private:
    QPoint move_point; //�ƶ��ľ���
    bool mouse_press; //����������

    QHBoxLayout *title_layout; //���Ⲽ��
    QLabel *title_icon_label; //����ͼ��
    QLabel *title_label; //����
    PushButton *close_button; //�رհ�ť

    QHBoxLayout *bottom_layout; //�ײ�����
    QPushButton *ok_button; //ȷ����ť
    QPushButton *cancel_button; //ȡ����ť

    QTabWidget *tab_widget;

    QWidget *tab1; //������ʽ
    QGroupBox *tab1_group_box;
    QRadioButton *auto_rise_button; //�Զ�����
    QRadioButton *not_auto_rise_button; //���Զ�����
    QCheckBox *rise_mummy_check_box; //������������ľ���
    QCheckBox *game_check_box; //��Ϸʱ������
    QCheckBox *g3_check_box; //3G����ʱ������
    QCheckBox *p2p_check_box; //ʹ��p2p/p2s����Ϊ�����������
    QCheckBox *mummy_check_box; //����ľ���������ɺ����½���ʾ

    QWidget *tab2; //�߼�����
    QGroupBox *tab2_group_box1;
    QGroupBox *tab2_group_box2;
    QGroupBox *tab2_group_box3;
    QCheckBox *auto_start_check_box; //����������
    QCheckBox *remove_own_check_box; //���ռ��
    QCheckBox *strong_remove_check_box; //ǿ��ɾ��
    QCheckBox *mummy_kill_check_box; //ľ���Ʋ�ɱ
    QCheckBox *display_count_check_box; //��ʾ���������

    QWidget *tab3; //��������
    QGroupBox *tab3_group_box1;
    QGroupBox *tab3_group_box2;
    QRadioButton *auto_check_button; //ÿ�������Զ����
    QRadioButton *first_check_button; //�״ο������
    QRadioButton *hand_check_button; //�ֶ��������
    QRadioButton *select_quit_button; //ѡ���˳���ʽ
    QRadioButton *backstage_mode_button; //��̨ģʽ
    QRadioButton *immediacy_close_button; //ֱ�ӹر�

    QWidget *tab4; //�û�����
    QGroupBox *tab4_group_box;
    QCheckBox *diaplay_experience_check_box; //���������ʾ��ȡ����ֵ�Ķ�̬����
    QCheckBox *diaplay_login_check_box; //�Զ���¼����ʾ��¼��ʾ����
    QCheckBox *tray_quit_check_box; //�����˳���¼����ʾ��ʾ����
    QCheckBox *new_character_check_box; //������Ȩʱ��ʾ֪ͨ����
    QCheckBox *rise_remind_check_box; //��������֪ͨ����

    QWidget *tab5; //���Ƽƻ�
    QGroupBox *tab5_group_box;
    QCheckBox *improve_plan_check_box;  //�μӡ�360�û������Ƽƻ���
    QPushButton *understand_detail_button; //�˽�����

    QWidget *tab6; //�ư�ȫ�ƻ�
    QGroupBox *tab6_group_box1;
    QGroupBox *tab6_group_box2;
    QLabel *file_safe_label; //�ļ���ȫ��ŵ
    QLabel *internet_safe_label; //��ַ��ȫ��ŵ
    QCheckBox *file_safe_check_box; //����360���ļ��ư�ȫ�ƻ���
    QCheckBox *internet_safe_check_box; //����360����ַ�ư�ȫ�ƻ���
    QPushButton *look_privacy_button; //�鿴360�û���˽������ŵ

};

#endif SETTINGDIALOG_H
