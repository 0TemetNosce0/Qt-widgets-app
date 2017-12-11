// +-------------------------------------------------------------------------+
// | QSimpleSheet simple spreadsheet                                         |
// | Copyright (C) 2008 Shahab <shahab.sh.70@gmail.com>                      |
// +-------------------------------------------------------------------------+
// | License:                                                                |
// |                                                                         |
// | QSimpleSheet is free software; you can redistribute it and/or modify    |
// | it under the terms of the GNU General Public License as published by    |
// | the Free Software Foundation; either version 2 of the License, or       |
// | (at your option) any later version.                                     |
// |                                                                         |
// | QSimpleSheet is distributed in the hope that it will be useful,         |
// | but WITHOUT ANY WARRANTY; without even the implied warranty of          |
// | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            |
// | GNU General Public License for more details.                            |
// |                                                                         |
// | You should have received a copy of the GNU General Public License       |
// | along with QSimpleSheet; if not, write to the Free Software             |
// | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA|
// |                                                                         |
// +-------------------------------------------------------------------------+
// | Author:  Shahab Shirazi <shahab.sh.70@gmail.com>                        |
// +-------------------------------------------------------------------------+


#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QWidget>
#include <QSize>
#include <QPaintEvent>
#include <QPoint>
#include <QDataStream>
class QPainter;
class QImage;

class Graphic: public QWidget
{
    Q_OBJECT

public:
    Graphic(QWidget* = 0);

    enum BoundaryPosition{TopLeft, TopRight, BottomLeft, BottomRight};

    void out(QDataStream&) const;
    void in(QDataStream&);
    virtual QSize getOriginalSize() const = 0;
    QSize getDisplaySize() const;
    void move(int, int);
    void move(const QPoint&);
    void scale(int, int, Qt::AspectRatioMode, BoundaryPosition);
    void scale(const QSize&);

public slots:
    void execPropertiesDialog();

signals:
    void graphicDraggedSignal(Graphic*, QPoint, QPoint);
    void graphicResizedSignal(Graphic*, QSize, QSize, Graphic::BoundaryPosition);
    void graphicSelectedSignal(Graphic*);
    void graphicContextMenuSignal(QPoint);
    void somethingChangedSignal();

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*)
    {execPropertiesDialog();}
    void contextMenuEvent(QContextMenuEvent*);
    void paintEvent(QPaintEvent*);
    virtual void drawInImage(QImage&) = 0;
    virtual void writeOutYourSelf(QDataStream&) const = 0;
    virtual void readInYourSelf(QDataStream&) = 0;


private:
    void drawBoundary(QPainter&);
    //returns the BoundaryPosition (enum) of the mouse in graphic
    //returns -1 for unknown position
    int whereIsMouse(const QPoint&) const;

    QSize scaleSize;

    QPoint pressedPosition;
    QPoint initialGraphicPosition;
    BoundaryPosition centreOfScale;
    QSize initialGraphicSize;
    bool scaling;
    bool dragging;
};



#endif

