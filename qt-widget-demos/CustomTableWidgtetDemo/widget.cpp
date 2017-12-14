/**
 * widget.cpp
 *
 * \author ramesh
 * \version $Id: widget.cpp,v 1.1 2009/05/04 07:26:06 ramesh Exp $
 */
#include "widget.h"
#include <QPushButton>
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    nr = new QLabel("No.of Rows");
    textEdit1 = new QTextEdit("0");
    nc = new QLabel("No.of Columns");
    textEdit2 = new QTextEdit("0");
    QPushButton *ok = new QPushButton("OK", this);
    QPushButton *cancel = new QPushButton("Cancel", this);
    ok->setFont(QFont("Times", 10, QFont::Bold));
    cancel->setFont(QFont("Times", 10, QFont::Bold));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nr, 0, 0);
    layout->addWidget(textEdit1, 0, 1);
    layout->addWidget(nc, 1, 0);
    layout->addWidget(textEdit2, 1, 1);
    layout->addWidget(ok, 2, 0);
    layout->addWidget(cancel, 2, 1);
    this->setLayout(layout);

    connect(ok, SIGNAL(clicked()), this, SLOT(getInput()));
    connect(ok, SIGNAL(clicked()), this, SLOT(close()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(output()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
}

void Widget::getInput()
{
    bool b = true;
    row = textEdit1->document()->toPlainText();
    nrs = row.toInt(&b, 10);
    column = textEdit2->document()->toPlainText();
    ncs = column.toInt(&b, 10);
    if(nrs == 0 && ncs == 0)
	{
		emit valueSelected(0,0);
	}
    else if(nrs <= 0 || ncs <= 0)
	{
        emit valueSelected(nrs, ncs);
	}
	else
	{
		emit valueSelected(nrs,ncs);
	}
}

void Widget::output()
{
    emit valueSelected(-1, -1);
}
