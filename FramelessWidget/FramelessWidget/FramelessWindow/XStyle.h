#ifndef XSTYLE_H
#define XSTYLE_H

#include "Xc.h"
#include <QColor>

class XStyleData;

class XStyle
{

public:
    XStyle();
    virtual ~XStyle();
    XStyleData* styleData();

private:
    XStyleData* d_ptr;
    X_DECLARE_PRIVATE(XStyle)

public:
    virtual void onStyleChanged();

public:
    void initStyle();
    void updateStyle();
    void setStyleData(XStyleData* style);

    /// Setters
    void setThemeColor(QColor color);
    // 设置圆角
    void setRadius(int ntTopLeft, int ntTopRight, int ntBottomLeft, int ntBottonRight);
    // 设置边框宽度
    void setBorderWidth(int ntLeft, int ntTop, int ntRight, int ntBottom);
    void setBorderWidth(int ntWidth);
    // 边框颜色
    void setBorderColor(QColor color);
    void setBorderActivatedColor(QColor color);
    void setBorderDeactivatedColor(QColor color);
    void setBorderColor(QColor colorACtivated, QColor colorDeactivated);
    // 背景颜色
    void setBackgroundColor(QColor color);
    void setBackgroundActivatedColor(QColor color);
    void setBackgroundDeactivatedColor(QColor color);
    void setBackgroundColor(QColor colorACtivated, QColor colorDeactivated);
    // 背景图片
    void setBackgroundImage(QString strURL);
    /// Getters
    QString getStylesheet();
    XStyleData* getStyleData();
    QColor getThemeColor();
    // 圆角半径
    int getTopLeftRadius();
    int getTopRightRadius();
    int getBottomLeftRadius();
    int getBottomRightRadius();
    // 边框宽度
    int getLeftBorderWidth();
    int getTopBorderWidth();
    int getRightBorderWidth();
    int getBottomBorderWidth();
    // 边框颜色
    QColor getBorderColor();
    QColor getBorderActivatedColor();
    QColor getBorderDeactivatedColor();
    // 背景颜色
    QColor getBackgroundColor();
    QColor getBackgroundActivatedColor();
    QColor getBackgroundDeactivatedColor();
};

#endif // XSTYLE_H
