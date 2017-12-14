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
    QPoint press_point;//��갴��ȥ�ĵ�
    bool is_move;

    QLabel *version_title; //����
    QPushButton *medal_button; //ѫ��ǽ
    PushButton *skin_button; //����
    PushButton *main_menu_button; //���˵�
    PushButton *min_button; //��С��
    PushButton *max_button; //���
    PushButton *close_button; //�ر�

    QList<ToolButton *> button_list;
};

#endif // TITLEWIDGET_H
