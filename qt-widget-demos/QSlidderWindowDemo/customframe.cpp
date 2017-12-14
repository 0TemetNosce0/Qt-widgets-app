#include "customframe.h"

CustomFrame::CustomFrame(QWidget* parent)
    : QFrame(parent)
{
    this->setMouseTracking(true);   //���ô˴����Ƿ�������
}

CustomFrame::~CustomFrame ()
{

}

void CustomFrame::mouseMoveEvent(QMouseEvent* e)
{
    emit signalsMousePosition(e->x(), e->y());
}
