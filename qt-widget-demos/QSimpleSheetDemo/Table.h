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


#ifndef SHPREADSHEET_H
#define SHPREADSHEET_H

#include <QTableWidget>
#include <QTableWidgetSelectionRange>
#include "Graphic.h"
class QUndoStack;
class QMimeData;
class TableSort;

#define GRAPHIC_TYPE "Graphic"
#define CELL_TYPE    "Cell"

class Table : public QTableWidget
{
    Q_OBJECT

public:
    Table(QWidget* = 0);

    void newSheet(int = 10, int = 10);
    bool writeSheet(const QString&);
    bool readSheet(const QString&);

    //(row,column,role) returns the item's text in the given position (row, column),
    //for the given role (DisplayRole, EditRole,...)
    QString getItemText(int, int, int = Qt::DisplayRole) const;
    //returns the text of the current cell for the given role
    QString getCurrentItemText(int = Qt::DisplayRole) const;
    //returns the text of cells in the selection for the given role
    QString getItemsText(const QTableWidgetSelectionRange&, int = Qt::DisplayRole) const;
    //returns the location of current cell in "AA1" format
    bool setItemText(int, int, const QString &);
    QByteArray getItemInByteArray(int, int) const;
    QByteArray getItemsInByteArray(const QTableWidgetSelectionRange&) const;
    int getItemEditor(int, int) const;
    bool setItemEditor(int, int, int);
    QString getCurrentItemLocation() const;
    QFont getItemFont(int, int) const;
    void setItemFont(int, int, const QFont&);
    int getItemAlignment(int, int) const;
    void setItemAlignment(int, int, int);
    QBrush getItemBackground(int, int) const;
    void setItemBackground(int, int, const QBrush&);
    QBrush getItemForeground(int, int) const;
    void setItemForeground(int, int, const QBrush&);

    Graphic* getGraphic(int) const;
    Graphic* getSelectedGraphic() const;
    QByteArray getGraphicInByteArray(const Graphic*) const;
    Graphic* createGraphic(int) const;
    int getGraphicCount() const;
    void deleteGraphic(int);
    void deleteGraphic(Graphic*);
    void addGraphic(Graphic*);

    void findNext(QString&, Qt::CaseSensitivity, int);
    void findPrevious(QString&, Qt::CaseSensitivity, int);

    void sort(TableSort);

    void insertRows(int, int);
    void insertColumns(int, int);

    void deleteContents(const QTableWidgetSelectionRange&);
    void deleteEntireRows(int, int);
    void deleteEntireColumns(int, int);

    void cut(QMimeData&); //cut data to a QMimeData
    void copy(QMimeData&); //copy data to a QMimeData
    bool paste(const QMimeData&, int, int); //paste data from a QMimeData, at row, column

    // receives an integer (column) and encode it
    // into a string in format "A","B",...,"AA","AB",...
    static void encodePosition(QString&, int);
    // receives two integer (row, column) and encodes
    // them into a string in format "A1","B1",...,"AA2","AB2",...
    static void encodePosition(QString&, int, int);
    // receives a QTableWidgetSelectionRange and encodes it
    // into a string in format "A1:B1"
    static void encodeRange(QString&, QTableWidgetSelectionRange);
    // receives a string in format "AB1" and decodes it into
    // two integer (row, column)
    static bool decodePosition(QString, int&, int&);
    // receives a string in format "A1:B1" and decodes it into
    // a QTableWidgetSelectionRange
    static bool decodeRange(QString, QTableWidgetSelectionRange&);

    QUndoStack* getUndoStack() const;
    QTableWidgetSelectionRange getSelectedRange();
    enum {InsertAfter, InsertBefore};
    enum {FindInFormula, FindInDisplayText};
    enum {EditorRole = 32};
    enum {TextLineEditor = 0, DateEditor, TimeEditor, IntegerEditor, DecimalEditor};
    enum {ImageType};

public slots:
    void selectAll();
    void selectCurrentRow();
    void selectCurrentColumn();

private slots:
    void someThingChanged();
    void graphicDraggedSlot(Graphic*, QPoint, QPoint);
    void graphicResizedSlot(Graphic*, QSize, QSize, Graphic::BoundaryPosition);
    void graphicSelectedSlot(Graphic*);

signals:
    void userChangedItemDataSignal(int, int, QString&, QString&);
    void graphicContextMenuSignal(QPoint);
    void modified();

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);

private:
    enum {Selected, Changed};
    enum {MagicWord = 0x93FE584F};
    void adjustHorizontalHeader();
    QTableWidgetItem* createGetItem(int, int);
    QUndoStack *undoStack;
    QList<Graphic*> graphics;
    Graphic* selectedGraphic;
};

class TableSort
{
public:
    enum SortDirection {SortRows, SortColumns};
    TableSort(const QTableWidgetSelectionRange&, const QList<int>&,
              const QList<bool>&, SortDirection, Qt::CaseSensitivity, const QString&);
    bool operator()(int, int) const;
    void setTable(Table *t)
    { table = t; }
    QTableWidgetSelectionRange getRange() const
    { return range; }
    SortDirection getSortDirection() const
    { return sortDirection; }

private:
    Table *table;
    QTableWidgetSelectionRange range;
    QList<int> sortKeys;
    QList<bool> ascending;
    SortDirection sortDirection;
    Qt::CaseSensitivity caseSensitivity;
    QStringList customOrder;

    int compare(const QString&, const QString&) const;
};

#endif
