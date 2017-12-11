#include <QDebug>
#include <QCursor>

#include "component.h"
#include "lcomponent.h"
#include "ui_component.h"

Component::Component(const int nComponentId, QWidget *parent)
    : QWidget(parent)
    , m_nMyComponentId(nComponentId)
    , ui(new Ui::Component)
    , m_bMousePressedInTitle(false)
    , m_bMousePressedInBorder(false)

    , m_bHorRelatived(false)
    , m_bVerRelatived(false)

    , m_bHorStick_s(false)
    , m_bVerStick_s(false)
    , m_bHorStick_c(false)
    , m_bVerStick_c(false)

    , m_nTitleHeight(CM_TITLE_HEIGHT)                   //原件标题栏高度
    , m_nBorderWidth(DEFAULT_BORDER_WIDTH)              //边界宽度
    , m_nMagneticOffset(DEFAULT_MAGNETIC_OFFSET)        //磁性效力范围
    , m_nErrorRange(DEFAULT_ERROR_RANGE)                //脱离磁力误差范围
    , m_nToolBarWidth(DEFAULT_TOOLBAR_WIDTH)            //所在容器ToolBar宽度
    , m_nStatusBarHeight(DEFAULT_STATUS_HEIGHT)         //所在容器StatusBar高度

    , m_nMoveCount(0)

    , m_eMousePos(mpCenter)
{
    ui->setupUi(this);
    initComponent();
}

Component::~Component()
{
    delete ui;
}

void Component::setBorderWidth(int nBorderWidth)
{
    m_nBorderWidth = nBorderWidth;
}

void Component::setMagneticOffset(int nMagneticOffset)
{
    m_nMagneticOffset = nMagneticOffset;
}

void Component::setErrorRange(int nErrorRange)
{
    m_nErrorRange = nErrorRange;
}

void Component::setToolBarWidth(int nToolBarWidth)
{
    m_nToolBarWidth = nToolBarWidth;
}

void Component::setStatusBarHeight(int nStatusBarHeight)
{
    m_nStatusBarHeight = nStatusBarHeight;
}

bool Component::event(QEvent* evt)
{
    // 检查光标
    if (!m_bMousePressedInBorder && m_eMousePos != mpCenter && evt->type() == QEvent::ToolTip)
    {
        m_eMousePos = mpCenter;
        setCursor(Qt::ArrowCursor);
    }

    return QWidget::event(evt);
}

void Component::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        updateMousePressedData(event);

        if (mouseOnWinBorder(event->pos()))
        {
            updateDataOnBorder(event);
        }
        else if (ui->qwTitleBar->geometry().contains(event->pos()))
        {
            updateDataOnTitleBar(event);
        }
    }

    QWidget::mousePressEvent(event);
}

void Component::mouseMoveEvent(QMouseEvent *event)
{
    updateMouseLeftLimit();

    if (m_bMousePressedInTitle)
    {
        event->accept();
        limitMouseArea();
        resetDragData(event);
        for (int i = 0; i < m_lComponent.size(); i++)
        {
            if (m_lComponent[i] != nullptr && i != m_nMyComponentId)
            {
                minBoundaryToComponent(m_rParentRect, m_lComponent[i]->geometry(), geometry(), event);

                if (m_bHorRelatived && m_bVerRelatived)
                {
                    break;
                }
            }
        }

        if ((!m_bHorStick_c && !m_bVerStick_c) && (!m_bHorRelatived && !m_bVerRelatived))
        {
            minBoundaryToVessel(m_rParentRect, geometry(), event);
        }
    }
    else if (m_bMousePressedInBorder)
    {
        event->accept();
        limitMouseArea();
        changeSize(event);
    }
    else
    {
        if (mouseOnWinBorder(event->pos()))
        {
            // 改变光标形状
            event->accept();
            setMouseResizeCursor(event->pos());
        }
        else
        {
            // 还原光标形状
            setCursor(QCursor(Qt::ArrowCursor));
        }
    }

    QWidget::mouseMoveEvent(event);
}

