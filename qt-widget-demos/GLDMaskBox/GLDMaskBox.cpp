#include "GLDMaskBox.h"
#include "CommonUtil.h"
#include "custompushbutton.h"

#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <QPainter>
#include <QPointer>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

QPointer<GLDMaskBox> GLDMaskBox::m_pTipBox;

GLDMaskBox::GLDMaskBox(GLDMaskBoxParam & oTipBoxParam, QWidget *parent)
    : QWidget(parent)
    , m_labelIco(nullptr)
    , m_labelTextTitle(nullptr)
    , m_labelTextBody(nullptr)
    , m_timerClose(nullptr)
    , m_btnClose(nullptr)
    , m_animFadeOut(nullptr)
    , m_effectOpacity(nullptr)
{
    m_oTipBoxParam = oTipBoxParam;

    if (nullptr != oTipBoxParam.m_wgtOwner)
    {
        connect(oTipBoxParam.m_wgtOwner, SIGNAL(clicked()), this, SLOT(slotClose()));
    }

    this->setObjectName(QString("GLDMaskBox"));

    if (m_oTipBoxParam.m_wgtOwner)
    {
        this->setParent(m_oTipBoxParam.m_wgtOwner);
    }

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::SplashScreen /*| Qt::WindowStaysOnTopHint*/ | Qt::WindowType_Mask);
    this->setAttribute(Qt::WA_TranslucentBackground);

    QVBoxLayout* pMainLayout = new QVBoxLayout();
    pMainLayout->setContentsMargins(0, 4, 10, 14);
    this->setLayout(pMainLayout);

    QHBoxLayout* pCloseLayout = new QHBoxLayout();
    pCloseLayout->setContentsMargins(0, 8, 0, 0);

    m_btnClose = new QPushButton(this);
    m_btnClose->setFlat(true);
    connect(m_btnClose, &QPushButton::clicked, this, &GLDMaskBox::slotClose);

    pCloseLayout->addStretch();
    pCloseLayout->addWidget(m_btnClose);

    pMainLayout->addLayout(pCloseLayout);

    QHBoxLayout* pContentLayout = new QHBoxLayout();
    pMainLayout->addSpacing(-20);
    pMainLayout->addLayout(pContentLayout);

    QVBoxLayout* pContentLeftLayout = new QVBoxLayout();
    m_labelIco = new QLabel(this);

    pContentLeftLayout->addSpacing(6);
    pContentLeftLayout->addWidget(m_labelIco);
    pContentLeftLayout->addStretch();
    pContentLeftLayout->addSpacing(18);

    QVBoxLayout* pContentRightLayout = new QVBoxLayout();
    m_labelTextTitle = new QLabel(this);
    //m_labelTextTitle->setHidden(true);
    m_labelTextTitle->setOpenExternalLinks(true);
    m_labelTextTitle->setWordWrap(true);
    m_labelTextTitle->setAlignment(Qt::AlignTop);
    pContentRightLayout->addWidget(m_labelTextTitle);

    m_labelTextBody = new QLabel(this);

    QPalette palette;
    palette.setColor(QPalette::WindowText, m_oTipBoxParam.m_bodyColor);
    m_labelTextBody->setPalette(palette);

    m_labelTextBody->setWordWrap(true);
    m_labelTextBody->setAlignment(Qt::AlignTop);
    m_labelTextBody->setOpenExternalLinks(true);
    m_labelTextBody->setFont(m_oTipBoxParam.m_bodyFont);

    pContentRightLayout->addWidget(m_labelTextBody);

    pContentLayout->addSpacing(21);
    pContentLayout->addLayout(pContentLeftLayout, 0);
    pContentLayout->addLayout(pContentRightLayout, 1);
    pContentLayout->addSpacing(21);

    //this->setContentsMargins(10, 5, 10, 15);

    // 关闭定时器设置
    m_timerClose = new QTimer(this);
    connect(m_timerClose, SIGNAL(timeout()), this, SLOT(slotCloseTimer()));

    // 渐隐效果动画设置
    m_effectOpacity = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(m_effectOpacity);
    m_effectOpacity->setOpacity(1);
    m_animFadeOut = new QPropertyAnimation(m_effectOpacity, "opacity", this);
    m_animFadeOut->setStartValue(1);
    m_animFadeOut->setEndValue(0);
    //m_animFadeOut->setDuration(m_oTipBoxParam.m_nTimeFadeOut);
    m_animFadeOut->setEasingCurve(QEasingCurve::Linear);
    connect(m_animFadeOut, SIGNAL(finished()), this, SLOT(slotFadeout()));

    // 安装事件过滤器
    QWidget* wgt = m_oTipBoxParam.m_wgtOwner;
    while (wgt)
    {
        wgt->installEventFilter(this);
        wgt = wgt->parentWidget();
    }
}

