/**
 * tablewidget.h
 *
 * \author ramesh
 * \version $Id: tablewidget.h,v 1.1 2009/05/04 07:26:06 ramesh Exp $
 */

#ifndef TABLEWIDGET_H_
#define TABLEWIDGET_H_
#include <QTableWidget>
#include <QObject>
#include <QLabel>
#include <QString>
#include <QTextEdit>
#include <QCloseEvent>

//#include "util_global.h"

/** \brief This class for creating table widget and for manipulating
 * operations on cell widgets in a table widget
*
* This class member function will set the table layout when we move the mouse
*/

class /*UTIL_EXPORT*/ TableWidget : public QTableWidget
{
	Q_OBJECT
public:
	int pc;
	int pr;
	int nRows;
	int nCols;
	int height;
	int width;
	int maxRowCell;
	int maxColCell;
    TableWidget(int nCellMaxRow, int cellMaxCol, int height, int width,
            int row, int col, QWidget *parent = 0);
    TableWidget(QTableWidget *parent=0);
    /// This fuction will call automatically when we close the table widget
public slots:
	/// This for setting table widget layout when we move the mouse and
	/// if we move the mouse beyond 5x5 (either row or column), it will
	/// open mywidget for entering rows and columns through keyboard
    void setTable(int, int);
	/// It will receives the row number and column number when we click
	/// on a cell widget of a table widget
    void cellSelected(int, int);

signals:
	/// This emitted signal will be called if we click on cell widget in a
	/// table widget which is beyond 5x5 (either rows or column)
	void open();
	/// This emitted signal will be called if we close the table widget
    void send(int, int);
	/// This emitted signal will be called if we click on cell widget in a
	/// table widget which is less than the size 5x5
    void valueSelected(int, int);

protected:
	void closeEvent(QCloseEvent*);
};
#endif /* TABLEWIDGET_H_ */
