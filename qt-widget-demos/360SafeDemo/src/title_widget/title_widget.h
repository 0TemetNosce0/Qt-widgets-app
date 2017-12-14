#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include "../push_button/push_button.h"
#include "../tool_button/tool_button.h"

class QLabel;

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);
    void translateLanguage();

signals:
    void showSkin();
    void showMin();
    void showMax();
    void showMainMenu();
    void closeWidget();

public slots:
    void turnPage(QString current_page);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

private:
    QPoint press_point;//鼠标按下去的点
    bool is_move;

    QLabel *version_title; //标题
    QPushButton *medal_button; //勋章墙
    PushButton *skin_button; //换肤
    PushButton *main_menu_button; //主菜单
    PushButton *min_button; //最小化
    PushButton *max_button; //最大化
    PushButton *close_button; //关闭

    QList<ToolButton *> button_list;
};

#endif // TITLEWIDGET_H
