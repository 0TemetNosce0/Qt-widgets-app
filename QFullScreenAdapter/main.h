/****************************************************************************
**
** Copyright (C) 2010 Richard Steffen and/or its subsidiary(-ies).
** All rights reserved.
** Contact: rsteffen@messbild.de, rsteffen@uni-bonn.de
**
** Observe the License Information
**
****************************************************************************/

#include <QtGui>
#include <QLabel>
#include <QImage>
#include "QFullScreenAdapter.h"

#include <iostream>
using namespace std;

class DrawIm : public QWidget, public QFullScreenAdapter
{
	Q_OBJECT
public:
	/// Constructor
	DrawIm(QString name, QWidget* parent=0) : QWidget(parent), QFullScreenAdapter(this)
	{        
		name_ = name;
		qimg_ = QImage("./lena.jpg");		
		//qimg_ = qimg_.convertToFormat(QImage::Format_Indexed8, Qt::MonoOnly);
		cout << qimg_.width() << " " << qimg_.height() << endl;
		setMinimumSize(100,100);
		setFocusPolicy ( Qt::StrongFocus); // important to catch focus
    }
	

protected:
	// catch the key
	void keyPressEvent(QKeyEvent* e)
	{
		cout << __FUNCTION__ << endl;
		if (e->key() == Qt::Key_F11)
			toogleFullScreen();
		else if (e->key() == Qt::Key_F12)
			saveScreenShot();
		
	}

	/// repaint the widget
	void paintEvent(QPaintEvent *)
    {
		QPainter p(this);
        p.fillRect(rect(), QColor(0, 0, 0));
		p.drawImage(rect(),qimg_);
		p.setPen(Qt::white);
		p.setBrush(Qt::white);
		p.drawText(20,20, name_);
    }


private:
	/// the image
	QImage qimg_;

	QString name_;
};
