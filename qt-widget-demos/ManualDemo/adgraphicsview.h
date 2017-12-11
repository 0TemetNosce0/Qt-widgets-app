#ifndef ADGRAPHICSVIEW_H
#define ADGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

class AdGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    AdGraphicsView();
    ~AdGraphicsView();
    void init();
    void loadMap(QByteArray map);
    void viewUpdate();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    QPixmap adMap;
    int width;
    int height;
    QGraphicsScene *adScene;
};

#endif // ADGRAPHICSVIEW_H
