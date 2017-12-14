#include <qmath.h>
#include "shadowwidget.h"

#include <QPainter>
#include <QMouseEvent>

ShadowWidget::ShadowWidget(QWidget *parent)
    : QDialog(parent)
    , m_mousePress(false)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setObjectName("basewidget");
    //setAttribute(Qt::WA_TranslucentBackground);
}

void ShadowWidget::paintEvent(QPaintEvent *)
{
    //����Ӱ����Ϊ��ƽ��ȥ��
//    QPainterPath path;
//    path.setFillRule(Qt::WindingFill);
//    path.addRect(10, 10, this->width()-20, this->height()-20);

//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.fillPath(path, QBrush(Qt::white));

//    QColor color(0, 0, 0, 50);
//    for(int i=0; i<10; i++)
//    {
//        QPainterPath path;
//        path.setFillRule(Qt::WindingFill);
//        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
//        color.setAlpha(150 - qSqrt(i)*50);
//        painter.setPen(color);
//        painter.drawPath(path);
//    }

}

void ShadowWidget::mousePressEvent(QMouseEvent *event)
{
    //ֻ�����������ƶ��͸ı��С
    if(event->button() == Qt::LeftButton)
    {
        m_mousePress = true;
    }
    //�����ƶ�����
    m_movePoint = event->globalPos() - pos();
}

void ShadowWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePress = false;
}

void ShadowWidget::mouseMoveEvent(QMouseEvent *event)
{
    //�ƶ�����
    if(m_mousePress)
    {
        QPoint movePpos = event->globalPos();
        move(movePpos - m_movePoint);
    }
}


