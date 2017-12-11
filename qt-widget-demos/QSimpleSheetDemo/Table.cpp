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

#include <iostream> //NOTE for debuging
#include <cmath>
#include <QMessageBox>
#include "Table.h"
#include "Cell.h"
#include "ItemDelegate.h"
#include "Graphic.h"
#include "Commands.h"
#include "PictureGraphic.h"

Table::Table(QWidget *parent)
    : QTableWidget(parent)
{
    undoStack = new QUndoStack(this);
    setSelectionMode(QAbstractItemView::ContiguousSelection);
    setItemPrototype(new Cell);
    ItemDelegate *itemDelegate = new ItemDelegate(QTableWidget::itemDelegate());
    setItemDelegate(itemDelegate);
    connect(itemDelegate, SIGNAL(dataChangedSignal(int, int, QString&, QString&)),
            this, SIGNAL(userChangedItemDataSignal(int, int, QString&, QString&)));
    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(someThingChanged()));
    selectedGraphic = 0;
}

///===================================================================

void Table::newSheet(int rowCount, int columnCount)
{
    setRowCount(0);
    setColumnCount(0);
    setRowCount(rowCount);
    setColumnCount(columnCount);
    adjustHorizontalHeader();
    undoStack->clear();
    for (int i=0; i<graphics.size(); i++)
        delete graphics[i];
    graphics.clear();
}

bool Table::writeSheet(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("Saving Failed"),
                             tr("Cannot write to file %1:\n%2")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }

    setCursor(Qt::WaitCursor);

    QDataStream outStream(&file);
    outStream.setVersion(QDataStream::Qt_4_2);

    int rows = rowCount();
    int columns = columnCount();

    outStream << quint32(MagicWord);
    outStream << qint16(rows) << qint16(columns);

    QTableWidgetItem *curItem;

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++)
        {
            curItem = item(i,j);
            if (curItem)
            {
                Cell *curCell = static_cast<Cell*>(curItem);
                outStream << qint16(i) << qint16(j) << *curCell;
            }
        }
    }

    outStream << qint16(-1); //start writing graphics
    for (int i=0; i<graphics.size(); i++)
        if (graphics[i]->isVisible())
            graphics[i]->out(outStream);

    unsetCursor();
    return true;
}

bool Table::readSheet(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Reading Failed"),tr("Cannot read the file %1 :\n%2")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }

    QDataStream inStream(&file);
    inStream.setVersion(QDataStream::Qt_4_2);

    quint32 magicWord;
    inStream >> magicWord;
    if (magicWord != MagicWord)
    {
        QMessageBox::warning(this, tr("Bad File"), tr("Unknown file format!"));
        return false;
    }

    setCursor(Qt::WaitCursor);

    qint16 row, column;
    QString text;
    inStream >> row >> column;
    newSheet(row, column);

    while(!file.atEnd())
    {
        Cell *curCell = new Cell;
        inStream >> row;
        if (row == -1)
            //fetching rows and cells are finished, now start fetching graphics.
            break;
        inStream >> column >> *curCell;
        setItem(row, column, curCell);
    }

    while(!file.atEnd())
    {
        qint16 graphicType;
        inStream >> graphicType;
        Graphic *newGraphic = createGraphic(graphicType);
        newGraphic->in(inStream);
        addGraphic(newGraphic);
    }

    unsetCursor();
    return true;
}

///===================================================================

QString Table::getItemText(int row, int column, int role) const
{
    QTableWidgetItem *curItem = item(row, column);

    if (curItem)
        return curItem->data(role).toString();
    else
        return "";
}

QString Table::getCurrentItemText(int role) const
{
    return getItemText(currentRow(), currentColumn(), role);
}

QString Table::getItemsText(const QTableWidgetSelectionRange &range, int role) const
{
    QString str;

    for (int i=range.topRow(); i<=range.bottomRow(); i++)
    {
        if (i!=range.topRow())
        {
            str += '\n';
        }

        for (int j=range.leftColumn(); j<=range.rightColumn(); j++)
        {
            if (j!= range.leftColumn())
            {
                str += '\t';
            }

            str += getItemText(i,j, role);
        }
    }

    return str;
}

