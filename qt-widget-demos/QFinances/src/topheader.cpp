/***************************************************************************
 *   Copyright (C) 2007 by Peter Komar                                     *
 *   udldevel@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "topheader.h"

#include <QtGui>

TopHeader::TopHeader(QWidget *p)
    : QWidget(p)
{
    setFixedHeight(200);
}

void TopHeader::paintEvent(QPaintEvent * /*event*/)
{
    QPainter p(this);
    p.fillRect(rect(), QBrush(qApp->palette().window()));

    QLinearGradient headerBackgroundGrd(0,0, 0,100);
    headerBackgroundGrd.setColorAt(0, QColor(115,115,115));
    headerBackgroundGrd.setColorAt(1, QColor(65,65,65));
    //headerBackgroundGrd.setColorAt(0, QColor(252,252,252));
    //headerBackgroundGrd.setColorAt(0.5, QColor(220,220,220));
    //headerBackgroundGrd.setColorAt(0.51, QColor(193,193,193));
    //headerBackgroundGrd.setColorAt(1, QColor(225,225,225));
    //headerBackgroundGrd.setColorAt(0, QColor(200,201,201));
    //headerBackgroundGrd.setColorAt(1, QColor(128,128,131));

    p.fillRect(QRect(0,0,width(),200), QBrush(headerBackgroundGrd));
    p.drawPixmap(0,0,QPixmap(":/img/Logom.png"));
}
