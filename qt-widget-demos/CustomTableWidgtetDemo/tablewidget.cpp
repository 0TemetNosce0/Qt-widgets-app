/**
 * tablewidget.cpp
 *
 * \author ramesh
 * \version $Id: tablewidget.cpp,v 1.1 2009/05/04 07:26:06 ramesh Exp $
 */
#include "tablewidget.h"
#include <QTableWidgetSelectionRange>
#include <QHeaderView>
#include <QScrollBar>
#include <QPushButton>
#include <QGridLayout>
#include <QCloseEvent>
#include <QDebug>

	// This constructor will initialise the member variables
TableWidget::TableWidget(QTableWidget *parent)
	: QTableWidget(parent)
{
    pr = 0;
    pc = 0;
    nRows = 0;
    nCols = 0;
}

TableWidget::TableWidget(int nCellMaxRow, int aCellMaxCol, int aRowHeight,
        int aColWidth, int aRow, int aCol, QWidget *parent)
		: QTableWidget(aRow,aCol,parent)
{
    maxRowCell = nCellMaxRow;
    maxColCell = aCellMaxCol;
    height = aRowHeight;
    width = aColWidth;
    // Setting mouse movements on
    setMouseTracking(true);
    // Hiding vertical and horizontal header
    this->verticalHeader()->hide();
    this->horizontalHeader()->hide();
    // When we entered a cell widget in a table widget, the signal cellEntered
    // of TableWidget will connect to the slot of Tablewidget and this
    // slot will set the cell widgets by adding or removing cell widgets with
    // respect to the mouse movements. In the last row of a table widget, we
    // will display the dimension which we are selected
    connect(this, SIGNAL(cellEntered(int,int)),this, SLOT(setTable(int,int)));
    // When we click a cell widget in a table widget, the signal cellClicked
    // of TableWidget will connect to the slot of TableWidget and this
    // slot emit a signal with the row number and column number which
    connect(this,SIGNAL(cellClicked(int,int)),
            this,SLOT(cellSelected(int,int)));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TableWidget::cellSelected(int aRows,int aCols)
{
    nRows = (aRows + 1);
    nCols = (aCols + 1);
    if(nRows > maxRowCell || nCols > maxColCell)
	{
		emit open();
		this->hide();
	}
    else if(nRows <= maxRowCell)
	{
        if(nCols <= maxColCell)
		{
			emit valueSelected(nRows,nCols);
			this->hide();
		}
	}
    else if(nCols <= maxColCell)
	{
        if(nRows <= maxRowCell)
		{
			emit valueSelected(nRows,nCols);
			this->hide();
		}
	}
}

void TableWidget::setTable(int row, int column)
{
    if ((row+1) > maxRowCell || (column+1) > maxColCell )
		return;

    for(int h = 0; h <= row; h++)
    {
        for(int w = 0; w <= column; w++)
        {
            this->setRowHeight(h, height);
            this->setColumnWidth(w, width);
        }
    }

    this->setSpan(pr+1,0,1,1);
    if (row == rowCount()-1)
    {
        if (!column)
        {
            column = columnCount()-2;
        }
    }

   	this->setRangeSelected(QTableWidgetSelectionRange(0,0,pr,pc),false);
    this->setColumnCount(column+2);
    this->setRowCount(row+2);

    this->setRangeSelected(QTableWidgetSelectionRange(0,0,row,column),true);
    this->setSpan(row+1,0,1,column+1);

    this->setItem(pr+1,0,new QTableWidgetItem(" "));
    this->setItem(row+1,0,new
            QTableWidgetItem(tr("   %0x%1").arg(row+1).arg(column+1)));

        /*if((ar+1)>(maxRowCell-1) || (ac+1)>(maxColCell-1))
                this->setItem(ar+1,0,new QTableWidgetItem(tr("")));*/
    pr = row;
    pc = column;
	this->setRowHeight(pr+1,height);
	this->setColumnWidth(pc+1,width);

	this->resize((this->width+1) * this->columnCount(),
                     (this->height+1) * this->rowCount());

}

void TableWidget::closeEvent(QCloseEvent *)
{
    emit send(-1, -1);
}