bool Table::setItemText(int row, int column, const QString &text)
{
    QTableWidgetItem *curItem = createGetItem(row, column);
    curItem->setText(text);
    return true;
}

QByteArray Table::getItemInByteArray(int row, int column) const
{
    QByteArray byteArray;
    QDataStream outStream(&byteArray, QIODevice::WriteOnly);
    Cell *cell = static_cast<Cell*>(item(row, column));

    if (cell)
    {
        outStream << *cell;
    }

    return byteArray;
}

QByteArray Table::getItemsInByteArray(const QTableWidgetSelectionRange &range) const
{
    QByteArray byteArray;
    QDataStream outStream(&byteArray, QIODevice::WriteOnly);

    outStream << range.rowCount() << range.columnCount();

    for (int i=range.topRow(); i<=range.bottomRow(); i++)
    {
        for (int j=range.leftColumn(); j<=range.rightColumn(); j++)
        {
            outStream << getItemInByteArray(i,j);
        }
    }

    return byteArray;
}

int Table::getItemEditor(int row, int column) const
{
    QTableWidgetItem *curItem = item(row, column);

    if (!curItem)
    {
        return 0;
    }
    else
    {
        return curItem->data(EditorRole).toInt();
    }
}

bool Table::setItemEditor(int row, int column, int editor)
{
    QTableWidgetItem *curItem = createGetItem(row, column);
    curItem->setData(EditorRole, editor);
    return true;
}

QString Table::getCurrentItemLocation() const
{
    QString location;
    encodePosition(location, currentRow(), currentColumn());
    return location;
}

QFont Table::getItemFont(int row, int column) const
{
    QTableWidgetItem *curItem = item(row, column);

    if (!curItem)
    {
        return QFont();
    }
    else
    {
        return curItem->data(Qt::FontRole).value<QFont>();
    }
}

void Table::setItemFont(int row, int column, const QFont &font)
{
    createGetItem(row, column)->setData(Qt::FontRole, font);
}

int Table::getItemAlignment(int row, int column) const
{
    QTableWidgetItem *curItem = item(row, column);

    if (!curItem)
    {
        return (Qt::AlignLeft | Qt::AlignVCenter);
    }
    else
    {
        return curItem->data(Qt::TextAlignmentRole).toInt();
    }
}

void Table::setItemAlignment(int row, int column, int alignment)
{
    createGetItem(row, column)->setData(Qt::TextAlignmentRole, alignment);
}

QBrush Table::getItemBackground(int row, int column) const
{
    QTableWidgetItem *curItem = item(row, column);

    if (!curItem)
    {
        return QBrush(QColor(Qt::white));
    }
    else
    {
        QBrush brush = curItem->data(Qt::BackgroundRole).value<QBrush>();
        return brush;
    }
}

void Table::setItemBackground(int row, int column, const QBrush &brush)
{
    createGetItem(row, column)->setData(Qt::BackgroundRole, brush);
}

QBrush Table::getItemForeground(int row, int column) const
{
    QTableWidgetItem *curItem = item(row, column);

    if (!curItem)
    {
        return QBrush(QColor(Qt::black));
    }
    else
    {
        return curItem->data(Qt::ForegroundRole).value<QBrush>();
    }
}

void Table::setItemForeground(int row, int column, const QBrush &brush)
{
    createGetItem(row, column)->setData(Qt::ForegroundRole, brush);
}

///===================================================================
Graphic* Table::getGraphic(int num) const
{
    if (num >= 0 && num < graphics.size())
        return graphics[num];
    else
        return 0;
}

QByteArray Table::getGraphicInByteArray(const Graphic *curGraphic) const
{
    QByteArray byteArray;
    QDataStream outStream(&byteArray, QIODevice::WriteOnly);
    curGraphic->out(outStream);
    return byteArray;
}

Graphic* Table::createGraphic(int graphicType) const
{
    if (graphicType == ImageType)
        return new PictureGraphic(viewport());
    else
        return 0;
}

Graphic* Table::getSelectedGraphic() const
{
    return selectedGraphic;
}

int Table::getGraphicCount() const
{
    return graphics.size();
}

