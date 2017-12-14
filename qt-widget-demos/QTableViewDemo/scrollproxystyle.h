#ifndef SCROLLPROXYSTYLE_H
#define SCROLLPROXYSTYLE_H

#include <QProxyStyle>

class ScrollProxyStyle : public QProxyStyle
{
    Q_OBJECT

public:
    ScrollProxyStyle();
    ~ScrollProxyStyle();

protected:
    virtual void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option,
                               QPainter *painter, const QWidget *widget) const;

private:
    void drawScrollbar(QStyle::ComplexControl control, const QStyleOptionComplex *option,
                  QPainter *painter, const QWidget *widget) const;
};

#endif // SCROLLPROXYSTYLE_H
