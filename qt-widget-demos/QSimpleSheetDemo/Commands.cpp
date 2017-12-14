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

#include <iostream> //NOTE: for debugging
#include <QApplication>
#include <QClipboard>
#include "Commands.h"
#include "Graphic.h"
#include "PictureGraphic.h"
#include "MainWindow.h"
#include "Cell.h"

///   Data Changed

DataChanged::DataChanged(Table *t, int r, int c, const QString &od, const QString &nd)
    : table(t)
    , row(r)
    , column(c)
    , oldData(od)
    , newData(nd)
{
    setText(QObject::tr("Modify Cell"));
}

void DataChanged::undo()
{
    table->setItemText(row, column, oldData);
    table->setCurrentCell(row, column);
}

void DataChanged::redo()
{
    table->setItemText(row, column, newData);
    table->setCurrentCell(row, column);
}

///   Cut
CutCommand::CutCommand(Table *t)
    : table(t)
{
    setText(QObject::tr("Cut"));
    table->copy(oldData);
    selectedRange = table->getSelectedRange();
    selectedGraphic = table->getSelectedGraphic();
}

void CutCommand::undo()
{
    if (oldData.hasFormat(CELL_TYPE))
    {
        table->paste(oldData, selectedRange.topRow(), selectedRange.leftColumn());
    }
    else
    {
        table->addGraphic(selectedGraphic);
    }
}

void CutCommand::redo()
{
    if (oldData.hasFormat(CELL_TYPE))
    {
        table->deleteContents(selectedRange);
        QMimeData *newMimeData = new QMimeData;
        newMimeData->setData(CELL_TYPE, oldData.data(CELL_TYPE));
        QApplication::clipboard()->setMimeData(newMimeData);
    }
    else if (oldData.hasFormat(GRAPHIC_TYPE))
    {
        table->deleteGraphic(selectedGraphic);
        QMimeData *newMimeData = new QMimeData;
        newMimeData->setData(GRAPHIC_TYPE, oldData.data(GRAPHIC_TYPE));
        QApplication::clipboard()->setMimeData(newMimeData);
    }
}

///   Paste
PasteCommand::PasteCommand(Table *t)
{
    setText(QObject::tr("Paste"));
    table = t;

    if (QApplication::clipboard()->mimeData()->hasFormat(CELL_TYPE))
    {
        QByteArray byteArray = QApplication::clipboard()->mimeData()->data(CELL_TYPE);
        QDataStream inStream(&byteArray, QIODevice::ReadOnly);
        newData.setData(CELL_TYPE, byteArray);
        row = table->currentRow();
        column = table->currentColumn();
        int numOfRows;
        int numOfColumns;
        inStream >> numOfRows >> numOfColumns;

        QTableWidgetSelectionRange range(row, column, row+numOfRows-1, column+numOfColumns-1);
        oldData.setData(CELL_TYPE, table->getItemsInByteArray(range));
    }
    else if (QApplication::clipboard()->mimeData()->hasFormat(GRAPHIC_TYPE))
    {
        QByteArray byteArray = QApplication::clipboard()->mimeData()->data(GRAPHIC_TYPE);
        QDataStream inStream(&byteArray, QIODevice::ReadOnly);
        newData.setData(GRAPHIC_TYPE, byteArray);
        qint16 graphicType;
        inStream >> graphicType;
        graphic = table->createGraphic(graphicType);
        graphic->in(inStream);
        graphic->move(table->columnViewportPosition(table->currentColumn()),
                        table->rowViewportPosition(table->currentRow()));
    }
    else if (QApplication::clipboard()->mimeData()->hasText())
    {
        QString string = QApplication::clipboard()->mimeData()->text();
        newData.setText(string);
        row = table->currentRow();
        column = table->currentColumn();
        int rowCount = string.count('\n')+1;
        int columnCount = string.count('\t')/rowCount + 1;
        QTableWidgetSelectionRange range(row, column, row+rowCount-1, column+columnCount-1);
        oldData.setData(CELL_TYPE, table->getItemsInByteArray(range));
    }
}

void PasteCommand::undo()
{
    if (newData.hasFormat(CELL_TYPE) || newData.hasText())
    {
        table->paste(oldData, row, column);
    }
    else if (newData.hasFormat(GRAPHIC_TYPE))
    {
        table->deleteGraphic(graphic);
    }
}

void PasteCommand::redo()
{
    if (newData.hasFormat(CELL_TYPE) || newData.hasText())
    {
        table->paste(newData, row, column);
    }
    else if (newData.hasFormat(GRAPHIC_TYPE))
    {
        table->addGraphic(graphic);
    }
}

