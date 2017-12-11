// +-------------------------------------------------------------------------+
// | SimpleSheet simple spreadsheet                                          |
// | Copyright (C) 2007 Shahab <shahab.sh.70@gmail.com>                      |
// +-------------------------------------------------------------------------+
// | License:                                                                |
// |                                                                         |
// | SimpleSheet is free software; you can redistribute it and/or modify     |
// | it under the terms of the GNU General Public License as published by    |
// | the Free Software Foundation; either version 2 of the License, or       |
// | (at your option) any later version.                                     |
// |                                                                         |
// | SimpleSheet is distributed in the hope that it will be useful,          |
// | but WITHOUT ANY WARRANTY; without even the implied warranty of          |
// | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            |
// | GNU General Public License for more details.                            |
// |                                                                         |
// | You should have received a copy of the GNU General Public License       |
// | along with SimpleSheet; if not, write to the Free Software              |
// | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA|
// |                                                                         |
// +-------------------------------------------------------------------------+
// | Author:  Shahab Shirazi <shahab.sh.70@gmail.com>                        |
// +-------------------------------------------------------------------------+

#include "../Table.h"
#include "SortDialog.h"

SortDialog::SortDialog(const QTableWidgetSelectionRange &r, QWidget *parent)
    : QDialog(parent)
    , range(r)
{
    setupUi(this);
    QSize lastSize(size());
    connect(sortColumnsRadioButton, SIGNAL(toggled(bool)), this, SLOT(setSortKeys()));
    connect(sortRowsRadioButton, SIGNAL(toggled(bool)), this, SLOT(setSortKeys()));
    customOrderComboBox -> addItem(tr("Monday, Tuesday, Wednesday, "
                                      "Thursday, Friday, Saturday, Sunday"));
    customOrderComboBox -> addItem(tr("January, February, March, April, May, June, July, "
                                      "August, September, October, November, December"));
    customOrderComboBox -> addItem(tr("Zero, One, Two, Three, Four, Five, Six, Seven, "
                                      "Eight, Nine, Ten"));
    customOrderComboBox -> addItem(tr("First, Second, Third, Fourth, Fifth, Sixth, Seventh, "
                                      "Eighth, Ninth, Tenth"));
    //After adding long data to customOrderComboBox, the dialog resizes
    //and also the minimumSize changes. so:
    setMinimumSize(lastSize);
    resize(lastSize);
    setSortKeys();
}

void SortDialog::setSortKeys()
{
    firstKeyComboBox -> clear();
    secondKeyComboBox -> clear();
    thirdKeyComboBox -> clear();

    secondKeyComboBox -> addItem(tr("Non"));
    thirdKeyComboBox -> addItem(tr("Non"));

    if (sortRowsRadioButton -> isChecked())
    {
        for (int i = range.leftColumn(); i <= range.rightColumn(); i++)
        {
            QString columnPos;
            Table::encodePosition(columnPos, i);
            firstKeyComboBox->addItem(tr("Column ") + columnPos);
            secondKeyComboBox->addItem(tr("Column ") + columnPos);
            thirdKeyComboBox->addItem(tr("Column ") + columnPos);
        }
    }
    else
    {
        for (int i = range.topRow(); i <= range.bottomRow(); i++)
        {
            firstKeyComboBox->addItem(tr("Row %1").arg(i+1));
            secondKeyComboBox->addItem(tr("Row %1").arg(i+1));
            thirdKeyComboBox->addItem(tr("Row %1").arg(i+1));
        }
    }
}

TableSort SortDialog::getTableSort()
{
    QList<int> sortKeys;
    int offset = sortRowsRadioButton -> isChecked() ? range.leftColumn() : range.topRow();
    sortKeys.append(firstKeyComboBox -> currentIndex()+offset);

    if (secondKeyComboBox->currentIndex() > 0)
    {
        sortKeys.append(secondKeyComboBox -> currentIndex()+offset-1);
    }

    if (thirdKeyComboBox->currentIndex() > 0)
    {
        sortKeys.append(thirdKeyComboBox -> currentIndex()+offset-1);
    }

    QList<bool> ascending;
    ascending.append(firstKeyOrderComboBox->currentIndex() == 0);

    if (secondKeyComboBox->currentIndex() > 0)
    {
        ascending.append(secondKeyOrderComboBox->currentIndex() == 0);
    }

    if (thirdKeyComboBox->currentIndex() > 0)
    {
        ascending.append(thirdKeyOrderComboBox -> currentIndex() == 0);
    }

    TableSort::SortDirection sortDirection = sortRowsRadioButton->isChecked()
            ? TableSort::SortRows : TableSort::SortColumns;

    Qt::CaseSensitivity caseSensitivity = caseSensitiveCheckBox -> isChecked()
            ? Qt::CaseSensitive : Qt::CaseInsensitive;

    QString customOrderString = useCustomOrderCheckBox -> isChecked()
            ? customOrderComboBox->currentText() : QString();

    TableSort tableSort(range, sortKeys, ascending, sortDirection,
                        caseSensitivity, customOrderString);
    return tableSort;
}

