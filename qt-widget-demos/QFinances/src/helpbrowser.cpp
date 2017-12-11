/***************************************************************************
 *   Copyright (C) 2007 by Peter Komar                                     *
 *   udldevel@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "helpbrowser.h"

#include <QPushButton>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>

HelpBrowser::HelpBrowser(QWidget* parent ): QWidget(parent)
{
	QPushButton *pcmdBack = new QPushButton("<<");
    pcmdHome = new QPushButton(tr("Home"));
	QPushButton *pcmdForward = new QPushButton(">>");
	ptxtBrowser = new QTextBrowser;
	
	connect(pcmdBack,SIGNAL(clicked()),ptxtBrowser,SLOT(backward()));
	connect(pcmdHome,SIGNAL(clicked()),ptxtBrowser,SLOT(home()));
	connect(pcmdForward,SIGNAL(clicked()),ptxtBrowser,SLOT(forward()));
	connect(ptxtBrowser,SIGNAL(backwardAvailable(bool)),pcmdBack,SLOT(setEnabled(bool)));
	connect(ptxtBrowser,SIGNAL(forwardAvailable(bool)),pcmdForward,SLOT(setEnabled(bool)));
		
	QVBoxLayout *pvbxLayout = new QVBoxLayout;
	QHBoxLayout *phbxLayout = new QHBoxLayout;
	phbxLayout->addWidget(pcmdBack);
	phbxLayout->addWidget(pcmdHome);
	phbxLayout->addWidget(pcmdForward);
	pvbxLayout->addLayout(phbxLayout);
	pvbxLayout->addWidget(ptxtBrowser);
	setLayout(pvbxLayout);
}


HelpBrowser::~HelpBrowser()
{
}

void HelpBrowser::load_source(const QString& name)
{
	ptxtBrowser->setSearchPaths(QStringList()<<name);
	ptxtBrowser->setSource(QString("index.html"));
	ptxtBrowser->reload();
}

void HelpBrowser::reload_ui()
{
    pcmdHome->setText(tr("Home"));
}
