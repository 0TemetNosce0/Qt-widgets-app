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

#include <QtGui>
#include "GraphicPropertiesDialog.h"

GraphicPropertiesDialog::GraphicPropertiesDialog(const QSize &os, const QSize &scaledSize,
                                                 QWidget *parent)
    : QDialog(parent)
    , originalSize(os)
{
    setupUi(this);

    connect(keepAspectRatioCheckBox, SIGNAL(stateChanged(int)),
            this, SLOT(keepAspectRatioSlot(int)));
    connect(originalSizeCheckBox, SIGNAL(stateChanged(int)),
            this, SLOT(originalSizeSlot(int)));
    connect(unitComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(unitChangedSlot(int)));

    widthSpinBox->setAnotherSpinBox(heightSpinBox);
    heightSpinBox->setAnotherSpinBox(widthSpinBox);
    widthSpinBox->setOriginalValue(originalSize.width());
    heightSpinBox->setOriginalValue(originalSize.height());
    widthSpinBox->setValue(scaledSize.width());
    heightSpinBox->setValue(scaledSize.height());
}

void GraphicPropertiesDialog::keepAspectRatioSlot(int ar)
{
    bool keepAspectRatio = (ar == Qt::Checked) ? true : false;
    widthSpinBox->setKeepAspectRatio(keepAspectRatio);
    heightSpinBox->setKeepAspectRatio(keepAspectRatio);

    if (keepAspectRatio)
    {
        widthSpinBox->setInitialValueOfAspectRatio(widthSpinBox->value());
        heightSpinBox->setInitialValueOfAspectRatio(heightSpinBox->value());
    }
}

void GraphicPropertiesDialog::originalSizeSlot(int os)
{
    bool status = (os == Qt::Checked) ? false : true;
    widthSpinBox->setEnabled(status);
    heightSpinBox->setEnabled(status);
    unitComboBox->setEnabled(status);
    keepAspectRatioCheckBox->setEnabled(status);
}

void GraphicPropertiesDialog::unitChangedSlot(int newUnit)
{
    newUnit = (newUnit == 0) ? MySpinBox::Pixel : MySpinBox::Percent;
    widthSpinBox->setUnit(newUnit);
    heightSpinBox->setUnit(newUnit);
}

QSize GraphicPropertiesDialog::getModifiedSizeProperty() const
{
    if (originalSizeCheckBox->isChecked())
    {
        return originalSize;
    }
    else
    {
        return QSize(widthSpinBox->value(), heightSpinBox->value());
    }
}

