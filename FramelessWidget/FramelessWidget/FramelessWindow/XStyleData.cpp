#include <QApplication>
#include <QDesktopWidget>

#include <QDebug>
#include "XStyleData.h"


/// 析构函数
XStyleData::~XStyleData()
{    }
/// 构造函数
XStyleData::XStyleData()
{   }

XStyleData::XStyleData(XStyle *parent)
    : x_ptr(parent)
{   }

void XStyleData::init()
{
    // 边框圆角
    ntTopLeftRadius = 0;
    ntTopRightRadius = 0;
    ntBottomLeftRadius = 0;
    ntBottomRightRadius = 0;
    // 边框宽度
    ntLeftBorderWidth = 0;
    ntTopBorderWidth = 0;
    ntRightBorderWidth = 0;
    ntBottomBorderWidth = 0;
    // 边框颜色
    colorBorder = Qt::transparent;
    colorBorder_activated = Qt::transparent;
    colorBorder_deactivated = Qt::transparent;
    // 背景颜色
    colorBackground = Qt::transparent;
    colorBackground_activated = Qt::transparent;
    colorBackground_deactivated = Qt::transparent;
    // 背景图片
    strBackgroundImage.clear();
    // End: 样式参数

    refresh();
}

void XStyleData::copyData(XStyleData *pStyleData)
{
    // 边框圆角
    ntTopLeftRadius = pStyleData->ntTopLeftRadius;
    ntTopRightRadius = pStyleData->ntTopRightRadius;
    ntBottomLeftRadius = pStyleData->ntBottomLeftRadius;
    ntBottomRightRadius = pStyleData->ntBottomRightRadius;
    // 边框宽度
    ntLeftBorderWidth = pStyleData->ntLeftBorderWidth;
    ntTopBorderWidth = pStyleData->ntTopBorderWidth;
    ntRightBorderWidth = pStyleData->ntRightBorderWidth;
    ntBottomBorderWidth = pStyleData->ntBottomBorderWidth;
    // 边框颜色
    colorBorder = pStyleData->colorBorder;
    colorBorder_activated = pStyleData->colorBorder_activated;
    colorBorder_deactivated = pStyleData->colorBorder_deactivated;
    // 背景颜色
    colorBackground = pStyleData->colorBackground;
    colorBackground_activated = pStyleData->colorBackground_activated;
    colorBackground_deactivated = pStyleData->colorBackground_deactivated;
    // 背景图片
    strBackgroundImage = pStyleData->strBackgroundImage;

    refresh();
}

void XStyleData::refresh()
{
    X_X(XStyle);

    strStylesheet.clear();

    strStylesheet += QString("{");
    // 圆角
    strStylesheet += QString("border-top-left-radius: %1;").arg(ntTopLeftRadius);
    strStylesheet += QString("border-top-right-radius: %1;").arg(ntTopRightRadius);
    strStylesheet += QString("border-bottom-left-radius: %1;").arg(ntBottomLeftRadius);
    strStylesheet += QString("border-bottom-right-radius: %1;").arg(ntBottomRightRadius);
    //边框
    strStylesheet += QString("border-left-width: %1;").arg(ntLeftBorderWidth);
    strStylesheet += QString("border-top-width: %1;").arg(ntTopBorderWidth);
    strStylesheet += QString("border-right-width: %1;").arg(ntRightBorderWidth);
    strStylesheet += QString("border-bottom-width: %1;").arg(ntBottomBorderWidth);
    strStylesheet += QString("border-style: solid;");
    strStylesheet += QString("border-color: %1;").arg(colorBorder.name(QColor::HexArgb));
    // 背景
    strStylesheet += QString("background-color: %1;").arg(colorBackground.name(QColor::HexArgb));

    if(!strBackgroundImage.isEmpty())
    {
        strStylesheet += QString("border-image: url(%1) %2 %3 %4 %5;")
                         .arg(ntLeftBorderWidth).arg(ntTopBorderWidth)
                         .arg(ntRightBorderWidth).arg(ntBottomBorderWidth);
    }


    // 结尾
    strStylesheet += QString("}");

    //qDebug() << "XStyleData::refresh: deactivated";
    x->onStyleChanged();
}


