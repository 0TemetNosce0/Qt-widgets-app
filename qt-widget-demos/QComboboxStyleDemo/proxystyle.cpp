#include "proxystyle.h"

CustomProxyStyle::CustomProxyStyle()
{

}

CustomProxyStyle::~CustomProxyStyle()
{

}

void CustomProxyStyle::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option,
                                    QPainter *painter, const QWidget *widget) const
{
    if (PE_FrameFocusRect == element)
    {
        /// do not draw focus rectangle
    }
    else
    {
        QProxyStyle::drawPrimitive(element, option,painter, widget);
    }
}

