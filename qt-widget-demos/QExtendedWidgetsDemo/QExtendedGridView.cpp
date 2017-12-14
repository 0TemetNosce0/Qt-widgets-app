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
#define QExtendedGridViewCPP
#include "QExtendedGridView.h"
#include "QExtendedGridView_p.h"
#undef QExtendedGridViewCPP

#include <QKeyEvent>
#include <QPainter>
#include <QScrollBar>
#include <QGridLayout>
#include <QIdentityProxyModel>
#include <QHeaderView>

const int QExtendedGridView_DEF_ROW_SIZE = 20; 
const int QExtendedGridView_BAND_HEADER_EPSILON = 4;
const int QExtendedGridView_COLUMN_HEADER_EPSILON = 4;
const int QExtendedGridView_CELL_EPSILON = 1;

// *****************************************************************************
//    Class QHeaderFixedSize 
// *****************************************************************************
class QHeaderFixedSize : public QHeaderView
{
public :

    QHeaderFixedSize ( Qt::Orientation orientation, QWidget * parent = 0 ) :
        QHeaderView ( orientation, parent ) {};

    QSize sizeHint () const
    {
        if ( !this->model() )
            return QSize ( 100, QExtendedGridView_DEF_ROW_SIZE );
        return qvariant_cast<QSize>( model()->headerData ( 0, Qt::Horizontal, Qt::SizeHintRole ) );
    };
};

// *****************************************************************************
//    Class QTreeViewEvents 
// *****************************************************************************
void QTreeViewEvents::keyboardSearch ( const QString & search )
{
    // Trick to maintain column position while doing keyboard search on a tree
    // Issue N246478 : pending to solve from QT
    int iCol = currentIndex().column();

    QTreeView::keyboardSearch ( search );

    setCurrentIndex ( model()->sibling ( currentIndex().row(), iCol, currentIndex() ) );
    emit currentIndexSet ( currentIndex() );
}

void QTreeViewEvents::SelectCell ( int Key )
{
    int iCol = 0;
    switch ( Key )
    {
    case Qt::Key_Right  : iCol = 1;
        break;
    case Qt::Key_Left   : iCol = -1;
        break;
    }

    QModelIndex AUX = currentIndex ();
    iCol = qMax ( 0, qMin ( AUX.column() + iCol, model()->columnCount() - 1 ) );
    setCurrentIndex ( model()->sibling ( AUX.row(), iCol, currentIndex() ) );
    emit currentIndexSet ( currentIndex() );
}

bool QTreeViewEvents::event ( QEvent * qe )
{
    if ( qe->type() != QEvent::KeyPress )
        return QTreeView::event ( qe );

    QKeyEvent * ke = dynamic_cast<QKeyEvent *>(qe);
    switch ( ke->key() )
    {
    // Special management of certain keys in trees
    case Qt::Key_Right  :
    case Qt::Key_Left   :
    {
        SelectCell ( ke->key() );
        qe->accept();
        return true;
    }
    case Qt::Key_Up  		:
    case Qt::Key_Down   :
    case Qt::Key_PageUp :
    case Qt::Key_PageDown :
    case Qt::Key_Home :
    case Qt::Key_End :
    {
        int iCol = currentIndex().column();
        if ( QTreeView::event ( qe ) )
        {
            setCurrentIndex ( model()->sibling ( currentIndex().row(), iCol, currentIndex() ) );
            emit currentIndexSet ( currentIndex() );
            return true;
        }
        return false;
    }
        break;
    }

    return QTreeView::event ( qe );
}

void QTreeViewEvents::testFocus ( QTreeViewEvents * Other, const QModelIndex & Index )
{ 
    if ( hasFocus() && isColumnHidden ( Index.column() ) )
        Other->setFocus();
    else
        if ( Other->hasFocus() && Other->isColumnHidden ( Index.column() ) )
            this->setFocus();
}

