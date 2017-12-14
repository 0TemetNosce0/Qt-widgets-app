#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QtMath>

#include <QDebug>
#include "XColorLabel.h"

XColorLabel::XColorLabel(QColor color, QWidget *parent)
    : QLabel(parent)
{
    setMinimumSize(40, 40);
    setColor(color);

}

XColorLabel::~XColorLabel()
{

}

QColor XColorLabel::color()
{
    return mo_color;
}

void XColorLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        mo_ptPressed = ev->pos();
    }
}

void XColorLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint ptReleased = ev->pos();
    double dblOffset = qSqrt(qPow(ptReleased.x()-mo_ptPressed.x(), 2) +
                             qPow(ptReleased.y()-mo_ptPressed.y(), 2));
    if(dblOffset < 15)  emit clicked(mo_color);
}

void XColorLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit doubleClicked();
}

void XColorLabel::setColor(QColor color)
{
    mo_color = color;
    setStyleSheet(QString("QLabel{ "
                          "  border: 2px solid transparent;"
                          "  background-color: %1;"
                          "  color: red;"
                          "  font: bold 14pt 微软雅黑;"
                          "}"
                          "QLabel:hover{ "
                          "  border-color: red; "
                          "}").arg(mo_color.name(QColor::HexArgb)));
}

void XColorLabel::setAlpha(int ntAlpha)
{
    //qDebug() << "XColorLabel::setAlpha";
    mo_color.setAlpha(ntAlpha);
    setColor(mo_color);
    emit colorChanged(mo_color);
}

void XColorLabel::setRed(int ntRed)
{
    //qDebug() << "XColorLabel::setRed";
    mo_color.setRed(ntRed);
    setColor(mo_color);
    emit colorChanged(mo_color);
}

void XColorLabel::setGreen(int ntGreen)
{
    //qDebug() << "XColorLabel::setGreen";
    mo_color.setGreen(ntGreen);
    setColor(mo_color);
    emit colorChanged(mo_color);
}

void XColorLabel::setBlue(int ntBlue)
{
    //qDebug() << "XColorLabel::setBlue";
    mo_color.setBlue(ntBlue);
    setColor(mo_color);
    emit colorChanged(mo_color);
}

void XColorLabel::setAlphaF(double dblAlpha)
{
    //qDebug() << "XColorLabel::setAlphaF";
    mo_color.setAlphaF(dblAlpha);
    setColor(mo_color);
    emit colorChanged(mo_color);
}

void XColorLabel::setRedF(double dblRed)
{
    //qDebug() << "XColorLabel::setRedF";
    mo_color.setRedF(dblRed);
    setColor(mo_color);
    emit colorChanged(mo_color);
}

void XColorLabel::setGreenF(double dblGreen)
{
    //qDebug() << "XColorLabel::setGreenF";
    mo_color.setGreenF(dblGreen);
    setColor(mo_color);
    emit colorChanged(mo_color);
}

void XColorLabel::setBlueF(double dblBlue)
{
    //qDebug() << "XColorLabel::setBlueF";
    mo_color.setBlueF(dblBlue);
    setColor(mo_color);
    emit colorChanged(mo_color);
}
