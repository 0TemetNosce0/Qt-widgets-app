#include "widgetscale.h"
#include "framelesshelper.h"
#include <QApplication>
#include <QDesktopWidget>
WidgetScale::WidgetScale(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
{
    resize(300, 200);
    backGroundPix.load(":/background.png");
    backGroundPix = backGroundPix.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    closeButton = new EPushButton(this);
    closeButton->setPixName(":/close");
    closeButton->setToolTip(tr("close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    //this指的是要处理的窗体
    FramelessHelper *pHelper = new FramelessHelper(this);
    pHelper->activateOn(this);  //激活当前窗体
    pHelper->setTitleHeight(30);  //设置窗体的标题栏高度
    pHelper->setWidgetMovable(true);  //设置窗体可移动
    pHelper->setWidgetResizable(true);  //设置窗体可缩放
    pHelper->setRubberBandOnMove(true);  //设置橡皮筋效果-可移动
    pHelper->setRubberBandOnResize(true);  //设置橡皮筋效果-可缩放

    move((QApplication::desktop()->width() - width())/2,  (QApplication::desktop()->height() - height())/2);
}

WidgetScale::~WidgetScale()
{

}

void WidgetScale::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), backGroundPix);
    painter.setFont(QFont("arial", 10, QFont::Bold));
    painter.setPen(QColor("#FFFFFF"));
    painter.drawText(QRectF(5, 5, 100, 35), tr("Happy Coder"));

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#2EB49E"));
    painter.drawRect(QRectF(0, 30, width(), height() - 30));
    QWidget::paintEvent(event);
}

void WidgetScale::resizeEvent(QResizeEvent *event)
{
    closeButton->move(width() - 27, 0);
    QWidget::resizeEvent(event);
}

