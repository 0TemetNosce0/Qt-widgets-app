#include <QKeyEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QHBoxLayout>

#include <QGraphicsDropShadowEffect>
#include <QGraphicsBlurEffect>
#include <QtMath>
#include <QDebug>
#include "XWindow.h"

/// 析构函数
XWindow::~XWindow(){   }

void XWindow::initTheme()
{

}

/// 构造函数
XWindow::XWindow(QWidget *parent)
    : QFrame(parent)
{
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setMouseTracking(true);

    initMembers();
    initControls();
    createTitleBar();
    createClientFrame();
    reLayout();
}

/// 公共接口

// 获取主题颜色
QColor XWindow::themeColor()
{
    return mo_colorTheme;
}

// 设置阴影半径
void XWindow::setShadowRadius(int ntRadius)
{
    if(mo_ntShadowWidth != ntRadius)
    {
        mo_ntShadowWidth  = mo_ntRtmShaowWidth = ntRadius;
        if(mo_ntShadowWidth > mo_ntLeftHitWidth)
        {
            mo_ntLeftHitWidth = mo_ntRightHitWidth = mo_ntBottomHitWidth = mo_ntShadowWidth;
            if(titleBar())    mo_ntTopHitWidth = mo_ntShadowWidth+5;
            else                mo_ntTopHitWidth = mo_ntShadowWidth;

        }
        if(mo_ntShadowWidth == 0)
        {
            mo_ntLeftHitWidth = mo_ntRightHitWidth = mo_ntBottomHitWidth = 5;
            if(titleBar())    mo_ntTopHitWidth = 10;
            else                mo_ntTopHitWidth = 5;
        }
        reLayout();
    }
}

// 设置阴影颜色
void XWindow::setShadowColor(QColor color)
{
    mo_colorShadow = color;
    reLayout();
}

// 设置碰撞半径
void XWindow::setHitRadius(int ntLeftWidth, int ntTopWidth, int ntRightWidth, int ntBottomWidth)
{
    mo_ntLeftHitWidth = ntLeftWidth;
    mo_ntTopHitWidth = ntTopWidth;
    mo_ntRightHitWidth = ntRightWidth;
    mo_ntBottomHitWidth = ntBottomWidth;
}

// 设置尺寸约束
void XWindow::setSizeConstraint(QLayout::SizeConstraint constraint)
{
    mp_layoutMain->setSizeConstraint(constraint);
    if(constraint == QLayout::SetFixedSize) mo_blResizable = false;
}

void XWindow::setFixedSize(int w, int h)
{
    QWidget::setFixedSize(w,h);
    mo_blResizable = false;
}

void XWindow::setFixedSize(const QSize &size)
{
    QWidget::setFixedSize(size);
    mo_blResizable = false;
}

// 模态显示
void XWindow::exec()
{
    setWindowModality(Qt::ApplicationModal);
    show();
    mo_evenLoop.exec();
    setWindowModality(Qt::NonModal);
}

// 获取边框部件
XBorderPanel *XWindow::borderFrame()
{
    return mp_frameBorder;
}

// 设置圆角
void XWindow::setRadius(int ntTopRadius, int ntBottomRadius)
{
    if(Q_LIKELY(mp_frameBorder))    mp_frameBorder->setRadius(ntTopRadius, ntTopRadius, ntBottomRadius, ntBottomRadius);

    if(Q_LIKELY(mp_frameTitle))
        mp_frameTitle->setRadius(
                    ntTopRadius-mp_frameBorder->getRightBorderWidth(),
                    ntTopRadius-mp_frameBorder->getRightBorderWidth(), 0, 0);

    if(Q_LIKELY(mp_frameClient))
        mp_frameClient->setRadius(0, 0,
                                  ntBottomRadius-mp_frameBorder->getLeftBorderWidth(),
                                  ntBottomRadius-mp_frameBorder->getRightBorderWidth());
}


/// 标题栏接口

