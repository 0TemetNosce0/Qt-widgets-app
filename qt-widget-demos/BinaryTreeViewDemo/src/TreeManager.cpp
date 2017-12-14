#include "../include/TreeManager.h"
#include "../include/TreeScene.h"
#include "../include/Node.h"
#include "../include/Edge.h"

#include <QtGui>
#include <QDebug>

TreeManager::TreeManager()
{
    const int defaultSceneWidth = 700;
    const int defaultSceneHeight = 400;
    m_scene = new TreeScene(-defaultSceneWidth / 2, -Node::maxSize().height(),
                            defaultSceneWidth, defaultSceneHeight);
    connect(m_scene, SIGNAL(itemsMoving()), this, SLOT(updateSceneRect()));
    m_scene->setBackgroundBrush(QColor(0xfff6e6));
    m_root = 0;
    m_treeSize = 0;

    connect(this, SIGNAL(treeChanged()), this, SLOT(updateScene()));
}

TreeScene* TreeManager::scene()
{
    return m_scene;
}

int TreeManager::treeSize()
{
    return m_treeSize;
}

bool TreeManager::addValue(int value)
{
    if (m_root)
    {
        Node *cur = m_root;
        while (true)
        {
            if (value == cur->value())
            {
                break;
            }
            else if (value < cur->value())
            {
                if (cur->leftChild())
                {
                    cur = cur->leftChild();
                }
                else
                {
                    break;
                }
            }
            else if (value > cur->value())
            {
                if (cur->rightChild())
                {
                    cur = cur->rightChild();
                }
                else
                {
                    break;
                }
            }
        }

        if (value == cur->value())
        {
            return false;
        }

        if (value < cur->value())
        {
            Node *newNode = new Node(value);
            cur->setLeftChild(newNode);
            m_scene->addItem(newNode);
            m_scene->addItem(newNode->parentEdge());
            newNode->parent()->updateSubTreeSize();
        }
        else if (value > cur->value())
        {
            Node *newNode = new Node(value);
            cur->setRightChild(newNode);
            m_scene->addItem(newNode);
            m_scene->addItem(newNode->parentEdge());
            newNode->parent()->updateSubTreeSize();
        }

    }
    else
    {
        m_root = new Node(value);
        m_scene->addItem(m_root);
        m_scene->addItem(m_root->parentEdge());
    }

    m_treeSize++;
    emit treeChanged();
    return true;
}

bool TreeManager::removeValue(int value)
{
    Node *node = searchValue(value);
    if (node)
    {
        deleteNode(node);
        return true;
    }
    else
    {
        return false;
    }
}

bool TreeManager::deleteSelected()
{
    QList<QGraphicsItem *> selection = m_scene->selectedItems();
    if (selection.isEmpty())
    {
        return false;
    }

    foreach(QGraphicsItem *item, selection)
    {
        Node *node = dynamic_cast<Node *>(item);
        if (node)
        {
            deleteNode(node);
        }
    }
    return true;
}

void TreeManager::setRoot(Node *node)
{
    m_root = node;
    node->removeParentEdge();
}

Node* TreeManager::searchValue(int value)
{
    if (m_root)
    {
        return searchDFS(m_root, value);
    }
    else
    {
        return 0;
    }
}

Node* TreeManager::searchDFS(Node *cur, int val)
{
    if (cur->value() == val)
    {
        return cur;
    }

    if (val < cur->value())
    {
        if (Node *left = cur->leftChild())
        {
            return searchDFS(left, val);
        }
        else
        {
            return 0;
        }
    }

    if (cur->value() < val)
    {
        if (Node *right = cur->rightChild())
        {
            return searchDFS(right, val);
        }
        else
        {
            return 0;
        }
    }

    return 0;
}

void TreeManager::deleteNode(Node *node)
{
    if (!node)
    {
        return;
    }

    Node* p = node->parent();
    Node* l = node->leftChild();
    Node* r = node->rightChild();
    int v = node->value();
    bool root = (node == m_root);

    m_scene->removeItem(node);

    if (node->parentEdge())
    {
        m_scene->removeItem(node->parentEdge());
    }
    delete node;

    Node *lowestNode = 0;       //subTreeSize update start node

    if (!l && !r)
    {             //node has no children
        if (root)
        {
            m_root = 0;
        }
        else
        {
            lowestNode = p;     //lowest = node's parent
        }
    }
    else
    {                    //node has children
        Node *x;
        if (l && r)
        {           //node has both children
            x = r;
            if (x->leftChild())
            {       //node's right child has left child
                while (x->leftChild())  //x = the most left node in node's right child subtree
                {
                    x = x->leftChild();
                }

                lowestNode = x->parent();   //lowest = parent of the x node

                if (x->rightChild())
                {      //x has no left child, but maybe it has right
                    x->parent()->setLeftChild(x->rightChild());
                }

                x->setRightChild(r);
            }
            else
            {
                lowestNode = x;     //node's right child has no left child; lowest = node's right child
            }
            x->setLeftChild(l);
        }
        else
        {                //node has only one child
            x = l ? l : r;
            lowestNode = x;     //lowest = node's child which takes node's stand
        }

        if (root)
        {
            setRoot(x);
        }
        else
        {
            if (v < p->value())
            {
                p->setLeftChild(x);
            }
            else
            {
                p->setRightChild(x);
            }
        }
    }

    if (lowestNode)
    {
        lowestNode->updateSubTreeSize();
    }

    m_treeSize--;
    emit treeChanged();
}

