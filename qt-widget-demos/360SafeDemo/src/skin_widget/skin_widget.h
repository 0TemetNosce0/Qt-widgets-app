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
    QString skin_name; //背景图片
    bool is_change; //是否改变背景
    QStringList skin_list;
    QStringList tip_list;

    QHBoxLayout *title_layout;
    QGridLayout *center_layout;
    QHBoxLayout *bottom_layout;

    QPoint move_point; //移动的距离
    bool mouse_press; //按下鼠标左键
    QLabel *title_label; //标题
    QLabel *title_icon_label; //标题图标
    PushButton *close_button; //关闭按钮
    int page_count; //总页数
    int page_count_point; //最后一页的显示个数
    int current_page; //当前为第几页

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
