#include "positioningmenubar.h"

#include <QResizeEvent>

PositioningMenuBar::PositioningMenuBar(QMenuBar *parent)
    : QMenuBar(parent)
{
//    parent->installEventFilter(this);
}

bool PositioningMenuBar::eventFilter(QObject *obj, QEvent *ev)
{
    if (ev->type() == QEvent::Resize)
    {
        QResizeEvent *resizeEvent = static_cast<QResizeEvent *>(ev);
        move(resizeEvent->size().width() - width(), 0);
    }

    return QMenuBar::eventFilter(obj, ev);
}
