#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>
#include <QtMath>

#include <QDebug>
#include "XSlider.h"

/// 公有方法
XSlider::XSlider(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);

    connect(this, SIGNAL(grooveNormalColorChanged(QColor)), this, SLOT(updateColor()));
    connect(this, SIGNAL(grooveDiameterChanged(int)), this, SLOT(onGrooveDiameterChanged()));
    connect(this, SIGNAL(grooveHoverColorChanged(QColor)), this, SLOT(updateColor()));
    connect(this, SIGNAL(headleNormalColorChanged(QColor)), this, SLOT(updateColor()));
    connect(this, SIGNAL(headleHoverColorChanged(QColor)), this, SLOT(updateColor()));

    initMembers();
    updateColor();
}

XSlider::~XSlider()
{}

// 设置滑动条方向
void XSlider::setOrientation(Qt::Orientation orientation)
{
    mo_orientation = orientation;
    if(orientation == Qt::Horizontal)
    {
        setFixedHeight(24);
        setMinimumWidth(160);
        mo_rctfWindow = QRectF(-50, -50, 100, 100);
        mo_szfHeadle = QSizeF(100, 100);
        mo_ptfHeadleBegin = QPointF(-50, 0);
        mo_ptfHeadleEnd = QPointF(50, 0);
        mo_ptfHeadlePos = mo_ptfHeadleBegin;

        mo_rctfGroove = QRectF(-50, -mo_ntGrooveDiameter/2.0, 100, mo_ntGrooveDiameter);
        mo_rctfGroove.setLeft(qCeil(mo_rctfWindow.left()+0.5));
        mo_rctfGroove.setRight(qFloor(mo_rctfWindow.right()-0.5));
    }
    else if(orientation == Qt::Vertical)
    {
        setFixedWidth(24);
        setMinimumHeight(160);
        mo_rctfWindow = QRectF(-50, -50, 100, 100);
        mo_szfHeadle = QSizeF(100, 100);
        mo_ptfHeadleBegin = QPointF(0, 50);
        mo_ptfHeadleEnd = QPointF(0, -50);
        mo_ptfHeadlePos = mo_ptfHeadleBegin;

        mo_rctfGroove = QRectF(-mo_ntGrooveDiameter/2.0, -50, mo_ntGrooveDiameter, 100);
        mo_rctfGroove.setTop(qCeil(mo_rctfWindow.top()+0.5));
        mo_rctfGroove.setBottom(qFloor(mo_rctfWindow.bottom()-0.5));
    }

    refreshHeadleRectByValue();
}

// 设置取值范围
void XSlider::setRange(int ntMinValue, int ntMaxValue)
{
    mo_ntMinValue = ntMinValue;
    mo_ntMaxValue = ntMaxValue;
    mo_ntValue = ntMinValue;

    refreshHeadleRectByValue();
}

// 设置当前取值
void XSlider::setValue(int ntValue)
{
    if(ntValue >= mo_ntMinValue &&
       ntValue <= mo_ntMaxValue)
        mo_ntValue = ntValue;
    refreshHeadleRectByValue();
}

// 设置滑动间隔
void XSlider::setSingleStep(int ntSingleStep)
{
    if(ntSingleStep >= mo_ntMaxValue-mo_ntSingleStep)    return;

    if(mo_ntValue != mo_ntMinValue)
    {
        if((mo_ntValue - mo_ntMinValue) % ntSingleStep == 0)
            mo_ntSingleStep = ntSingleStep;
    }
    else
    {
        mo_ntSingleStep = ntSingleStep;
    }
}

// 设置外观
void XSlider::setOutlook(QString strStylesheet)
{
    strStylesheet.replace(QLatin1Char('$'), "qproperty-");
    strStylesheet.prepend("XSlider{ ");
    strStylesheet.append("}");

    setStyleSheet(strStylesheet);
}

int XSlider::value()
{
    return mo_ntValue;
}

/// 重写的保护方法

// event 事件. 检测鼠标进入离开状态
bool XSlider::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::Enter:
        mo_blIsEnter = true;
        break;
    case QEvent::Leave:
        mo_hoverTest = NoHover;
        mo_blIsEnter = false;
        updateColor();
        break;
    default:
        break;
    }

    return QWidget::event(event);
}

void XSlider::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);

    if(!validateValues())       return;

    drawGroove(this);
    drawHeadle(this);
}

