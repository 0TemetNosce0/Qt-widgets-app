#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QtMath>

#include <QDebug>
#include "XPicture.h"

XPicture::XPicture(QPixmap pic, QWidget *parent) : QLabel(parent)
{
    setMinimumSize(QSize(160,90));
    mo_pixmap = pic;
    setScaledContents(true);
    setPixmap(pic);

    setStyleSheet("QLabel{ "
                  "border: 2px solid transparent; }"
                  "QLabel:hover{ border-color: red; }");
}

XPicture::~XPicture()
{

}

QPixmap XPicture::pixmap() const
{
    return mo_pixmap;
}

/*
void XPicture::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);

    painter.drawPixmap(rect(), mo_pixmap.scaled(rect().size()));

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
*/
void XPicture::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        mo_ptPressed = ev->pos();
    }
}

void XPicture::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint ptReleased = ev->pos();
    double dblOffset = qSqrt(qPow(ptReleased.x()-mo_ptPressed.x(), 2) +
                             qPow(ptReleased.y()-mo_ptPressed.y(), 2));
    if(dblOffset < 15)  emit clicked(mo_pixmap);
    //qDebug() << ptReleased << mo_ptPressed << dblOffset;
}

void XPicture::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit doubleClicked();
}
