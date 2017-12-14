/**
 * gridwidget.cpp
 *
 * \author ramesh
 * \version $Id: gridwidget.cpp,v 1.1 2009/05/04 07:26:06 ramesh Exp $
 */
#include "gridwidget.h"
#include "tablewidget.h"
#include "widget.h"
#include <QGridLayout>

    // constructor of GridWidget with the parameters row height,column
	// width, no.of rows and columns
GridWidget::GridWidget(int acell_max_row, int acell_max_col, int aHeight,
        int aWidth, int aRows, int aCols, QWidget *parent,
        Qt::WindowFlags flag)
    : QWidget(parent, flag)
{
	// creating a table widget with the mentioned rows & columns including the
	// height & width of a widget in the table widget by calling TableWidget
	// constructor
	QGridLayout* layout = new QGridLayout;
	this->setLayout(layout);

    TableWidget *mytablewidget = new TableWidget(acell_max_row, acell_max_col,
            aHeight, aWidth, aRows, aCols);
	//mytablewidget->setSizePolicy(Qt::MinimumSize);
	layout->addWidget(mytablewidget);

	// creating a widget for entering rows and columns through keyboard when
	// exceed the size 5x5 (either row or column) by left click on a mouse
    Widget *mywidget = new Widget(0);
	// showing the table widget
	//mytablewidget->show();
	// connecting the signal open() of mytablewidget to the slot show() of
	// mywidget when we go beyond the size 5x5 (either row or column), for
	// entering the no.of rows and columns through keyboard
	connect(mytablewidget,SIGNAL(open()),mywidget,SLOT(show()));
	// the selected cell widget from the table widget will connect to the slot
	// of GridWidget (this specifies the invoking object of GridWidget)
	// and finally the slot function will emit a signal with the selected
	// row number and column number
	connect(mytablewidget,SIGNAL(valueSelected(int,int)),
			this,SLOT(result(int,int)));
	// if we close table widget (it will automatically calls
	// closeEvent(QCloseEvent*) for closing event), the signal of
	// mytablewidget will connect to the slot of TableWidget and the slot
	// emit a signal with (-1,-1)
	connect(mytablewidget,SIGNAL(send(int,int)),
			this,SLOT(closeMyTableWidget(int,int)));
	// the signal(the entered rows and columns through keyboard) of mywidget
	// will connect to the slot of GridWidget
	connect(mywidget,SIGNAL(valueSelected(int,int)),
			this,SLOT(result(int,int)));
}

	// this function will receive row number and column number as a parameter
	// and it will emit a signal with row number and column number
void GridWidget::result(int aRows,int aCols)
{
	emit selected(aRows,aCols);
}

void GridWidget::closeMyTableWidget(int aRows,int aCols)
{
	emit selected(aRows,aCols);
}