void QTreeViewEvents::paintEvent ( QPaintEvent* event )
{
    QTreeView::paintEvent ( event );
    QPainter painter ( viewport() );
    QPen gridPen = QPen ( QColor ( 210, 210, 210 ) );
    QPen oldPen = painter.pen();
    painter.setPen ( gridPen );

    for ( int i = 0; i < header()->count(); ++i )
    {
        // Draw only visible sections starting from second column
        if ( header()->isSectionHidden ( i ) ||
             header()->visualIndex ( i ) < 0 )
            continue;

        // Position mapped to viewport
        int pos = header()->sectionViewportPosition(i) + header()->sectionSize(i) - 1;
        if ( pos > 0 )
            painter.drawLine ( QPoint ( pos, 0 ), QPoint ( pos, height() ) );
    }
    painter.setPen ( oldPen );
}

// *****************************************************************************
//    Class QBandsProxyModel 
// *****************************************************************************
class QBandsProxyModel : public  QIdentityProxyModel
{
public :

    typedef enum QHdrModelType { hmtHeader = 0, hmtFooter };

    QBandsProxyModel(QHdrModelType type, QObject * parent = 0)
        : QIdentityProxyModel(parent)
        , m_Type(type)
    {

    };

    QVariant headerData ( int section, Qt::Orientation orientation, int role ) const
    {
        if ( !sourceModel() )
            return QVariant();

        // Footer makes a "Bypass", changing section sign ( 0 => -1, 1 => -2 )
        if ( m_Type == hmtFooter )
            return sourceModel()->headerData ( -section - 1, Qt::Horizontal, role );

        if ( role != Qt::SizeHintRole )
            return sourceModel()->headerData ( section, orientation, Qt::UserRole + role );

        switch ( orientation )
        {
        // Header band columns : width comes from contained columns, height from font plus an epsilon
        case Qt::Horizontal :
        {
            int iWidth = 0;
            if ( section < m_BandList.size() )
            {
                // Sum of column widths
                for ( int iSect = m_BandList.at ( section ).first; iSect < m_BandList.at ( section ).second; iSect++ )
                    iWidth += qvariant_cast<QSize>( sourceModel()->headerData ( iSect, orientation, Qt::SizeHintRole ) ).width();
            }

            QFontMetrics FM ( qvariant_cast<QFont>(sourceModel()->headerData ( section, orientation, Qt::UserRole + Qt::FontRole )) );
            return QSize ( iWidth, FM.height() + QExtendedGridView_BAND_HEADER_EPSILON );
        }
            break;
            // Rows : height calculated from font size plus an epsilon
        case Qt::Vertical :
        {
            QFontMetrics FM ( qvariant_cast<QFont>(sourceModel()->headerData ( section, orientation, Qt::UserRole + Qt::FontRole )) );
            return QSize ( 0, FM.height() + QExtendedGridView_CELL_EPSILON );
        }
            break;
        default: break;
        }

        return QVariant();
    };

    QVariant data (const QModelIndex & , int) const
    {
        return QVariant();
    }

    int rowCount ( const QModelIndex & ) const
    {
        return 0;
    }

    int columnCount (const QModelIndex & Index) const
    {
        if ( !sourceModel() )
            return 0;

        if ( m_Type == hmtHeader)
            return m_BandList.size();

        return sourceModel()->columnCount ( Index );
    };

private :

    friend class QExtendedGridView;
    friend class QExtendedGridViewPrivate;

    QHdrModelType m_Type;
    QList < QPair < int, int> > m_BandList;
};

// *****************************************************************************
//    Class QExtendedGridViewPrivate 
// *****************************************************************************
class QExtendedGridViewPrivate
{
    QExtendedGridView* q_ptr;

public :

    Q_DECLARE_PUBLIC(QExtendedGridView)

    QHeaderView* m_GridTopBand;
    QHeaderView* m_GridFooter;
    QHeaderView* m_GridTopBandLock;
    QHeaderView* m_GridFooterLock;

    QTreeViewEvents* m_GridWidgetLock;
    QTreeViewEvents* m_GridWidget;

    QBandsProxyModel* m_GridTopBandModel;
    QBandsProxyModel* m_GridFooterModel;

    int m_iLockedCols;

    QExtendedGridViewPrivate ( QExtendedGridView * Parent )
        : q_ptr ( Parent )
        , m_GridTopBand (0)
        , m_GridFooter (0)
        , m_GridTopBandLock (0)
        , m_GridFooterLock (0)
        , m_GridWidgetLock (0)
        , m_GridWidget (0)
        , m_iLockedCols (0)
    {

    }

