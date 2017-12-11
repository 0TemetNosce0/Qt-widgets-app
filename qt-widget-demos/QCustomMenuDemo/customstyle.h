#ifndef CUSTOMSTYLE_H
#define CUSTOMSTYLE_H

#include <QProxyStyle>
#include <QStyleOption>

/**
 * @brief 定制菜单style
 */
class CCustomStyle : public QProxyStyle
{
    Q_OBJECT

public:
    CCustomStyle(QStyle *style = 0);
    void setIconSize(const QSize& iconSize) { _iconSize = iconSize; }

    void drawControl(ControlElement control, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget) const;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                       QPainter *painter, const QWidget *widget) const;

    int pixelMetric(PixelMetric pm, const QStyleOption * opt, const QWidget * widget) const;

private:
    void drawMenuItem(const QStyleOption *option,
                      QPainter *painter, const QWidget *widget) const;


    QPixmap 	_pixShadow	 ; //阴影图片
    QSize       _iconSize;     // note: only the width is currently used.
};

#endif // CUSTOMSTYLE_H
