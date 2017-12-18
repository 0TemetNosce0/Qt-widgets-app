#ifndef MYSHOWWIDGET_H
#define MYSHOWWIDGET_H
#include <QWidget>
#include <QPaintEvent>
class MyShowWidget:public QWidget
{
    Q_OBJECT
public:
    explicit MyShowWidget(QWidget * parent = 0);
    virtual void paintEvent(QPaintEvent *event);
};

#endif // MYSHOWWIDGET_H
