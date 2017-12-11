#include "SpNode.h"

using namespace std;

SpNode::SpNode(QPointF pos, QPointF tan_1, QPointF tan_2)
{
    radius = 7;
    position = pos;
    lef = new SpHook(tan_1,1);
    rig = new SpHook(tan_2,2);
    this->addToGroup(lef);
    this->addToGroup(rig);
    this->setPos(position);
    color = Qt::red;
}

SpNode::~SpNode()
{

}

QRectF SpNode::boundingRect() const
{
    return QRectF(0, 0, 10, 10);
}

void SpNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush(Qt::black);
    painter->drawLine(QPointF(0,0), lef->GetPosition());
    painter->drawLine(QPointF(0,0), rig->GetPosition());

    painter->setBrush(color);
    painter->drawEllipse(-radius/2, -radius/2, radius, radius);
}

QPointF SpNode::GetPosition()
{
    return position;
}

void SpNode::SetPosition(QPointF pos)
{
    position = pos;
}

SpHook * SpNode::getLef()
{
    return lef;
}

SpHook * SpNode::getRig()
{
    return rig;
}

void SpNode::mouseHoverEvent(QGraphicsSceneMouseEvent * event)
{
    color = Qt::yellow;
}

void SpNode::mouseLeaveEvent(QGraphicsSceneMouseEvent * event)
{
    color = Qt::red;
}
