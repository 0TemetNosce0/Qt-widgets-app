#include "../include/TreeScene.h"

TreeScene::TreeScene(QObject *parent)
    :QGraphicsScene(parent)
{

}

TreeScene::TreeScene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
{

}

TreeScene::TreeScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QGraphicsScene(x, y, width, height, parent)
{

}

void TreeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (!selectedItems().isEmpty())
    {
        emit itemsMoving();
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