QSize GLDMaskBox::sizeHint() const
{
    QSize sz;

    int textWidth = m_labelTextBody->fontMetrics().width(m_oTipBoxParam.m_strBody);
    //    int textHeight = m_labelTextBody->fontMetrics().ascent() + m_labelTextBody->fontMetrics().descent();
    int singalTextHeight = m_oTipBoxParam.m_nRowHeight;

    if (textWidth <= m_oTipBoxParam.m_nMaxWidth - 87)
    {
        sz.setWidth(87 + textWidth);
        sz.setHeight(64 + singalTextHeight);
    }
    else
    {
        QStringList list = m_oTipBoxParam.m_strBody.split("\n");

        if (list.count() == 1)
        {
            sz.setWidth(m_oTipBoxParam.m_nMaxWidth);

            if (textWidth % (m_oTipBoxParam.m_nMaxWidth - 87) == 0)
            {
                sz.setHeight(64 + singalTextHeight * (textWidth / (m_oTipBoxParam.m_nMaxWidth - 87)));
            }
            else
            {
                sz.setHeight(64 + singalTextHeight * (textWidth / (m_oTipBoxParam.m_nMaxWidth - 87) + 1));
            }
        }
        else
        {
            QStringList::iterator iter = list.begin();
            int rowCount = 0;
            int maxWidth = 0;

            while (iter != list.end())
            {
                int subTextWidth = m_labelTextBody->fontMetrics().width(*iter);

                if (subTextWidth % (m_oTipBoxParam.m_nMaxWidth - 87) != 0)
                {
                    ++rowCount;
                }
                rowCount += subTextWidth / (m_oTipBoxParam.m_nMaxWidth - 87);

                if (subTextWidth >= (m_oTipBoxParam.m_nMaxWidth - 87))
                {
                    maxWidth = m_oTipBoxParam.m_nMaxWidth - 87;
                }
                else
                {
                    if (maxWidth < subTextWidth)
                    {
                        maxWidth = subTextWidth;
                    }
                }
                iter++;
            }
            sz.setWidth(maxWidth + 87);
            sz.setHeight(64 + singalTextHeight * rowCount);
        }
    }

    return sz;
}

QPoint GLDMaskBox::calcPosOfOwner()
{
    QPoint pt(0, 0);

    do
    {
        // 计算owner位置对应屏幕中心的象限
        if (!m_oTipBoxParam.m_wgtOwner)
        {
            break;
        }

        QPoint ptGlobalOwnerCenter = m_oTipBoxParam.m_wgtOwner->mapToGlobal(
            m_oTipBoxParam.m_wgtOwner->rect().center());
        QPoint ptGlobalScreen = QApplication::desktop()->screenGeometry().center();
        QPoint ptDelta = ptGlobalOwnerCenter - ptGlobalScreen;

        if (ptDelta.x() >= 0 && ptDelta.y() <= 0)
        {
            // 第一象限
            pt = QPoint(ptGlobalOwnerCenter.x() - m_oTipBoxParam.m_wgtOwner->width()/2,
                            ptGlobalOwnerCenter.y() + m_oTipBoxParam.m_wgtOwner->height()/2);
            pt += QPoint(-this->width()/2, 0);
        }
        else if (ptDelta.x() <= 0 && ptDelta.y() <= 0)
        {
            // 第二象限
            pt = QPoint(ptGlobalOwnerCenter.x() + m_oTipBoxParam.m_wgtOwner->width()/2,
                            ptGlobalOwnerCenter.y() + m_oTipBoxParam.m_wgtOwner->height()/2);
            pt += QPoint(-this->width()/2, 0);
        }
        else if (ptDelta.x() <= 0 && ptDelta.y() >= 0)
        {
            // 第三象限
            pt = QPoint(ptGlobalOwnerCenter.x() + m_oTipBoxParam.m_wgtOwner->width()/2,
                            ptGlobalOwnerCenter.y() - m_oTipBoxParam.m_wgtOwner->height()/2);
            pt += QPoint(-this->width()/2, -this->height());
        }
        else if (ptDelta.x() >= 0 && ptDelta.y() >= 0)
        {
            // 第四象限
            pt = QPoint(ptGlobalOwnerCenter.x() - m_oTipBoxParam.m_wgtOwner->width()/2,
                        ptGlobalOwnerCenter.y() - m_oTipBoxParam.m_wgtOwner->height()/2);
            pt += QPoint(-this->width()/2, -this->height());
        }

        // 超出屏幕范围的校准
        QRect rcThis(pt, pt + QPoint(this->width(), this->height()));
        QRect rcScreen = QApplication::desktop()->screenGeometry();

        if (!rcScreen.contains(rcThis.topLeft()))
        {
            int nXOffset = rcThis.topLeft().x() - rcScreen.topLeft().x();
            int nYOffset = rcThis.topLeft().y() - rcScreen.topLeft().y();

            if (nXOffset < 0)
            {
                pt.setX(pt.x() - nXOffset);
            }

            if (nYOffset < 0)
            {
                pt.setY(pt.y() - nYOffset);
            }
        }
        else if (!rcScreen.contains(rcThis.topRight()))
        {
            int nXOffset = rcThis.topRight().x() - rcScreen.topRight().x();
            int nYOffset = rcThis.topRight().y() - rcScreen.topRight().y();

            if (nXOffset > 0)
            {
                pt.setX(pt.x() - nXOffset);
            }

            if (nYOffset < 0)
            {
                pt.setY(pt.y() - nYOffset);
            }
        }
        else if (!rcScreen.contains(rcThis.bottomLeft()))
        {
            int nXOffset = rcThis.bottomLeft().x() - rcScreen.bottomLeft().x();
            int nYOffset = rcThis.bottomLeft().y() - rcScreen.bottomLeft().y();

            if (nXOffset < 0)
            {
                pt.setX(pt.x() - nXOffset);
            }

            if (nYOffset > 0)
            {
                pt.setY(pt.y() - nYOffset);
            }
        }
        else if (!rcScreen.contains(rcThis.bottomRight()))
        {
            int nXOffset = rcThis.bottomRight().x() - rcScreen.bottomRight().x();
            int nYOffset = rcThis.bottomRight().y() - rcScreen.bottomRight().y();

            if (nXOffset > 0)
            {
                pt.setX(pt.x() - nXOffset);
            }

            if (nYOffset > 0)
            {
                pt.setY(pt.y() - nYOffset);
            }
        }

    } while(0);

    return pt;
}

