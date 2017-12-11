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

#include "Cell.h"
#include "Calculator.h"
#include "Table.h"
#include <iostream> //for debugging

QDataStream& operator<<(QDataStream &out, const Cell &cell)
{
    out << cell.data(Qt::TextAlignmentRole).toInt()
        << cell.data(Qt::BackgroundRole).value<QBrush>()
        << cell.data(Qt::ForegroundRole).value<QBrush>()
        << cell.data(Qt::FontRole).value<QFont>()
        << cell.data(Table::EditorRole).toInt()
        << cell.data(Qt::EditRole).toString();
    return out;
}

QDataStream& operator>>(QDataStream &in, Cell &cell)
{
    int alignment;
    QBrush background;
    QBrush foreground;
    QFont font;
    int editor;
    QString string;
    in >> alignment >> background >> foreground >> font >> editor >> string;
    cell.setData(Qt::TextAlignmentRole, alignment);
    cell.setData(Qt::BackgroundRole, background);
    cell.setData(Qt::ForegroundRole, foreground);
    cell.setData(Qt::FontRole, font);
    cell.setData(Table::EditorRole, editor);
    cell.setData(Qt::EditRole, string);
    return in;
}

Cell::Cell()
    : QTableWidgetItem()
{
    setData(Qt::TextAlignmentRole, static_cast<int>(Qt::AlignLeft|Qt::AlignVCenter));
    setData(Qt::BackgroundRole, QBrush(QColor(Qt::white)));
    setData(Qt::ForegroundRole, QBrush(QColor(Qt::black)));
    editor = Table::TextLineEditor;
}

QTableWidgetItem* Cell::clone() const
{
    return new Cell(*this);
}

QVariant Cell::data(int role) const
{
    if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
    {
        QString cellData = QTableWidgetItem::data(Qt::EditRole).toString();

        if (cellData.startsWith("/="))
        {
            cellData.remove(0,1);
            return cellData;
        }
        else
        {
            return Calculator::calculator() ->
                    calculate(static_cast<Table*>(tableWidget()), row(), column());
        }
    }
    else if (role == Table::EditorRole)
    {
        return editor;
    }
    else
    {
        return QTableWidgetItem::data(role);
    }
}

void Cell::setData(int role, const QVariant &newValue)
{
    if (role == Table::EditorRole)
    {
        editor = newValue.toInt();
    }
    else
    {
        QTableWidgetItem::setData(role, newValue);
    }
}