void TreeManager::rotateSelectedLeft()
{
    QList<QGraphicsItem *> selection = m_scene->selectedItems();
    if (selection.size() != 1)
    {
        return;
    }

    Node *node = qgraphicsitem_cast<Node*>(selection[0]);
    bool root = (node == m_root);
    if (Node *r = node->rightChild())
    {
        Node *p = node->parent();
        if (root)
        {
            setRoot(r);
        }
        else
        {
            if (node->value() < p->value())
            {
                p->setLeftChild(r);
            }
            else
            {
                p->setRightChild(r);
            }
        }

        node->setRightChild(r->leftChild());
        r->setLeftChild(node);

        node->updateSubTreeSize();
    }
    else
    {
        return;
    }

    emit treeChanged();
}

void TreeManager::rotateSelectedRigth()
{
    QList<QGraphicsItem *> selection = m_scene->selectedItems();
    if (selection.size() != 1)
    {
        return;
    }

    Node *node = qgraphicsitem_cast<Node*>(selection[0]);
    bool root = (node == m_root);
    if (Node *l = node->leftChild())
    {
        Node *p = node->parent();
        if (root)
        {
            setRoot(l);
        }
        else
        {
            if (node->value() < p->value())
            {
                p->setLeftChild(l);
            }
            else
            {
                p->setRightChild(l);
            }
        }

        node->setLeftChild(l->rightChild());
        l->setRightChild(node);

        node->updateSubTreeSize();
    }
    else
    {
        return;
    }

    emit treeChanged();
}

int TreeManager::subTreeHeight(Node *node)
{
    return subTreeHeightDFS(node);
}

int TreeManager::subTreeHeightDFS(Node *cur)
{
    int l = 0, r = 0;

    if (Node *left = cur->leftChild())
    {
        l = subTreeHeightDFS(left);
    }

    if (Node *right = cur->rightChild())
    {
        r = subTreeHeightDFS(right);
    }

    return qMax(l, r) + 1;
}

void TreeManager::updateScene()
{
    recalcRelPos();
    recalcAbsPos();
    updateSceneRect();
}

void TreeManager::updateSceneRect()
{
    qreal maxY = 0;
    qreal maxX = 0;

    QList<QGraphicsItem *> items = m_scene->items();

    foreach(QGraphicsItem *item, items)
    {
        maxX = qMax(maxX, qAbs(item->sceneBoundingRect().right()));
        maxX = qMax(maxX, qAbs(item->sceneBoundingRect().left()));
        maxY = qMax(maxY, qAbs(item->sceneBoundingRect().bottom()));
    }

    maxX += Node::maxSize().width() / 2;
    maxY += 2 * Node::maxSize().height();

    m_scene->setSceneRect(-maxX, -Node::maxSize().height(), 2 * maxX, maxY);
}

void TreeManager::recalcRelPos()
{
    if (!m_root) return;
    qreal l = m_root->boundingRect().width() / 2;
    qreal r = m_root->boundingRect().width() / 2;

    if (m_root->leftChild())
    {
        l = recalcRelPosDFS(m_root->leftChild(), LeftChild);
    }

    if (m_root->rightChild())
    {
        r = recalcRelPosDFS(m_root->rightChild(), RightChild);
    }

    m_root->setPos((l - r) / 2, 0);
}

qreal TreeManager::recalcRelPosDFS(Node *node, ChildType type)
{
    const qreal margin = 5;
    qreal leftSubTreeWidth = 0, rightSubTreeWidth = 0;

    if (Node *left = node->leftChild())
    {
        leftSubTreeWidth = recalcRelPosDFS(left, LeftChild);
    }

    if (Node *right = node->rightChild())
    {
        rightSubTreeWidth = recalcRelPosDFS(right, RightChild);
    }

    leftSubTreeWidth = qMax(leftSubTreeWidth + margin,
                            node->boundingRect().width() / 2);
    rightSubTreeWidth = qMax(rightSubTreeWidth + margin,
                             node->boundingRect().width() / 2);

    switch (type)
    {
    case LeftChild:
        node->setRelPos(QPointF(-(rightSubTreeWidth + margin),
                                Node::levelSpacing()));
        break;
    case RightChild:
        node->setRelPos(QPointF(leftSubTreeWidth + margin,
                                Node::levelSpacing()));
        break;
    }

    return leftSubTreeWidth + rightSubTreeWidth;
}

void TreeManager::recalcAbsPos()
{
    if (!m_root)
    {
        return;
    }

    //m_root->setPos(0, 0);
    if (Node *left = m_root->leftChild())
    {
        recalcAbsPosDFS(left);
    }

    if (Node *right = m_root->rightChild())
    {
        recalcAbsPosDFS(right);
    }
}
void TreeManager::recalcAbsPosDFS(Node *node)
{
    node->setPos(node->parent()->pos() + node->relPos());

    if (Node *left = node->leftChild())
    {
        recalcAbsPosDFS(left);
    }

    if (Node *right = node->rightChild())
    {
        recalcAbsPosDFS(right);
    }
}

bool TreeManager::isEmpty()
{
    return m_treeSize == 0;
}

int TreeManager::valueByIndex(int index)
{
    if ((index > m_treeSize) || (index < 0) || (!m_root))
    {
        return 0;
    }

    return valueByIndexDFS(m_root, index);
}

int TreeManager::valueByIndexDFS(Node *node, int index)
{
    int nodeIndex = (node->leftChild() ? node->leftChild()->subTreeSize() : 0) + 1;

    if (index < nodeIndex)
    {
        return valueByIndexDFS(node->leftChild(), index);
    }
    else if (index > nodeIndex)
    {
        return valueByIndexDFS(node->rightChild(), index - nodeIndex);
    }

    return node->value();
}
