#include <QtGui>
#include <cmath>

#include "../include/TreeView.h"

TreeView::TreeView(QWidget *parent)
    : QGraphicsView(parent)
{
    setDragMode(RubberBandDrag);
    setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    m_zoom = 1;
}

void TreeView::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers() && Qt::ControlModifier)
    {
        qreal numDegrees = event->delta() / 8.0;
        qreal numSteps = numDegrees / 15.0;
        qreal factor = std::pow(1.125, numSteps);
        scale(factor, factor);
        m_zoom *= factor;
        emit zoomChanged();
    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }
}

void TreeView::zoomIn()
{
    const qreal factor = 1.2;
    scale(factor, factor);  m_zoom *= factor;
    emit zoomChanged();
}

void TreeView::zoomOut()
{
    const qreal factor = 1.2;
    scale(1 / factor, 1 / factor);  m_zoom /= factor;
    emit zoomChanged();
}

void TreeView::zoomNormal()
{
    scale(1 / m_zoom, 1 / m_zoom);  m_zoom = 1;
    emit zoomChanged();
}

qreal TreeView::zoom()
{
    return m_zoom;
}

void TreeView::setHandCursor()
{
    setDragMode(ScrollHandDrag);
}

void TreeView::setArrowCursor()
{
    setDragMode(RubberBandDrag);
}
