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
#ifndef QExtendedTabWidgetH
#define QExtendedTabWidgetH

#include <QTabWidget>

class QExtendedTabWidgetPrivate;
class QExtendedTabWidget : public QTabWidget
{
	Q_OBJECT

		QExtendedTabWidgetPrivate * d_ptr;
		Q_DECLARE_PRIVATE(QExtendedTabWidget)

	public :

		QExtendedTabWidget ( QWidget * parent = 0 );
		virtual ~QExtendedTabWidget ();

		QString HideTab ( int index );
		void ShowTab ( const QString & TabName );

	protected :
	
		virtual void tabInserted ( int index );
};

#endif
