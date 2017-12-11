#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>

class QLabel;
class QSplitter;
class QPushButton;
class QToolButton;
class QProgressBar;

class ContentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContentWidget(QWidget *parent = 0);
    void translateLanguage();

private:
    void initLeft();
    void initRightTop();
    void initRightCenter();
    void initRightCenterFunction();
    void initRightBottom();
    void initRight();

    bool eventFilter(QObject *obj, QEvent *event);

private:
    QSplitter *main_splitter;

    QWidget *left_widget;
    QLabel *label;
    QLabel *suggest_label;
    QLabel *system_safe_label;
    QPushButton *power_button; //������찴ť

    QSplitter *right_splitter;
    QWidget *right_widget;
    QWidget *right_top_widget;
    QLabel *name_label;
    QToolButton *menu_button;
    QProgressBar *progress_bar;
    QToolButton *grade_button;

    QPushButton *login_button; //��¼�ҵ�360�ʺ�
    QLabel *priv_label; //��שͼ��
    QLabel *info_label; //�����Ŷ�����ͼ��
    QLabel *privilege_label; //ת����Ȩ
    QPushButton *register_button; //10�����ע��
    QPushButton *safe_button;
    QPushButton *tab_button;
    QPushButton *pet_button;
    QPushButton *lottery_button;
    QPushButton *cloud_five_button;
    QPushButton *caipiao_button;

    QWidget *right_center_widget;
    QToolButton *fireproof_button; //360����ǽ
    QToolButton *triggerman_button; //360����
    QToolButton *net_shop_button; //��������
    QLabel *line_label_1; //����
    QLabel *line_label_2; //����

    QWidget *right_center_function_widget;
    QLabel *function_label; //���ܴ�ȫ
    QPushButton *more_button; //����
    QToolButton *recovery_button; //�ļ��ָ�
    QToolButton *mobile_button; //�ֻ�����
    QToolButton *game_box_button; //��Ϸ����
    QToolButton *desktop_button; //��ȫ����
    QToolButton *net_repair_button; //����������
    QToolButton *auto_run_button; //��������
    QToolButton *net_speed_button; //���������
    QToolButton *net_pretext_button; //360����
    QToolButton *first_add_button; //ϵͳ������

    QWidget *right_bottom_widget;
    QLabel *icon_label; //��ͼ��
    QLabel *connect_label; //�ɹ������ư�ȫ
    QLabel *version_label; //�汾��
    QPushButton *version_button; //�汾����
};

#endif // CONTENTWIDGET_H
