
#include "bird.h"

bird::bird(QGraphicsObject *parent) : QGraphicsObject(parent)
{
    status = 1;
    statusChange = 10;
    can_up = true;
    changeAnimation = true;
    animation = new QPropertyAnimation(this, "pos");
    setPos(QPoint(0, 0));
}

QRectF bird::boundingRect() const
{
    return QRectF(175, 215, BIRD_SIZE, BIRD_SIZE);
}

void bird::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->save();

    statusChange--;

    if (0 == statusChange)
    {
        statusChange = 10;
        if (3 > status)
            status++;
        else
            status = 1;
    }

        if (1 == status)
        {
            painter->drawImage(boundingRect(), QImage(":/resource/Resource/bird1.png"));
        }
        else if (2 == status)
        {
            painter->drawImage(boundingRect(), QImage(":/resource/Resource/bird2.png"));
        }
        else
        {
            painter->drawImage(boundingRect(), QImage(":/resource/Resource/bird3.png"));
        }

    painter->restore();
}

void bird::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)\
    {
        birdUp();
    }
}

void bird::birdUp()
{
    if (can_up)
    {
        animation->stop();
        changeAnimation = false;
        can_up = false;

        if (this->pos().y() > BIRD_UPBOUND)
        {
            animation->setDuration(BIRD_UPTIME);
            animation->setStartValue(pos());
            animation->setEndValue(QPoint(pos().x(), pos().y() - BIRD_UPDISTANCE));
        }
        else
        {
            animation->setDuration(BIRD_UPTIME);
            animation->setStartValue(pos());
            animation->setEndValue(QPoint(pos().x(), -HEIGHT / 2));
        }
        animation->setEasingCurve(QEasingCurve::OutQuad);
        animation->start();
        connect(animation, SIGNAL(finished()), this, SLOT(setChangeAnimation()));
    }
}

void bird::setChangeAnimation()
{
    changeAnimation = true;
    can_up = true;

    emit adjustTimer();
    disconnect(animation, SIGNAL(finished()), this, SLOT(setChangeAnimation()));
}

void bird::riseAndfall()
{
    if (changeAnimation)
    {
        animation->stop();
        int DValue = HEIGHT - pos().y();
        animation->setDuration(DValue * BIRD_DIVISOR);
        animation->setStartValue(pos());
        animation->setEndValue(QPoint(pos().x(), pos().y() + DValue));
        animation->setEasingCurve(QEasingCurve::InQuad);
        animation->start();
        changeAnimation = false;
    }
}

bool bird::checkCollide()
{
    if (!collidingItems().isEmpty())
        return true;
    else
        return false;
}

void bird::reset()
{
    animation->stop();
    setPos(0, 0);
    changeAnimation = true;
    can_up = true;
}
