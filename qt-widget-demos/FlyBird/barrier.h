#ifndef BARRIER_H
#define BARRIER_H

#include <QGraphicsObject>
#include "mainwindow.h"

class barrier : public QGraphicsObject
{
    Q_OBJECT

public:
    barrier();
    ~barrier();
    QPainterPath shape() const;
    void beginMove();

signals:
    void add_Score();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    bool is_addScore;
    qreal height;
    qreal width;
    qreal height2;
    qreal width2;
    QPropertyAnimation *animation;
};

#endif // BARRIER_H
