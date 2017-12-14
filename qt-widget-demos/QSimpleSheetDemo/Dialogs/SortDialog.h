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

#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include <QTableWidgetSelectionRange>
#include "ui_SortDialog.h"
class TableSort;

class SortDialog : public QDialog, public Ui::SortDialog
{
    Q_OBJECT

public:
    SortDialog(const QTableWidgetSelectionRange&, QWidget* = 0);
    TableSort getTableSort();

private slots:
    void setSortKeys();

private:
    QTableWidgetSelectionRange range;
};

#endif