void Table::deleteGraphic(int num)
{
    if (num >= 0 && num < graphics.size())
        //graphics should not be deleted to support Undo and Redo;
        graphics[num]->hide();
    someThingChanged();
}

void Table::deleteGraphic(Graphic *graphicPointer)
{
    for (int i=0; i<graphics.size(); i++)
        if (graphics[i] == graphicPointer)
            deleteGraphic(i);
    if (selectedGraphic == graphicPointer)
        selectedGraphic = 0;
}

void Table::addGraphic(Graphic *newGraphic)
{
    int i;
    if (!newGraphic)
        return;
    for (i=0; i<graphics.size() && graphics[i] != newGraphic ; i++);
    if (i == graphics.size()) //if newGraphic does not exist:
    {
        graphics.append(newGraphic);
        connect(newGraphic, SIGNAL(graphicDraggedSignal(Graphic*, QPoint, QPoint)),
                this, SLOT(graphicDraggedSlot(Graphic*, QPoint, QPoint)));
        connect(newGraphic, SIGNAL(graphicResizedSignal(Graphic*, QSize, QSize,
                                                        Graphic::BoundaryPosition)),
                this, SLOT(graphicResizedSlot(Graphic*,QSize,QSize,Graphic::BoundaryPosition)));
        connect(newGraphic, SIGNAL(graphicSelectedSignal(Graphic*)),
                this, SLOT(graphicSelectedSlot(Graphic*)));
        connect(newGraphic, SIGNAL(graphicContextMenuSignal(QPoint)),
                this, SIGNAL(graphicContextMenuSignal(QPoint)));
        connect(newGraphic, SIGNAL(somethingChangedSignal()),
                this, SLOT(someThingChanged()));
    }
    newGraphic->show();
    someThingChanged();
}

///===================================================================

void Table::findNext(QString &text, Qt::CaseSensitivity cs, int findIn)
{
    if (text.isEmpty())
        return;

    int initialRow = currentRow();
    int initialColumn = currentColumn();
    int i=initialRow;
    int j=initialColumn;
    bool found = false;

    do
    {
        j++;
        if (j >= columnCount())
        {
            j=0;
            i++;
        }
        if (i >= rowCount())
            i=0;

        QString itemText = findIn == FindInFormula ? getItemText(i, j, Qt::EditRole) : getItemText(i, j);
        if (itemText.contains(text, cs))
        {
            found = true;
            break;
        }
    } while(i!=initialRow || j!=initialColumn);

    if (found)
        setCurrentCell(i,j);
}

void Table::findPrevious(QString &text, Qt::CaseSensitivity cs, int findIn)
{
    if (text.isEmpty())
        return;

    int initialRow = currentRow();
    int initialColumn = currentColumn();
    int i=initialRow;
    int j=initialColumn;
    bool found = false;

    do
    {
        j--;
        if (j < 0)
        {
            j=columnCount()-1;
            i--;
        }
        if (i < 0)
            i=rowCount()-1;

        QString itemText = findIn == FindInFormula ? getItemText(i, j, Qt::EditRole) : getItemText(i, j);
        if (itemText.contains(text, cs))
        {
            found = true;
            break;
        }
    } while(i!=initialRow || j!=initialColumn);

    if (found)
        setCurrentCell(i,j);
}

///===================================================================

void Table::sort(TableSort tableSort)
{
    QTableWidgetSelectionRange range = tableSort.getRange();
    QList<int> rowsOrColumns; //TODO: can we do it without QList to get higher speed?

    if (tableSort.getSortDirection() == TableSort::SortRows)
        for (int i=range.topRow(); i<=range.bottomRow(); i++)
            rowsOrColumns.append(i);
    else
        for (int j=range.leftColumn(); j<=range.rightColumn(); j++)
            rowsOrColumns.append(j);

    tableSort.setTable(this);
    qStableSort(rowsOrColumns.begin(), rowsOrColumns.end(), tableSort);

    QTableWidgetItem *cells[10][10];
    for (int i=0; i<range.rowCount(); i++)
        for (int j=0; j<range.columnCount(); j++)
            cells[i][j] = takeItem(i+range.topRow(), j+range.leftColumn());

    if (tableSort.getSortDirection() == TableSort::SortRows)
    {
        for (int i=0; i<range.rowCount(); i++)
            for (int j=0; j<range.columnCount(); j++)
                setItem(i+range.topRow(), j+range.leftColumn(),
                        cells[ rowsOrColumns[i]-range.topRow() ][j]);
    }
    else
    {
        for (int i=0; i<range.rowCount(); i++)
            for (int j=0; j<range.columnCount(); j++)
                setItem(i+range.topRow(), j+range.leftColumn(),
                        cells[i][rowsOrColumns[j]-range.leftColumn()]);
    }
}

