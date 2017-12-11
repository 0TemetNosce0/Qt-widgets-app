#ifndef ROADITEM_H
#define ROADITEM_H

#include <QGraphicsObject>
#include "mainwindow.h"

class roadItem : public QGraphicsObject
{
    Q_OBJECT

public:
    roadItem(int ID, QGraphicsObject *parent = 0);
    void beginMove();
    void stopMove();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


public slots:
    void rebegin();

private:
    int id;
    QPropertyAnimation *animation;
};

#endif // ROADITEM_H
