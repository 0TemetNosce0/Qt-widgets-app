#ifndef SPHOOK_H
#define SPHOOK_H

#include <QGraphicsItemGroup>
#include <QPointF>
#include <QRectF>
#include <QPainter>
#include <QPainterPath>
#include <QWidget>
#include <iostream>


using namespace std;

class SpHook : public QGraphicsItem
{
private:
    QPointF position;
    int type;
    int radius;

public:
    SpHook(QPointF,int);
    ~SpHook();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPointF GetPosition();
    void SetPosition(QPointF);
};



#endif 