///===================================================================

void Table::insertRows(int position, int amount)
{
    for (int i=0; i<amount; i++)
        insertRow(position);

    QTableWidgetSelectionRange selectionRange(position, 0, position+amount-1, columnCount()-1);
    clearSelection();
    setRangeSelected(selectionRange, true);

    someThingChanged();
}

void Table::insertColumns(int position, int amount)
{
    for (int i=0; i<amount; i++)
        insertColumn(position);

    adjustHorizontalHeader();
    QTableWidgetSelectionRange selectionRange(0, position, rowCount()-1, position+amount-1);
    clearSelection();
    setRangeSelected(selectionRange, true);

    someThingChanged();
}

///===================================================================

void Table::selectAll()
{
    clearSelection();
    QTableWidget::selectAll();
}

void Table::selectCurrentRow()
{
    selectRow(currentRow());
}

void Table::selectCurrentColumn()
{
    selectColumn(currentColumn());
}

///===================================================================

void Table::cut(QMimeData &mimeData)
{
    copy(mimeData);
    if (selectedGraphic == 0)
        deleteContents(getSelectedRange());
    else
        deleteGraphic(selectedGraphic);
}

void Table::copy(QMimeData &mimeData)
{
    if (selectedGraphic == 0)
    {
        QTableWidgetSelectionRange range = getSelectedRange();
        mimeData.setData(CELL_TYPE, getItemsInByteArray(range));
    }
    else
        mimeData.setData(GRAPHIC_TYPE, getGraphicInByteArray(getSelectedGraphic()));
}

bool Table::paste(const QMimeData &mimeData, int row, int column)
{
    if (mimeData.hasFormat(CELL_TYPE))
    {
        QByteArray byteArray = mimeData.data(CELL_TYPE);
        QDataStream inStream(&byteArray, QIODevice::ReadOnly);
        Cell *currentCell;
        int pasteDataRowCount;
        int pasteDataColumnCount;

        if (!inStream.atEnd())
            inStream >> pasteDataRowCount >> pasteDataColumnCount;
        if (pasteDataRowCount+row > rowCount() || pasteDataColumnCount+column > columnCount())
            return false;

        for (int i=0; i<pasteDataRowCount; i++)
        {
            for (int j=0; j<pasteDataColumnCount && !inStream.atEnd(); j++)
            {
                currentCell = new Cell;
                QByteArray cellByteArray;
                inStream >> cellByteArray;
                if (!cellByteArray.isEmpty())
                {
                    QDataStream cellInStream(&cellByteArray, QIODevice::ReadOnly);
                    cellInStream >> *currentCell;
                }
                setItem(row+i, column+j, currentCell);
            }
        }
        QTableWidgetSelectionRange selectionRange(row, column,row+pasteDataRowCount-1,
                                                  column+pasteDataColumnCount-1);
        clearSelection();
        setRangeSelected(selectionRange, true);
    }
    else if (mimeData.hasFormat(GRAPHIC_TYPE))
    {
        QByteArray byteArray = mimeData.data(GRAPHIC_TYPE);
        QDataStream inStream(&byteArray, QIODevice::ReadOnly);
        qint16 graphicType;
        inStream >> graphicType;
        Graphic *newGraphic = createGraphic(graphicType);
        newGraphic->in(inStream);
        addGraphic(newGraphic);
    }
    else if (mimeData.hasText())
    {
        QString str = mimeData.text();
        int pasteContentRows = str.count('\n')+1;
        int pasteContentColumns = str.count('\t')/pasteContentRows + 1;

        if (row+pasteContentRows > rowCount() || column+pasteContentColumns > columnCount())
            return false;

        QStringList sentences = str.split('\n');
        for (int i=0; i<pasteContentRows; i++)
        {
            QStringList words = sentences[i].split('\t');
            for (int j=0; j<pasteContentColumns; j++)
            {
                if (words[j].isEmpty() && !item(row+i, column+j))
                    continue;
                setItemText(row+i, column+j, words[j]);
            }
        }
        QTableWidgetSelectionRange selectionRange(row, column,
                                                  row+pasteContentRows-1,
                                                  column+pasteContentColumns-1);
        clearSelection();
        setRangeSelected(selectionRange, true);

    }
    else
        return false;

    return true;
}

