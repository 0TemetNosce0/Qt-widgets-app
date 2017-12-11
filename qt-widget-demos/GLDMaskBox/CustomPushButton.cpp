#include "custompushbutton.h"

#include <QPainter>


CustomPushButton::CustomPushButton(QString imagePath, QWidget *parent)
    : QPushButton(parent)
    , m_imagePath(imagePath)
{
    //…Ë÷√±≥æ∞Õ∏√˜
    setAttribute(Qt::WA_TranslucentBackground);

    //º”‘ÿÕºœÒ
    pic.load(m_imagePath);

    resize(pic.size());
}

void CustomPushButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    //ªÊ÷∆ÕºœÒ
    painter.drawPixmap(0, 0, pic);
}
