#include "moveanimation.h"

MoveAnimation::MoveAnimation(QObject *parent) :
    QObject(parent), a_direction(RightToLeft), a_duration(Normal)
{
}

MoveAnimation::MoveAnimation(QWidget *target, MoveAnimation::Direction direction, MoveAnimation::MoveDuration duration, QObject *parent) :
        QObject(parent), a_target(target), a_direction(direction), a_duration(duration)
{
}

MoveAnimation::MoveAnimation(QWidget *target, QObject *parent) :
    QObject(parent), a_target(target), a_direction(RightToLeft), a_duration(Normal)
{
}

void MoveAnimation::setupDirection()
{
    int startPosition[2];
    switch (a_direction)
    {
    case LeftToRight:
        startPosition[0] = a_target->x() + 50;
        startPosition[1] = a_target->y();
        break;
    case RightToLeft:
        startPosition[0] = a_target->x() - 50;
        startPosition[1] = a_target->y();
        break;
    case BottomToTop:
        startPosition[0] = a_target->x();
        startPosition[1] = a_target->y() + 50;
        break;
    case TopToBottom:
        startPosition[0] = a_target->x();
        startPosition[1] = a_target->y() - 50;
        break;
    }
    a_anim.setStartValue(QPoint(startPosition[0], startPosition[1]));
}

void MoveAnimation::start()
{
    a_anim.setDuration(a_duration);
    if(a_anim.endValue().isNull()) //If it hasn't been set yet
        setupDirection();
    a_anim.setTargetObject(a_target);
    a_anim.setPropertyName("pos");
    a_anim.setEndValue(QPoint(a_target->x(), a_target->y()));
    if(a_anim.state() == QPropertyAnimation::Running)
        a_anim.stop();
    a_anim.start();
    connect(&a_anim, SIGNAL(finished()), this, SLOT(hasFinished()));
}

MoveAnimation::~MoveAnimation()
{
    a_target = nullptr;
}
