#ifndef CONTROLITEM_H
#define CONTROLITEM_H

#include <QGraphicsEllipseItem>
#include <QPen>

class ControlItem : public QGraphicsItem
{
public:
    static const int DEFAULT_SIZE;

    ControlItem();
    ControlItem(QGraphicsItem *parent, int size);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int getSize() const;
    void setSize(int value);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    int size;
    QPen pen;
};

#endif // CONTROLITEM_H
