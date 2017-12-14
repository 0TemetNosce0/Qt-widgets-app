#ifndef NODE_H_
#define NODE_H_

#include <QVector>
#include <QGraphicsItem>
#include <QLinearGradient>

class Edge;

class Node : public QGraphicsItem
{
public:
    Node(int value);
    ~Node();

    int value() const;
    QColor backColor() const;
    void setBackColor(const QColor &color);

    QVector<Edge *> edges();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

    static QSizeF maxSize();
    static qreal levelSpacing();
    static qreal normalHeight();

    QPointF relPos() const;
    void setRelPos(const QPointF &relPos);

    Edge* parentEdge() const;
    Node* parent() const;

    void setLeftChild(Node *node);
    Node* leftChild() const;
    void setRightChild(Node *node);
    Node* rightChild() const;
    void removeParentEdge();

    void updateSubTreeSize();
    int subTreeSize() const;

protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    QRectF outlineRect() const;
    int roundness(double size) const;

    void setParent(Node *node);
    void removeParent();
    void removeChild(Node *node);

    static const qreal hoverScaleFactor;
    static const int padding;
    static const int glowWidth;
    static const int margin;

    int m_value;
    int m_subTreeSize;
    QPointF m_relPos;
    QColor m_backColor;
    QColor m_textColor;
    QColor m_outlineColor;
    QLinearGradient m_backGradient;

    Node *m_leftChild, *m_rightChild;
    Edge *m_parentEdge;

    bool m_hover;
};

#endif /* NODE_H_ */