///===================================================================

void Table::deleteContents(const QTableWidgetSelectionRange &range)
{
    for (int i=range.topRow(); i<=range.bottomRow(); i++)
    {
        for (int j=range.leftColumn(); j<=range.rightColumn(); j++)
        {
            QTableWidgetItem *curItem = item(i,j);
            if (curItem)
                delete curItem;
            //      curItem = 0;  //NOTE is it needed?
        }
    }
    someThingChanged();
}

void Table::deleteEntireRows(int position, int amount)
{
    for (int i=0; i<amount; i++)
        removeRow(position);
    clearSelection();
    someThingChanged();
}

void Table::deleteEntireColumns(int position, int amount)
{
    for (int i=0; i<amount; i++)
        removeColumn(position);
    clearSelection();
    adjustHorizontalHeader();
    someThingChanged();
}

///===================================================================

void Table::encodePosition(QString &text, int column)
{
    text.clear();
    QChar letter;

    letter = 'A' + column%26;
    text.insert(0, letter);

    if (column>=26)
    {
        column = column/26;
        do
        {
            column--;
            QChar letter('A'+column%26);
            text.insert(0, letter);
            column = column/26;
        } while(column>0);
    }
}

void Table::encodePosition(QString &text, int row, int column)
{
    encodePosition(text, column);
    text += QString::number(row+1);
}

void Table::encodeRange(QString &text, QTableWidgetSelectionRange range)
{
    QString position;
    encodePosition(position, range.topRow(), range.leftColumn());
    text = position;
    text += ':';
    encodePosition(position, range.bottomRow(), range.rightColumn());
    text += position;
}

bool Table::decodePosition(QString text, int &row, int &column)
{
    text = text.toUpper();
    QRegExpValidator validator(QRegExp("[A-Z]+[1-9][0-9]*"), 0);
    int pos = 0;
    if (validator.validate(text,pos) != QValidator::Acceptable)
        return false;

    row = column = 0;
    int letterCount = text.indexOf(QRegExp("[1-9]")); //returns the position of first digit (is equal to number of letters)

    for (int i=0; i<letterCount; i++)
        column += static_cast<int>(std::pow(26.0, letterCount-i-1)) * (text[i].unicode()-'A'+1);
    column--;

    for (int j=letterCount; j<text.length(); j++)
        row = row*10 + text[j].unicode()-'0';
    row--;

    return true;
}

bool Table::decodeRange(QString text, QTableWidgetSelectionRange &range)
{
    int topRow, bottomRow, leftColumn, rightColumn;
    text = text.toUpper();

    int colonPosition = text.indexOf(':');
    if (colonPosition == -1)
        return false;
    if (!decodePosition(text.mid(0, colonPosition), topRow, leftColumn))
        return false;
    if (!decodePosition(text.mid(colonPosition+1), bottomRow, rightColumn))
        return false;

    if (topRow > bottomRow)
    {
        int temp = topRow;
        topRow = bottomRow;
        bottomRow = temp;
    }
    if (leftColumn > rightColumn)
    {
        int temp = leftColumn;
        leftColumn = rightColumn;
        rightColumn = temp;
    }

    QTableWidgetSelectionRange r(topRow, leftColumn, bottomRow, rightColumn);
    range = r;
    return true;
}

///===================================================================

QUndoStack* Table::getUndoStack() const
{
    return undoStack;
}

void Table::someThingChanged()
{
    viewport()->update();
    emit modified();
}

