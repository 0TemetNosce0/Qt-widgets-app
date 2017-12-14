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
#define QExtendedTabWidgetCPP
  #include "QExtendedTabWidget.h"
#undef QExtendedTabWidgetCPP

// *****************************************************************************
//    Class QExtendedTabWidgetPrivate 
// *****************************************************************************
struct QTabInfo
{
	QWidget * m_Widget;
	QIcon     m_Icon;
	QString   m_Label;
	
	bool operator == ( const QTabInfo & Other ) const { return m_Widget == Other.m_Widget; }; 
};
	
class QExtendedTabWidgetPrivate
{
	public :
	
		QList<QTabInfo> m_IniWidgets,
										m_Widgets,
										m_Hidden;
};

// *****************************************************************************
//    Class QExtendedTabWidget 
// *****************************************************************************
QExtendedTabWidget::QExtendedTabWidget ( QWidget * parent ) : 
	QTabWidget ( parent ),
	d_ptr ( new QExtendedTabWidgetPrivate )
{
}

QExtendedTabWidget::~QExtendedTabWidget ( void )
{
	delete d_ptr;
}

void QExtendedTabWidget::tabInserted ( int index )
{
	// Inherited
	QTabWidget::tabInserted ( index );

	Q_D(QExtendedTabWidget);
	QTabInfo INFO;
	INFO.m_Widget = widget ( index );
	if ( !INFO.m_Widget )
		return;

	INFO.m_Icon  = tabIcon ( index );
	INFO.m_Label = tabText ( index );

	// To maintain relative order, widgets stored as they are inserted
	if ( !d->m_IniWidgets.contains ( INFO ) )
		d->m_IniWidgets.insert ( index, INFO );

	if ( !d->m_Widgets.contains ( INFO ) )
		d->m_Widgets.push_back ( INFO );
}

QString QExtendedTabWidget::HideTab ( int index )
{
	QTabInfo INFO;
	INFO.m_Widget = widget ( index );
	if ( !INFO.m_Widget )
		return QString();

	INFO.m_Icon  = tabIcon ( index );
	INFO.m_Label = tabText ( index );

	Q_D(QExtendedTabWidget);
	d->m_Hidden.push_back  ( INFO );
	d->m_Widgets.removeOne ( INFO );
	removeTab ( index ); 

	return INFO.m_Widget->objectName();
}

void QExtendedTabWidget::ShowTab ( const QString & TabName )
{
	Q_D(QExtendedTabWidget);
	foreach ( const QTabInfo & INFO, d->m_Hidden )
	{
		if ( INFO.m_Widget->objectName().compare ( TabName, Qt::CaseInsensitive ) == 0 )
		{
			int iPos = d->m_IniWidgets.indexOf ( INFO ),
					iOffset = 0;
			for ( int iIter = 0; iIter < iPos; iIter++ )
			{
				if ( !d->m_Widgets.contains ( d->m_IniWidgets.at ( iIter ) ) )
					iOffset++;
			}
 			setUpdatesEnabled ( false );
 			insertTab ( iPos - iOffset, INFO.m_Widget, INFO.m_Icon, INFO.m_Label );
			setUpdatesEnabled ( true );
			d->m_Hidden.removeOne ( INFO );
			return;
		} 
	}
}
