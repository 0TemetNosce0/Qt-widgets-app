#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsItem>
#include <QList>
#include <QPointF>
#include <QRectF>
#include <QPolygonF>
#include <QPainter>
#include <QPainterPath>
#include <QWidget>
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "SpNode.h"
#include "SpBezier.h"

using namespace std;

class scene : public QGraphicsScene
{
private:
    QList<SpNode*> points;
    QList<SpBezier*> curves;
    QPointF pos_klick;
    QPointF pos_release;
    int numpoints;

public:
    //scene();
    //~scene();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
#endif