void Component::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bMousePressedInTitle = false;
        m_bMousePressedInBorder = false;
    }

    QWidget::mouseReleaseEvent(event);
}

void Component::paintEvent(QPaintEvent *event)
{
    QPixmap m_LeftBorder(":/images/win/win_border_left.png");
    QPixmap m_RightBorder(":/images/win/win_border_right.png");
    QPixmap m_TopBorder(":/images/win/win_border_top.png");
    QPixmap m_BottomBorder(":/images/win/win_border_bottom.png");

    QPixmap m_TopLeftCorner("images/win/win_corner_lefttop.png");
    QPixmap m_BottomLeftCorner("images/win/win_corner_bottomleft");
    QPixmap m_TopRightCorner("images/win/win_corner_topright.png");
    QPixmap m_BottomRightCorner("images/win/win_corner_rightbottom.png");

    QPainter painter(this);

    int width = geometry().width();
    int height = geometry().height();

    painter.drawPixmap(0, m_nBorderWidth + m_nTitleHeight, m_nBorderWidth, height - 2 * m_nBorderWidth - m_nTitleHeight,
        m_LeftBorder, 0, 0, m_nBorderWidth, m_nBorderWidth);
    painter.drawPixmap(width - m_nBorderWidth, m_nBorderWidth + m_nTitleHeight, m_nBorderWidth, height - 2 * m_nBorderWidth - m_nTitleHeight,
        m_RightBorder, 0, 0, m_nBorderWidth, m_nBorderWidth);
    painter.drawPixmap(m_nBorderWidth, 0, width - 2 * m_nBorderWidth, m_nBorderWidth,
        m_TopBorder, 0, 0, m_nBorderWidth, m_nBorderWidth);
    painter.drawPixmap(m_nBorderWidth, height - m_nBorderWidth, width - 2 * m_nBorderWidth, m_nBorderWidth,
        m_BottomBorder, 0, 0, m_nBorderWidth, m_nBorderWidth);

    painter.drawPixmap(0, 0, m_nBorderWidth, m_nBorderWidth + m_nTitleHeight,
        m_TopLeftCorner, 0, 0, m_nBorderWidth, m_nTitleHeight - 1);
    painter.drawPixmap(0, height - m_nBorderWidth, m_nBorderWidth, m_nBorderWidth,
        m_BottomLeftCorner, 0, 0, m_nBorderWidth, m_nBorderWidth);
    painter.drawPixmap(width - m_nBorderWidth, 0, m_nBorderWidth, m_nBorderWidth + m_nTitleHeight,
        m_TopRightCorner, 0, 0, m_nBorderWidth, m_nBorderWidth + m_nTitleHeight);
    painter.drawPixmap(width - m_nBorderWidth, height - m_nBorderWidth, m_nBorderWidth, m_nBorderWidth,
        m_BottomRightCorner, 0, 0, m_nBorderWidth, m_nBorderWidth);

    QWidget::paintEvent(event);
}

