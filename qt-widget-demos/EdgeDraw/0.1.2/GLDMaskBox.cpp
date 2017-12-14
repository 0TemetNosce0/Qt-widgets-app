#include "GLDMaskBox.h"
#include "GLDFileUtils.h"

#include <qevent.h>

#include <QRect>
#include <QDebug>
#include <QPoint>
#include <QRegion>
#include <QBitmap>
#include <QPainter>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QSharedPointer>


QPointer<GLDMaskBox> GLDMaskBox::m_pMaskBox = nullptr;

Impl::Impl(QWidget* pWidget, QWidget* parent)
    : m_pClippedWgt(pWidget)
    , m_parent(parent)
{

}

Impl::Impl(const QPoint &pos, float iR, float oR)
    : m_innerRadius(iR)
    , m_outerRadius(oR)
    , m_pos(pos)
{

}

Impl::~Impl()
{

}

void Impl::createMaskImage(QImage &image)
{
    int outerWidth = m_outerRadius * 2;
    int outerHeight = outerWidth;
    int innerWidth = m_innerRadius * 2;
    int innerHeight = m_innerRadius * 2;
    int widthDelta = (outerWidth - innerWidth) / 2;
    int heightDelta = (outerHeight - innerHeight) / 2;

    image = QImage(outerWidth, outerHeight, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter imagePainter(&image);

    imagePainter.setRenderHints(QPainter::Antialiasing);
    imagePainter.setPen(QPen(Qt::NoPen));
    imagePainter.setBrush(QColor(0, 0, 0));
    imagePainter.drawEllipse(0, 0, outerWidth, outerHeight);
    imagePainter.setBrush(Qt::white);
    imagePainter.drawEllipse(widthDelta, heightDelta, innerWidth, innerHeight);
}

void Impl::drawDonut(QPainter &painter)
{
    int w = m_outerRadius * 2;
    int h = m_outerRadius * 2;

    QColor color(143, 143, 143);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.setPen(QPen(color));
    painter.setBrush(color);
    painter.drawRect(1, 1, w - 2, h - 2);

    painter.setBrush(color);
    QPainter::CompositionMode mode = painter.compositionMode();
    painter.setCompositionMode(QPainter::CompositionMode_Xor);
    int iW = m_innerRadius * 2;
    int iH = iW;
    int iX = (w - iW) / 2;
    int iY = iX;
    painter.drawRect(iX, iY, iW, iH);
    painter.setCompositionMode(mode);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(color, 2));
    painter.drawRect(iX, iY, iW, iH);
}

void Impl::drawDonut(QPainter& painter, QWidget* parent)
{
    Q_UNUSED(parent);

    int w = m_parent->size().width();
    int h = m_parent->size().height();

    QColor color(0, 0, 0, 100);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.setPen(QPen(color));
    painter.setBrush(color);
    painter.drawRect(1, 1, w - 2, h - 2);

    painter.setBrush(color);
    QPainter::CompositionMode mode = painter.compositionMode();
    painter.setCompositionMode(QPainter::CompositionMode_Xor);

    m_nClippedWidgetWidth = m_pClippedWgt->size().width();
    m_nClippedWidgetHeight = m_pClippedWgt->size().height();
    m_ptGlobalOwnerCenter = m_pClippedWgt->mapToParent(m_pClippedWgt->rect().topLeft());
    painter.drawRect(m_ptGlobalOwnerCenter.x(), m_ptGlobalOwnerCenter.y(), m_nClippedWidgetWidth, m_nClippedWidgetHeight);

    painter.setCompositionMode(mode);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(color, 2));
    painter.drawRect(m_ptGlobalOwnerCenter.x(), m_ptGlobalOwnerCenter.y(), m_nClippedWidgetWidth, m_nClippedWidgetHeight);
}

void Impl::drawMask(QPainter &painter)
{
    painter.drawImage(0, 0, m_maskImage);
}

GLDMaskBox *GLDMaskBox::showMaskBox(QWidget *wgtOwner)
{
    GLDMaskBox* pTip = nullptr;

    do
    {
        if (!wgtOwner)
        {
            break;
        }

        // 如果owner和内容相同,认为是同一个,不可反复弹出
        //if (!GLDMaskBox::m_pMaskBox.isNull())
        //{
        //    if (wgtOwner == GLDMaskBox::m_pMaskBox->tipBoxParam().m_wgtOwner)
        //    {
        //        pTip = GLDMaskBox::m_pTipBox;
        //        break;
        //    }
        //}

        if (!GLDMaskBox::m_pMaskBox.isNull())
        {
            GLDMaskBox::m_pMaskBox->immediateCloseThis();
        }

        QWidget* pWidget = topParentWidget(wgtOwner);
        qDebug() << pWidget->objectName();

        pTip = new GLDMaskBox(wgtOwner, pWidget);

        GLDMaskBox::m_pMaskBox = pTip;

        pTip->show();

    }while(0);

    return pTip;
}

