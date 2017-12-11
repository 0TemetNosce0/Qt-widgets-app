#ifndef GLINE_H
#define GLINE_H

#include <QColor>
#include <QWidget>
#include <QPainter>

class GLine : public QWidget
{
    Q_OBJECT

public :
    GLine(QWidget *parent=0);
    void setPen(int penSize, const QColor & color);
    void draw(int z, int len); ///z=0 H,z=1,V

protected:
    void paintEvent(QPaintEvent *);

private:
    int z;
    int len;
    int penSize;
    QColor penColor;
};

#endif // GLINE_H

