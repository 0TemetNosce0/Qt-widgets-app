#ifndef EDGE_H_
#define EDGE_H_

#include <QGraphicsLineItem>

class Node;

class Edge : public QGraphicsLineItem
{
public:
    Edge(Node *fromNode, Node *toNode);

    void setColor(const QColor &color);
    QColor color() const;

    Node* fromNode() const;
    void setFromNode(Node *node);
    Node* toNode() const;

    void trackNodes();

private:
    Node *m_fromNode, *m_toNode;
};

#endif /* EDGE_H_ */
