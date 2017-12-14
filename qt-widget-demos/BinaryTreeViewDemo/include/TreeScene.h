#ifndef TREESCENE_H_
#define TREESCENE_H_

#include <QGraphicsScene>

class TreeScene : public QGraphicsScene{
    Q_OBJECT;
public:
    TreeScene(QObject *parent = 0);
    TreeScene(const QRectF &sceneRect, QObject *parent = 0);
    TreeScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);
signals:
    void itemsMoving();
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif /* TREESCENE_H */
