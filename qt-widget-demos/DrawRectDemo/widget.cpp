#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_isDown = false;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() && Qt::LeftButton)
    {
        m_isDown = true;
        m_start = e->pos();
        m_stop = e->pos();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(m_isDown)
    {
        m_stop = e->pos();
    }
    update();
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() && Qt::LeftButton)
    {
        m_isDown = false;
    }

}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    if(!m_isDown)
    {
        return;
    }
    p.drawRect(QRect(m_start, m_stop));
}

