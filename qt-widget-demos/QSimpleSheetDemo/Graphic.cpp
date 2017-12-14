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

#include "Graphic.h"
#include <QPainter>
#include "Dialogs/GraphicPropertiesDialog.h"

Graphic::Graphic(QWidget *parent)
    : QWidget(parent)
    , scaleSize(-1, -1)
{
    dragging = scaling = false;
    setContextMenuPolicy(Qt::DefaultContextMenu);
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(true);
}

void Graphic::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        initialGraphicPosition = pos();
        pressedPosition = event->globalPos();
        int position = whereIsMouse(event->pos());

        if (position != -1)
        {
            switch (position)
            {
            case TopLeft: centreOfScale = BottomRight; break;
            case TopRight: centreOfScale = BottomLeft; break;
            case BottomLeft: centreOfScale = TopRight; break;
            case BottomRight: centreOfScale = TopLeft; break;
            }
            scaling = true;
            initialGraphicSize = size();
        }
        else
        {
            dragging = true;
            setCursor(Qt::ClosedHandCursor);
        }
    }

    emit graphicSelectedSignal(this);
}

void Graphic::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons())
    {
        int position = whereIsMouse(event->pos());

        if (position == TopLeft || position == BottomRight)
        {
            setCursor(Qt::SizeFDiagCursor);
        }
        else if (position == TopRight || position == BottomLeft)
        {
            setCursor(Qt::SizeBDiagCursor);
        }
        else
        {
            setCursor(Qt::OpenHandCursor);
        }
    }

    if ((event->buttons() & Qt::LeftButton))
    {
        if (dragging)
        {
            QPoint curPosition = event->globalPos() - pressedPosition + initialGraphicPosition;
            //          if (curPosition.x() < 0)
            //             curPosition.setX(0);
            //          if (curPosition.y() < 0)
            //             curPosition.setY(0);
            //          if ((curPosition.x()+width()) > parentWidget() -> width())
            //             curPosition.setX(parentWidget()->width() - width());
            //          if ((curPosition.y()+height()) > parentWidget() -> height())
            //             curPosition.setY(parentWidget()->height() - height());
            move(curPosition);
        }
        else if (scaling)
        {
            int scaleWidth = event->globalPos().x() - pressedPosition.x();
            int scaleHeight = event->globalPos().y() - pressedPosition.y();

            if (centreOfScale == TopLeft)
            {
                scaleWidth = initialGraphicSize.width()+scaleWidth;
                scaleHeight = initialGraphicSize.height()+scaleHeight;
            }
            else if (centreOfScale == TopRight)
            {
                scaleWidth = initialGraphicSize.width()-scaleWidth;
                scaleHeight = initialGraphicSize.height()+scaleHeight;
            }
            else if (centreOfScale == BottomLeft)
            {
                scaleWidth = initialGraphicSize.width()+scaleWidth;
                scaleHeight = initialGraphicSize.height()-scaleHeight;
            }
            else if (centreOfScale == BottomRight)
            {
                scaleWidth = initialGraphicSize.width()-scaleWidth;
                scaleHeight = initialGraphicSize.height()-scaleHeight;
            }

            Qt::AspectRatioMode aspectRatioMode = (event->modifiers() & Qt::ShiftModifier)
                    ? Qt::KeepAspectRatio : Qt::IgnoreAspectRatio;

            scale(scaleWidth, scaleHeight, aspectRatioMode, centreOfScale);
        }
    }
}

void Graphic::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (dragging)
        {
            if (initialGraphicPosition != pos())
            {
                emit graphicDraggedSignal(this, initialGraphicPosition, pos());
                emit somethingChangedSignal();
            }
        }
        else if (scaling)
        {
            emit graphicResizedSignal(this, initialGraphicSize, size(), centreOfScale);
            emit somethingChangedSignal();
        }
        dragging = scaling = false;
        unsetCursor();
    }
}

void Graphic::contextMenuEvent(QContextMenuEvent *event)
{
    emit graphicContextMenuSignal(event->globalPos());
}

