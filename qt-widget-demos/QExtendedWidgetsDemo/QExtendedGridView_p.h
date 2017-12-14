/****************************************************************************
**
** Copyright (C) 2009 Jordi Pujol Foyo
**
** GNU General Public License Usage
**
** This file may be used under the terms of the GNU General Public License 
** version 3.0 as published by the Free SoftwareFoundation.
** Please review the following information to ensure the GNU General Public 
** License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** This piece of code is available under dual licence ( just like Qt itself ),
** GPL for Open Source development and Commercial licence for other users. 
**
** If you want to purchase a Commercial licence, please contact me by sending
** an email to yuri.podiolu<at>gmail.com 
** 
****************************************************************************/
#pragma once
#ifndef QExtendedGridView_pH
#define QExtendedGridView_pH

#include <QTreeView>

class QTreeViewEvents : public QTreeView
{
	Q_OBJECT

		void keyboardSearch ( const QString & search );
		void SelectCell ( int Key );

	public : 

		QTreeViewEvents ( QWidget * parent = 0 ) : QTreeView ( parent ) {};

		void testFocus ( QTreeViewEvents * Other, const QModelIndex & Index ); 

	protected :

	  bool event ( QEvent * qe );
    void paintEvent ( QPaintEvent* event );

	signals :
   
  	void currentIndexSet ( const QModelIndex & Index ); 
};

#endif
