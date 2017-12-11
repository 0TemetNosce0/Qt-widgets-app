#include "roaditem.h"

roadItem::roadItem(int ID, QGraphicsObject *parent) : QGraphicsObject(parent)
{
    id = ID;
}

QRectF roadItem::boundingRect() const
{
    if (1 == id)
        return QRectF(0, ROAD_YVALUE, WIDTH, ROAD_HEIGHT);
    else
        return QRectF(WIDTH - 2, ROAD_YVALUE, WIDTH, ROAD_HEIGHT);
}

void roadItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (1 == id)
    {
        painter->save();
        painter->drawImage(QRectF(0, ROAD_YVALUE, WIDTH, ROAD_HEIGHT), QImage(":/resource/Resource/roadMove.png"));
        painter->restore();
    }
    else
    {
        painter->save();
        painter->drawImage(QRectF(WIDTH - 2, ROAD_YVALUE, WIDTH, ROAD_HEIGHT), QImage(":/resource/Resource/roadMove.png"));
        painter->restore();
    }
}

void roadItem::beginMove()
{
    animation = new QPropertyAnimation(this, "pos");

    if (id == 1)
    {
        animation->setDuration(ROAD_TIME);
        animation->setStartValue(pos());
        animation->setEndValue(QPoint(pos().x()-WIDTH, pos().y()));
        animation->start();
        connect(animation, SIGNAL(finished()), this, SLOT(rebegin()));
    }
    else
    {
        animation->setDuration(ROAD_TIME * 2);
        animation->setStartValue(QPoint(pos().x() - 2, pos().y()));
        animation->setEndValue(QPoint(pos().x() - WIDTH * 2, pos().y()));
        animation->setLoopCount(-1);
        animation->start();
    }
}

void roadItem::rebegin()
{
    disconnect(animation, SIGNAL(finished()), this, SLOT(rebegin()));
    animation->setDuration(ROAD_TIME * 2);
    animation->setStartValue(QPoint(pos().x() + WIDTH * 2 - 7, pos().y()));
    animation->setEndValue(pos());
    animation->setLoopCount(-1);
    animation->start();
}

void roadItem::stopMove()
{
    setPos(0, 0);
    animation->stop();
}


