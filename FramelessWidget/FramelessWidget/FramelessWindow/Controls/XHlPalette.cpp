#include "XHlPalette.h"
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QToolTip>

#include <QDebug>

/// 公有函数
XHlPalette::~XHlPalette(){}

XHlPalette::XHlPalette(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(QSize(240, 80));
    // 启用鼠标跟踪以便可以接收到无鼠标按键按下时的鼠标移动事件
    setMouseTracking(true);
    initMembers();
}

// 获取颜色值
QColor XHlPalette::color()
{
    return mo_color;
}

/// 公有槽

// 饱和度设置槽
void XHlPalette::setSaturation(double dblsaturation)
{
    mo_dblSaturation = dblsaturation;
    update();                           // 更新重绘调色盘背景
    calculateColor(false);              // 提交颜色(游标位置未更新)
}


/// 重新实现的保护函数

void XHlPalette::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::NoBrush);

    /*
    qDebug() << "HSL(Red) = " << dblRH << dblRS << dblRL;
    qDebug() << "HSL(Green) = " << dblGH << dblGS << dblGL;
    qDebug() << "HSL(Blue) = " << dblBH << dblBS << dblBL;
    */


    int ntRight = rect().right();
    int ntBottm = rect().bottom();
    QColor colorStart, colorDatum, colorFinal;
    for(int it=0; it< ntRight+1; it++)
    {
        colorStart.setHslF(it/double(ntRight), mo_dblSaturation, 1);
        colorDatum.setHslF(it/double(ntRight), mo_dblSaturation, 0.5);
        colorFinal.setHslF(it/double(ntRight), mo_dblSaturation, 0);

        QLinearGradient linearGradient;
        linearGradient.setStart(QPointF(it, 0));
        linearGradient.setFinalStop(QPointF(it, ntBottm));
        linearGradient.setColorAt(0.0, colorStart);
        linearGradient.setColorAt(0.5, colorDatum);
        linearGradient.setColorAt(1.0, colorFinal);

        QBrush brush(linearGradient);
        painter.setPen(QPen(brush,1));
        painter.drawLine(QPointF(it, 0), QPointF(it, ntBottm));
    }

    // 绘制游标
    painter.setPen(QPen(Qt::black, 2));
    painter.drawEllipse(mo_ptfVernierPos, 5, 5);

    painter.setPen(QPen(Qt::white, 2));
    painter.drawEllipse(mo_ptfVernierPos, 7, 7);
}

void XHlPalette::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    // 计算尺寸改变后游标新位置
    mo_ptfVernierPos.setX(rect().right() * mo_ptfVernierPercentPos.rx());
    mo_ptfVernierPos.setY(rect().bottom() * mo_ptfVernierPercentPos.ry());

    update();
}

void XHlPalette::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mo_ptfCursorPos = event->globalPos();
        mo_ptfVernierPos = event->pos();
        calculateColor(true);
        update();
    }
}

void XHlPalette::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton &&
       !(event->buttons() & Qt::RightButton))
    {
        // 鼠标左键按下时的，更新颜色并重绘更新游标
        QPointF ptfCursorPos = event->globalPos();
        QPointF ptfOffect = ptfCursorPos - mo_ptfCursorPos;
        mo_ptfCursorPos = ptfCursorPos;
        QPointF ptfVernierTemp = mo_ptfVernierPos + ptfOffect;
        // 此处的条件判断防止游标超出范围
        if(rect().contains(ptfVernierTemp.toPoint()))
        {
            mo_ptfVernierPos = ptfVernierTemp;
            calculateColor(true);
            update();
        }
    }
    else    // 显示ToolTip
    {
        // 鼠标左键没按下时，碰撞检测显示ToolTip
        QPainterPath path;
        path.addEllipse(mo_ptfVernierPos, 7, 7);
        if(path.contains(event->pos()))
        {
            QToolTip::showText(mapToGlobal(event->pos())+QPoint(0,5), tr("调节色调和亮度111"), this,
                               QRect(mo_ptfVernierPos.toPoint()-QPoint(8,8), QSize(16, 16)), 10000);
        }
    }
}

/// 槽

// 设置颜色
void XHlPalette::setColor(QColor color)
{
    //qDebug() << "XHlPalette::setColor";
    mo_ptfVernierPercentPos.setX(color.hslHueF());
    mo_ptfVernierPercentPos.setY(1-color.lightnessF());
    mo_ptfVernierPos.setX(rect().right() * mo_ptfVernierPercentPos.rx());
    mo_ptfVernierPos.setY(rect().bottom() * mo_ptfVernierPercentPos.ry());
    update();
}

/// 私有函数

// 成员初始化
void XHlPalette::initMembers()
{
    mo_dblSaturation = 1.0;
}

/*****************************************************************************************************
 *  计算并发射新颜色信号
 *  当游标位置改变时:blPosChanged实参为true,表示HL颜色更新,此时void baseColorChanged(QClor)信号会被发射
 *  当游标位置没改变时:blPosChanged实参为false,表示HL颜色未更新,此时void baseColorChanged(QClor)信号不会被发射
 *****************************************************************************************************/
void XHlPalette::calculateColor(bool blPosChanged)
{
    // 记录游标百分比位置
    mo_ptfVernierPercentPos.setX(mo_ptfVernierPos.x()/double(rect().right()));
    mo_ptfVernierPercentPos.setY(mo_ptfVernierPos.y()/double(rect().bottom()));

    // 提交颜色
    mo_color.setHslF(mo_ptfVernierPercentPos.rx(),
                     mo_dblSaturation,
                     1-mo_ptfVernierPercentPos.ry());

    emit colorChanged();
    emit colorChanged(mo_color);
    if(blPosChanged)
    {
        emit baseColorChanged(mo_color);
    }
}
