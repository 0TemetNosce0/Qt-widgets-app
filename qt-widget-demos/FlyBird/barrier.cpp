
#include "barrier.h"

barrier::barrier()
{
    is_addScore = false;
    QTime time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);
    height = qrand() % 105+ 80;//448 - 174 = 274        //124
    height2 = 274 - height;
    width = 40;
    beginMove();
}

QRectF barrier::boundingRect() const
{
    return QRectF(WIDTH, 0, width, HEIGHT);
}

void barrier::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->drawImage(QRectF(WIDTH, 0, width, height), QImage(":/resource/Resource/pipe1.png"));
    painter->drawImage(QRectF(WIDTH, height + 110, width, height2), QImage(":/resource/Resource/pipe2.png").scaled(width, height2));
    painter->restore();

    if (!is_addScore && pos().x() < -190)
    {
        is_addScore = true;
        emit add_Score();
    }
}

QPainterPath barrier::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(WIDTH, 0, width, height));
    path.addRect(QRectF(WIDTH, height + 125, width, height2));
    return path;
}

void barrier::beginMove()
{
    animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(BARRIER_TIME);
    animation->setStartValue(pos());
    animation->setEndValue(QPoint(pos().x() - WIDTH - 50, pos().y()));
    animation->start();
}

barrier::~barrier()
{
}
