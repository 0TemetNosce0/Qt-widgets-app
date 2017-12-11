#include "toollistwidget.h"

ToolListWidget::ToolListWidget(QWidget *parent)
    : QListWidget(parent)
{

}

void ToolListWidget::mouseMoveEvent(QMouseEvent *e)
{
    QListWidget::mouseMoveEvent(e);
    static int offset = 0;

    QWheelEvent wheelEvent(QPoint(),
                           offset--,
                           Qt::MiddleButton,
                           Qt::NoModifier,
                           Qt::Vertical);

    qDebug() << "mouseMoveEvent" << ":" << this->focusWidget()->objectName();

    QApplication::sendEvent(this->focusWidget(), &wheelEvent);
}

void ToolListWidget::wheelEvent(QWheelEvent *e)
{
    QListWidget::wheelEvent(e);

    qDebug() << "wheelEvent" << ":" << this->focusWidget()->objectName();
}