void XSlider::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        // 记录全局鼠标位置,并检测点击区域
        mo_ptfCursorTrack = event->globalPos();
        hitTest();
    }
}

void XSlider::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        // 鼠标抬起刷新滑块位置到当前值的位置
        refreshHeadleRectByValue();
    }
}

void XSlider::mouseMoveEvent(QMouseEvent *event)
{
    // 临时记录鼠标全局位置
    QPointF ptfCursor = event->globalPos();

    if(event->buttons() & Qt::LeftButton)
    {
        if(mo_hitTest == HeadleHit)     // 此处不可调用hitTest()
        {
            refreshHeadleRectByCursor(ptfCursor);   // 刷新滑动位置
            updateValue(ptfCursor);                 // 更新当前值
            mo_ptfCursorTrack = ptfCursor;          // 记录全局鼠标位置
        }
    }
    else
    {
        mo_ptfCursorTrack = ptfCursor;  // 记录全局鼠标位置
        hoverTest();                    // 悬浮区域检测
    }
}

void XSlider::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    int side = qMin(width(), height());
    if(mo_orientation == Qt::Horizontal)
    {
        // 更新滑块滑动范围
        mo_ptfHeadleBegin.setX(qCeil(mo_rctfWindow.left() + mo_rctfWindow.width()*side/2.0/width()+0.0));
        mo_ptfHeadleEnd.setX(qFloor(mo_rctfWindow.right() - mo_rctfWindow.width()*side/2.0/width()-0.0));
        // 更新 滑块矩形区域
        mo_szfHeadle.setWidth(mo_rctfWindow.width() * height()/double(width()));
    }
    else
    {
        mo_ptfHeadleBegin.setY(qFloor(mo_rctfWindow.bottom() - mo_rctfWindow.height()*side/2.0/height()-0.0));
        mo_ptfHeadleEnd.setY(qCeil(mo_rctfWindow.top() + mo_rctfWindow.height()*side/2.0/height()+0.0));
        mo_szfHeadle.setHeight(mo_rctfWindow.height() * width()/double(height()));
    }

    // 刷新当前值滑块位置
    refreshHeadleRectByValue();
}

/// 槽
// 控件颜色改变槽
void XSlider::updateColor()
{
    if(hoverTest() == GrooveHover || hoverTest() == HeadleHover)
    {
        mo_colorHeadle = mo_colorHeadleHover;
        mo_colorGroove = mo_colorGrooveHover;
    }
    else
    {
        mo_colorHeadle = mo_colorHeadleNormal;
        mo_colorGroove = mo_colorGrooveNormal;
    }
    update();
}

// 滑槽比例改变槽
void XSlider::onGrooveDiameterChanged()
{
    if(mo_orientation == Qt::Horizontal)
    {
        mo_rctfGroove = QRectF(-50, -mo_ntGrooveDiameter/2.0, 100, mo_ntGrooveDiameter);
        mo_rctfGroove.setLeft(qCeil(mo_rctfWindow.left()+0.5));
        mo_rctfGroove.setRight(qFloor(mo_rctfWindow.right()-0.5));
    }
    else
    {
        mo_rctfGroove = QRectF(-mo_ntGrooveDiameter/2.0, -50, mo_ntGrooveDiameter, 100);
        mo_rctfGroove.setTop(qCeil(mo_rctfWindow.top()+0.5));
        mo_rctfGroove.setBottom(qFloor(mo_rctfWindow.bottom()-0.5));
    }
}

/// 私有方法

// 初始化成员
void XSlider::initMembers()
{
    // 输入参数
    mo_orientation  = Qt::Horizontal;
    mo_ntValue = 0;
    mo_ntMinValue = 0;
    mo_ntMaxValue = 0;
    mo_ntSingleStep = 1;

    // 属性
    mo_colorGrooveNormal = QColor("lightgray");
    mo_colorGrooveHover = QColor("darkgray");
    mo_colorHeadleNormal = QColor("darkgray");
    mo_colorHeadleHover = QColor("deepskyblue");
    mo_ntHeadleBorderWidth = 10;
    mo_ntGrooveDiameter = 10;
    mo_blShowValueText = true;

    // 变量
    mo_szfHeadle = QSizeF(0, 0);
    mo_ptfHeadleBegin = QPointF(-0, 0);
    mo_ptfHeadleEnd = QPointF(0, 0);
    mo_ptfHeadlePos = mo_ptfHeadleBegin;

    mo_rctfGroove = QRectF(0, 0, 0, 0);

    mo_blIsEnter = false;
    mo_hitTest = NoHit;
    mo_hoverTest = NoHover;
}

