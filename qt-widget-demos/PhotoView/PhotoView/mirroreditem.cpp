#include "mirroreditem.h"

QRectF MirroredItem::boundingRect() const
{
    return QRectF(0.0f,0.0f,myWidth,myHeight);
}

void MirroredItem::paint(QPainter* painter,const QStyleOptionGraphicsItem*,
                         QWidget*)
{
    painter->drawPixmap(0,0,item);
    painter->drawPixmap(0,static_cast<int>(myHeight*0.5f),itemMirror);
}

int MirroredItem::getWidth()
{
    return myWidth;
}

int MirroredItem::getHeight()
{
    return myHeight;
}

int MirroredItem::getStack()
{
    return stackNumber;
}

int MirroredItem::getWX()
{
    return wantedX;
}

int MirroredItem::getWY()
{
    return wantedY;
}

void MirroredItem::makeReflection()
{
    itemMirror = QPixmap(myWidth,static_cast<int>(myHeight*0.5f));
    QPainter* painter = new QPainter(&itemMirror);
    painter->drawPixmap(0,0,QPixmap::fromImage(item.toImage()
                                               .mirrored(false,true)));
    painter->resetTransform();
    QPen pen(Qt::transparent);
    painter->setPen(pen);
    QLinearGradient gradient;
    gradient = QLinearGradient(0,0,0,static_cast<int>(myHeight*0.375f));
    gradient.setColorAt(0.0f,QColor(0,15,15,155));
    gradient.setColorAt(1.0f,QColor(0,15,15,255));
    painter->setBrush(QBrush(gradient));
    painter->drawRect(0,0,myWidth,static_cast<int>(myHeight*0.5f));
    delete painter;
}

void MirroredItem::makePhoto(QPixmap image)
{
    item =  QPixmap(myWidth,static_cast<int>(myHeight*0.5f));
    if((image.width() > myWidth - 2) || (image.height() > myHeight*0.5f-2))
        image = image.scaled(myWidth-2,static_cast<int>(myHeight*0.5f-2),
                             Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QPainter* painter = new QPainter(&item);
    QPen pen(Qt::darkGray);
    pen.setWidth(2);
    painter->setPen(pen);
    QLinearGradient gradient;
    gradient = QLinearGradient(0,0,0,static_cast<int>(myHeight*0.5f));
    gradient.setColorAt(0.0f,QColor(175,175,175));
    gradient.setColorAt(0.5f,QColor(215,215,215));
    gradient.setColorAt(1.0f,QColor(175,175,175));
    painter->setBrush(QBrush(gradient));
    painter->drawRect(0,0,myWidth,static_cast<int>(myHeight*0.5f));
    painter->drawPixmap(static_cast<int>(myWidth*0.5f-(image.width()*0.5f)),
                        static_cast<int>(myHeight*0.25f-(image.height()*0.5f)),
                        image);
    delete painter;
}

void MirroredItem::moveLeft()
{
    if(stackNumber == 0)
    {
        wantedX = pos().x() - myWidth - 50;
        wantedY = pos().y() + 25;
        setZValue(wantedX*-1);
    }
    else if(stackNumber == -1)
    {
        wantedX = pos().x() - 50;
        wantedY = pos().y() + 15;
        setZValue(wantedX*-1);
    }
    else if(stackNumber == 1)
    {
        wantedX = pos().x() - 50;
        wantedY = pos().y() - 15;
        setZValue(wantedX);
    }
}

void MirroredItem::moveRight()
{
    if(stackNumber == 0)
    {
        wantedX = pos().x() + myWidth + 50;
        wantedY = pos().y() + 25;
        setZValue(wantedX*-1);
    }
    else if(stackNumber == -1)
    {
        wantedX = pos().x() + 50;
        wantedY = pos().y() - 15;
        setZValue(wantedX*-1);
    }
    else if(stackNumber == 1)
    {
        wantedX = pos().x() + 50;
        wantedY = pos().y() + 15;
        setZValue(wantedX);
    }
}

void MirroredItem::moveCenter()
{
    wantedY = static_cast<int>(scene()->height()*0.5f - myHeight*0.45f);
    wantedX = static_cast<int>(scene()->width()*0.5f - myWidth*0.5f);
    setZValue(0);
}

void MirroredItem::moveTo(int posX,int posY)
{
    wantedX = posX;
    wantedY = posY;
}

bool MirroredItem::isInPlace() const
{
    return (wantedX == pos().x()) && (wantedY == pos().y());
}

void MirroredItem::setScatk(int stack)
{
    stackNumber = stack;
}

void MirroredItem::animate()
{   
    int x = pos().x();
    int y = pos().y();
    if(pos().x() < wantedX)
    {
        if((pos().x() + dX >= wantedX))
            x = wantedX;
        else
            x = pos().x() + dX;
    }
    else if(pos().x() > wantedX)
    {
        if((pos().x() - dX <= wantedX))
            x = wantedX;
        else
            x = pos().x() - dX;
    }

    if(pos().y() < wantedY)
    {
        if((pos().y() + dY >= wantedY))
            y = wantedY;
        else
            y = pos().y() + dY;
    }
    else if(pos().y() > wantedY)
    {
        if((pos().y() - dY <= wantedY))
            y = wantedY;
        else
            y = pos().y() - dY;
    }
    setPos(x,y);
}

MirroredItem::MirroredItem(QPixmap image,int width,int height)
    :QGraphicsItem()
{
    myWidth = width;
    myHeight = height;
    makePhoto(image);
    makeReflection();
    wantedX = 0;
    wantedY = 0;
    stackNumber = 0;
    dX = static_cast<unsigned>(myWidth * 0.125f);
    dY = 15;
}
