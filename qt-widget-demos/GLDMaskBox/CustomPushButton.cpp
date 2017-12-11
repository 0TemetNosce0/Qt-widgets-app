#include "custompushbutton.h"

#include <QPainter>


CustomPushButton::CustomPushButton(QString imagePath, QWidget *parent)
    : QPushButton(parent)
    , m_imagePath(imagePath)
{
    //���ñ���͸��
    setAttribute(Qt::WA_TranslucentBackground);

    //����ͼ��
    pic.load(m_imagePath);

    resize(pic.size());
}

void CustomPushButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    //����ͼ��
    painter.drawPixmap(0, 0, pic);
}