// 设置标题栏
void XWindow::showTileBar(bool exist)
{
    if(!mp_frameTitle && exist)
    {
        createTitleBar();
        reLayout();
    }
    else if(mp_frameTitle && !exist)
    {
        delete mp_frameTitle;
        mp_frameTitle = nullptr;
        reLayout();
    }
}

// 获取标题栏
XTitlePanel *XWindow::titleBar()
{
    return mp_frameTitle;
}

// 设置标题栏系统按钮
void XWindow::setTitleButtonHints(int ntButtonHints)
{
    if(titleBar())
    {
        titleBar()->setButtonHints(ntButtonHints);
    }
}

// 设置标题栏部件
void XWindow::setTitleWidget(QWidget *pWgt)
{
    Q_UNUSED(pWgt)
}

// 设置标题
void XWindow::setWindowTitle(QString strTitle, QString strStylesheet)
{
    if(titleBar())
        titleBar()->setTitle(strTitle, strStylesheet);
}

// 设置标题对齐方式
void XWindow::setTitleAlignment(Qt::Alignment align)
{
    if(titleBar())
        titleBar()->setTitleAlignment(align);
}

// 设置图标
void XWindow::setWindowIcon(QString strStylesheet)
{
    if(titleBar())
        titleBar()->setIcon(strStylesheet);
}

// 添加部件到标题栏
void XWindow::addWidgetTotitleBar(QWidget *pWgt)
{
    if(titleBar())
        titleBar()->addWidget(pWgt);
}

/// 客户区接口

// 获取客户区
XClientPanel *XWindow::clientFrame()
{
    return mp_frameClient;
}

// 设置客户区布局
void XWindow::setLayout(QLayout *pLayout)
{
    clientFrame()->setLayout(pLayout);
    mp_layoutMain->setSizeConstraint(pLayout->sizeConstraint());
    if(pLayout->sizeConstraint() == QLayout::SetFixedSize)
        mo_blResizable = false;
}

/// 私有成员函数
///
// 成员初始化
void XWindow::initMembers()
{
    // 子控件
    mp_frameBorder = nullptr;                           // 边框Frame
    mp_frameTitle = nullptr;                            // 标题栏
    mp_frameClient = nullptr;                           // 客户区
    mp_layoutMain = nullptr;                            // 主布局


    // 标志成员
    mo_blMovable = true;                                // 可移动标志
    mo_blResizable = true;                              // 尺寸可变标志
    mo_blMaximised = false;                             // 最大化标志
    mo_blPressed = false;                               // 鼠标左键按下状态
    //mo_blThemehelper = true;                            // 启用主题帮助

    // 位置
    mo_ptPressedOffset = QPoint(0,0);                   // 鼠标按下相对位置
    mo_ptOffset = QPoint(0,0);                          // 鼠标相对位置
    mo_ptPos = QPoint(0,0);                             // 鼠标绝对位置
    mo_ptLastPos = QPoint(0,0);                         // 鼠标上一次绝对位置
    mo_rctResPos = QRect(QPoint(0,0), QSize(0,0));      // 窗口恢复位置
    mo_moveArea = QPainterPath(QPoint(0,0));            // 移动区域路径

    // 碰撞
    mo_hitSection = NoSection;                          // 点击区域
    mo_ntLeftHitWidth = 20;                             // 左尺寸框宽度
    mo_ntTopHitWidth = 25;                              // 上尺寸框宽度
    mo_ntRightHitWidth = 20;                            // 右尺寸框宽度
    mo_ntBottomHitWidth = 20;                           // 下尺寸框宽度

    // 阴影
    mo_ntShadowWidth = 20;
    mo_ntRtmShaowWidth = 20;
    mo_colorShadow = QColor(0,0,0);                      // 框架颜色
}

