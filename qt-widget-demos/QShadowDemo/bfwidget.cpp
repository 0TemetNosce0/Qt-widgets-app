#include <QDebug>
#include <QPalette>
#include <QBoxLayout>
#include <QSizePolicy>
#include <QGraphicsDropShadowEffect>

#include "bfwidget.h"

BFWidget::BFWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    central_widget = new QWidget();
    central_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding); ////ˮƽ����ʹ�ֱ����������չ

    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QColor(255,255,255)));
    central_widget->setPalette(palette);
    central_widget->setAutoFillBackground(true);

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect();
    shadow_effect->setBlurRadius(10.0);
    shadow_effect->setColor(QColor(0, 0, 0, 100));
    shadow_effect->setOffset(1.0);
    central_widget->setGraphicsEffect(shadow_effect);

    QVBoxLayout * main_layout = new QVBoxLayout();
    main_layout->addWidget(central_widget, Qt::AlignCenter);
    main_layout->addSpacing(0);
    main_layout->setContentsMargins(5,5,5,5);
    QWidget::setLayout(main_layout);
}

void BFWidget::setLayout(QLayout *layout)
{
    central_widget->setLayout(layout);
}

void BFWidget::mousePressEvent( QMouseEvent * event )
{
    //ֻ�����������ƶ��͸ı��С
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }

    //�����ƶ�����
    move_point = event->globalPos() - pos();
}

void BFWidget::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void BFWidget::mouseMoveEvent(QMouseEvent *event)
{
    //�ƶ�����
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}

//void BFWidget::resizeEvent(QResizeEvent *event)
//{
//    QSize size = event->size();
//    central_widget->setGeometry(5, 5, size.width() - 10, size.height() - 10);
//    qDebug() << central_widget->rect();
//}