// 初始化Painter
void XSlider::initPainter(QPainter *pPainter)
{
    pPainter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    pPainter->setWindow(mo_rctfWindow.toRect());
    pPainter->setPen(Qt::NoPen);
    pPainter->setBrush(Qt::NoBrush);
}


// 坐标转换，将逻辑坐标转换为窗口坐标
QPointF XSlider::worldMap(QPointF ptf)
{    
    double dblWindowX = mo_rctfWindow.left() + mo_rctfWindow.width()  * ptf.rx() / width();
    double dblWindowY = mo_rctfWindow.top()  + mo_rctfWindow.height() * ptf.ry() / height();
    return QPointF(dblWindowX, dblWindowY);
}

// 绘制滑动槽
void XSlider::drawGroove(QPaintDevice *pPaintDevice)
{    
    QPainter painter(pPaintDevice);
    initPainter(&painter);

    // 构造填充区与未填充区路径
    QPainterPath pathGrooveUnfilled, pathGrooveFilled;
    int ntRadius = mo_ntGrooveDiameter/2.0;
    if(mo_orientation == Qt::Horizontal)
    {
        pathGrooveFilled.addRoundedRect(QRectF(mo_rctfGroove.topLeft(), QPointF(mo_ptfHeadlePos.rx(), mo_rctfGroove.bottom())), ntRadius*height()/width(), ntRadius);
        pathGrooveUnfilled.addRoundedRect(QRectF(QPointF(mo_ptfHeadlePos.rx(), mo_rctfGroove.top()), mo_rctfGroove.bottomRight()), ntRadius*height()/width(), ntRadius);
    }
    else if(mo_orientation == Qt::Vertical)
    {
        pathGrooveFilled.addRoundedRect(QRectF(QPointF(mo_rctfGroove.left(), mo_ptfHeadlePos.ry()), mo_rctfGroove.bottomRight()), ntRadius, ntRadius*width()/height());
        pathGrooveUnfilled.addRoundedRect(QRectF(mo_rctfGroove.topLeft(), QPointF(mo_rctfGroove.right(), mo_ptfHeadlePos.ry())), ntRadius, ntRadius*width()/height());
    }

    // 绘制填充区与未填充区
    painter.fillPath(pathGrooveFilled, mo_colorHeadle);
    painter.fillPath(pathGrooveUnfilled, mo_colorGroove);
}

// 绘制滑块
void XSlider::drawHeadle(QPaintDevice *pPaintDevice)
{
    QPainter painter(pPaintDevice);
    initPainter(&painter);

    // 将视口设置为以滑块当前位置为中心的正方形
    QRect rctfWindow = painter.window();
    int side = qMin(width(), height());
    if(mo_orientation == Qt::Horizontal)
    {
        QRectF rctF = QRectF(width()*(mo_ptfHeadlePos.rx() - mo_rctfWindow.left())/mo_rctfWindow.width()-side/2, (height()-side)/2, side, side);
        painter.setViewport(rctF.toRect());
    }
    else
    {
        QRectF rctF = QRectF((width()-side)/2, height() - height()*(mo_rctfWindow.bottom() - mo_ptfHeadlePos.ry())/mo_rctfWindow.height()-side/2, side, side);
        painter.setViewport(rctF.toRect());
    }

    // 绘制滑块内圆与圆环
    QPainterPath pathOuter;
    pathOuter.addEllipse(rctfWindow);
    QPainterPath pathInner;
    pathInner.addEllipse(rctfWindow.adjusted(mo_ntHeadleBorderWidth, mo_ntHeadleBorderWidth, -mo_ntHeadleBorderWidth, -mo_ntHeadleBorderWidth));
    if(mo_blShowValueText)
    {
        painter.fillPath(pathInner, Qt::white);
        painter.fillPath(pathOuter.subtracted(pathInner), mo_colorHeadle);
    }
    else
        painter.fillPath(pathOuter, mo_colorHeadle);

    // 绘制当前值文本
    if(mo_blShowValueText)
    {
        QFont font;
        font.setFamily("微软雅黑");
        font.setWeight(QFont::Medium);
        // 根据数字最大位数设置文本大小
        int ntMax = qMax(qAbs(mo_ntMinValue), qAbs(mo_ntMaxValue));
        if(ntMax < 10)       font.setPixelSize(75);
        else if(ntMax < 100)       font.setPixelSize(50);
        else if(ntMax < 1000)       font.setPixelSize(35);
        else if(ntMax < 10000)       font.setPixelSize(25);
        // 绘制文本
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
        painter.setFont(font);
        painter.drawText(rctfWindow, Qt::AlignCenter, QString::number(mo_ntValue));
    }
}