// 初始化子控件
void XWindow::initControls()
{
    mp_frameBorder = new XBorderPanel;


    // 创建主布局
    mp_layoutMain = new QHBoxLayout;
    mp_layoutMain->setMargin(mo_ntRtmShaowWidth);

    // 主布局添加部件
    mp_layoutMain->addWidget(mp_frameBorder);
    QFrame::setLayout(mp_layoutMain);

    connect(this, SIGNAL(activationChanged(bool)), mp_frameBorder, SLOT(onActivationChanged(bool)));
    connect(this, SIGNAL(activationChanged(bool)), this, SLOT(onActivationChanged(bool)));
}

// 创建标题栏
void XWindow::createTitleBar()
{
    Q_ASSERT(mp_frameBorder != nullptr);

    if(mp_frameTitle)    return;
    mp_frameTitle = new XTitlePanel;
    mp_frameBorder->setTitleWidget(mp_frameTitle);

    connect(mp_frameTitle, SIGNAL(toMinimize()), this, SLOT(onMinimize()));
    connect(mp_frameTitle, SIGNAL(toMaximize()), this, SLOT(onMaximize()));
    connect(mp_frameTitle, SIGNAL(toRestore()), this, SLOT(onRestore()));
    connect(mp_frameTitle, SIGNAL(toClose()), this, SLOT(onClose()));
    connect(this, SIGNAL(activationChanged(bool)), mp_frameTitle, SLOT(onActivationChanged(bool)));
}

// 创建客户区
void XWindow::createClientFrame()
{
    Q_ASSERT(mp_frameBorder != nullptr);

    if(mp_frameClient)  return;
    mp_frameClient = new XClientPanel;
    connect(this, SIGNAL(activationChanged(bool)), mp_frameClient, SLOT(onActivationChanged(bool)));
    mp_frameClient->setObjectName("FrameClient");
    mp_frameClient->setMouseTracking(true);
    mp_frameClient->setMinimumSize(QSize(480,320));
    mp_frameClient->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mp_frameBorder->setClientWidget(mp_frameClient);
}

// 布局子控件
void XWindow::reLayout()
{
    mp_layoutMain->setMargin(mo_ntRtmShaowWidth);

    mp_frameBorder->setGraphicsEffect(nullptr);

    QGraphicsDropShadowEffect *pShadowEffect = new QGraphicsDropShadowEffect;
    pShadowEffect->setColor(mo_colorShadow);
    pShadowEffect->setBlurRadius(mo_ntRtmShaowWidth);
    pShadowEffect->setOffset(0,0);
    mp_frameBorder->setGraphicsEffect(pShadowEffect);

    mp_layoutMain->setMargin(mo_ntRtmShaowWidth);
}

// 更新窗口位置
void XWindow::moveWindow()
{
    move(mo_ptPos-mo_ptPressedOffset);
    mo_rctResPos = frameGeometry();
}

