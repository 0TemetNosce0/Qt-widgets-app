#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QWidget>
class MyShowWidget;
class MyWidget:public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent =0);
       MyShowWidget * test;

       void mousePressEvent(QMouseEvent *event);
       void paintEvent(QPaintEvent * event);
};

#endif // MYWIDGET_H
