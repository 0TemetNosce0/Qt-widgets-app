#ifndef XHSLPALETTE_H
#define XHSLPALETTE_H

#include <QWidget>
class XHlPalette;
class XSaturationPalette;

class XHslPalette : public QWidget
{
    Q_OBJECT

public:
    XHslPalette(QWidget *parent = 0);
    ~XHslPalette();   

signals:
    void colorChanged(QColor color);

public slots:
    void setColor(QColor color);

private:
    void initMembers();
    void initContents();

private:
    XHlPalette *mp_wgtHlPalette;
    XSaturationPalette *mp_wgtSaturationIndicator;
};

#endif // XHSLPALETTE_H
