#include "clabel.h"
#include "ctooltip.h"
#include "global.h"

#include <QEvent>
#include <QDebug>
#include <QCursor>
#include <QMouseEvent>

CLabel::CLabel(QWidget *parent)
    : QLabel(parent)
{
    m_bPressed = false;
}

bool CLabel::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip)
    {
        qDebug() << "tool tip show";
        g_toolTip->showMessage(this->pixmap(), QCursor::pos());
    }
    else if (event->type() == QEvent::Leave)
    {
        qDebug() << "tool tip leave";
        g_toolTip->hide();
    }
    return QLabel::event(event);
}

void CLabel::mousePressEvent(QMouseEvent *)
{
    m_bPressed = true;
}

void CLabel::mouseReleaseEvent(QMouseEvent *)
{
    if (m_bPressed)
    {
        emit signalClicked();
        m_bPressed = false;
    }
}
