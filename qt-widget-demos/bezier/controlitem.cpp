#include "controlitem.h"

#include <QPainter>
#include <QPoint>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>

const int ControlItem::DEFAULT_SIZE = 5;

ControlItem::ControlItem()
{

}

ControlItem::ControlItem(QGraphicsItem *parent, int size) :
    QGraphicsItem(parent),
    size(size),
    pen(Qt::gray, 2, Qt::SolidLine, Qt::RoundCap)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
    setCursor(QCursor(Qt::PointingHandCursor));
}

QRectF ControlItem::boundingRect() const {
    int realSize = size + pen.width();
    return QRectF(-realSize, -realSize, 2*realSize, 2*realSize);
}

void ControlItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    painter->drawEllipse(QPoint(0,0), size, size);
}

void ControlItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    pen.setColor(Qt::red);
    update();
}

void ControlItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    pen.setColor(Qt::gray);
    update();
}

void ControlItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    setPos(event->scenePos());
    update();
}

void ControlItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
}

int ControlItem::getSize() const {
    return size;
}

void ControlItem::setSize(int value) {
    size = value;
}