// 更新窗口尺寸
void XWindow::resizeWindow()
{
    QPoint movePoint = mo_ptPos-mo_ptLastPos;       // 鼠标移动向量

    QPoint pos = this->pos();                       // 窗口原位置
    QSize size = this->geometry().size();           // 窗口原尺寸

    if(mo_hitSection == TopLeftSection)             // 上侧尺寸拖拽
    {
        //qDebug() << "TopHittest Update";
        size -= QSize(movePoint.x(), movePoint.y());
        // 窗口尺寸最小值判断
        if(size.width()<=this->minimumWidth())
            movePoint.setX(0);
        if(size.height()<=this->minimumHeight())
            movePoint.setY(0);
        pos = pos + QPoint(movePoint.x(),movePoint.y());

        move(pos);
        resize(size);
    }
    else if(mo_hitSection == TopSection)            // 上侧尺寸拖拽
    {
        //qDebug() << "TopHittest Update";
        size -= QSize(0, movePoint.y());
        // 窗口尺寸最小值判断
        if(size.width()<=this->minimumWidth())
            movePoint.setX(0);
        if(size.height()<=this->minimumHeight())
            movePoint.setY(0);
        pos = pos + QPoint(0,movePoint.y());

        move(pos);
        resize(size);
    }
    else if(mo_hitSection == TopRightSection)       // 右上角尺寸拖拽
    {
        //qDebug() << "ToprightHittest Update";
        size -= QSize(-movePoint.x(), movePoint.y());
        // 窗口尺寸最小值判断
        if(size.width()<=this->minimumWidth())
            movePoint.setX(0);
        if(size.height()<=this->minimumHeight())
            movePoint.setY(0);
        pos = pos + QPoint(0,movePoint.y());
        this->move(pos);
        this->resize(size);
    }
    else if(mo_hitSection == LeftSection)           // 左侧尺寸拖拽
    {
        //qDebug() << "LeftHittest Update";
        size -= QSize(movePoint.x(), 0);
        // 窗口尺寸最小值判断
        if(size.width()<=this->minimumWidth())
            movePoint.setX(0);
        if(size.height()<=this->minimumHeight())
            movePoint.setY(0);
        pos = pos + QPoint(movePoint.x(),0);
        this->move(pos);
        this->resize(size);
    }
    else if(mo_hitSection == RightSection)          // 右侧尺寸拖拽
    {
        //qDebug() << "RightHittest Update";
        size += QSize(movePoint.x(), 0);
        this->move(pos);
        this->resize(size);
    }
    else if(mo_hitSection == BottomLeftSection)     // 左下角尺寸拖拽
    {
        //qDebug() << "BottomleftHittest Update";
        size += QSize(-movePoint.x(), movePoint.y());
        // 窗口尺寸最小值判断
        if(size.width()<=this->minimumWidth())
            movePoint.setX(0);
        if(size.height()<=this->minimumHeight())
            movePoint.setY(0);
        pos = pos + QPoint(movePoint.x(),0);
        this->move(pos);
        this->resize(size);
    }
    else if(mo_hitSection == BottomSection)         // 下侧尺寸拖拽
    {
        //qDebug() << "BottomHittest Update";
        size += QSize(0, movePoint.y());
        this->move(pos);
        this->resize(size);
    }
    else if(mo_hitSection == BottomRightSection)    // 右下角尺寸拖拽
    {
        //qDebug() << "BottomRightHittest Update";
        size += QSize(movePoint.x(), movePoint.y());
        this->move(pos);
        this->resize(size);
    }

    // 更新鼠标跟踪绝对位置
    mo_ptLastPos = mo_ptPos;
    mo_rctResPos = frameGeometry();
}