GLDMaskBox::GLDMaskBox(const QPoint &pos, float iR, float oR, QWidget *parent)
    : QWidget(parent)
    , d(new Impl(pos, iR, oR))
{
    int w = oR * 2;
    int h = oR * 2;
    int x = 0;
    int y = 0;

    int iW = iR * 2;
    int iH = iR * 2;
    int iX = x + (w - iW) / 2;
    int iY = y + (h - iH) / 2;

    d->m_region = QSharedPointer<QRegion>(new QRegion(x, y, w - 1, h - 1, QRegion::Ellipse));
    d->m_innerRegion = QSharedPointer<QRegion>(new QRegion(iX, iY, iW - 1, iH - 1, QRegion::Ellipse));
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_TranslucentBackground);

    setGeometry(x + 100, y + 100, w, h);

    d->createMaskImage(d->m_maskImage);
}

GLDMaskBox::GLDMaskBox(QWidget *wgtOwner, QWidget *parent)
    : QWidget(parent)
    , m_pWgt(wgtOwner)
    , m_parent(parent)
    , m_pTipBox(new IrregularForm(this))
    , d(new Impl(wgtOwner, parent))
{
    setFixedSize(QApplication::desktop()->width(), QApplication::desktop()->height());
    //this->setFixedSize(m_parent->width(), m_parent->height());

    //QString path = exePath() + "/images/Msg/change_skin_text.png";
    //QPixmap img(path);
    //m_pTipBox->setPixmap(img);

    connect(m_pTipBox, &IrregularForm::irregularFormClicked, this, &GLDMaskBox::slotClose);

    //QVBoxLayout* pLayout = new QVBoxLayout(this);
    //pLayout->addWidget(m_pTipBox);
    //setLayout(pLayout);
}

GLDMaskBox::~GLDMaskBox()
{

}

void GLDMaskBox::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    const int iW = m_pWgt->size().width();
    const int iH = m_pWgt->size().height();

    QPoint ptGlobalOwnerCenter = m_pWgt->mapToParent(m_pWgt->rect().topLeft());
    QRect pOwnerRect(ptGlobalOwnerCenter.x(), ptGlobalOwnerCenter.y(), iW, iH);

    QRegion rect = this->rect();
    rect -= pOwnerRect;

    painter.setClipRegion(rect);

    d->drawDonut(painter, m_parent);

    m_pTipBox->move(93, 116);
}

void GLDMaskBox::mousePressEvent(QMouseEvent * event)
{
    QRect rect(d->m_ptGlobalOwnerCenter.rx(), d->m_ptGlobalOwnerCenter.ry(),
        d->m_nClippedWidgetWidth, d->m_nClippedWidgetHeight);

    if (rect.contains(event->pos()))
    {
        slotClose();
    }

    QWidget::mousePressEvent(event);
}

QPoint GLDMaskBox::calcPosOfOwner()
{
    QPoint pt(0, 0);

    do
    {
        // 计算owner位置对应屏幕中心的象限
        if (!m_pWgt)
        {
            break;
        }

        QPoint ptGlobalOwnerCenter = m_pWgt->mapToGlobal(m_pWgt->rect().center());
        QPoint ptGlobalScreen = QApplication::desktop()->screenGeometry().center();
        QPoint ptDelta = ptGlobalOwnerCenter - ptGlobalScreen;

        if (ptDelta.x() >= 0 && ptDelta.y() <= 0)
        {
            // 第一象限
            pt = QPoint(ptGlobalOwnerCenter.x() - m_pWgt->width()/2,
                            ptGlobalOwnerCenter.y() + m_pWgt->height()/2);
            pt += QPoint(-this->width()/2, 0);
        }
        else if (ptDelta.x() <= 0 && ptDelta.y() <= 0)
        {
            // 第二象限
            pt = QPoint(ptGlobalOwnerCenter.x() + m_pWgt->width()/2,
                            ptGlobalOwnerCenter.y() + m_pWgt->height()/2);
            pt += QPoint(-this->width()/2, 0);
        }
        else if (ptDelta.x() <= 0 && ptDelta.y() >= 0)
        {
            // 第三象限
            pt = QPoint(ptGlobalOwnerCenter.x() + m_pWgt->width()/2,
                            ptGlobalOwnerCenter.y() - m_pWgt->height()/2);
            pt += QPoint(-this->width()/2, -this->height());
        }
        else if (ptDelta.x() >= 0 && ptDelta.y() >= 0)
        {
            // 第四象限
            pt = QPoint(ptGlobalOwnerCenter.x() - m_pWgt->width()/2,
                        ptGlobalOwnerCenter.y() - m_pWgt->height()/2);
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

void GLDMaskBox::immediateCloseThis()
{
    this->slotClose();
}

void GLDMaskBox::slotClose()
{
    this->close();
    this->deleteLater();
}