void GLDMaskBox::showEvent(QShowEvent* event)
{
    G_UNUSED(event);

    if (!m_oTipBoxParam.m_wgtOwner)
    {
        return;
    }

    if (m_oTipBoxParam.m_nMaxWidth > 0)
    {
        this->setMaximumWidth(m_oTipBoxParam.m_nMaxWidth);
    }

    QIcon icon(m_oTipBoxParam.m_strCloseIcon);

    if (m_oTipBoxParam.m_bIsOverTimeShow)
    {
        m_btnClose->setIcon(icon);
        m_btnClose->setEnabled(true);
    }
    else
    {
        m_btnClose->setEnabled(false);
    }

    m_labelTextTitle->setFont(m_oTipBoxParam.m_titleFont);
    m_labelTextTitle->setText(m_oTipBoxParam.m_strTitle);

    m_labelTextBody->setFont(m_oTipBoxParam.m_bodyFont);
    m_labelTextBody->setText(m_oTipBoxParam.m_strBody);

    //为了设置行高,采用HTML,html换行为 <br/>
    m_oTipBoxParam.m_strBody.replace("\n", "<br/>");
    m_labelTextBody->setText(QString("<p style=\"line-height:%1px\">%2</p>")
        .arg(m_oTipBoxParam.m_nRowHeight).arg(m_oTipBoxParam.m_strBody));

    // 设置根据内容调整气泡提示的大小
    //this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    m_labelTextBody->adjustSize();

    QPixmap pxpIco;
    pxpIco.load(m_oTipBoxParam.m_strWarnIcon);

    if (!m_oTipBoxParam.m_sizeIcon.isEmpty())
    {
        pxpIco = pxpIco.scaled(m_oTipBoxParam.m_sizeIcon.width(), m_oTipBoxParam.m_sizeIcon.height(), Qt::KeepAspectRatio);
    }

    m_labelIco->setPixmap(pxpIco);

    m_animFadeOut->setDuration(m_oTipBoxParam.m_nTimeFadeOut);

    QWidget* pWgt = m_oTipBoxParam.m_wgtOwner;
    while (pWgt)
    {
        qDebug() << "objectName is:" << pWgt->objectName();
        pWgt->installEventFilter(this);
        pWgt = pWgt->parentWidget();
    }

    if (m_timerClose)
    {
        //m_timerClose->start(m_oTipBoxParam.m_nTimeRemain);
    }

    QWidget::showEvent(event);
}

