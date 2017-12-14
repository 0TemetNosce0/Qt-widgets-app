#include "epushbutton.h"

EPushButton::EPushButton(QWidget *parent)
    : QPushButton(parent)
{
    //setAutoFillBackground(false);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0xFF,0xFF,0xFF,0x00));
    setPalette(pal);
    resize(27, 22);
    status = NORMAL;
    mouse_press = false;
}

EPushButton::~EPushButton()
{
}

void EPushButton::setPixName(QString pix_name)
{
    this->pix_name = pix_name;
    //setFixedSize(QPixmap(pix_name).size());
}

void EPushButton::enterEvent(QEvent *)
{
    setCursor(Qt::PointingHandCursor);
    status = ENTER;
    update();
}

void EPushButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        mouse_press = true;
        status = PRESS;
        update();
    }
}

void EPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(mouse_press  && this->rect().contains(event->pos())) {
        mouse_press = false;
        status = ENTER;
        update();
        emit clicked();
    }
}

void EPushButton::leaveEvent(QEvent *)
{
    setCursor(Qt::ArrowCursor);
    status = NORMAL;
    update();
}

void EPushButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    switch(status) {
    case NORMAL: {
            pixmap.load(pix_name);
            break;
        }
    case ENTER: {
            pixmap.load(pix_name + QString("_hover"));
            break;
        }
    case PRESS: {
            pixmap.load(pix_name + QString("_pressed"));
            break;
        }
    case NOSTATUS: {
            pixmap.load(pix_name);
            break;
        }
    default:
        pixmap.load(pix_name);
    }
    //pixmap = pixmap.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(rect(), pixmap);
}
