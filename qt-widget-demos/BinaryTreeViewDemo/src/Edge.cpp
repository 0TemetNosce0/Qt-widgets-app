#include "../include/Edge.h"
#include "../include/Node.h"
#include <QtGui>
#include <QDebug>

Edge::Edge(Node *fromNode, Node *toNode)
{
    m_fromNode = fromNode;
    m_toNode = toNode;

    setZValue(-1);

    setColor(QColor(0x65502c));
    trackNodes();
}

void Edge::setColor(const QColor &color)
{
    setPen(QPen(color, 1.5));
}

QColor Edge::color() const
{
    return pen().color();
}

Node* Edge::fromNode() const
{
    return m_fromNode;
}

void Edge::setFromNode(Node *node)
{
    m_fromNode = node;
    setVisible(m_fromNode ? true : false);
}

Node* Edge::toNode() const
{
    return m_toNode;
}

void Edge::trackNodes()
{
    if (m_fromNode && m_toNode)
    {
        setLine(QLineF(m_fromNode->pos(), m_toNode->pos()));    //mapFromScene()
    }
}
