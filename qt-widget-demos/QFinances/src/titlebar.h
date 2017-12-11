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

#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QtWidgets/QWidget>

class TitleBar : public QWidget
{
Q_OBJECT
public:
    TitleBar(QWidget *parent = 0);

    ~TitleBar();
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    void setTitleText(const QString& title);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent ( QMouseEvent * event );
private:
    QPixmap centerPm, rightPm;
    QString titleTxt;
    bool bpress; //daraw press button or no
    bool but_press; //press button or no

    void create_pixmap();
    void draw_close_btn();
};

#endif