///   Insert Rows
InsertRowsCommand::InsertRowsCommand(Table *t, int pos, int am)
{
    setText(QObject::tr("Insert Row(s)"));
    table = t;
    position = pos == Table::InsertAfter ? 1 : 0;
    position += table->currentRow();
    amount = am;
}

void InsertRowsCommand::undo()
{
    table->deleteEntireRows(position, amount);
}

void InsertRowsCommand::redo()
{
    table->insertRows(position, amount);
}

///   Insert Columns
InsertColumnsCommand::InsertColumnsCommand(Table *t, int pos, int am)
    : table(t)
{
    setText(QObject::tr("Insert Column(s)"));
    position = pos == Table::InsertAfter ? 1 : 0;
    position += table->currentColumn();
    amount = am;
}

void InsertColumnsCommand::undo()
{
    table->deleteEntireColumns(position, amount);
}

void InsertColumnsCommand::redo()
{
    table->insertColumns(position, amount);
}

///   Insert Image
InsertImageCommand::InsertImageCommand(Table *t, const QImage &i, int x, int y)
    : table(t)
    , xCoordinate(x)
    , yCoordinate(y)
{
    setText(QObject::tr("Insert Image"));
    graphic = new PictureGraphic(table->viewport(), i);
    graphic->move(xCoordinate, yCoordinate);
}

void InsertImageCommand::undo()
{
    table->deleteGraphic(graphic);
}

void InsertImageCommand::redo()
{
    table->addGraphic(graphic);
}

///   Delete Contents
DeleteContents::DeleteContents(Table *t)
    : table (t)
{
    setText(QObject::tr("Delete"));
    range = table->getSelectedRange();
    graphic = table->getSelectedGraphic();

    if (!graphic)
    {
        table->copy(oldData);
    }
}

void DeleteContents::undo()
{
    if (oldData.hasFormat(CELL_TYPE))
    {
        table->paste(oldData, range.topRow(), range.leftColumn());
    }
    else if (graphic)
    {
        table->addGraphic(graphic);
    }
}

void DeleteContents::redo()
{
    if (oldData.hasFormat(CELL_TYPE))
    {
        table->deleteContents(range);
    }
    else if (graphic)
    {
        table->deleteGraphic(graphic);
    }
}

///   Delete Entire Rows
DeleteEntireRows::DeleteEntireRows(Table *t, int pos, int am)
{
    setText(QObject::tr("Delete Row(s)"));
    table = t;
    position = pos;
    amount = am;
    QTableWidgetSelectionRange range(position, 0, position+amount-1, table->columnCount()-1);
    oldData.setData(CELL_TYPE, table->getItemsInByteArray(range));
}

void DeleteEntireRows::undo()
{
    table->insertRows(position, amount);
    table->paste(oldData, position, 0);
}

void DeleteEntireRows::redo()
{
    table->deleteEntireRows(position, amount);
}

///   Delete Entire Columns
DeleteEntireColumns::DeleteEntireColumns(Table *t, int pos, int am)
{
    setText(QObject::tr("Delete Column(s)"));
    table = t;
    position = pos;
    amount = am;
    QTableWidgetSelectionRange range(0, position, table->rowCount()-1, position+amount-1);
    oldData.setData(CELL_TYPE, table->getItemsInByteArray(range));
}

void DeleteEntireColumns::undo()
{
    table->insertColumns(position, amount);
    table->paste(oldData, 0, position);
}

void DeleteEntireColumns::redo()
{
    table->deleteEntireColumns(position, amount);
}

///   Change Cells Editor
ChangeCellsEditor::ChangeCellsEditor(Table *t, QTableWidgetSelectionRange r, int e)
    : table(t)
    , range(r)
    , newEditor(e)
{
    setText(QObject::tr("Change Data Format"));

    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            oldEditors.append(table->getItemEditor(i+range.topRow(), j+range.leftColumn()));
        }
    }
}

void ChangeCellsEditor::undo()
{
    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            table->setItemEditor(i+range.topRow(), j+range.leftColumn(),
                                 oldEditors[i*range.columnCount()+j]);
        }
    }
}

void ChangeCellsEditor::redo()
{
    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            table->setItemEditor(i+range.topRow(), j+range.leftColumn(), newEditor);
        }
    }
}

///   Change Cells Font

ChangeCellsFont::ChangeCellsFont(Table *t, QTableWidgetSelectionRange r, QFont f)
    : table(t)
    , range(r)
    , newFont(f)
{
    setText(QObject::tr("Change Font"));

    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            oldFonts.append(table->getItemFont(i+range.topRow(), j+range.leftColumn()));
        }
    }
}

