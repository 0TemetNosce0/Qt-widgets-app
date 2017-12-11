#include "fadewindow.h"

/* Armada of constructors...
   Those are so this class can receive any type of Window widgets available.
*/

FadeWindow::FadeWindow(QObject *parent)
    : QObject(parent)
    , a_finished(false)
    , a_timerEnabled(false)
{

}

FadeWindow::FadeWindow(QDialog *dialogWidget, QObject *parent)
    : a_target(dialogWidget)
    , a_duration(200)
    , a_finished(false)
    , a_timerEnabled(false)
    , QObject(parent)
{}

FadeWindow::FadeWindow(QDialog *dialogWidget, int msecs, FadeWindow::FadeMode mode, QObject *parent)
    : a_target(dialogWidget)
    , a_duration(msecs)
    , a_finished(false)
    , a_timerEnabled(false)
    , QObject(parent)
    , a_mode(mode)
{}

FadeWindow::FadeWindow(QWindow *windowWidget, QObject *parent)
    : a_target(windowWidget)
    , a_duration(200)
    , a_finished(false)
    , a_timerEnabled(false)
    , QObject(parent)
{

}

FadeWindow::FadeWindow(QWindow *windowWidget, int msecs, FadeWindow::FadeMode mode, QObject *parent)
    : a_target(windowWidget)
    , a_duration(msecs)
    , a_finished(false)
    , a_timerEnabled(false)
    , QObject(parent)
    , a_mode(mode)
{

}

FadeWindow::FadeWindow(QMainWindow *mainWindowWidget, int msecs, FadeWindow::FadeMode mode, QObject *parent)
    : a_target(mainWindowWidget)
    , a_duration(msecs)
    , a_finished(false)
    , a_timerEnabled(false)
    , QObject(parent)
    , a_mode(mode)
{

}

FadeWindow::FadeWindow(QMainWindow *mainWindowWidget, QObject *parent)
    : a_target(mainWindowWidget)
    , a_duration(200)
    , a_finished(false)
    , a_timerEnabled(false)
    , QObject(parent)
{

}


//Helper method
void FadeWindow::setMode(QPropertyAnimation *anim, FadeWindow::FadeMode mode, qreal endValue)
{
    if(mode == FadeIn)
    {
        anim->setStartValue(0.0);
        if(endValue != 1.0)
            anim->setEndValue(endValue);
        else
            anim->setEndValue(1.0);
    }
    else //Fade out
    {
        anim->setStartValue(1.0);
        if(endValue != 0.0)
            anim->setEndValue(endValue);
        else
            anim->setEndValue(0.0);
    }
}

//Actual method

void FadeWindow::start(qreal endValue)
{
    QPropertyAnimation *animation;
    animation = new QPropertyAnimation(this);
    animation->setTargetObject(a_target);
    animation->setDuration(a_duration);
    setMode(animation, a_mode, endValue);
    animation->setPropertyName("windowOpacity");
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    //If the timer is enabled, the user will be able to be notified by checking via getter if the animation is finished.
    if(a_timerEnabled)
        connect(animation, SIGNAL(finished()), this, SLOT(setFinished()));
}

FadeWindow::~FadeWindow()
{
    a_target = nullptr;
}
