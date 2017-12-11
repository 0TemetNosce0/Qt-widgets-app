#ifndef XCOLORLABEL_H
#define XCOLORLABEL_H

#include <QLabel>

class XColorLabel : public QLabel
{
    Q_OBJECT

public:
    explicit XColorLabel(QColor color = QColor(), QWidget *parent = nullptr);
    ~XColorLabel();
    QColor color();

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void clicked(QColor color);
    void colorChanged(QColor color);
    void doubleClicked();

public slots:
    void setColor(QColor color);
    void setAlpha(int ntAlpha);
    void setRed(int ntRed);
    void setGreen(int ntGreen);
    void setBlue(int ntBlue);

    void setAlphaF(double dblAlpha);
    void setRedF(double dblRed);
    void setGreenF(double dblGreen);
    void setBlueF(double dblBlue);

private:
    QColor mo_color;
    QPoint mo_ptPressed;
};

#endif // XCOLORLABEL_H