void ChangeCellsFont::undo()
{
    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            table->setItemFont(i+range.topRow(), j+range.leftColumn(),
                               oldFonts[i*range.columnCount()+j]);
        }
    }
}

void ChangeCellsFont::redo()
{
    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            table->setItemFont(i+range.topRow(), j+range.leftColumn(), newFont);
        }
    }
}

///   Change Cells Alignment

ChangeCellsAlignment::ChangeCellsAlignment(Table *t, QTableWidgetSelectionRange r, int a)
    : table(t)
    , range(r)
    , newAlignment(a)
{
    setText(QObject::tr("Change Alignment"));

    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            oldAlignments.append(table->getItemAlignment(i+range.topRow(),
                                                         j+range.leftColumn()));
        }
    }
}

void ChangeCellsAlignment::undo()
{
    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            table->setItemAlignment(i+range.topRow(), j+range.leftColumn(),
                                    oldAlignments[i*range.columnCount()+j]);
        }
    }
}

void ChangeCellsAlignment::redo()
{
    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            table->setItemAlignment(i+range.topRow(), j+range.leftColumn(), newAlignment);
        }
    }
}

///   Change Cells Background

ChangeCellsBackground::ChangeCellsBackground(Table *t, QTableWidgetSelectionRange r, QColor b)
    : table(t)
    , range(r)
    , newBackground(b)
{
    setText(QObject::tr("Change Background"));

    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            oldBackgrounds.append(table->getItemBackground(i+range.topRow(),
                                                           j+range.leftColumn()).color());
        }
    }
}

void ChangeCellsBackground::undo()
{
    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            table->setItemBackground(i+range.topRow(), j+range.leftColumn(),
                                     QBrush(oldBackgrounds[i*range.columnCount()+j]));
        }
    }
}

void ChangeCellsBackground::redo()
{
    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            table->setItemBackground(i+range.topRow(), j+range.leftColumn(),
                                     QBrush(newBackground));
        }
    }
}


///   Change Cells Foreground
ChangeCellsForeground::ChangeCellsForeground(Table *t, QTableWidgetSelectionRange r, QColor f)
    : table(t)
    , range(r)
    , newForeground(f)
{
    setText(QObject::tr("Change Text Color"));

    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            oldForegrounds.append(table->getItemForeground(i+range.topRow(),
                                                           j+range.leftColumn()).color());
        }
    }
}

void ChangeCellsForeground::undo()
{
    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            table->setItemForeground(i+range.topRow(), j+range.leftColumn(),
                                     QBrush(oldForegrounds[i*range.columnCount()+j]));
        }
    }
}

void ChangeCellsForeground::redo()
{
    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            table->setItemForeground(i+range.topRow(), j+range.leftColumn(), QBrush(newForeground));
        }
    }
}

///   Sort

SortCommand::SortCommand(Table *t, const TableSort &ts)
    : table(t)
    , tableSort(ts)
{
    setText(QObject::tr("Sort"));
    range = table->getSelectedRange();
    oldData.setData(CELL_TYPE, table->getItemsInByteArray(range));
}

void SortCommand::undo()
{
    table->paste(oldData, range.topRow(), range.leftColumn());
}

void SortCommand::redo()
{
    table->sort(tableSort);
}

///   Graphic Dragged
GraphicDraggedCommand::GraphicDraggedCommand(Graphic *g, QPoint op, QPoint np)
    : graphic(g)
    , oldPosition(op)
    , newPosition(np)
{
    setText(QObject::tr("Move Graphic"));
}

void GraphicDraggedCommand::undo()
{
    graphic->move(oldPosition);
}

void GraphicDraggedCommand::redo()
{
    graphic->move(newPosition);
}

///   Graphic Resized
GraphicResizedCommand::GraphicResizedCommand(Graphic *g, QSize os, QSize ns,
                                             Graphic::BoundaryPosition bp)
    : graphic(g)
    , oldSize(os)
    , newSize(ns)
    , boundaryPosition(bp)
{
    setText(QObject::tr("Resize Graphic"));
}

void GraphicResizedCommand::undo()
{
    graphic->scale(oldSize.width(), oldSize.height(),
                     Qt::IgnoreAspectRatio, boundaryPosition);
}

void GraphicResizedCommand::redo()
{
    graphic->scale(newSize.width(), newSize.height(),
                     Qt::IgnoreAspectRatio, boundaryPosition);
}