void Graphic::move(int x, int y)
{
    emit somethingChangedSignal();
    QWidget::move(x,y);
}

void Graphic::move(const QPoint &point)
{
    move(point.x(), point.y());
}

void Graphic::drawBoundary(QPainter &painter)
{
    if (hasFocus() && width() >= 10 && height() >= 10)
    {
        QBrush brush(Qt::gray);
        QBrush brushRef = brush;
        painter.fillRect(0,0,10,10, brushRef);
        painter.fillRect(width()-10,0,10,10,brushRef);
        painter.fillRect(0,height()-10, 10, 10, brushRef);
        painter.fillRect(width()-10, height()-10, 10, 10, brushRef);
    }
}

void Graphic::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QImage image;
    drawInImage(image);
    if (scaleSize.isValid() && scaleSize != image.size())
    {
        image = image.scaled(scaleSize.width(), scaleSize.height(),
                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    if (image.size() != size())
        resize(image.size());
    painter.drawImage(0, 0, image);
    drawBoundary(painter);
}

void Graphic::scale(int newWidth, int newHeight,
                    Qt::AspectRatioMode aspectRatioMode,
                    BoundaryPosition centreOfScale)
{
    if (aspectRatioMode == Qt::KeepAspectRatio)
    {
        QSize newSize;
        if (scaling)
            newSize = initialGraphicSize;
        else
            newSize = size();
        newSize.scale(newWidth, newHeight, Qt::KeepAspectRatio);
        newWidth = newSize.width();
        newHeight = newSize.height();
    }
    if (newWidth < 5)
        newWidth = 5;
    if (newHeight < 5)
        newHeight = 5;

    scaleSize.setWidth(newWidth);
    scaleSize.setHeight(newHeight);
    QPoint newPosition = pos();
    if (centreOfScale == BottomRight)
        newPosition = QPoint(pos().x()+width()-newWidth, pos().y()+height()-newHeight);
    else if (centreOfScale == BottomLeft)
        newPosition = QPoint(pos().x(), pos().y()+height()-newHeight);
    else if (centreOfScale == TopRight)
        newPosition = QPoint(pos().x()+width()-newWidth, pos().y());

    setGeometry(newPosition.x(), newPosition.y(), newWidth, newHeight);
    repaint();
}

void Graphic::scale(const QSize &newScaleSize)
{
    scaleSize = newScaleSize;
}

void Graphic::execPropertiesDialog()
{
    GraphicPropertiesDialog dialog(getOriginalSize(), getDisplaySize(), this);
    if (dialog.exec())
    {
        QSize modifiedSize = dialog.getModifiedSizeProperty();
        if (modifiedSize != size())
            emit graphicResizedSignal(this, size(), modifiedSize, TopLeft);
    }
}

QSize Graphic::getDisplaySize() const
{
    return size();
}

int Graphic::whereIsMouse(const QPoint &mousePos) const
{
    if (mousePos.x() <= 4 && mousePos.y() <= 4)
        return TopLeft;
    else if (mousePos.x() >= width()-5 && mousePos.y() <= 4)
        return TopRight;
    else if (mousePos.x() <= 4 && mousePos.y() >= height()-5)
        return BottomLeft;
    else if (mousePos.x() >= width()-5 && mousePos.y() >= height()-5)
        return BottomRight;
    else
        return -1;
}

void Graphic::out(QDataStream &outStream) const
{
    writeOutYourSelf(outStream); //write the data of inherited classes
    outStream << pos() << qint16(scaleSize.width()) << qint16(scaleSize.height());
}

void Graphic::in(QDataStream &inStream)
{
    QPoint newPosition;
    qint16 newWidth;
    qint16 newHeight;

    readInYourSelf(inStream); //read the data of inherited classes
    inStream >> newPosition >> newWidth >> newHeight;
    scaleSize.setWidth(newWidth);
    scaleSize.setHeight(newHeight);
    move(newPosition);
}


