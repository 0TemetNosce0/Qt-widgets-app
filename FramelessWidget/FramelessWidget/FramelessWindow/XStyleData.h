#ifndef XStyleData_H
#define XStyleData_H

#include <QColor>
#include "XStyle.h"

class XStyleData
{    

public:
    XStyleData();
    XStyleData(XStyle *parent);
    XStyleData&operator=(XStyleData* pStyleData);

    virtual ~XStyleData();

private:
    XStyle *x_ptr;
    X_DECLARE_PUBLIC(XStyle)

public:
    void init();
    void copyData(XStyleData* pStyleData);
    void refresh();

public:
    QString strStylesheet;       // 样式表
    QColor colorTheme;           // 主题色

    /// BEGIN: 样式参数
    // 边框圆角
    int ntTopLeftRadius;
    int ntTopRightRadius;
    int ntBottomLeftRadius;
    int ntBottomRightRadius;
    // 边框宽度
    int ntLeftBorderWidth;
    int ntTopBorderWidth;
    int ntRightBorderWidth;
    int ntBottomBorderWidth;
    // 边框颜色
    QColor colorBorder;
    QColor colorBorder_activated;         // 激活边框颜色
    QColor colorBorder_deactivated;       // 失去激活边框颜色
    // 背景颜色
    QColor colorBackground;
    QColor colorBackground_activated;     // 激活背景颜色
    QColor colorBackground_deactivated;   // 失去激活背景颜色
    // 背景图片
    QString strBackgroundImage;
    /// End: 样式参数
};

#endif // XStyleData_H
