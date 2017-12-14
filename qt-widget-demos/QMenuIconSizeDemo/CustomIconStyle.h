///////////////////////////////////////////////////////////
// QMenu的大图标定义
///////////////////////////////////////////////////////////

#ifndef CUSTOMICONSTYLE_H
#define CUSTOMICONSTYLE_H

#include <QProxyStyle>

class CustomProxyStylee : public QProxyStyle
{
    Q_OBJECT

public:
    CustomProxyStylee();
    ~CustomProxyStylee();

    void setCustomSize(int);

protected:
    virtual int pixelMetric(PixelMetric metric, const QStyleOption * option, const QWidget * widget) const;

private:
    int m_size;
};

#endif // CUSTOMICONSTYLE_H
