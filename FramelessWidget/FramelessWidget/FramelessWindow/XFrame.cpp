#include <QPainter>
#include <QStyleOption>
#include "XFrame.h"
#include "XStyleData.h"

#include <QDebug>

// 构造析构函数
/// DESTRUCTOR
XFrame::~XFrame()
{
    if(mp_pixmap != nullptr)
    {
        delete mp_pixmap;
        mp_pixmap = nullptr;
    }
}

/// PUBLIC_CONTTRUCTOR
XFrame::XFrame(QWidget *parent) : QFrame(parent),
    mo_blEnableThemeHelper(true),
    mo_blIsActivated(true),
    mp_pixmap(nullptr)
{

}

/// PUBLIC_FUNCTIONS
void XFrame::switchThemeHelper(bool blOn)
{
    mo_blEnableThemeHelper = blOn;
}

void XFrame::setBackgroundImage(QPixmap pixmap)
{
    //qDebug() << "XFrame::setBackgroundImage";
    if(mp_pixmap != nullptr)    delete mp_pixmap;
    mp_pixmap = new QPixmap(pixmap);
    update();
}

void XFrame::removeBackgroundImage()
{
    if(mp_pixmap != nullptr)
    {
        delete mp_pixmap;
        mp_pixmap = nullptr;
    }
}


/// PUBLIC_SLOTS
// 样式表改变槽
void XFrame::onStyleChanged(XStyleData *style)
{
    if(mo_blEnableThemeHelper)
    {
        XStyle::setStyleData(style);
    }
}

// 激活状态改变槽
void XFrame::onActivationChanged(bool activated)
{
    if(activated)
    {
        mo_blIsActivated = activated;
        setBorderColor(getBorderActivatedColor());
        setBackgroundColor(getBackgroundActivatedColor());

    }
    else
    {
        mo_blIsActivated = activated;
        setBorderColor(getBorderDeactivatedColor());
        setBackgroundColor(getBackgroundDeactivatedColor());
    }
}

void XFrame::paintEvent(QPaintEvent *)
{
    if(mp_pixmap != nullptr)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::NoBrush);

        qDebug() << "BorderWidth = " << getLeftBorderWidth();
        QPainterPath pathTitle, pathClient;
        int ntMaxRadius = qMax(getTopLeftRadius()+getLeftBorderWidth(), getBottomLeftRadius()+getLeftBorderWidth());
        pathTitle.addRoundedRect(rect().adjusted(0, 0, 0, -ntMaxRadius),
                                 getTopLeftRadius(), getTopLeftRadius());
        pathClient.addRoundedRect(rect().adjusted(0,ntMaxRadius,0,0),
                                  getBottomLeftRadius()-0, getBottomLeftRadius()-0);
        painter.setClipPath(pathTitle + pathClient);
        painter.drawPixmap(rect(), mp_pixmap->scaled(rect().size()));
    }

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

/// PROTECTED_FUNCTIONS
void XFrame::onStyleChanged()
{
    onActivationChanged(mo_blIsActivated);
    QString strStylesheet;
    strStylesheet += QString("QFrame#%1").arg(objectName());
    strStylesheet += getStylesheet();
    QFrame::setStyleSheet(strStylesheet);

}