void GLDMaskBox::slotClose()
{
    if (m_timerClose)
    {
        m_timerClose->stop();
    }

    this->close();
    this->deleteLater();
}

bool GLDMaskBox::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == this->m_oTipBoxParam.m_wgtOwner)
    {
        if (ev->type() == QEvent::Resize
                || ev->type() == QEvent::Move
                || ev->type() == QEvent::ParentChange
                || ev->type() == QEvent::Paint
                || ev->type() == QEvent::DragMove)
        {
            if (this->m_oTipBoxParam.m_wgtOwner->isMinimized())
            {
                this->hide();
            }

            this->update();
        }
    }

    return QWidget::eventFilter(obj, ev);
}

void GLDMaskBox::mousePressEvent(QMouseEvent *e)
{
    if (!m_oTipBoxParam.m_bIsOverTimeShow)
    {
        if (e->button() == Qt::LeftButton)
        {
            slotClose();
        }
    }
}

void GLDMaskBox::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);

    do{
        if (!m_oTipBoxParam.m_wgtOwner)
        {
            return;
        }

        this->move(calcPosOfOwner());

        // 设置渐变画刷
//        QRect rc = this->rect();
//        QLinearGradient linear(
//            rc.topLeft(),
//            rc.bottomLeft()
//            );
//        linear.setColorAt(0, QColor(247, 247, 250));
//        linear.setColorAt(0.5, QColor(240, 242, 247));
//        linear.setColorAt(1, QColor(233, 233, 242));


        //QPainter oPainter(this);
        //QPainterPath roundPath;
        //roundPath.addRect(parentWidget()->rect());
        //oPainter.setRenderHint(QPainter::Antialiasing);
        //oPainter.fillPath(roundPath, QColor(0, 0, 0, 100));
        //update();


        //const QString pxpStr = exePath() + "/images/Msg/target.png";
        //QPixmap pxpIco;
        //pxpIco.load(pxpStr);

        //QPainter p(&pxpIco);
        //QBrush b(QColor(0, 0, 0, 128)); // adjust color and alpha to taste
        //p.setBrush(b);
        //p.drawPath(path);



        //QPainter painter(this);
        //const QString pxpStr = exePath() + "/images/Msg/target.png";
        //painter.drawPixmap(0, 0, QPixmap(pxpStr));



        // 建造tip形状
        QPainterPath path = this->buildPathRoundRectTip();

        QPainter painter(this);
        painter.begin(this);

        painter.setRenderHint(QPainter::Antialiasing, true);
        QPen pen(QColor(0, 0, 0, 100));
        pen.setWidth(2);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.setBrush(QColor(127, 127, 127, 100));

        painter.drawPath(path);

//         painter.setRenderHint(QPainter::Antialiasing, true);
//         painter.setPen(Qt::black);
//         //painter.setBrush(linear);
//         painter.drawPath(path);

        painter.end();

    }while(0);
}

QPainterPath GLDMaskBox::buildPathRoundRectTip()
{
    // 建立圆角矩形tip路径
    QPainterPath path;

    do
    {
        QRect rc = this->rect();

        if (m_oTipBoxParam.m_arrowSize.isValid())
        {
            rc -= QMargins(m_oTipBoxParam.m_arrowSize.height(),
                           m_oTipBoxParam.m_arrowSize.height(),
                           m_oTipBoxParam.m_arrowSize.height(),
                           m_oTipBoxParam.m_arrowSize.height());
        }
        else
        {
            break;
        }

        if (!m_oTipBoxParam.m_wgtOwner)
        {
            break;
        }

        // 添加圆角矩形
        path.addRoundedRect(rc, 5, 5);

        // 计算箭头（按照屏幕坐标进行计算）

        // 计算第一个交点（与外围）
        QPoint ptOwnerCenter = m_oTipBoxParam.m_wgtOwner->mapToGlobal(
                    m_oTipBoxParam.m_wgtOwner->rect().center());
        QPoint ptThisCenter = this->mapToGlobal(this->rect().center());

        QLineF lineCenters(ptOwnerCenter, ptThisCenter);
        QRectF rcRing(this->mapToGlobal(this->rect().topLeft()),
                      this->mapToGlobal(this->rect().bottomRight()));

        QPointF pt1(0, 0);
        QPointF pt2(0, 0);

        if (!calcCrossLine2Rect(lineCenters, rcRing, pt1, pt2))
        {
            break;
        }

        QPoint ptArrow1 = pt1.isNull() ? pt2.toPoint() : pt1.toPoint();

        // 计算剩下两个交点（与内围）
        double dR = 0;
        double dAngle = 0;

        calcRadiusAndAngleOfPt2d(ptThisCenter, dR, dAngle, ptArrow1);
        QPointF ptNew1 = calcPtOfAngle2d(dR, dR, dAngle + 10, ptArrow1).toPoint();
        QPointF ptNew2 = calcPtOfAngle2d(dR, dR, dAngle - 10, ptArrow1).toPoint();

        QLineF line1(ptOwnerCenter, ptNew1);
        QLineF line2(ptOwnerCenter, ptNew2);

        QRectF rcInsideRing(this->mapToGlobal(rc.topLeft()), this->mapToGlobal(rc.bottomRight()));

        if (!calcCrossLine2Rect(line1, rcInsideRing, pt1, pt2))
        {
            break;
        }

        QPoint ptArrow2 = pt1.isNull() ? pt2.toPoint() : pt1.toPoint();

        if (!calcCrossLine2Rect(line2, rcInsideRing, pt1, pt2))
        {
            break;
        }

        QPoint ptArrow3 = pt1.isNull() ? pt2.toPoint() : pt1.toPoint();

        QVector<QPoint> ptsArrow;
        ptsArrow << mapFromGlobal(ptArrow1)
                 << mapFromGlobal(ptArrow2)
                 << mapFromGlobal(ptArrow3)
                 << mapFromGlobal(ptArrow1);

        QPolygonF polygon(ptsArrow);
        QPainterPath pathArrow;
        pathArrow.addPolygon(polygon);

        path += pathArrow;

    } while(0);

    return path;
}