void Table::graphicDraggedSlot(Graphic *curGraphic, QPoint oldPosition, QPoint newPosition)
{
    getUndoStack()->push(new GraphicDraggedCommand(curGraphic, oldPosition, newPosition));
}

void Table::graphicResizedSlot(Graphic *curGraphic, QSize oldSize,
                               QSize newSize, Graphic::BoundaryPosition boundaryPosition)
{
    getUndoStack()->push(new GraphicResizedCommand(curGraphic, oldSize, newSize,
                                                     boundaryPosition));
}


QTableWidgetSelectionRange Table::getSelectedRange()
{
    QList<QTableWidgetSelectionRange> range = selectedRanges();
    if (range.isEmpty())
        return QTableWidgetSelectionRange();
    return range.first();
}

void Table::adjustHorizontalHeader()
{
    int columns = columnCount();
    QTableWidgetItem *item;
    for (int i=0; i<columns; i++)
    {
        QString text;
        encodePosition(text, i);
        item = new QTableWidgetItem(text);
        setHorizontalHeaderItem(i, item);
    }
}

QTableWidgetItem* Table::createGetItem(int row, int column)
{
    if (row >= rowCount() || column >= columnCount())
        return 0;
    QTableWidgetItem *curItem = item(row, column);
    if (!curItem)
    {
        curItem = new Cell;
        setItem(row, column, curItem);
    }
    return curItem;
}

void Table::paintEvent(QPaintEvent *event)
{
    /*   for(int i=0; i<graphics.size(); i++) //NOTE: is it needed?
      graphics[i]->update();*/
    QTableWidget::paintEvent(event);
}

void Table::mousePressEvent(QMouseEvent *event)
{
    selectedGraphic = 0;
    QTableWidget::mousePressEvent(event);
}

void Table::graphicSelectedSlot(Graphic *curGraphic)
{
    selectedGraphic = curGraphic;
    //debugging:
    //std::cout << "selected" << getSelectedGraphic() << std::endl;
}

///===================================================================
///===================================================================

TableSort::TableSort(const QTableWidgetSelectionRange &r, const QList<int> &sk,
                     const QList<bool> &a, SortDirection sd, Qt::CaseSensitivity cs,
                     const QString &co)
    : range(r),
      sortKeys(sk),
      ascending(a),
      sortDirection(sd),
      caseSensitivity(cs)
{
    table = 0;
    if (!co.isEmpty())
        customOrder = co.split(QRegExp("\\s*,\\s*"));
}

bool TableSort::operator()(int firstPosition, int secondPosition) const
{
    if (!table)
        return false;

    int comparisonResult=0;
    for (int i=0; i<sortKeys.size() && comparisonResult==0; i++)
    {
        QString firstString;
        QString secondString;
        if (sortDirection == SortRows)
        {
            firstString = table->getItemText(firstPosition, sortKeys[i]);
            secondString = table->getItemText(secondPosition, sortKeys[i]);
        }
        else
        {
            firstString = table->getItemText(sortKeys[i], firstPosition);
            secondString = table->getItemText(sortKeys[i], secondPosition);
        }
        comparisonResult = compare(firstString, secondString);
        if (!ascending[i])
            comparisonResult *= -1;
    }

    return comparisonResult<0;
}

int TableSort::compare(const QString &firstString, const QString &secondString) const
{
    int comparisonResult = 0;
    if (customOrder.isEmpty())
        comparisonResult = firstString.compare(secondString, caseSensitivity);
    else
    {
        int indexOfFirstString = customOrder.indexOf(QRegExp(firstString,
                                                             caseSensitivity));
        int indexOfSecondString = customOrder.indexOf(QRegExp(secondString,
                                                              caseSensitivity));
        if (indexOfFirstString == indexOfSecondString)
            ;
        else if (indexOfFirstString == -1 && indexOfSecondString != -1)
            comparisonResult = 1;
        else if (indexOfFirstString != -1 && indexOfSecondString == -1)
            comparisonResult = -1;
        else
            comparisonResult = indexOfFirstString<indexOfSecondString ? -1 : 1;
    }

    return comparisonResult;
}





