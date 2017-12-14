#include "CustomIconStyle.h"

CustomProxyStyle::CustomProxyStyle()
{
    m_size = 40;
}

CustomProxyStyle::~CustomProxyStyle()
{

}


void CustomProxyStyle::setCustomSize(int nSize)
{
    m_size = nSize;
}

int CustomProxyStyle::pixelMetric(PixelMetric metric, const QStyleOption * option, const QWidget * widget) const
{
    int s = QProxyStyle::pixelMetric(metric, option, widget);

    if (metric == QStyle::PM_SmallIconSize)
    {
        s = m_size;
    }

    return s;
}
