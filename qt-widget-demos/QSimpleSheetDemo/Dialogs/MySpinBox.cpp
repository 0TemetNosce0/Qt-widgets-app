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

#include "MySpinBox.h"

MySpinBox::MySpinBox(QWidget *parent)
    : QDoubleSpinBox(parent)
{
    validator = new QRegExpValidator(this);
    anotherSpinBox = 0;
    originalValue = initialValueOfAspectRatio = 0;
    unit = Pixel;
    setValue(0.0);
    keepAspectRatio = false;
    connect(this, SIGNAL(editingFinished()), this, SLOT(syncronizeSpinBoxes()));
}

void MySpinBox::stepBy(int steps)
{
    if (unit == Pixel)
    {
        setValue(value()+steps*singleStep());
    }
    else if (unit == Percent)
    {
        setValue(value()+steps*originalValue/100.0);
    }

    syncronizeSpinBoxes();
}

QValidator::State MySpinBox::validate(QString &text, int &pos) const
{
    if (unit == Pixel)
    {
        validator->setRegExp(QRegExp("[1-9][0-9]{0,}"));
    }
    else if (unit == Percent)
    {
        validator->setRegExp(QRegExp("[1-9][0-9]{0,}\\.{0,1}[0-9]{0,2}"));
    }

    return validator->validate(text, pos);
}

double MySpinBox::valueFromText(const QString &text) const
{
    if (unit == Pixel)
    {
        return text.toDouble();
    }
    else
    {
        return text.toDouble()*originalValue/100;
    }
}

QString MySpinBox::textFromValue(double value) const
{
    if (unit == Pixel)
    {
        return QString::number(static_cast<int>(value));
    }
    else
    {
        return QString::number(value*100/originalValue);
    }
}

void MySpinBox::syncronizeSpinBoxes()
{
    if (keepAspectRatio)
    {
        anotherSpinBox->setValue(value()/initialValueOfAspectRatio
                                   *anotherSpinBox->getInitialValueOfAspectRatio());
    }
}

