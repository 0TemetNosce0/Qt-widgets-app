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

#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include "ItemDelegate.h"
#include "Table.h"
#include <iostream> //NOTE for debugging

ItemDelegate::ItemDelegate(QAbstractItemDelegate *d, QObject *parent)
    : QItemDelegate(parent)
    , lastItemDelegate(d)
{
    //empty body
}

QWidget* ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &view, const QModelIndex &index) const
{
    QWidget *editorWidget;
    int editorFormat = index.model()->data(index, Table::EditorRole).toInt();

    if (editorFormat == Table::TextLineEditor)
    {
        return lastItemDelegate->createEditor(parent, view, index);
    }
    else if (editorFormat == Table::DateEditor)
    {
        QDateEdit *editor = new QDateEdit(parent);
        editor->setDisplayFormat("dd/MM/yyyy");
        editor->setCalendarPopup(true);
        editorWidget = editor;
    }
    else if (editorFormat == Table::TimeEditor)
    {
        QTimeEdit *editor = new QTimeEdit(parent);
        editor->setDisplayFormat("h:mm:ss");
        editorWidget = editor;
    }
    else if (editorFormat == Table::IntegerEditor)
    {
        QSpinBox *editor = new QSpinBox(parent);
        //how to set the range to infinite?
        editor->setRange(-9999999, 9999999);
        editorWidget = editor;
    }
    else if (editorFormat == Table::DecimalEditor)
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        //how to set the range to infinite?
        editor->setRange(-9999999.9999999, 9999999.9999999);
        editor->setDecimals(3);
        editor->setSingleStep(0.1);
        editorWidget = editor;
    }
    else //should not happen
    {
        editorWidget = new QLineEdit(parent);
    }

    editorWidget->installEventFilter(const_cast<ItemDelegate*>(this));
    return editorWidget;
}

void ItemDelegate::setEditorData(QWidget *editorWidget, const QModelIndex &index) const
{
    int editorFormat = index.model()->data(index, Table::EditorRole).toInt();
    QVariant indexValue = index.model()->data(index, Qt::EditRole);

    if (editorFormat == Table::TextLineEditor)
    {
        QLineEdit *editor = dynamic_cast<QLineEdit*>(editorWidget);
        QString itemText = indexValue.toString();
        editor->setText(itemText);
    }
    else if (editorFormat == Table::DateEditor)
    {
        QDateEdit *editor = dynamic_cast<QDateEdit*>(editorWidget);
        editor->setDate(QDate::fromString(indexValue.toString(), "dd/MM/yyyy"));
    }
    else if (editorFormat == Table::TimeEditor)
    {
        QTimeEdit *editor = dynamic_cast<QTimeEdit*>(editorWidget);
        editor->setTime(QTime::fromString(indexValue.toString(), "h:mm:ss"));
    }
    else if (editorFormat == Table::IntegerEditor)
    {
        QSpinBox *editor = dynamic_cast<QSpinBox*>(editorWidget);
        editor->setValue(indexValue.toInt());
    }
    else if (editorFormat == Table::DecimalEditor)
    {
        QDoubleSpinBox *editor = dynamic_cast<QDoubleSpinBox*>(editorWidget);
        editor->setValue(indexValue.toDouble());
    }
}

void ItemDelegate::setModelData(QWidget *editorWidget, QAbstractItemModel *model, const QModelIndex &index) const
{
    QString oldData = model->data(index, Qt::EditRole).toString();
    QString newData;
    int editorFormat = index.model()->data(index, Table::EditorRole).toInt();

    if (editorFormat == Table::TextLineEditor)
    {
        QLineEdit *editor = dynamic_cast<QLineEdit*>(editorWidget);
        newData = editor->text();
    }
    else if (editorFormat == Table::DateEditor)
    {
        QDateEdit *editor = dynamic_cast<QDateEdit*>(editorWidget);
        newData = editor->date().toString("dd/MM/yyyy");
    }
    else if (editorFormat == Table::TimeEditor)
    {
        QTimeEdit *editor = dynamic_cast<QTimeEdit*>(editorWidget);
        newData = editor->time().toString("hh:mm:ss");
    }
    else if (editorFormat == Table::IntegerEditor)
    {
        QSpinBox *editor = dynamic_cast<QSpinBox*>(editorWidget);
        newData = editor->text();
    }
    else if (editorFormat == Table::DecimalEditor)
    {
        QDoubleSpinBox *editor = dynamic_cast<QDoubleSpinBox*>(editorWidget);
        newData = editor->text();
    }

    if (oldData != newData)
        emit dataChangedSignal(index.row(), index.column(), oldData, newData);
    // model->setData(index, newData);
    //NOTE: data wil be set by emiting this signal, so the upper line is not needed.

}