// 刷新滑块滑动位置
void XSlider::refreshHeadleRectByCursor(QPointF ptfCursor)
{
    QPointF ptfHeadlePos;   // 位置临时坐标
    if(mo_orientation == Qt::Horizontal)
    {
        // 当前鼠标位置与上一次的便宜
        QPointF ptfMove = ptfCursor - mo_ptfCursorTrack;
        // 窗口坐标下的水平偏移
        double dblWindowMoveX = mo_rctfWindow.width() * ptfMove.rx() / width();
        // 临时位置
        ptfHeadlePos  = QPointF(mo_ptfHeadlePos.rx() + dblWindowMoveX, 0);
        // 超出边界则不更新滑块位置
        if(ptfHeadlePos.rx() < mo_ptfHeadleBegin.rx() ||
           ptfHeadlePos.rx() > mo_ptfHeadleEnd.rx())
            return ;
    }
    else if(mo_orientation == Qt::Vertical)
    {        
        QPointF ptfMove = ptfCursor - mo_ptfCursorTrack;
        double dblWindowMoveY = mo_rctfWindow.height() * ptfMove.ry() / height();
        ptfHeadlePos = QPointF(0, mo_ptfHeadlePos.ry() + dblWindowMoveY);
        if(ptfHeadlePos.ry() < mo_ptfHeadleEnd.ry() ||
          ptfHeadlePos.ry() > mo_ptfHeadleBegin.ry())
                    return ;
    }
    // 更新滑块位置
    mo_ptfHeadlePos = ptfHeadlePos;
    // 更新滑块矩形用于鼠标检测
    mo_rctfHeadle.setTopLeft(mo_ptfHeadlePos + QPointF(-mo_szfHeadle.width()/2, -mo_szfHeadle.height()/2));
    mo_rctfHeadle.setSize(mo_szfHeadle);

    // 重绘
    update();
}

// 刷新滑块当前值位置
void XSlider::refreshHeadleRectByValue()
{
    if(!validateValues())  return;

    // 计算滑块中心窗口坐标系位置
    double dblValueX = mo_ptfHeadleBegin.rx() + (mo_ptfHeadleEnd.rx() - mo_ptfHeadleBegin.rx()) * mo_ntValue / (mo_ntMaxValue - mo_ntMinValue);
    double dblValueY = mo_ptfHeadleBegin.ry() + (mo_ptfHeadleEnd.ry() - mo_ptfHeadleBegin.ry()) * mo_ntValue / (mo_ntMaxValue - mo_ntMinValue);
    // 更新滑块位置
    mo_ptfHeadlePos = QPointF(dblValueX, dblValueY);
    // 更新滑块矩形区域
    mo_rctfHeadle.setTopLeft(mo_ptfHeadlePos + QPointF(-mo_szfHeadle.width()/2, -mo_szfHeadle.height()/2));
    mo_rctfHeadle.setSize(mo_szfHeadle);

    update();
}

// 点击检测
XSlider::HitTest &XSlider::hitTest(bool blDebug)
{
    HitTest hitTest;

    // 构造滑槽与滑块窗口坐标系下的路径
    QPainterPath pathGroove, pathHeadle;
    pathGroove.addRoundedRect(mo_rctfGroove, 5, 5);
    pathHeadle.addRoundedRect(mo_rctfHeadle, 20, 20);
    // 全局鼠标位置转换为窗口坐标系下的位置
    QPointF ptfCursorPos = worldMap(mapFromGlobal(mo_ptfCursorTrack.toPoint()));
    // 点击检测
    if(pathHeadle.contains(ptfCursorPos))
    {
        hitTest = HeadleHit;
    }
    else if(pathGroove.contains(ptfCursorPos))
    {
        hitTest = GrooveHit;
    }
    else hitTest = NoHit;

    // debug 点击检测结果
    if(mo_hitTest != hitTest)
    {
        mo_hitTest = hitTest;
        if(blDebug)
        {
            switch (mo_hitTest)
            {
            case HeadleHit:
                qDebug() << "Headle Hit";
                break;
            case GrooveHit:
                qDebug() << "Groove Hit";
                break;
            default:
                qDebug() << "No Hit";
                break;
            }
        }
    }

    // 返回点击检测结果
    return mo_hitTest;
}

