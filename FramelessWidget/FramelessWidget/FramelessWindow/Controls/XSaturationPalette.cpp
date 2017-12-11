#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QLinearGradient>
#include <QToolTip>

#include <QDebug>
#include "XSaturationPalette.h"

/// 公有函数
XSaturationPalette::~XSaturationPalette(){}

XSaturationPalette::XSaturationPalette(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setMinimumWidth(240);
    setMinimumHeight(16);
    setMaximumHeight(24);

    initMembers();
}

// 获取饱和度
double XSaturationPalette::saturation()
{
    return mo_dblSaturation;
}

// HL颜色分量改变槽
void XSaturationPalette::setBaseColor(QColor color)
{
    mo_color = color;
    update();
}

void XSaturationPalette::setColor(QColor color)
{
    setBaseColor(color);
    mo_dblVernierPercentX = 1-color.hslSaturationF();
    mo_dblVernierX = rect().right() * mo_dblVernierPercentX;
    //qDebug() << mo_dblVernierPercentX << mo_dblVernierX;
    update();
}

/// 重写的保护函数: 事件处理器

void XSaturationPalette::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::NoBrush);

    int ntRight = rect().right();
    int ntBottm = rect().bottom();

    double dblVH, dblVS, dblVL = -100.0;
    mo_color.getHslF(&dblVH, &dblVS, &dblVL);
    QColor colorCenter; colorCenter.setHslF(dblVH, 0.5, dblVL);
    QColor colorStart;  colorStart.setHslF(dblVH, 1, dblVL);
    QColor colorFinal;  colorFinal.setHslF(dblVH, 0, dblVL);

    QLinearGradient linearGradient;
    linearGradient.setStart(QPointF(0, 0));
    linearGradient.setFinalStop(QPointF(ntRight, 0));
    linearGradient.setColorAt(0.0, colorStart);
    linearGradient.setColorAt(1.0, colorFinal);

    QBrush brush(linearGradient);
    painter.fillRect(rect(), brush);

    // 绘制游标
    QPointF ptfCenter(mo_dblVernierX, ntBottm/2.0);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawEllipse(ptfCenter, 5, 5);

    painter.setPen(QPen(Qt::white, 2));
    painter.drawEllipse(ptfCenter, 7, 7);
}

void XSaturationPalette::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    mo_dblVernierX = rect().right() * mo_dblVernierPercentX;
    update();
}

void XSaturationPalette::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mo_ptfCursorPos = event->globalPos();
        mo_dblVernierX = event->pos().rx();
        calculateSuration();
        update();
    }
}

void XSaturationPalette::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton &&
       !(event->buttons() & Qt::RightButton))
    {
        QPointF ptfCursorPos = event->globalPos();
        QPointF ptfOffset = ptfCursorPos - mo_ptfCursorPos;
        mo_ptfCursorPos = ptfCursorPos;
        double dblVerinerX = mo_dblVernierX + ptfOffset.rx();
        if(rect().contains(QPointF(dblVerinerX, rect().center().ry()).toPoint()))
        {
            mo_dblVernierX = dblVerinerX;
            calculateSuration();
            update();
        }
    }
    else
    {
        QPointF ptfCenter(mo_dblVernierX, rect().bottom()/2.0);
        QPainterPath path;
        path.addEllipse(ptfCenter, 7, 7);
        if(path.contains(event->pos()))
        {
            QToolTip::showText(mapToGlobal(event->pos())+QPoint(0,5), tr("调节色调和亮度111"), this,
                               QRect(event->pos()-QPoint(8,8), QSize(16, 16)), 10000);
        }
    }
}

/// 私有函数

void XSaturationPalette::initMembers()
{
    mo_color = Qt::red;
    mo_dblVernierX = 0;
    mo_dblVernierPercentX = 0;
    mo_dblSaturation = 0;
}

void XSaturationPalette::calculateSuration()
{
    mo_dblVernierPercentX = mo_dblVernierX/rect().right();
    mo_dblSaturation = 1- mo_dblVernierPercentX;

    mo_color.setHslF(mo_color.hslHueF(), mo_dblSaturation, mo_color.lightnessF());
    emit saturationChanged();
    emit saturationChanged(mo_dblSaturation);
    emit colorChanged();
    emit colorChanged(mo_color);
}