void GLDMaskBox::slotCloseTimer()
{
    m_timerClose->stop();

    m_animFadeOut->start();
}

void GLDMaskBox::slotFadeout()
{
    this->close();
    this->deleteLater();
}

void GLDMaskBox::immediateCloseThis()
{
    QEventLoop eventloop;
    connect(this, SIGNAL(destroyed()), &eventloop, SLOT(quit()));
    this->slotClose();
}

GLDMaskBoxParam& GLDMaskBox::tipBoxParam()
{
    return m_oTipBoxParam;
}

GLDMaskBox* GLDMaskBox::showTipBox(QWidget* wgtOwner, const QString& strTitle, const QString& strBody)
{
    GLDMaskBox* pTip = nullptr;

    do
    {
        if (!wgtOwner)
        {
            break;
        }

        // 如果owner和内容相同,认为是同一个,不可反复弹出
        if (!GLDMaskBox::m_pTipBox.isNull())
        {
            if (wgtOwner == GLDMaskBox::m_pTipBox->tipBoxParam().m_wgtOwner
                && strBody == GLDMaskBox::m_pTipBox->tipBoxParam().m_strBody)
            {
                pTip = GLDMaskBox::m_pTipBox;
                break;
            }
        }


        if (!GLDMaskBox::m_pTipBox.isNull())
        {
            GLDMaskBox::m_pTipBox->immediateCloseThis();
        }

        GLDMaskBoxParam param;
        param.m_wgtOwner = wgtOwner;
        param.m_strTitle = strTitle;
        param.m_strBody = strBody;
        pTip = new GLDMaskBox(param);

        QWidget* pWidget = topParentWidget(wgtOwner);
        qDebug() << pWidget->objectName();

        GLDMaskBox::m_pTipBox = pTip;

        pTip->show();

    }while(0);

    return pTip;
}

GLDMaskBox* GLDMaskBox::showTipBox(GLDMaskBoxParam* pParam)
{
    GLDMaskBox* pTip = nullptr;

    do
    {
        if (!pParam)
        {
            break;
        }

        if (!pParam->m_wgtOwner)
        {
            break;
        }


        // 如果owner和内容相同，认为是同一个，不可反复弹出
//         if (!GLDTipBox::m_pTipBox.isNull())
//         {
//             if (pParam->m_wgtOwner == GLDTipBox::m_pTipBox->tipBoxParam().m_wgtOwner
//                 && pParam->m_strBody == GLDTipBox::m_pTipBox->tipBoxParam().m_strBody)
//             {
//                 pTip = GLDTipBox::m_pTipBox;
//                 break;
//             }
//         }
        // end

        if (!GLDMaskBox::m_pTipBox.isNull())
        {
            GLDMaskBox::m_pTipBox->immediateCloseThis();
        }

        pTip = new GLDMaskBox(*pParam);

        GLDMaskBox::m_pTipBox = pTip;

        pTip->show();

    }while(0);

    return pTip;
}

void GLDMaskBox::closeThis()
{
    if (!GLDMaskBox::m_pTipBox.isNull())
    {
        GLDMaskBox::m_pTipBox->immediateCloseThis();
    }
}
