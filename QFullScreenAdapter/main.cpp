/****************************************************************************
**
** Copyright (C) 2010 Richard Steffen and/or its subsidiary(-ies).
** All rights reserved.
** Contact: rsteffen@messbild.de, rsteffen@uni-bonn.de
**
** Observe the License Information
**
****************************************************************************/

#include "main.h"

int main(int argc, char* argv[])
{
    
    QApplication app(argc, argv);
      
	// create widget hierarchy
	QWidget* base = new QWidget();
	base->resize(500,500);
    base->setLayout(new QHBoxLayout());
	
	// first as Boxlayout
	QWidget* wt1 = new QWidget();	
	wt1->setLayout(new QVBoxLayout());
	DrawIm* im1 = new DrawIm("Box");
	wt1->layout()->addWidget(im1);
	wt1->layout()->addWidget(new QLabel("Make a focus on the Image and press F11.\nNote, the Widget is embedded into a layout! (no Top Level Widget)\nTo save a screenshot, press F12"));
	base->layout()->addWidget(wt1);

	// second as QSplitter layout
	QSplitter *splitter = new QSplitter(Qt::Vertical);    
	DrawIm* im2 = new DrawIm("Splitter 1");
	DrawIm* im3 = new DrawIm("Splitter 2");
    splitter->addWidget(im2);
	splitter->addWidget(im3);
	base->layout()->addWidget(splitter);

	// grid layout
	QWidget* wt2 = new QWidget();	
	QGridLayout* glay = new QGridLayout();
	wt2->setLayout(glay);
	DrawIm* im4 = new DrawIm("Grid 1 1"); glay->addWidget(im4, 0,0);
	DrawIm* im5 = new DrawIm("Grid 1 2"); glay->addWidget(im5, 0,1);
	DrawIm* im6 = new DrawIm("Grid 2 1"); glay->addWidget(im6, 1,0);
	DrawIm* im7 = new DrawIm("Grid 2 2"); glay->addWidget(im7, 1,1);
	base->layout()->addWidget(wt2);


    base->show();	    
    int ret = app.exec();

    base->hide();

    cout << "Return Code: " << ret << endl;

    return ret;
}
