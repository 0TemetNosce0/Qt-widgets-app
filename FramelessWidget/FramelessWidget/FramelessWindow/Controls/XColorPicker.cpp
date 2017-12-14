#include <QApplication>
#include <QTimer>
#include <QDesktopWidget>
#include <QtMath>
#include <QScreen>
#include <QCursor>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

#include <QDebug>
#include "XColorPicker.h"

XColorPicker::XColorPicker(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_DeleteOnClose, true);

    setMouseTracking(true);

    initMembers();
}


XColorPicker::~XColorPicker()
{
    // 销毁计时器
    if(Q_LIKELY(mp_timer))
    {
        mp_timer->stop();
        delete mp_timer;
        mp_timer = nullptr;
    }
}


void XColorPicker::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);

    // 绘制Alpha闪烁背景
    if(mo_blTransparent)    painter.fillRect(rect(), Qt::transparent);
    else
    {
        QColor color(0,0,0,0);
        color.setAlphaF(0.01);
        painter.fillRect(rect(), color);
    }

    // 绘制放大器
    if(mo_blMoved)  drawMagnifier(this, mo_ptCursorPos);
}


void XColorPicker::mousePressEvent(QMouseEvent *event)
{
    // 左键完成取色,右键关闭取色窗口
    if(event->button() == Qt::LeftButton)
        mo_ptPressed = event->pos();
    else if(event->button() == Qt::RightButton)
        close();
}


void XColorPicker::mouseReleaseEvent(QMouseEvent *event)
{
    // 检测单击事件,完成取色
    if(event->button() == Qt::LeftButton)
    {
        double dblOffset = qSqrt(qPow(event->pos().x() - mo_ptPressed.x(), 2) +
                                 qPow(event->pos().y() - mo_ptPressed.y(), 2));
        if(dblOffset < 45)
        {
            emit colorFinished(mo_color);
            close();
        }
    }
}


void XColorPicker::mouseMoveEvent(QMouseEvent *event)
{
    // 截取桌面上 以mo_ptCursorPos为中心尺寸为24*18的矩形图片
    mo_ptCursorPos = event->pos();
    QRect rctSource(mo_ptCursorPos+QPoint(-12,-9),QSize(24,18));
    QScreen *pScreen = QApplication::primaryScreen();
    mo_pxmpScreenSnapshoot = pScreen->grabWindow(QApplication::desktop()->winId(),
                                                 rctSource.left(), rctSource.top(),
                                                 rctSource.width(), rctSource.height());
    mo_imgScreenSnapshoot = mo_pxmpScreenSnapshoot.toImage();

    // 取色发射颜色改变信号
    mo_color = mo_imgScreenSnapshoot.pixelColor(mo_imgScreenSnapshoot.rect().center());
    emit colorChanged();
    emit colorChanged(mo_color);
    mo_blMoved = true;
    update();
}


