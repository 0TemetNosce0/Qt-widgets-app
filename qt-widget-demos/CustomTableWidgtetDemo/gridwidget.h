/**
 * gridwidget.h
 *
 * \author ramesh
 * \version $Id: gridwidget.h,v 1.1 2009/05/04 07:26:06 ramesh Exp $
 */
#ifndef GRIDWIDGET_H_
#define GRIDWIDGET_H_
#include <QWidget>
#include <QObject>
#include <QCloseEvent>

/** \brief We will create a Table widget inside of a GridWidget constructor
 *  with the parameters mentioned in the GridWidget constructor.
*
* Initially we will hide this widget layout for showing TableWidget layout
* Finally it sends a signal of selected cell in the table widget or entered
* cell information
*/

class GridWidget: public QWidget
{
	Q_OBJECT
public:
    GridWidget(int cell_max_row = 5, int cell_max_col = 5, int height = 35,
            int width = 50, int rows = 5, int cols = 5, QWidget *parent = 0, Qt::WindowFlags f = 0);

public slots:
	/// This function will receive the row number and column number which
    /// we have selected or entered. It will send a signal called
	/// selected(int,int) with the row number and column number
	void result(int,int);
	/// This function will send a signal called selected(-1,-1)
	/// when we close the TableWidget table
	void closeMyTableWidget(int,int);
	signals:
	/// This is the emitted signal from the selected widget from the table
	///  widget or entered cell widget information
	void selected(int,int);

};
#endif /* GRIDWIDGET_H_ */
