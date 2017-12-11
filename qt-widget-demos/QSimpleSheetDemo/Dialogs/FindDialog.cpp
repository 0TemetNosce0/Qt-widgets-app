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

#include <QWidget>
#include "FindDialog.h"
#include "../Table.h"

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(updateFindButton()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findButtonClicked()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

void FindDialog::findButtonClicked()
{
    if (findBackwardsCheckBox -> isChecked())
    {
        emit findPreviousSignal();
    }
    else
    {
        emit findNextSignal();
    }
}

void FindDialog::updateFindButton()
{
    findButton->setEnabled(!lineEdit->text().isEmpty());
}

Qt::CaseSensitivity FindDialog::caseSensitivity() const
{
    return caseSensitiveCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
}

int FindDialog::inFormula() const
{
    return inFormulaCheckBox->isChecked() ? Table::FindInFormula : Table::FindInDisplayText;
}

QString FindDialog::text() const
{
    return lineEdit->text();
}
