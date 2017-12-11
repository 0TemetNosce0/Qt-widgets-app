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

#ifndef MYSPINBOX_H
#define MYSPINBOX_H

#include <QSpinBox>
class QRegExpValidator;

class MySpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:
    MySpinBox(QWidget* = 0);

    void stepBy(int);

    QValidator::State validate(QString&, int&) const;

    void setAnotherSpinBox(MySpinBox *asb)
    {
        anotherSpinBox = asb;
    }

    int getInitialValueOfAspectRatio() const
    {
        return initialValueOfAspectRatio;
    }

    void setInitialValueOfAspectRatio(int i)
    {
        initialValueOfAspectRatio = i;
    }

    int getOriginalValue() const
    {
        return originalValue;
    }

    void setOriginalValue(int i)
    {
        originalValue = initialValueOfAspectRatio = i;
    }

    void setKeepAspectRatio (bool kar)
    {
        keepAspectRatio = kar;
    }

    void setUnit(int u)
    {
        unit = u;
        setValue(value()); /* just to refresh the sping box */
    }

    enum {Pixel, Percent};

protected:
    double valueFromText(const QString&) const;
    QString textFromValue(double) const;

private slots:
    void syncronizeSpinBoxes();

private:
    MySpinBox *anotherSpinBox;
    int initialValueOfAspectRatio;
    int originalValue;
    int unit;
    bool keepAspectRatio;

    QRegExpValidator *validator;
};

#endif

