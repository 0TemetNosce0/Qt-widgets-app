#ifndef BIRD_H
#define BIRD_H

#include <QGraphicsObject>
#include "mainwindow.h"

class bird : public QGraphicsObject
{
    Q_OBJECT

public:
    bird(QGraphicsObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void riseAndfall();
    void birdUp();
    bool checkCollide();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void adjustTimer();

protected slots:
    void setChangeAnimation();
    void reset();

private:
    int status;
    int statusChange;
    bool changeAnimation;
//    bool is_up;
    bool is_down;
    bool can_up;
    QPropertyAnimation *animation;
};

#endif // BIRD_H
