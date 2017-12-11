#ifndef TOOlBUTTON_H
#define TOOlBUTTON_H

#include <QToolButton>

class ToolButton : public QToolButton
{
    Q_OBJECT

public:
    explicit ToolButton(QString pic_name, QWidget *parent = 0);
    ~ToolButton();
    void setMousePress(bool mouse_press);

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void painterInfo(int top_color, int middle_color, int bottom_color);

public:
    bool mouse_over; //����Ƿ��ƹ�
    bool mouse_press; //����Ƿ���
};

#endif //TOOlBUTTON_H
