#ifndef EPUSHBUTTON_H
#define EPUSHBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class EPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit EPushButton(QWidget *parent = 0);
    ~EPushButton();
    void setPixName(QString pix_name);

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    enum ButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};
    ButtonStatus status;
    QString pix_name;
    int btn_width;
    int btn_height;
    bool mouse_press;
};

#endif // EPUSHBUTTON_H