void Component::setMouseResizeCursor(const QPoint& pt)
{
    if (rightBorder().contains(pt) && bottomBorder().contains(pt))
    {
        // 右下角
        m_eMousePos = mpRightBottom;
        setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if (rightBorder().contains(pt) && topBorder().contains(pt))
    {
        // 右上角
        m_eMousePos = mpRightTop;
        setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if (leftBorder().contains(pt) && bottomBorder().contains(pt))
    {
        // 左下角
        m_eMousePos = mpLeftBottom;
        setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if (leftBorder().contains(pt) && topBorder().contains(pt))
    {
        // 左上角
        m_eMousePos = mpLeftTop;
        setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if (rightBorder().contains(pt))
    {
        // 右边
        m_eMousePos = mpRight;
        setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (bottomBorder().contains(pt))
    {
        // 底边
        m_eMousePos = mpBottom;
        setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if (leftBorder().contains(pt))
    {
        // 左边
        m_eMousePos = mpLeft;
        setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (topBorder().contains(pt))
    {
        // 上边
        m_eMousePos = mpTop;
        setCursor(QCursor(Qt::SizeVerCursor));
    }
    else
    {
        m_eMousePos = mpCenter;
        setCursor(QCursor(Qt::ArrowCursor));
    }
}

void Component::initComponent()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setMouseTracking(true);
    ui->qwTitleBar->setMouseTracking(true);
    ui->qwContextArea->setMouseTracking(true);
}

void Component::updateMousePressedData(QMouseEvent *event)
{
    m_qpMousePressPoint = event->pos();
    m_rParentRect = parentWidget()->geometry();
    m_lComponent = static_cast<LComponent*>(parentWidget())->getComponentList();
}

void Component::updateDataOnBorder(QMouseEvent *event)
{
    event->accept();
    m_bMousePressedInBorder = true;
    m_pDragMoveOffset = rect().bottomRight() - event->pos();
}

void Component::updateDataOnTitleBar(QMouseEvent *event)
{
    event->accept();
    m_bMousePressedInTitle = true;
    m_pDragPosition = event->pos();
}

void Component::updateMouseLeftLimit()
{
    m_rMouseLimitRect.setLeft(m_rParentRect.x() + m_nToolBarWidth);
    m_rMouseLimitRect.setRight(m_rParentRect.x() + m_rParentRect.width());
    m_rMouseLimitRect.setTop(m_rParentRect.y());
    m_rMouseLimitRect.setBottom(m_rParentRect.y() + m_rParentRect.height() - m_nStatusBarHeight);
}

void Component::limitMouseArea()
{
    if (QCursor::pos().x() < m_rMouseLimitRect.left())
    {
        QCursor::setPos(m_rMouseLimitRect.left(), QCursor::pos().y());
    }

    if (QCursor::pos().x() > m_rMouseLimitRect.right())
    {
        QCursor::setPos(m_rMouseLimitRect.right(), QCursor::pos().y());
    }


    if (QCursor::pos().y() < m_rMouseLimitRect.top())
    {
        QCursor::setPos(QCursor::pos().x(), m_rMouseLimitRect.top());
    }

    if (QCursor::pos().y() > m_rMouseLimitRect.bottom())
    {
        QCursor::setPos(QCursor::pos().x(), m_rMouseLimitRect.bottom());
    }
}

void Component::resetDragData(QMouseEvent *event)
{
    m_bHorRelatived = false;
    m_bVerRelatived = false;
    m_qpDiffPos = event->pos() - m_qpMousePressPoint;
}

void Component::minBoundaryToComponent(const QRect &parentRect, const QRect &bechmarkRect, const QRect &targetRect, QMouseEvent *event)
{
    Q_UNUSED(event);

    // parent component's geometry info
    int parentLeft = parentRect.left();
    int parentRight = parentRect.right();
    int parentTop = parentRect.top();
    int parentBottom = parentRect.bottom();
    // other component's geometry info
    int bechmarkLeft = bechmarkRect.left();
    int bechmarkRight = bechmarkRect.right();
    int bechmarkTop = bechmarkRect.top();
    int bechmarkBottom = bechmarkRect.bottom();
    // this component's geometry info
    int targetLeft = targetRect.left();
    int targetRight = targetRect.right();
    int targetTop = targetRect.top();
    int targetBottom = targetRect.bottom();

    QPoint finalPosition;
    m_bHorStick_c = false;
    m_bVerStick_c = false;

    int nBreakeStickOffset_c = m_nMagneticOffset + m_nErrorRange;

    int nLeftMagneticPos = pos().x() + parentLeft + m_nToolBarWidth - targetLeft;
    int nRightMagneticPos = pos().x() + parentRight - targetRight;
    int nTopMagneticPos = pos().y() + parentTop - targetTop;
    int nBottomMagneticPos = pos().y() + parentBottom - m_nStatusBarHeight - targetBottom;

    int nRightDistanceOfVesselLeft = bechmarkLeft - targetRight;
    int nLeftMagneticPos_c = pos().x() + nRightDistanceOfVesselLeft;
    int nLeftDistanceOfVesselRight = bechmarkRight - targetLeft;
    int nRightMagneticPos_c = pos().x() + nLeftDistanceOfVesselRight;

    int nBottomDistanceOfVesselTop = bechmarkTop - targetBottom ;
    int nTopMagneticPos_c = pos().y() + nBottomDistanceOfVesselTop;
    int nTopDistanceOfVesselBottom = bechmarkBottom  - targetTop;
    int nBottomMagneticPos_c = pos().y() + nTopDistanceOfVesselBottom;

    if (qAbs(m_qpDiffPos.x()) < nBreakeStickOffset_c
        || m_bVerStick_s
        )
    {
        if (!m_bHorRelatived)
        {
            //horizontal-1:right to left
            if (qAbs(nRightDistanceOfVesselLeft) < m_nMagneticOffset
                && pos().y() >= nTopMagneticPos_c && pos().y() <= nBottomMagneticPos_c
                )
            {
                if (nLeftMagneticPos <= nLeftMagneticPos_c)
                {
                    if (m_bVerRelatived)
                    {
                        finalPosition.setX(nLeftMagneticPos_c);
                        finalPosition.setY(pos().y());
                    }
                    else if ((pos().y() + m_qpDiffPos.y()) >= nTopMagneticPos
                        && (pos().y() + m_qpDiffPos.y()) <= nBottomMagneticPos)
                    {
                        finalPosition.setX(nLeftMagneticPos_c);
                        finalPosition.setY(pos().y() + m_qpDiffPos.y());
                    }
                    else
                    {
                        finalPosition.setX(nLeftMagneticPos_c);
                        finalPosition.setY(pos().y());
                    }
                    m_bHorStick_c |= true;
                    m_bHorRelatived |= true;
                }
            }
            //horizontal-2:left to right
            if (qAbs(nLeftDistanceOfVesselRight) < m_nMagneticOffset
                && pos().y() >= nTopMagneticPos_c && pos().y() <= nBottomMagneticPos_c
                )
            {
                if (nRightMagneticPos >= nRightMagneticPos_c)
                {
                    if (m_bVerRelatived)
                    {
                        finalPosition.setX(nRightMagneticPos_c);
                        finalPosition.setY(pos().y());
                    }
                    else if ((pos().y() + m_qpDiffPos.y()) >= nTopMagneticPos
                        && (pos().y() + m_qpDiffPos.y()) <= nBottomMagneticPos)
                    {
                        finalPosition.setX(nRightMagneticPos_c);
                        finalPosition.setY(pos().y() + m_qpDiffPos.y());
                    }
                    else
                    {
                        finalPosition.setX(nRightMagneticPos_c);
                        finalPosition.setY(pos().y());
                    }
                    m_bHorStick_c |= true;
                    m_bHorRelatived |= true;
                }
            }
        }
    }

    if (qAbs(m_qpDiffPos.y()) < nBreakeStickOffset_c
        || m_bHorStick_s
        )
    {
        if (!m_bVerRelatived)
        {
            //veritcal-1:bottom to top
            if (qAbs(nBottomDistanceOfVesselTop) < m_nMagneticOffset
                && pos().x() >= nLeftMagneticPos_c && pos().x() <= nRightMagneticPos_c
                )
            {
                if (nTopMagneticPos <= nTopMagneticPos_c)
                {
                    if (m_bHorRelatived)
                    {
                        finalPosition.setX(pos().x());
                        finalPosition.setY(nTopMagneticPos_c);
                    }
                    else if ((pos().x() + m_qpDiffPos.x()) >= nLeftMagneticPos
                        && (pos().x() + m_qpDiffPos.x()) <= nRightMagneticPos)
                    {
                        finalPosition.setX(pos().x() + m_qpDiffPos.x());
                        finalPosition.setY(nTopMagneticPos_c);
                    }
                    else
                    {
                        finalPosition.setX(pos().x());
                        finalPosition.setY(nTopMagneticPos_c);
                    }
                    m_bVerStick_c |= true;
                    m_bVerRelatived |= true;
                }
            }
            //veritcal-2:top to bottom
            if (qAbs(nTopDistanceOfVesselBottom) < m_nMagneticOffset
                && pos().x() >= nLeftMagneticPos_c && pos().x() <= nRightMagneticPos_c
                )
            {
                if (nBottomMagneticPos >= nBottomMagneticPos_c)
                {
                    if (m_bHorRelatived)
                    {
                        finalPosition.setX(pos().x());
                        finalPosition.setY(nBottomMagneticPos_c);
                    }
                    else if ((pos().x() + m_qpDiffPos.x()) >= nLeftMagneticPos
                        && (pos().x() + m_qpDiffPos.x()) <= nRightMagneticPos)
                    {
                        finalPosition.setX(pos().x() + m_qpDiffPos.x());
                        finalPosition.setY(nBottomMagneticPos_c);
                    }
                    else
                    {
                        finalPosition.setX(pos().x());
                        finalPosition.setY(nBottomMagneticPos_c);
                    }
                    m_bVerStick_c |= true;
                    m_bVerRelatived |= true;
                }
            }
        }
    }

    if (m_bHorStick_c || m_bVerStick_c)
    {
        move(finalPosition);
        m_bHorStick_s = false;
        m_bVerStick_s = false;
    }
}

void Component::minBoundaryToVessel(const QRect &bechmarkRect, const QRect &targetRect, QMouseEvent *event)
{
    int nMousePosX = event->pos().x();
    int nMousePosY = event->pos().y();

    // vessel's geometry info
    int bechmarkLeft = bechmarkRect.left();
    int bechmarkRight = bechmarkRect.right();
    int bechmarkTop = bechmarkRect.top();
    int bechmarkBottom = bechmarkRect.bottom();
    // component's geometry info
    int targetLeft = targetRect.left();
    int targetRight = targetRect.right();
    int targetTop = targetRect.top();
    int targetBottom = targetRect.bottom();

    QPoint finalPosition;
    m_bHorStick_s = false;
    m_bVerStick_s = false;

    int nBreakeStickOffset = m_nMagneticOffset + m_nErrorRange;

    int nLeftDistanceOfVesselLeft = bechmarkLeft + m_nToolBarWidth - targetLeft;
    int nLeftMagneticPos = pos().x() + nLeftDistanceOfVesselLeft;
    int nRightDistanceOfVesselRight = bechmarkRight - targetRight;
    int nRightMagneticPos = pos().x() + nRightDistanceOfVesselRight;

    int nTopDistanceOfVesselTop = bechmarkTop - targetTop;
    int nTopMagneticPos = pos().y() + nTopDistanceOfVesselTop;
    int nBottomDistanceOfVesselBottom = bechmarkBottom - m_nStatusBarHeight - targetBottom;
    int nBottomMagneticPos = pos().y() + nBottomDistanceOfVesselBottom;

    if (qAbs(m_qpDiffPos.x()) < nBreakeStickOffset
        && qAbs(m_qpDiffPos.y()) < nBreakeStickOffset)
    {
        //horizontal-1:left to left
        if (qAbs(nLeftDistanceOfVesselLeft) < m_nMagneticOffset)
        {
            if (m_bVerStick_s || m_bVerRelatived)
                finalPosition.setX(nLeftMagneticPos);
            else
            {
                finalPosition.setX(nLeftMagneticPos);
                finalPosition.setY(pos().y() + m_qpDiffPos.y());
            }
            m_bHorStick_s |= true;
        }
        //horizontal-2:right to right
        if (qAbs(nRightDistanceOfVesselRight) < m_nMagneticOffset)
        {
            if (m_bVerStick_s || m_bVerRelatived)
                finalPosition.setX(nRightMagneticPos);
            else
            {
                finalPosition.setX(nRightMagneticPos);
                finalPosition.setY(pos().y() + m_qpDiffPos.y());
            }
            m_bHorStick_s |= true;
        }

        //veritcal-1:top to top
        if (qAbs(nTopDistanceOfVesselTop) < m_nMagneticOffset)
        {
            if (m_bHorStick_s)
                finalPosition.setY(nTopMagneticPos);
            else
            {
                finalPosition.setX(pos().x() + m_qpDiffPos.x());
                finalPosition.setY(nTopMagneticPos);
            }
            m_bVerStick_s |= true;
        }
        //veritcal-2:bottom to bottom
        if (qAbs(nBottomDistanceOfVesselBottom) < m_nMagneticOffset)
        {
            if (m_bHorStick_s)
                finalPosition.setY(nBottomMagneticPos);
            else
            {
                finalPosition.setX(pos().x() + m_qpDiffPos.x());
                finalPosition.setY(nBottomMagneticPos);
            }
            m_bVerStick_s |= true;
        }
    }

    if (m_bHorStick_s || m_bVerStick_s)
        move(finalPosition);
    else if ((pos() + m_qpDiffPos).x() > nLeftMagneticPos &&
        (pos() + m_qpDiffPos).x() < nRightMagneticPos
        && (pos() + m_qpDiffPos).y() > nTopMagneticPos &&
        (pos() + m_qpDiffPos).y() < nBottomMagneticPos
        )
        move(pos() + m_qpDiffPos);
    else
    {
        if (qAbs(nLeftDistanceOfVesselLeft) < qAbs(m_qpDiffPos.x())
            && nMousePosX < 0)
        {
            finalPosition.setX(nLeftMagneticPos);
            m_bHorStick_s |= true;
        }
        else if (qAbs(nRightDistanceOfVesselRight) < qAbs(m_qpDiffPos.x())
            && nMousePosX > 0)
        {
            finalPosition.setX(nRightMagneticPos);
            m_bHorStick_s |= true;
        }
        else
        {
            finalPosition.setX(pos().x());
        }

        if (qAbs(nTopDistanceOfVesselTop) < qAbs(m_qpDiffPos.y())
            && nMousePosY < 0)
        {
            finalPosition.setY(nTopMagneticPos);
            m_bVerStick_s |= true;
        }
        else if (qAbs(nBottomDistanceOfVesselBottom) < qAbs(m_qpDiffPos.y())
            && nMousePosY > 0)
        {
            finalPosition.setY(nBottomMagneticPos);
            m_bVerStick_s |= true;
        }
        else
        {
            finalPosition.setY(pos().y());
        }

        if ((pos() + m_qpDiffPos).y() > nTopMagneticPos
            && (pos() + m_qpDiffPos).y() < nBottomMagneticPos)
        {
            finalPosition.setY(pos().y() + m_qpDiffPos.y());
        }
        if ((pos() + m_qpDiffPos).x() > nLeftMagneticPos
            && (pos() + m_qpDiffPos).x() < nRightMagneticPos)
        {
            finalPosition.setX(pos().x() + m_qpDiffPos.x());
        }

        move(finalPosition);
    }
}

bool Component::mouseOnWinBorder(const QPoint& pt)
{
    return (rightBorder().contains(pt)
        || bottomBorder().contains(pt)
        || leftBorder().contains(pt)
        || topBorder().contains(pt));
}

void Component::changeSize(QMouseEvent* evt)
{
    QPoint p = evt->globalPos() + m_pDragMoveOffset;
    QPoint pp = evt->globalPos() - m_pDragPosition;

    QSize ms = calcMinSize(window()->sizeHint(), window()->minimumSizeHint(),
        window()->minimumSize(), window()->maximumSize(), window()->sizePolicy());
    int mw = ms.width();
    int mh = ms.height();

    QSize maxsize(window()->maximumSize());
    QSize mpsize(window()->geometry().right() - pp.x() + 1,
        window()->geometry().bottom() - pp.y() + 1);
    mpsize = mpsize.expandedTo(window()->minimumSize()).expandedTo(QSize(mw, mh)).boundedTo(maxsize);
    QPoint mp(window()->geometry().right() - mpsize.width() + 1,
        window()->geometry().bottom() - mpsize.height() + 1);

    QRect geom = window()->geometry();
    switch (m_eMousePos)
    {
    case mpLeftTop:
        geom = QRect(mp, window()->geometry().bottomRight());
        break;
    case mpRightBottom:
        geom = QRect(window()->geometry().topLeft(), p);
        break;
    case mpLeftBottom:
        geom = QRect(QPoint(mp.x(), window()->geometry().y()), QPoint(window()->geometry().right(), p.y()));
        break;
    case mpRightTop:
        geom = QRect(QPoint(window()->geometry().x(), mp.y()), QPoint(p.x(), window()->geometry().bottom()));
        break;
    case mpTop:
        geom = QRect(QPoint(window()->geometry().left(), mp.y()), window()->geometry().bottomRight());
        break;
    case mpBottom:
        geom = QRect(window()->geometry().topLeft(), QPoint(window()->geometry().right(), p.y()));
        break;
    case mpLeft:
        geom = QRect(QPoint(mp.x(), window()->geometry().top()), window()->geometry().bottomRight());
        break;
    case mpRight:
        geom = QRect(window()->geometry().topLeft(), QPoint(p.x(), window()->geometry().bottom()));
        break;
    case mpCenter:
        geom.moveTopLeft(pp);
        break;
    default:
        break;
    }

    geom = QRect(geom.topLeft(),
        geom.size().expandedTo(window()->minimumSize()).expandedTo(QSize(mw, mh)).boundedTo(maxsize));

    if (geom != window()->geometry())
    {
        window()->setGeometry(geom);
    }
}

QSize Component::calcMinSize(const QSize &sizeHint, const QSize &minSizeHint,
    const QSize &minSize, const QSize &maxSize,
    const QSizePolicy &sizePolicy)
{
    QSize s(0, 0);
    if (sizePolicy.horizontalPolicy() != QSizePolicy::Ignored)
    {
        if (sizePolicy.horizontalPolicy() & QSizePolicy::ShrinkFlag)
        {
            s.setWidth(minSizeHint.width());
        }
        else
        {
            s.setWidth(qMax(sizeHint.width(), minSizeHint.width()));
        }
    }

    if (sizePolicy.verticalPolicy() != QSizePolicy::Ignored)
    {
        if (sizePolicy.verticalPolicy() & QSizePolicy::ShrinkFlag)
        {
            s.setHeight(minSizeHint.height());
        }
        else
        {
            s.setHeight(qMax(sizeHint.height(), minSizeHint.height()));
        }
    }

    s = s.boundedTo(maxSize);

    if (minSize.width() > 0)
    {
        s.setWidth(minSize.width());
    }

    if (minSize.height() > 0)
    {
        s.setHeight(minSize.height());
    }

    return s.expandedTo(QSize(0, 0));
}

QRect Component::leftBorder() const
{
    return QRect(0, 0, m_nBorderWidth, height());
}

QRect Component::rightBorder() const
{
    return QRect(width() - m_nBorderWidth, 0, m_nBorderWidth, height());
}

QRect Component::topBorder() const
{
    return QRect(0, 0, width(), m_nBorderWidth);
}

QRect Component::bottomBorder() const
{
    return QRect(0, height() - m_nBorderWidth, width(), m_nBorderWidth);
}

void Component::on_btnClose_clicked()
{
    emit onComponentClose(m_nMyComponentId);

    close();
}