    QHeaderView* CreateHeader(const QString& Name, Qt::Orientation orientation, int iRowHeight)
    {
        QHeaderView* Res = new QHeaderFixedSize ( orientation, q_ptr );
        Res->setObjectName(Name);
        Res->setMinimumHeight(iRowHeight);
        Res->setMaximumHeight(iRowHeight);
        Res->setSectionResizeMode(QHeaderView::Fixed);
        Res->setFocusPolicy(Qt::NoFocus);
        QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sp.setHorizontalStretch(0);
        sp.setVerticalStretch(0);
        Res->setSizePolicy(sp);
        return Res;
    }

    void UpdateFixedWidth(void)
    {
        Q_Q(QExtendedGridView);
        if ( !q->model() )
        {
            return;
        }

        int iWidth = 0;
        for (int iCol = 0; iCol < qMin( m_iLockedCols, q->model()->columnCount()); iCol++ )
        {
            if (m_GridWidget->isColumnHidden(iCol))
            {
                iWidth += m_GridWidgetLock->columnWidth(iCol);
            }
        }

        int iAdd = 4 * m_GridWidgetLock->lineWidth();

        if (iWidth > 0)
        {
            m_GridWidgetLock->setFixedWidth(iWidth + iAdd);
            m_GridTopBandLock->setFixedWidth(iWidth + iAdd);
            m_GridFooterLock->setFixedWidth(iWidth + iAdd);
        }
    }

    void SetVisibleCols ( void )
    {
        Q_Q(QExtendedGridView);
        if (!q->model())
        {
            return;
        }

        for ( int iCol = 0; iCol < q->model()->columnCount(); iCol++ )
        {
            if ( iCol < m_iLockedCols )
            {
                m_GridWidget->hideColumn(iCol);
                m_GridWidgetLock->showColumn(iCol);
                m_GridFooter->hideSection(iCol);
                m_GridFooterLock->showSection(iCol);
            }
            else
            {
                m_GridWidget->showColumn(iCol);
                m_GridWidgetLock->hideColumn(iCol);
                m_GridFooter->showSection(iCol);
                m_GridFooterLock->hideSection(iCol);
            }
            ResizeHeaderBand ( iCol );
        }
        UpdateFixedWidth();
    }

    void ResizeHeaderBand ( int colIndex )
    {
        for ( int iBand = 0; iBand < m_GridTopBandModel->m_BandList.size() ; iBand++ )
        {
            // Estamos calculando la banda actual ?
            QPair<int,int> BAND = m_GridTopBandModel->m_BandList.at ( iBand );
            if ((BAND.first <= colIndex) && (colIndex < BAND.second))
            {
                int iWidthLock = 0;
                int iWidth = 0;
                for (int iCol = BAND.first; iCol < BAND.second; iCol++ )
                {
                    if ( m_GridWidget->isColumnHidden(iCol))
                    {
                        iWidthLock += m_GridWidgetLock->columnWidth(iCol);
                    }
                    else
                    {
                        iWidth += m_GridWidget->columnWidth(iCol);
                    }
                }

                m_GridTopBand->resizeSection(iBand, iWidth);
                m_GridTopBandLock->resizeSection(iBand, iWidthLock );
                return;
            }
        }
    }
};

/******************************************************************************/
/*           Class QExtendedGridView                                          */
/******************************************************************************/
void QExtendedGridView::focusInEvent (QFocusEvent *)
{
    focusNextChild();
}

