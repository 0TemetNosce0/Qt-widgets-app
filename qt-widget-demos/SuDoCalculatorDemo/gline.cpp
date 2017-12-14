#include "gline.h"

GLine::GLine(QWidget *parent)
    : QWidget(parent)
{
    setPen(3, QColor(Qt::black));
    draw(0, 100);
}

void GLine::setPen(int penSize, const QColor &color)
{
    this->penSize = penSize;
    this->penColor = color;
}

void GLine::draw(int z, int len)
{
    this->z = z;
    this->len = len;

    if(z == 0)
    {
        setMinimumSize(len, penSize);
        setMaximumSize(len, penSize);
    }
    else
    {
        setMinimumSize(penSize, len);
        setMaximumSize(penSize, len);
    }
    this->update();
}


void GLine::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(penSize);
    pen.setColor(penColor);
    int sx,sy,ex,ey;
    if(z == 0)
    {
        sx = 0;
        sy = penSize/2;
        ex = len;
        ey = sy;
    }
    else
    {
        sx = penSize/2;
        sy = 0;
        ex = sx;
        ey = len;
    }
    painter.setPen(pen);
    painter.drawLine(sx,sy,ex,ey);
}

