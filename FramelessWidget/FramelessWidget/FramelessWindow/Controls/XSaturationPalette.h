#ifndef XSATURATIONPALETTE_H
#define XSATURATIONPALETTE_H

#include <QWidget>

class XSaturationPalette : public QWidget
{
    Q_OBJECT

public:
    explicit XSaturationPalette(QWidget *parent = nullptr);
    ~XSaturationPalette();

    double saturation();

signals:
    void saturationChanged();
    double saturationChanged(double dblSaturation);
    void colorChanged();
    void colorChanged(QColor color);

public slots:
    void setBaseColor(QColor color);
    void setColor(QColor color);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void initMembers();
    void calculateSuration();

private:
    QColor mo_color;
    QPointF mo_ptfCursorPos;
    double mo_dblVernierX;
    double mo_dblVernierPercentX;
    double mo_dblSaturation;
};

#endif // XSATURATIONPALETTE_H