QExtendedGridView::QExtendedGridView ( QWidget * parent, int iDefRowHeight, int iDefColWidth ) : QWidget ( parent )
{
    d_ptr = new QExtendedGridViewPrivate ( this );
    Q_D(QExtendedGridView);

    int iRowHeight = iDefRowHeight < 5?QExtendedGridView_DEF_ROW_SIZE:iDefRowHeight;
    // FVAR

    //	QExtendedGridView widget is composed of many sub-widgets, disposed like this :
    //		 __________________________________________________
    //		|__LOCKED BANDS__|______BANDS_____|________________|^
    //		|__LOCKED HEADER_|______|_________|___|________|___| |
    //		|   						 |			|					|		|				 |   | |
    //		|  		LOCKED		 |			|					|		|				 |   | |
    //		|  							 |			|					|		|				 |   | |
    //		|  		GROUP      |			|		DATA	|		|				 |   | |
    //		|  							 |			|					|		|				 |   | |  <-- Vertical ScrollBar
    //		|  		&	TREE  	 |			|	  TREE  |		|				 |   | |
    //		|  							 |			|					|		|				 |   | |
    //		|  							 |			|					|		|				 |   | |
    //		|  							 |			|					|		|				 |   | |
    //		|  							 |			|					|		|				 |   | |
    //		|  							 |			|					|		|				 |   | |
    //		|  							 |			|					|		|				 |   | |
    //		|________________|______|_________|___|________|___| |
    //		  							 |______|_FOOTERS_|___|________|___|v
    //    ScrollBar -->    <|_______________________________|>

    // CENTER-lEFT : Tree widget for locked columns
    d->m_GridWidgetLock = new QTreeViewEvents(this);
    d->m_GridWidgetLock->setObjectName("GridTreeLock");

    QSizePolicy spLeft(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spLeft.setVerticalStretch(0);
    d->m_GridWidgetLock->setSizePolicy(spLeft);
    d->m_GridWidgetLock->setWordWrap(false);
    d->m_GridWidgetLock->setSortingEnabled(false);
    d->m_GridWidgetLock->setMidLineWidth(1);
    d->m_GridWidgetLock->setUniformRowHeights(true);
    d->m_GridWidgetLock->setSelectionBehavior(QAbstractItemView::SelectRows);
    d->m_GridWidgetLock->setSelectionMode(QAbstractItemView::SingleSelection);

    d->m_GridWidgetLock->header()->setHighlightSections(false);
    d->m_GridWidgetLock->header()->setDefaultSectionSize(iDefColWidth);
    d->m_GridWidgetLock->header()->setMinimumSectionSize(0);
    d->m_GridWidgetLock->header()->setSectionsMovable(false);
    d->m_GridWidgetLock->header()->setStretchLastSection(false);

    // Deactivation of scrollbars in "fixed cols" widget
    d->m_GridWidgetLock->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    d->m_GridWidgetLock->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // CENTER : Tree MAIN widget
    d->m_GridWidget = new QTreeViewEvents(this);
    d->m_GridWidget->setObjectName("GridTree");
    QSizePolicy spCentral(QSizePolicy::Expanding, QSizePolicy::Expanding );
    spCentral.setHorizontalStretch(0);
    spCentral.setVerticalStretch(0);
    d->m_GridWidget->setSizePolicy(spCentral);
    d->m_GridWidget->setWordWrap(false);
    d->m_GridWidget->setSortingEnabled(false);
    d->m_GridWidget->setMidLineWidth(1);
    d->m_GridWidget->setUniformRowHeights(true);
    d->m_GridWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    d->m_GridWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    d->m_GridWidget->header()->setHighlightSections ( false );
    d->m_GridWidget->header()->setDefaultSectionSize ( iDefColWidth );
    d->m_GridWidget->header()->setMinimumSectionSize ( 0 );
    d->m_GridWidget->header()->setSectionsMovable( false );

    QScrollBar * SCROLLH = new QScrollBar ( Qt::Horizontal, this );
    SCROLLH->setObjectName ( "SCROLLH" );
    QScrollBar * SCROLLV = new QScrollBar ( Qt::Vertical, this );
    SCROLLV->setObjectName ( "SCROLLV" );

    // Scrollbars Outside grids, bands & footers
    d->m_GridWidget->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    d->m_GridWidget->setVerticalScrollBarPolicy   ( Qt::ScrollBarAlwaysOff );
    d->m_GridWidget->setHorizontalScrollBar ( SCROLLH );
    d->m_GridWidget->setVerticalScrollBar ( SCROLLV );

    // Focus-control
    setFocusPolicy ( Qt::StrongFocus );

    // TOP : Band headers
    d->m_GridTopBandLock = d->CreateHeader("GridTopBandLock", Qt::Horizontal, iRowHeight );
    d->m_GridTopBandLock->setOffset(-2 * d->m_GridWidgetLock->lineWidth());

    d->m_GridTopBand = d->CreateHeader("GridTopBand", Qt::Horizontal, iRowHeight );

    // FOOTER : Summay @ column footers
    d->m_GridFooterLock = d->CreateHeader("GridFooterLock", Qt::Horizontal, iRowHeight );
    d->m_GridFooterLock->setOffset ( -2 * d->m_GridWidgetLock->lineWidth() );

    d->m_GridFooter = d->CreateHeader ( "GridFooter", Qt::Horizontal, iRowHeight );

    // We mount here the pieces : TOP HEADER, CENTRAL TREE, BOTTOM FOOTER, SCROLLBARS
    QGridLayout *layout = new QGridLayout ( this );
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setObjectName ( "MPFGrid_Layout" );

    layout->addWidget ( d->m_GridTopBandLock, 0, 0, 1, 1 );
    layout->addWidget ( d->m_GridTopBand	, 0, 1, 1, 1 );
    layout->addWidget ( d->m_GridWidgetLock	, 1, 0, 1, 1 );
    layout->addWidget ( d->m_GridWidget  	, 1, 1, 1, 1 );
    layout->addWidget ( d->m_GridFooterLock	, 2, 0, 1, 1 );
    layout->addWidget ( d->m_GridFooter	   	, 2, 1, 1, 1 );
    layout->addWidget ( SCROLLH				, 3, 1, 1, 1 );
    layout->addWidget ( SCROLLV				, 0, 2, 4, 1 );

    // ****** Connecting necessary signals ******
    // To sync expand / collapse
    connect ( d->m_GridWidgetLock, SIGNAL ( expanded  ( const QModelIndex & ) ),
              d->m_GridWidget		 , SLOT   ( expand    ( const QModelIndex & ) ) );
    connect ( d->m_GridWidgetLock, SIGNAL ( collapsed ( const QModelIndex & ) ),
              d->m_GridWidget		 , SLOT   ( collapse  ( const QModelIndex & ) ) );
    connect ( d->m_GridWidget		 , SIGNAL ( expanded  ( const QModelIndex & ) ),
              d->m_GridWidgetLock, SLOT   ( expand    ( const QModelIndex & ) ) );
    connect ( d->m_GridWidget		 , SIGNAL ( collapsed ( const QModelIndex & ) ),
              d->m_GridWidgetLock, SLOT   ( collapse  ( const QModelIndex & ) ) );

    // To maintain header / footer / header bands coherency
    connect ( d->m_GridWidget->header()		 , SIGNAL ( sectionResized(int,int,int) ), this, SLOT ( SectionResized(int,int,int) ) );
    connect ( d->m_GridWidgetLock->header(), SIGNAL ( sectionResized(int,int,int) ), this, SLOT	( SectionResized(int,int,int) ) );

    // To connect external horizontal / vertical scrollbar to main grid
    connect ( d->m_GridWidget->horizontalScrollBar(), SIGNAL ( valueChanged(int) ), this, SLOT ( ScrollHorizontal(int) ) );
    connect ( d->m_GridWidget->horizontalScrollBar(), SIGNAL ( rangeChanged ( int, int ) ),
              this, SLOT ( ShowOrHideHScrollBar() ), Qt::QueuedConnection );
    connect ( d->m_GridWidget->verticalScrollBar()	, SIGNAL ( rangeChanged ( int, int ) ),
              this, SLOT ( ShowOrHideVScrollBar() ), Qt::QueuedConnection );

    // Syncronize indexes of both grids...
    connect ( d->m_GridWidget    , SIGNAL ( currentIndexSet ( const QModelIndex & ) ),
              this							 , SLOT   ( setCurrentIndex ( const QModelIndex & ) ) );
    connect ( d->m_GridWidgetLock, SIGNAL ( currentIndexSet ( const QModelIndex & ) ),
              this							 , SLOT   ( setCurrentIndex ( const QModelIndex & ) ) );

    // Syncronize vertical movement of both grids
    connect ( d->m_GridWidget->verticalScrollBar()		, SIGNAL ( valueChanged ( int ) ),
              d->m_GridWidgetLock->verticalScrollBar(), SLOT   ( setValue ( int ) ) );
    connect ( d->m_GridWidgetLock->verticalScrollBar(), SIGNAL ( valueChanged ( int ) ),
              d->m_GridWidget->verticalScrollBar()		, SLOT   ( setValue ( int ) ) );

    // To accept user interaction...
    connect ( d->m_GridWidget		 , SIGNAL ( activated 	 	( const QModelIndex & ) ),
              this							 , SIGNAL ( ActivatedTree ( const QModelIndex & ) ) );
    connect ( d->m_GridWidgetLock, SIGNAL ( activated 	 	( const QModelIndex & ) ),
              this							 , SIGNAL ( ActivatedTree ( const QModelIndex & ) ) );

    // Proxy models for header band & footer
    d->m_GridTopBandModel = new QBandsProxyModel ( QBandsProxyModel::hmtHeader, this );
    d->m_GridFooterModel  = new QBandsProxyModel ( QBandsProxyModel::hmtFooter, this );

    d->m_GridTopBand->setModel 		 ( d->m_GridTopBandModel );
    d->m_GridTopBandLock->setModel ( d->m_GridTopBandModel );
    d->m_GridFooter->setModel  		 ( d->m_GridFooterModel );
    d->m_GridFooterLock->setModel  ( d->m_GridFooterModel );

    // Initially, no locked columns
    SetLockedColumns ( 0 );
    ShowOrHideHScrollBar();
    ShowOrHideVScrollBar();
}

QExtendedGridView::~QExtendedGridView ( void )
{
    delete d_ptr;
}

void QExtendedGridView::setStretchLastSection ( bool Stretch )
{
    Q_D(QExtendedGridView);
    d->m_GridWidget->header()->setStretchLastSection ( Stretch );
}

void QExtendedGridView::setRootIsDecorated ( bool Visible )
{
    Q_D(QExtendedGridView);
    d->m_GridWidgetLock->setRootIsDecorated ( Visible );
    d->m_GridWidget->setRootIsDecorated ( Visible && !d->m_GridWidgetLock->isVisible() );
}

void QExtendedGridView::setAlternatingRowColors ( bool Value )
{
    Q_D(QExtendedGridView);
    d->m_GridWidget->setAlternatingRowColors ( Value );
    d->m_GridWidgetLock->setAlternatingRowColors ( Value );
}

void QExtendedGridView::resizeColumnToContents ( int iCol )
{
    Q_D(QExtendedGridView);
    d->m_GridWidget->resizeColumnToContents ( iCol );
    d->m_GridWidgetLock->resizeColumnToContents ( iCol );
}

void QExtendedGridView::setModel ( QAbstractItemModel * model )
{
    Q_D(QExtendedGridView);
    d->m_GridWidget->setModel 		( model );
    d->m_GridWidgetLock->setModel ( model );
    d->m_GridWidgetLock->setSelectionModel ( d->m_GridWidget->selectionModel() );
    d->m_GridTopBandModel->setSourceModel(model);
    d->m_GridFooterModel->setSourceModel(model);

    if ( !model )
        return;

    d->SetVisibleCols();

    // Reset ScrollBar state..
    ScrollHorizontal ( 0 );
}

void QExtendedGridView::collapseAll ( void )
{
    Q_D(QExtendedGridView);
    d->m_GridWidget->collapseAll();
    d->m_GridWidgetLock->collapseAll();
}

void QExtendedGridView::expandAll ( void )
{
    Q_D(QExtendedGridView);
    d->m_GridWidget->expandToDepth ( 100 );
    d->m_GridWidgetLock->expandToDepth ( 100 );
}

void QExtendedGridView::expandToDepth ( int depth )
{
    Q_D(QExtendedGridView);
    d->m_GridWidget->expandToDepth ( depth );
    d->m_GridWidgetLock->expandToDepth ( depth );
}

bool QExtendedGridView::isExpanded ( const QModelIndex & index ) const
{
    Q_D(const QExtendedGridView);
    return d->m_GridWidget->isExpanded ( index ) || d->m_GridWidgetLock->isExpanded ( index );
}

void QExtendedGridView::clearSelection ( void )
{
    Q_D(QExtendedGridView);
    d->m_GridWidget->clearSelection();
    d->m_GridWidgetLock->clearSelection();
}

void QExtendedGridView::SectionResized ( int logicalIndex, int /* oldSize */, int newSize )
{
    Q_D(QExtendedGridView);

    // Resizing the footer ( follows table's header )
    d->m_GridFooter->resizeSection ( logicalIndex, newSize );
    d->m_GridFooterLock->resizeSection ( logicalIndex, newSize );

    // Force a full header's band data refresh...
    d->ResizeHeaderBand ( logicalIndex );
    d->UpdateFixedWidth();
}

QAbstractItemModel * QExtendedGridView::model () const { return d_ptr->m_GridWidget->model (); }

void QExtendedGridView::SetLockedColumns ( int iLockedCols )
{
    Q_D(QExtendedGridView);
    d->m_iLockedCols = iLockedCols;

    if ( d->m_iLockedCols < 1 )
    {
        d->m_GridWidgetLock->hide();
        d->m_GridTopBandLock->hide();
        d->m_GridFooterLock->hide();
        d->SetVisibleCols();
    }
    else
    {
        d->SetVisibleCols();
        d->m_GridWidgetLock->show();
        d->m_GridTopBandLock->show();
        d->m_GridFooterLock->show();
    }
}

void QExtendedGridView::ShowOrHideHScrollBar ( void )
{
    QScrollBar * hbar = d_func()->m_GridWidget->horizontalScrollBar();
    if ( !hbar ) return;
    hbar->setVisible ( hbar->minimum() < hbar->maximum() );
}

void QExtendedGridView::ShowOrHideVScrollBar ( void )
{
    QScrollBar * vbar = d_func()->m_GridWidget->verticalScrollBar();
    if ( !vbar ) return;
    vbar->setVisible ( vbar->minimum() < vbar->maximum() );
}

void QExtendedGridView::ScrollHorizontal ( int /* scrollValue */ )
{
    Q_D(QExtendedGridView);
    int iOffset = d->m_GridWidget->header()->offset() - d->m_GridWidget->lineWidth();
    d->m_GridTopBand->setOffset ( iOffset );
    d->m_GridFooter->setOffset  ( iOffset );
}

void QExtendedGridView::setCurrentIndex ( const QModelIndex & index )
{
    Q_D(QExtendedGridView);
    if ( d->m_GridWidget->currentIndex () != index )
        d->m_GridWidget->setCurrentIndex ( index );
    if ( d->m_GridWidgetLock->currentIndex () != index )
        d->m_GridWidgetLock->setCurrentIndex ( index );

    d->m_GridWidget->testFocus ( d->m_GridWidgetLock, index );
}

void QExtendedGridView::SetDefaultColumnWidth ( int colWidth )
{
    Q_D(QExtendedGridView);
    d->m_GridWidget->header()->setDefaultSectionSize ( colWidth );
    d->m_GridWidgetLock->header()->setDefaultSectionSize ( colWidth );
}

void QExtendedGridView::SetVisibleBands ( bool Visible )
{
    Q_D(QExtendedGridView);
    int HEIGHT = QWIDGETSIZE_MAX;
    if ( Visible )
    {
        QVariant variant = d->m_GridTopBand->model()->headerData ( 0, Qt::Horizontal, Qt::SizeHintRole );
        if ( variant.isValid() )
            HEIGHT = qvariant_cast<QSize>(variant).height();
    }

    d->m_GridTopBand->setMinimumHeight ( 0 );
    d->m_GridTopBand->setMaximumHeight ( Visible?HEIGHT:0 );
    d->m_GridTopBandLock->setMinimumHeight ( 0 );
    d->m_GridTopBandLock->setMaximumHeight ( Visible?HEIGHT:0 );
}

void QExtendedGridView::SetVisibleHeader ( bool Visible )
{
    Q_D(QExtendedGridView);
    d->m_GridWidgetLock->setHeaderHidden ( !Visible );
    d->m_GridWidget->setHeaderHidden ( !Visible );
}
void QExtendedGridView::SetVisibleFooter ( bool Visible )
{
    Q_D(QExtendedGridView);
    int HEIGHT = QWIDGETSIZE_MAX;
    if ( Visible )
    {
        QVariant variant = d->m_GridFooter->model()->headerData ( 0, Qt::Horizontal, Qt::SizeHintRole );
        if ( variant.isValid() )
            HEIGHT = qvariant_cast<QSize>(variant).height();
    }

    d->m_GridFooter->setMinimumHeight ( 0 );
    d->m_GridFooter->setMaximumHeight ( Visible?HEIGHT:0 );

    d->m_GridFooterLock->setMinimumHeight ( 0 );
    d->m_GridFooterLock->setMaximumHeight ( Visible?HEIGHT:0 );
}

void QExtendedGridView::SetDefaultSectionSizes ( void )
{
    Q_D(QExtendedGridView);
    QAbstractItemModel * pModel = d->m_GridWidget->model();

    if ( !pModel ) return;

    // VAR
    int iDefSize = d->m_GridWidget->header()->defaultSectionSize(),
            iColSize;
    QVariant SIZE;
    // VAR

    for ( int iCnt = 0; iCnt < pModel->columnCount(); iCnt++ )
    {
        SIZE = pModel->headerData ( iCnt, Qt::Horizontal, Qt::SizeHintRole );
        iColSize = ( SIZE.isValid() )?qvariant_cast<QSize>(SIZE).width():iDefSize;
        setColumnWidth ( iCnt, iColSize );
    }
    d->UpdateFixedWidth();
}

void QExtendedGridView::ClearBands ( void )
{
    Q_D(QExtendedGridView);
    d->m_GridTopBandModel->m_BandList.clear();
}

void QExtendedGridView::AddBand ( int ColNum )
{
    Q_D(QExtendedGridView);
    int AntCol;
    if ( d->m_GridTopBandModel->m_BandList.isEmpty() )
        AntCol = 0;
    else
        AntCol = d->m_GridTopBandModel->m_BandList.at ( d->m_GridTopBandModel->m_BandList.size() - 1 ).second;

    d->m_GridTopBandModel->m_BandList.push_back ( qMakePair ( AntCol, ColNum + AntCol ) );
}

void QExtendedGridView::resizeColumnsToContents()
{
    Q_D(QExtendedGridView);
    if ( model() )
    {
        // We enforce ALL column sizes !!!
        for ( int iCol = 0; iCol < model()->columnCount(); iCol++ )
            resizeColumnToContents ( iCol );
    }

    d->m_GridTopBand->resizeSections ( QHeaderView::Fixed );
    d->m_GridFooter->resizeSections  ( QHeaderView::Fixed );
    d->m_GridTopBandLock->resizeSections ( QHeaderView::Fixed );
    d->m_GridFooterLock->resizeSections  ( QHeaderView::Fixed );
    d->UpdateFixedWidth();
}

int QExtendedGridView::GetLockedColumns ( void ) const { return d_ptr->m_iLockedCols; }

void QExtendedGridView::setColumnWidth ( int colIndex, int colWidth )
{
    Q_D(QExtendedGridView);
    d->m_GridWidget->setColumnWidth ( colIndex, colWidth );
    d->m_GridFooter->resizeSection  ( colIndex, colWidth );

    d->m_GridWidgetLock->setColumnWidth ( colIndex, colWidth );
    d->m_GridFooterLock->resizeSection ( colIndex, colWidth );

    // We enforce calculation of new band header's size
    d->ResizeHeaderBand ( colIndex );
}

int QExtendedGridView::columnWidth ( int colIndex ) const
{
    Q_D(const QExtendedGridView);
    return qMax ( d->m_GridWidget->columnWidth ( colIndex ),
                  d->m_GridWidgetLock->columnWidth ( colIndex ) );
}

QItemSelectionModel * QExtendedGridView::selectionModel () const
{
    return d_func()->m_GridWidget->selectionModel ();
}

int QExtendedGridView::GetColumnAtCursor ( void ) const
{
    Q_D(const QExtendedGridView);
    QTreeViewEvents * pTree;
    if ( d->m_GridWidget->hasFocus() )
        pTree = d->m_GridWidget;
    else
        pTree = d->m_GridWidgetLock;

    return pTree->columnAt ( pTree->mapFromGlobal ( pTree->cursor(). pos() ).x()  );
}

void QExtendedGridView::SetFocus ( void )
{
    Q_D(QExtendedGridView);
    QTreeViewEvents * pTree;
    if ( d->m_iLockedCols < 1 )
        pTree = d->m_GridWidget;
    else
        pTree = d->m_GridWidgetLock;

    pTree->setFocus ( Qt::OtherFocusReason );
}
