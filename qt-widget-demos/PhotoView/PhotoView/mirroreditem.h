#ifndef MIRROREDITEM_H
#define MIRROREDITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QImage>
#include <QLinearGradient>
#include <QPainter>

class MirroredItem : public QGraphicsItem
{
public:
    MirroredItem(QPixmap image,int width,int height);
    QRectF boundingRect() const;
    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option,
               QWidget* widget);
    int getWidth();
    int getHeight();
    void moveLeft();
    void moveRight();
    void moveCenter();
    void moveTo(int posX,int posY);
    void animate();
    bool isInPlace() const;
    void setScatk(int stack);
    int getWX();
    int getWY();
    int getStack();

private:
    void makePhoto(QPixmap image);
    void makeReflection();
    QPixmap item;
    QPixmap itemMirror;
    int wantedX;
    int wantedY;
    unsigned dX,dY;
    int myWidth;
    int myHeight;
    int stackNumber; //-1-left 0-center 1-right
    QTimer* timer;
};

#endif // MIRROREDITEM_H
