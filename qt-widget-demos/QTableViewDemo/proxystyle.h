///////////////////////////////////////////////////////////
// È¥µô¾ØÐÎµãÕóÐé¿ò
///////////////////////////////////////////////////////////

#ifndef PROXYSTYLE_H
#define PROXYSTYLE_H

#include <QProxyStyle>

class CustomProxyStyle : public QProxyStyle
{
    Q_OBJECT

public:
    CustomProxyStyle();
    ~CustomProxyStyle();

protected:
    virtual void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                               QPainter *painter, const QWidget *widget = 0) const;
};
#endif // PROXYSTYLE_H
