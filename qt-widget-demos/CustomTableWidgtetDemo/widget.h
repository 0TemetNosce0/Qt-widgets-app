#ifndef WIDGET_H_
#define WIDGET_H_

#include <QLabel>
#include <QWidget>
#include <QObject>
#include <QString>
#include <QTextEdit>

/** \brief This class will create a widget for entering rows and columns
*
* When we go beyond 5x5 (either row or column) in a table widget, this widget
* will be shown for entering values through keyboard
*/

class Widget: public QWidget
{
	Q_OBJECT

public:
	int nrs;
	int ncs;
	/// These strings will hold the values of row number and column number
    QString row;
    QString column;
	/// These labels for observation for what we have to enter
	QLabel *nr;
	QLabel *nc;
	/// These for entering values through keyboard
    QTextEdit *textEdit1;
    QTextEdit *textEdit2;
    Widget(QWidget *parent = 0);

public slots:
	/// This function will receive the row number and column number
	void getInput();
	void output();

signals:
	void valueSelected(int,int);
};
#endif /* WIDGET_H_ */
