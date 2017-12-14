#ifndef MYDOCKTITLEBAR_H
#define MYDOCKTITLEBAR_H

#include <QSize>
#include <QDockWidget>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "qdebug.h"
#include <QStyle>

class MyDockTitleBar : public QWidget
{
    Q_OBJECT
public:
    MyDockTitleBar(QWidget *parent = 0);

    QSize sizeHint() const { return minimumSizeHint(); }
    QSize minimumSizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void updateMask();

private:
    QPixmap minPix, closePix, floatPix;

};


#endif // MYDOCKTITLEBAR_H
