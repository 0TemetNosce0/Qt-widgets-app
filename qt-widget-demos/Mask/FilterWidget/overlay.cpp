#include "overlay.h"

#include <QPainter>
#include <QWidget>
#include <QEvent>


OverLay::OverLay(QWidget * parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void OverLay::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), QColor(80, 80, 255, 128));
}


Filter::Filter(QObject * parent)
    : QObject(parent)
{

}

bool Filter::eventFilter(QObject * obj, QEvent * ev)
{
    if (!obj->isWidgetType())
    {
        return false;
    }

    QWidget * w = static_cast<QWidget*>(obj);

    if (ev->type() == QEvent::MouseButtonPress)
    {
        if (!m_overlay)
        {
            m_overlay = new OverLay(w->parentWidget());
        }

        m_overlay->setGeometry(w->geometry());
        m_overlayOn = w;
        m_overlay->show();
    }
    else if (ev->type() == QEvent::Resize)
    {
        if (m_overlay && m_overlayOn == w)
        {
            m_overlay->setGeometry(w->geometry());
        }
    }

    return false;
}
