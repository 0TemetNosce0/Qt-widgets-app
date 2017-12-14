#include "../include/Node.h"
#include "../include/Edge.h"

#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QStyleOptionGraphicsItem>

const int Node::padding = 6;
const int Node::glowWidth = 3;
const qreal Node::hoverScaleFactor = 1.1;
const int Node::margin = Node::glowWidth + 1;

Node::Node(int value)
{
    m_value = value;
    m_parentEdge = new Edge(this, this);
    m_leftChild = m_rightChild = 0;
    m_subTreeSize = 1;

    m_textColor.setRgb(0x744f0e);
    m_outlineColor.setRgb(0x65502c);
    m_backColor.setRgb(0xffdda2);
    m_backGradient.setStart(QPointF(0, -10));
    m_backGradient.setFinalStop(QPointF(0, 30));
    m_backGradient.setColorAt(0, QColor(0xffebc8));
    m_backGradient.setColorAt(1, QColor(0xdaa64b));

    setFlags(ItemIsMovable | ItemIsSelectable);
    this->setAcceptHoverEvents(true);
    m_hover = false;

#if QT_VERSION >= 0x040600
    setFlag(ItemSendsGeometryChanges, true);
#endif
}

Node::~Node()
{
    if (parent())
    {
        parent()->removeChild(this);
    }

    if (m_leftChild)
    {
        m_leftChild->removeParent();
    }

    if (m_rightChild)
    {
        m_rightChild->removeParent();
    }

    delete m_parentEdge;
}

int Node::value() const
{
    return m_value;
}

QColor Node::backColor() const
{
    return m_backColor;
}

void Node::setBackColor(const QColor &color)
{
    m_backColor = color;
    update();
}

Edge* Node::parentEdge() const
{
    return m_parentEdge;
}

Node* Node::parent() const
{
    Node* parent = m_parentEdge ? m_parentEdge->fromNode() : 0;
    if (parent == this)
        parent = 0;
    return parent;
}

Node* Node::leftChild() const
{
    return m_leftChild;
}

Node* Node::rightChild() const
{
    return m_rightChild;
}

void Node::setParent(Node *node)
{
    if (parent() == node)
    {
        return;
    }

    if (m_parentEdge)
    {
        if (parent())
        {
            parent()->removeChild(this);
        }
        m_parentEdge->setFromNode(node);
    }
    else
    {
        m_parentEdge = new Edge(node, this);
    }
}

void Node::setLeftChild(Node *node)
{
    if (m_leftChild == node)
    {
        return;
    }

    if (m_leftChild)
    {
        m_leftChild->removeParent();
    }
    m_leftChild = node;

    if (m_leftChild)
    {
        m_leftChild->setParent(this);
    }
}

void Node::setRightChild(Node *node)
{
    if (m_rightChild == node)
    {
        return;
    }

    if (m_rightChild && (m_rightChild->parent() == this))
    {
        m_rightChild->removeParent();
    }

    m_rightChild = node;

    if (m_rightChild)
    {
        m_rightChild->setParent(this);
    }
}

void Node::removeParent()
{
    if (m_parentEdge)
        m_parentEdge->setFromNode(0);
}

void Node::removeChild(Node *node)
{
    if (m_leftChild == node)
    {
        m_leftChild = 0;
    }

    if (m_rightChild == node)
    {
        m_rightChild = 0;
    }
}

void Node::removeParentEdge()
{
    if (m_parentEdge)
    {
        if (parent())
        {
            parent()->removeChild(this);
        }
        /*
         delete m_parentEdge;
         m_parentEdge = 0;
         */

        //m_parentEdge->setFromNode(this);
        m_parentEdge->setFromNode(0);
    }
}

QPointF Node::relPos() const
{
    return m_relPos;
}

void Node::setRelPos(const QPointF &relPos)
{
    m_relPos = relPos;
}

QVector<Edge *> Node::edges()
{
    QVector<Edge *> edges;

    if (m_parentEdge)
    {
        edges.append(m_parentEdge);
    }

    if (m_leftChild)
    {
        edges.append(m_leftChild->parentEdge());
    }

    if (m_rightChild)
    {
        edges.append(m_rightChild->parentEdge());
    }

    return edges;
}

QRectF Node::boundingRect() const
{
    return outlineRect().adjusted(-margin, -margin, margin, margin);
}

QPainterPath Node::shape() const
{
    QRectF rect = outlineRect();
    QPainterPath path;
    path.addRoundRect(rect, roundness(rect.width()), roundness(rect.height()));

    return path;
}

QRectF Node::outlineRect() const
{
    QFontMetrics fm(qApp->font());
    QRectF rect = fm.boundingRect(QString::number(m_value));
    rect.adjust(-padding, -padding, padding, padding);
    rect.translate(-rect.center());
    return rect;
}

int Node::roundness(double size) const
{
    const int Diameter = 12;
    return 100 * Diameter / int(size);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    if (m_hover)
    {
        QRect r = outlineRect().toRect();
        r.adjust(-glowWidth, -glowWidth, glowWidth, glowWidth);
        QPixmap glow = QPixmap(":/img/nodeglow.png").scaled(r.size(),
                Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap(-glow.size().width() / 2,
                            -glow.size().height() / 2, glow);
    }

    QPen pen(m_outlineColor.darker(350));
    if (option->state & QStyle::State_Selected)
    {
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
    }

    painter->setPen(pen);
    //painter->setBrush(m_backColor);
    painter->setBrush(m_backGradient);

    QRectF rect = outlineRect();
    painter->drawRoundedRect(rect, roundness(rect.width()), roundness(
            rect.height()), Qt::RelativeSize);
    /*
     if (m_hover) {
     painter->setBrush(QColor(0, 0, 0, 10));
     painter->setPen()
     painter->drawRoundedRect(rect, roundness(rect.width()),
     roundness(rect.height()));
     }
     */
    painter->setPen(m_textColor);
    painter->drawText(rect, Qt::AlignCenter, QString::number(m_value));
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged || change == ItemPositionChange)
    {
        QVector<Edge *> edges = this->edges();
        foreach (Edge *edge, edges)
        {
            edge->trackNodes();
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

QSizeF Node::maxSize()
{
    QFontMetrics fm(qApp->font());
    QRectF rect = fm.boundingRect(QString::number(-2147483647));
    rect.adjust(-padding, -padding, padding, padding);
    rect.adjust(-margin, -margin, margin, margin);

    return rect.size();
}

qreal Node::levelSpacing()
{
    const int num = 2;
    return maxSize().height() * num;
}

qreal Node::normalHeight()
{
    return maxSize().height() - 2 * margin;
}

void Node::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //scale(hoverScaleFactor, hoverScaleFactor);
    m_hover = true;
    QGraphicsItem::hoverEnterEvent(event);
}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //scale(1 / hoverScaleFactor, 1 / hoverScaleFactor);
    m_hover = false;
    QGraphicsItem::hoverLeaveEvent(event);
}

void Node::updateSubTreeSize()
{
    m_subTreeSize = 1;
    if (m_leftChild)
    {
        m_subTreeSize += m_leftChild->subTreeSize();
    }

    if (m_rightChild)
    {
        m_subTreeSize += m_rightChild->subTreeSize();
    }

    if (parent())
    {
        parent()->updateSubTreeSize();
    }
}

int Node::subTreeSize() const
{
    return m_subTreeSize;
}
