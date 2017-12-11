/***************************************************************************
 *   Copyright (C) 2008 - Giuseppe Cigala                                  *
 *   g_cigala@virgilio.it                                                  *
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

#ifndef QPROG_H
#define QPROG_H

#include <QWidget>
#include <QtDesigner/QDesignerExportWidget>
#include <math.h>


class QDESIGNER_WIDGET_EXPORT QProg : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double value READ value WRITE setValue);
    Q_PROPERTY(double min READ minValue WRITE setMinValue);
    Q_PROPERTY(double max READ maxValue WRITE setMaxValue);
    Q_PROPERTY(int font READ font WRITE setFontDim);
    Q_PROPERTY(int numPrec READ numPrec WRITE setPrecision);
    Q_PROPERTY(QColor color READ color WRITE setBarColor);

    double value() const
    {
        return actVal;
    }
    double minValue() const
    {
        return minVal;
    }
    double maxValue() const
    {
        return maxVal;
    }
    int font() const
    {
        return fontDim;
    }
    int numPrec() const
    {
        return precision;
    }
    QColor color() const
    {
        return colBar;
    }

public:
    QProg(QWidget *parent = 0);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

signals:
    void valueChanged(double);

public slots:
    void setValue(double);
    void setMaxValue(double);
    void setMinValue(double);
    void setFontDim(int);
    void setPrecision(int);
    void setBarColor(QColor);

protected:
    void paintEvent(QPaintEvent *);
    void initValue();
    void paintBorder();
    void paintBar();
    void paintLine();
    void paintValue();

private:
    int fontDim;
    int precision;
    double lengthBar;
    double minVal;
    double maxVal;
    double actVal;
    QColor colBar;
};

#endif
