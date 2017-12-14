#include "customframe.h"

CustomFrame::CustomFrame(QWidget* parent)
    : QFrame(parent)
{
    this->setMouseTracking(true);   //设置此窗体是否跟踪鼠标
}

CustomFrame::~CustomFrame ()
{

}

void CustomFrame::mouseMoveEvent(QMouseEvent* e)
{
    emit signalsMousePosition(e->x(), e->y());
}
