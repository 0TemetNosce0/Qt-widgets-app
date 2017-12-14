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
#ifndef QExtendedGridViewH
#define QExtendedGridViewH

#include <QWidget>
class QAbstractItemModel;
class QItemSelectionModel;
class QModelIndex;

class QExtendedGridViewPrivate;
class QExtendedGridView : public QWidget
{
	Q_OBJECT

		QExtendedGridViewPrivate * d_ptr;
		Q_DECLARE_PRIVATE(QExtendedGridView)

	protected :

		virtual void focusInEvent ( QFocusEvent * event );

	public :

		QExtendedGridView ( QWidget * parent = 0, int iDefRowHeight = 20, int iDefColWidth = 120 );
		virtual ~QExtendedGridView ();

		// Overload / Reimplementation of QTs methods for "QExtendedGridView" tables
		void setStretchLastSection ( bool Stretch );
		void setRootIsDecorated ( bool Visible );
  	void setAlternatingRowColors ( bool Value );

		void resizeColumnToContents ( int iCol );

		void setModel	( QAbstractItemModel * model );

		void resizeColumnsToContents ( void );

	  void setColumnWidth ( int colIndex, int colWidth );
	  int columnWidth ( int colIndex ) const;

		QItemSelectionModel * selectionModel () const;
		QAbstractItemModel * model() const;

		// To control Tree
		void collapseAll ( void );
		void expandAll ( void );
		void expandToDepth ( int depth );
		
		bool isExpanded ( const QModelIndex & index ) const;

		// Utility methods to control "QExtendedGridView"'s behavior  
		void SetDefaultColumnWidth ( int colWidth );

		void SetVisibleBands  ( bool Visible );
		void SetVisibleHeader ( bool Visible );
		void SetVisibleFooter ( bool Visible );
		void SetDefaultSectionSizes ( void );
		
		void ClearBands ( void );
		void AddBand ( int ColNum );

		void SetLockedColumns ( int iLockedCols );
		int GetLockedColumns ( void ) const;
		
		int GetColumnAtCursor ( void ) const;

		void SetFocus ( void );

	signals :

		void ActivatedTree ( const QModelIndex & index );

	public slots :
	
		void clearSelection ( void );
		void setCurrentIndex ( const QModelIndex & index );

	private slots :
	
		void SectionResized ( int logicalIndex, int oldSize, int newSize );

		void ShowOrHideHScrollBar ( void );
		void ShowOrHideVScrollBar ( void );
		void ScrollHorizontal ( int scrollValue );
};

#endif
