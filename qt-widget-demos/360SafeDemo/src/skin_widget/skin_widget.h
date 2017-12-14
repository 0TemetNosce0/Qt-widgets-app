#ifndef SKIN_WIDGET_H
#define SKIN_WIDGET_H

#include "../push_button/push_button.h"
#include "../change_skin_widget/change_skin_widget.h"

class QLabel;
class QHBoxLayout;
class QGridLayout;

class SkinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SkinWidget(QWidget *parent = 0);
    void translateLanguage();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

signals:
    void changeSkin(QString skin_name);

private slots:
    void showSkin(QString page_count);
    void varyfySkin(QString skin_name);

private:
    void initTitle();
    void initCenter();
    void initBottom();

private:
    QString skin_name; //����ͼƬ
    bool is_change; //�Ƿ�ı䱳��
    QStringList skin_list;
    QStringList tip_list;

    QHBoxLayout *title_layout;
    QGridLayout *center_layout;
    QHBoxLayout *bottom_layout;

    QPoint move_point; //�ƶ��ľ���
    bool mouse_press; //����������
    QLabel *title_label; //����
    QLabel *title_icon_label; //����ͼ��
    PushButton *close_button; //�رհ�ť
    int page_count; //��ҳ��
    int page_count_point; //���һҳ����ʾ����
    int current_page; //��ǰΪ�ڼ�ҳ

    ChangeSkinWidget *change_skin_widget_0;
    ChangeSkinWidget *change_skin_widget_1;
    ChangeSkinWidget *change_skin_widget_2;
    ChangeSkinWidget *change_skin_widget_3;
    ChangeSkinWidget *change_skin_widget_4;
    ChangeSkinWidget *change_skin_widget_5;
    ChangeSkinWidget *change_skin_widget_6;
    ChangeSkinWidget *change_skin_widget_7;

    QPushButton *first_page_button;
    QPushButton *previous_page_button;
    QPushButton *next_page_button;
    QPushButton *last_page_button;

};

#endif // SKIN_WIDGET_H