// 碰撞检测&更新光标形状
void XWindow::hitTest()
{
    if(mo_blMaximised)  return;
    if(!mo_blResizable) return;
    // 构造碰撞检测矩形 开始
    QRect rect;
    rect = this->rect();

    QRect   topLeftRect(rect.topLeft(),
                        QSize(mo_ntLeftHitWidth,
                              mo_ntTopHitWidth));

    QRect   topRect(rect.topLeft()+QPoint(mo_ntLeftHitWidth,0),
                    QSize(rect.width()-mo_ntLeftHitWidth-mo_ntRightHitWidth,
                          mo_ntTopHitWidth));

    QRect   topRightRect(rect.topRight()-QPoint(mo_ntRightHitWidth,
                                                0),
                         QSize(mo_ntRightHitWidth,
                               mo_ntTopHitWidth));

    QRect   leftRect(rect.topLeft()+QPoint(0,mo_ntTopHitWidth),
                     QSize(mo_ntLeftHitWidth,
                           rect.height()-mo_ntTopHitWidth-mo_ntBottomHitWidth));

    QRect   rightRect(rect.topRight()+
                      QPoint(-mo_ntRightHitWidth+1,
                             mo_ntTopHitWidth),
                      QSize(mo_ntRightHitWidth,
                            rect.height()-mo_ntTopHitWidth-mo_ntBottomHitWidth));

    QRect   bottomLeftRect(rect.bottomLeft()-QPoint(0,mo_ntBottomHitWidth),
                           QSize(mo_ntLeftHitWidth,
                                 mo_ntBottomHitWidth));

    QRect   bottomRect(rect.bottomLeft()+QPoint(mo_ntLeftHitWidth,
                                                -mo_ntBottomHitWidth+1),
                       QSize(rect.width()-mo_ntLeftHitWidth-mo_ntRightHitWidth,
                             mo_ntBottomHitWidth));

    QRect   bottomRightRect(rect.bottomRight()+QPoint(-mo_ntRightHitWidth+1,
                                                      -mo_ntBottomHitWidth+1),
                            QSize(mo_ntRightHitWidth,
                                  mo_ntBottomHitWidth));
    // 构造碰撞检测矩形 结束

    // 碰撞检测 开始
    if(mo_blPressed &&(mo_hitSection != NoSection)) return;

    if(topLeftRect.contains(mo_ptOffset))
    {
        if(mo_hitSection != TopLeftSection)
            //qDebug() << "TopLeft Rect";

        setCursor(QCursor(Qt::SizeFDiagCursor));
        mo_hitSection = TopLeftSection;
    }

    else if(topRect.contains(mo_ptOffset))
    {
        if(mo_hitSection != TopSection)
            //qDebug() << "Top Rect";

        setCursor(QCursor(Qt::SizeVerCursor));
        mo_hitSection = TopSection;
    }

    else if(topRightRect.contains(mo_ptOffset))
    {
        if(mo_hitSection != TopRightSection)
            //qDebug() << "TopRight Rect";

        setCursor(QCursor(Qt::SizeBDiagCursor));
        mo_hitSection = TopRightSection;
    }

    else if(leftRect.contains(mo_ptOffset))
    {
        if(mo_hitSection != LeftSection)
            //qDebug() << "Left Rect";

        setCursor(QCursor(Qt::SizeHorCursor));
        mo_hitSection = LeftSection;
    }

    else if(rightRect.contains(mo_ptOffset))
    {
        if(mo_hitSection != RightSection)
            //qDebug() << "Right Rect";

        setCursor(QCursor(Qt::SizeHorCursor));
        mo_hitSection = RightSection;
    }

    else if(bottomLeftRect.contains(mo_ptOffset))
    {
        if(mo_hitSection != BottomLeftSection)
            //qDebug() << "BottomLeft Rect";

        setCursor(QCursor(Qt::SizeBDiagCursor));
        mo_hitSection = BottomLeftSection;
    }

    else if(bottomRect.contains(mo_ptOffset))
    {
        if(mo_hitSection != BottomSection)
            //qDebug() << "Bottom Rect";

        setCursor(QCursor(Qt::SizeVerCursor));
        mo_hitSection = BottomSection;
    }

    else if(bottomRightRect.contains(mo_ptOffset))
    {
        if(mo_hitSection != BottomRightSection)
            //qDebug() << "BottomRight Rect";

        setCursor(QCursor(Qt::SizeFDiagCursor));
        mo_hitSection = BottomRightSection;
    }

    else
    {
        if(mo_hitSection != NoSection)
            //qDebug() << "No Rect";

        setCursor(QCursor(Qt::ArrowCursor));
        mo_hitSection = NoSection;
    }
    // 碰撞检测 结束
}

/// XWindow 事件响应

// 通用事件
bool XWindow::event(QEvent *event)
{
    // 仅处理主窗口激活事件
    switch(event->type())
    {
    case QEvent::WindowActivate:
        emit activationChanged(true);
        return true;
    case QEvent::WindowDeactivate:
        emit activationChanged(false);
        return true;
    default:
        return QWidget::event(event);
    }
}

// 键盘事件
void XWindow::keyPressEvent(QKeyEvent *event)
{
    // ESC 按键按下关闭窗口,效果等同于关闭按钮
    if(event->modifiers() == Qt::NoModifier)
    {
        if(event->key() == Qt::Key_Escape)
        {
            //qDebug()<< "ESC Pressed";
            this->close();
        }
    }
    event->accept();
}


// 鼠标按下事件
void XWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //qDebug() << "LBtn Pressed";
        mo_ptPressedOffset = event->pos();
        mo_ptOffset = mo_ptPressedOffset;
        mo_ptLastPos = event->globalPos();
        mo_ptPos = mo_ptLastPos;
        mo_blPressed = true;
    }
}

