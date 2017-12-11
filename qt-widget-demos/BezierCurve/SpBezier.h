#ifndef SPBEZIER_H
#define SPBEZIER_H

#include <QGraphicsItemGroup>
#include <QPointF>
#include <QRectF>
#include <QPainter>
#include <QPainterPath>
#include <QWidget>
#include <iostream>
#include "SpNode.h"

using namespace std;

class SpBezier:public QGraphicsItemGroup
{
private:
    QList<QPointF> curve;
    //QList<SpNode> points;

public:
    //SpBezier();
    SpBezier(SpNode&, SpNode&);
    //~SpBezier();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void genB();
    friend QList<QPointF>* teile(QList<QPointF>*, int);
};
#endif