void XColorPicker::pickColor()
{  
    // 启动定时器
    mp_timer = new QTimer(this);
    connect(mp_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    mp_timer->start(300);
    // 全屏显示设置鼠标为十字鼠标
    showFullScreen();
    setCursor(QCursor(Qt::CrossCursor));
}


void XColorPicker::onTimeout()
{
    // 切换Alpha控制标志并请求重绘
    mo_blTransparent = !mo_blTransparent;
    update();
}


void XColorPicker::initMembers()
{
    mo_szScreen = QApplication::desktop()->availableGeometry().size();
    mo_blMoved = false;
    mp_timer = nullptr;
    mo_blTransparent = false;
}


void XColorPicker::drawMagnifier(QPaintDevice *pPaintDevice, QPointF ptfPos)
{
    int ntBorderWidth = 2;
    int ntInfoHeight = 40;

    QRectF rctfMagnifier;
    rctfMagnifier.setTopLeft(ptfPos + QPointF(ntBorderWidth+10, ntBorderWidth+10));

    // 计算最外层矩形
    int ntMagnifierWidth = 140+2*ntBorderWidth;
    if(rect().right() - ptfPos.x() < ntMagnifierWidth &&
       rect().bottom() - ptfPos.y() < ntMagnifierWidth)
    {
        rctfMagnifier.setLeft(ptfPos.x() - ntMagnifierWidth-ntBorderWidth-10);
        rctfMagnifier.setTop(ptfPos.y() - ntMagnifierWidth-ntBorderWidth-10);
    }
    else if(rect().right() - ptfPos.x() < ntMagnifierWidth)
    {
        rctfMagnifier.setLeft(ptfPos.x() - ntMagnifierWidth-ntBorderWidth-10);
        rctfMagnifier.setTop(ptfPos.y() + ntBorderWidth+10);
    }
    else if(rect().bottom() - ptfPos.y() < ntMagnifierWidth)
    {
        rctfMagnifier.setLeft(ptfPos.x() + ntBorderWidth+10);
        rctfMagnifier.setTop(ptfPos.y() - ntMagnifierWidth-ntBorderWidth-10);
    }
    rctfMagnifier.setSize(QSize(140, 140));

    // 最外矩形框实际绘制矩形
    QRectF rctDrawnMagnifier = rctfMagnifier.adjusted(-qCeil(ntBorderWidth/2), -qCeil(ntBorderWidth/2),
                                                      qFloor(ntBorderWidth/2), qFloor(ntBorderWidth/2));


    // 计算放大镜矩形与颜色信息区矩形
    QRectF rctfZoom = rctfMagnifier.adjusted(0, 0, 0, -ntInfoHeight);
    QRectF rctfInfo = rctfMagnifier.adjusted(0, 140-ntInfoHeight, 0, 0);

    QPainter painter(pPaintDevice);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);

    // 绘制整个放大器边框
    painter.setPen(QPen(Qt::red, ntBorderWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.drawRect(rctDrawnMagnifier);

    // 绘制局部放大
    painter.drawPixmap(rctfZoom, mo_pxmpScreenSnapshoot, mo_pxmpScreenSnapshoot.rect());

    // 绘制准星
    QRectF rctfTemp = rctfZoom.adjusted(10, 10, -10, -10);
    painter.setPen(QPen(QColor("deepskyblue"), 5, Qt::SolidLine,Qt::SquareCap));
    painter.drawLine(rctfTemp.left(), rctfTemp.center().ry(), rctfTemp.right(), rctfTemp.center().ry());
    painter.drawLine(rctfTemp.center().rx(), rctfTemp.top(), rctfTemp.center().rx(), rctfTemp.bottom());

    // 填充信息背景
    painter.fillRect(rctfInfo.adjusted(0, 0, 0, 0), QBrush(QColor(0, 0, 0, 180)));
    painter.setPen(QPen(Qt::white));
    // 绘制信息文字
    QString strGeometry = tr("%1*%2-%3*%4").arg(mo_ptCursorPos.x()).arg(mo_ptCursorPos.y())
                          .arg(mo_szScreen.width()).arg(mo_szScreen.height());
    QString strHtmlColor = tr("Html: %1").arg(mo_color.name(QColor::HexRgb).toUpper());
    QString strRGBColor = tr(" RGB: %1,%2,%3").arg(mo_color.red()).arg(mo_color.green()).arg(mo_color.blue());

    painter.drawText(rctfInfo.adjusted(5, 0, 0, -2*ntInfoHeight/3.0), Qt::AlignVCenter, strGeometry);
    painter.drawText(rctfInfo.adjusted(5, ntInfoHeight/3.0, 0, -ntInfoHeight/3.0), Qt::AlignVCenter, strHtmlColor);
    painter.drawText(rctfInfo.adjusted(5, 2*ntInfoHeight/3.0, 0, 0), Qt::AlignVCenter, strRGBColor);
}
