#ifndef RIGHTPOP_H
#define RIGHTPOP_H

#include "epushbutton.h"
#include <QtGui>

class WidgetScale : public QWidget
{
    Q_OBJECT

public:
    WidgetScale(QWidget *parent = 0);
    ~WidgetScale();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent * event);

private:
    QPixmap backGroundPix;
    EPushButton *closeButton;
};

#endif // RIGHTPOP_H