// 鼠标抬起事件
void XWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //qDebug() << "LBtn Released";
        mo_ptPressedOffset = event->pos();
        mo_ptOffset = mo_ptPressedOffset;
        mo_blPressed = false;
        hitTest();
    }
}

// 鼠标移动事件
void XWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 更新鼠标相对位置和绝对位置
    mo_ptOffset = event->pos();
    mo_ptPos = event->globalPos();
    if(!mo_blPressed)   hitTest();

    if(mo_blPressed)
    {
        if(mo_hitSection == NoSection)
            moveWindow();
        else
            resizeWindow();
    }
}

// 关闭事件
void XWindow::closeEvent(QCloseEvent *)
{
    if(mo_evenLoop.isRunning())
        mo_evenLoop.exit();
}

// 尺寸事件
void XWindow::resizeEvent(QResizeEvent *event)
{
    event->accept();
}

// 移动事件
void XWindow::moveEvent(QMoveEvent *event)
{
    event->accept();
}

/// 槽函数

// 最小化窗口
void XWindow::onMinimize()
{
    showMinimized();
}

// 最大化窗口
void XWindow::onMaximize()
{
    if(!mo_blMaximised)
    {
        // 保存最大化前的窗口位置
        mo_rctResPos = frameGeometry();

        // 取消阴影
        mo_ntRtmShaowWidth = 0;

        // 重置主布局
        reLayout();

        // 获取桌面矩形区，最大化窗口
        QRect desktopRect = QApplication::desktop()->availableGeometry();
        QRect FactRect = QRect(desktopRect.x(), desktopRect.y(), desktopRect.width(), desktopRect.height());
        setGeometry(FactRect);

        // 更新最大化标志
        mo_blMaximised = true;
    }
}

// 恢复窗口
void XWindow::onRestore()
{
    if(mo_blMaximised)
    {
        //qDebug() << "toRestore";

        // 恢复阴影
        mo_ntRtmShaowWidth = mo_ntShadowWidth;

        setGeometry(mo_rctResPos);

        // 重置主布局
        reLayout();

        mo_blMaximised = false;
    }
}

// 关闭窗口
void XWindow::onClose()
{
    close();
}

// 窗口激活事件响应
void XWindow::onActivationChanged(bool activated)
{
    if(activated)
    {       
        mo_colorShadow.setHslF(mo_colorShadow.hslHueF(), 1.0, mo_colorShadow.lightnessF());
        reLayout();
        //qDebug() << "Activated";
    }
    else
    {      
        mo_colorShadow.setHslF(mo_colorShadow.hslHueF(), 0.5, mo_colorShadow.lightnessF());
        reLayout();
        //qDebug() << "Deactivated";
    }
}

// 设置主题颜色
void XWindow::setThemeColor(QColor color)
{
    mo_colorTheme = color;
    if(Q_LIKELY(mp_frameBorder))
    {
        mp_frameBorder->removeBackgroundImage();
        mp_frameBorder->setBackgroundColor(color, color);
    }
}

// 设置背景图片
void XWindow::setBackgroundImage(QPixmap pixmap)
{
    if(Q_LIKELY(mp_frameBorder))
    {
        mp_frameBorder->setBackgroundImage(pixmap);
        mp_frameBorder->setBackgroundColor(Qt::transparent, Qt::transparent);
    }
    if(Q_LIKELY(mp_frameTitle))     mp_frameTitle->setBackgroundColor(Qt::transparent, Qt::transparent);
    if(Q_LIKELY(mp_frameClient))    mp_frameTitle->setBackgroundColor(Qt::transparent, Qt::transparent);
}

// 设置主题透明度
void XWindow::setThemeAlpha(int ntAlpha)
{    
    QColor color = clientFrame()->getBackgroundColor();
    color.setAlpha(ntAlpha);
    clientFrame()->setBackgroundColor(color, color);
}