// 鼠标悬浮检测，同点击检测
XSlider::HoverTest &XSlider::hoverTest(bool blDebug)
{
    if(!mo_blIsEnter)
    {
        mo_hoverTest = NoHover;
        return mo_hoverTest;
    }

    QPainterPath pathGroove, pathHeadle;
    pathGroove.addRoundedRect(mo_rctfGroove, 5, 5);
    pathHeadle.addRoundedRect(mo_rctfHeadle, 20, 20);

    HoverTest hoverTest;
    QPointF ptfCursorPos = worldMap(mapFromGlobal(mo_ptfCursorTrack.toPoint()));
    if(pathHeadle.contains(ptfCursorPos))
    {
        hoverTest = HeadleHover;
    }
    else if(pathGroove.contains(ptfCursorPos))
    {
        hoverTest = GrooveHover;
    }
    else hoverTest = NoHover;

    if(mo_hoverTest != hoverTest)
    {
        mo_hoverTest = hoverTest;
        updateColor();
        if(blDebug)
        {
            switch (mo_hoverTest)
            {
            case HeadleHover:
                qDebug() << "Headle Hover";
                break;
            case GrooveHover:
                qDebug() << "Groove Hover";
                break;
            default:
                qDebug() << "No Hover";
                break;
            }
        }
    }
    return mo_hoverTest;
}

// 根据全局鼠标位置更新当前值
void XSlider::updateValue(QPointF ptfCursor)
{    
    QPointF ptfMove = ptfCursor - mo_ptfCursorTrack;    // 光标位置偏移
    double dblValueOffse = 0;                           // 浮点值偏移
    QPointF ptfHeadlePos;                               // 滑块浮点位置

    if(mo_orientation == Qt::Horizontal)
    {
        // 计算水平窗口坐标系偏移
        double dblWindowMoveX = mo_rctfWindow.width() * ptfMove.rx()/width();
        // 计算滑块浮点位置
        ptfHeadlePos = QPointF(mo_ptfHeadlePos.rx() + dblWindowMoveX, 0);
        // 计算浮点值偏移
        dblValueOffse = (mo_ntMaxValue - mo_ntMinValue) *
                        (ptfHeadlePos.rx() - mo_ptfHeadleBegin.rx()) / (mo_ptfHeadleEnd.rx() - mo_ptfHeadleBegin.rx());

    }
    else if(mo_orientation == Qt::Vertical)
    {
        double dblWindowMoveY = mo_rctfWindow.height() * ptfMove.ry()/height();
        ptfHeadlePos = QPointF(0, mo_ptfHeadlePos.ry() + dblWindowMoveY);
        dblValueOffse = (mo_ntMaxValue - mo_ntMinValue) *
                        (mo_ptfHeadleBegin.ry() - ptfHeadlePos.ry()) / (mo_ptfHeadleBegin.ry() - mo_ptfHeadleEnd.ry());
    }

    // 以滑动间隔为分度值计算滑块量化位置
    int ntValueTemp = qRound(dblValueOffse / double(mo_ntSingleStep)) * mo_ntSingleStep;

    // 当前值更新
    if(mo_ntValue != ntValueTemp && ntValueTemp >= mo_ntMinValue && ntValueTemp <= mo_ntMaxValue)
    {
        mo_ntValue = ntValueTemp;
        emit valueChanged(mo_ntValue);
        emit valueChanged();
    }
}

// 参数有效性验证
bool XSlider::validateValues()
{
    if(mo_ntMinValue >= mo_ntMaxValue)  return false;

    if(mo_ntValue < mo_ntMinValue)  mo_ntValue = mo_ntMinValue;
    if(mo_ntValue > mo_ntMaxValue)  mo_ntValue = mo_ntMaxValue;

    if(mo_ntSingleStep >= mo_ntMaxValue-mo_ntMinValue ||
       mo_ntSingleStep <= 0 ||
       (mo_ntMaxValue-mo_ntMinValue) % mo_ntSingleStep != 0 ||
       (mo_ntValue-mo_ntMinValue) % mo_ntSingleStep != 0
       )
        mo_ntSingleStep = 1;

    return true;
}

