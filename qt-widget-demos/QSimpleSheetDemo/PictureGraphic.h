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

#ifndef PICTUREGRAPHIC_H
#define PICTUREGRAPHIC_H

#include <QImage>
#include <QSize>
#include "Graphic.h"

class QWidget;
class QPaintEvent;

class PictureGraphic : public Graphic
{
    Q_OBJECT

public:
    PictureGraphic(QWidget*, const QImage& = QImage());
    QSize sizeHint() const;
    virtual void writeOutYourSelf(QDataStream&) const;
    virtual void readInYourSelf(QDataStream&);
    virtual QSize getOriginalSize() const;

protected:
    virtual void drawInImage(QImage&);

private:
    QImage image;
};


#endif
