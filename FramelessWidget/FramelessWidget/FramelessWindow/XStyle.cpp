#include "XStyle.h"
#include "XStyleData.h"
#include <QMetaType>
#include <QDebug>

/// 构造函数
XStyle::XStyle() : d_ptr(new XStyleData(this))
{
    qRegisterMetaType<XStyleData*>("XStyleData*");
    initStyle();
}

/// 析构函数
XStyle::~XStyle()
{    }

XStyleData *XStyle::styleData()
{
    return d_ptr;
}


///
///     公有方法
///

void XStyle::initStyle()
{
    X_D(XStyle);
    d->init();
}

void XStyle::updateStyle()
{
    X_D(XStyle);
    d->refresh();
}

// 设置新style
void XStyle::setStyleData(XStyleData *style)
{

    X_D(XStyle);
    d->copyData(style);
}

/// Setters

// 设置主体颜色
void XStyle::setThemeColor(QColor color)
{
    X_D(XStyle);
    d->colorTheme = color;
}
// 设置圆角
void XStyle::setRadius(int ntTopLeft, int ntTopRight, int ntBottomLeft, int ntBottonRight)
{
    X_D(XStyle);
    d->ntTopLeftRadius = ntTopLeft;
    d->ntTopRightRadius = ntTopRight;
    d->ntBottomLeftRadius = ntBottomLeft;
    d->ntBottomRightRadius = ntBottonRight;
    d->refresh();
}
// 设置边框宽度
void XStyle::setBorderWidth(int ntLeft, int ntTop, int ntRight, int ntBottom)
{
    X_D(XStyle);
    d->ntLeftBorderWidth = ntLeft;
    d->ntTopBorderWidth = ntTop;
    d->ntRightBorderWidth = ntRight;
    d->ntBottomBorderWidth = ntBottom;
    d->refresh();
}

void XStyle::setBorderWidth(int ntWidth)
{
    setBorderWidth(ntWidth, ntWidth, ntWidth, ntWidth);
}

// 设置边框颜色
void XStyle::setBorderColor(QColor color)
{
    X_D(XStyle);
    if(d->colorBorder != color)
    {
        d->colorBorder = color;
        d->refresh();
    }
}
void XStyle::setBorderActivatedColor(QColor color)
{
    X_D(XStyle);
    d->colorBorder_activated = color;
    d->refresh();
}
void XStyle::setBorderDeactivatedColor(QColor color)
{
    X_D(XStyle);
    d->colorBorder_deactivated = color;
    d->refresh();
}

void XStyle::setBorderColor(QColor colorACtivated, QColor colorDeactivated)
{
    setBorderActivatedColor(colorACtivated);
    setBorderDeactivatedColor(colorDeactivated);
}

// 设置背景颜色
void XStyle::setBackgroundColor(QColor color)
{
    X_D(XStyle);
    if(d->colorBackground != color)
    {
        d->colorBackground = color;
        d->refresh();
    }
}
void XStyle::setBackgroundActivatedColor(QColor color)
{
    X_D(XStyle);
    d->colorBackground_activated = color;
    d->refresh();
}
void XStyle::setBackgroundDeactivatedColor(QColor color)
{
    X_D(XStyle);
    d->colorBackground_deactivated = color;
    d->refresh();
}

void XStyle::setBackgroundColor(QColor colorACtivated, QColor colorDeactivated)
{
    setBackgroundActivatedColor(colorACtivated);
    setBackgroundDeactivatedColor(colorDeactivated);
}

// 设置背景图片
void XStyle::setBackgroundImage(QString strURL)
{
    X_D(XStyle);
    d->strBackgroundImage = strURL;
    d->refresh();
}

/// Getters
QString XStyle::getStylesheet()
{
    X_D(XStyle);
    return d->strStylesheet;
}

XStyleData *XStyle::getStyleData()
{
    X_D(XStyle);
    return d;
}

QColor XStyle::getThemeColor()
{
    X_D(XStyle);
    return d->strStylesheet;
}
// 获取圆角
int XStyle::getTopLeftRadius()
{
    X_D(XStyle);
    return d->ntTopLeftRadius;
}
int XStyle::getTopRightRadius()
{
    X_D(XStyle);
    return d->ntTopRightRadius;
}
int XStyle::getBottomLeftRadius()
{
    X_D(XStyle);
    return d->ntBottomLeftRadius;
}
int XStyle::getBottomRightRadius()
{
    X_D(XStyle);
    return d->ntBottomRightRadius;
}
// 获取边框参数
int XStyle::getLeftBorderWidth()
{
    X_D(XStyle);
    return d->ntLeftBorderWidth;
}
int XStyle::getTopBorderWidth()
{
    X_D(XStyle);
    return d->ntTopBorderWidth;
}
int XStyle::getRightBorderWidth()
{
    X_D(XStyle);
    return d->ntRightBorderWidth;
}
int XStyle::getBottomBorderWidth()
{
    X_D(XStyle);
    return d->ntBottomBorderWidth;
}
// 获取边框颜色
QColor XStyle::getBorderColor()
{
    X_D(XStyle);
    return d->colorBorder;
}
QColor XStyle::getBorderActivatedColor()
{
    X_D(XStyle);
    return d->colorBorder_activated;
}
QColor XStyle::getBorderDeactivatedColor()
{
    X_D(XStyle);
    return d->colorBorder_deactivated;
}
// 获取背景颜色
QColor XStyle::getBackgroundColor()
{
    X_D(XStyle);
    return d->colorBackground;
}
QColor XStyle::getBackgroundActivatedColor()
{
    X_D(XStyle);
    return d->colorBackground_activated;
}
QColor XStyle::getBackgroundDeactivatedColor()
{
    X_D(XStyle);
    return d->colorBackground_deactivated;
}


///
///     保护方法
///
void XStyle::onStyleChanged()
{
    //qDebug() << "XStyle::onStyleChanged";
}


