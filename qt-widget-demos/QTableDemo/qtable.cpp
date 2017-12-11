// QTable - table wrapper for models
// Licence: LGPL (see http://www.gnu.org/licenses/lgpl.html)
// Author:
// chemmalion (email: chemmalion@gmail.com, PLEASE use "QTable" at start of mail topic name)

#include "qtable.h"

QTableLine::QTableLine()
{
}

QTableLine::QTableLine( QVector<QVariant> cells )
{
    p_cells = cells;
}

QTableLine::QTableLine( QVariant cell0 )
{
    p_cells << cell0;
}

QTableLine::QTableLine( QVariant cell0, QVariant cell1 )
{
    p_cells << cell0 << cell1;
}

QTableLine::QTableLine( QVariant cell0, QVariant cell1, QVariant cell2 )
{
    p_cells << cell0 << cell1 << cell2;
}

QTableLine::QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3 )
{
    p_cells << cell0 << cell1 << cell2 << cell3;
}

QTableLine::QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3, QVariant cell4 )
{
    p_cells << cell0 << cell1 << cell2 << cell3 << cell4;
}

QTableLine::QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3, QVariant cell4, QVariant cell5 )
{
    p_cells << cell0 << cell1 << cell2 << cell3 << cell4 << cell5;
}

QTableLine::QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3, QVariant cell4, QVariant cell5, QVariant cell6 )
{
    p_cells << cell0 << cell1 << cell2 << cell3 << cell4 << cell5 << cell6;
}

QTableLine::QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3, QVariant cell4, QVariant cell5, QVariant cell6, QVariant cell7 )
{
    p_cells << cell0 << cell1 << cell2 << cell3 << cell4 << cell5 << cell6 << cell7;
}

QTableLine::QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3, QVariant cell4, QVariant cell5, QVariant cell6, QVariant cell7, QVariant cell8 )
{
    p_cells << cell0 << cell1 << cell2 << cell3 << cell4 << cell5 << cell6 << cell7 << cell8;
}

QTableLine::QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3, QVariant cell4, QVariant cell5, QVariant cell6, QVariant cell7, QVariant cell8, QVariant cell9 )
{
    p_cells << cell0 << cell1 << cell2 << cell3 << cell4 << cell5 << cell6 << cell7 << cell8 << cell9;
}

QTableLine::~QTableLine()
{
}

void QTableLine::setCells(QVector<QVariant> cells)
{
    p_cells = cells;
}

void QTableLine::setValue(int index, QVariant value)
{
    if((index < 0) || (index >= p_cells.size()))
    {
        return;
    }
    p_cells.replace(index,value);
}

QVector<QVariant> QTableLine::cells() const
{
    return p_cells;
}

QVariant QTableLine::at( int index ) const
{
    return p_cells.at(index);
}

QVariant QTableLine::value( int index ) const
{
    return p_cells.value(index);
}

QTableLine& QTableLine::operator =(const QTableLine& value)
{
    p_cells = value.cells();
    return *this;
}

QTable::QTable(QObject *parent)
    : QObject(parent)
{
    p_table = new QTableModel(this);
}

QTable::QTable(QAbstractItemModel * model, QObject *parent )
{
    Q_UNUSED(parent);

    if(model != 0)
    {
        p_table = model;
    }
    else
    {
        p_table = new QTableModel(this);
    }
}

QTable::QTable( int rows, int columns, QAbstractItemModel * model, QObject *parent )
{
    Q_UNUSED(parent);

    if( model != 0 )
    {
        p_table = model;
    }
    else
    {
        p_table = new QTableModel(this);
    }

    setRowCount( rows );
    setColumnCount( columns );
}

QTable::~QTable()
{
    // p_table will be destructed automatically if it was created in constructor
}

void QTable::setModel( QAbstractItemModel * model )
{
    p_table = model;
}

QAbstractItemModel *QTable::model()
{
    return p_table;
}

void QTable::setParent( QPersistentModelIndex parent )
{
    p_parent = parent;
}

QPersistentModelIndex QTable::parent()
{
    return p_parent;
}

QVariant QTable::at ( int row, int column, int role ) const
{
    if(!p_table)
    {
        return QVariant();
    }
    return p_table->data(p_table->index(row, column, p_parent), role);
}

QVariant QTable::value ( int row, int column, int role ) const
{
    if( !p_table )
    {
        return QVariant();
    }

    return p_table->data( p_table->index( row, column, p_parent ), role );
}

void QTable::replace ( int row, int column, const QVariant & value, int role )
{
    if( !p_table )
    {
        return;
    }
    p_table->setData( p_table->index( row, column, p_parent ), value, role );
}

void QTable::set ( int row, int column, const QVariant & value, int role )
{
    if( !p_table )
    {
        return;
    }
    p_table->setData( p_table->index( row, column, p_parent ), value, role );
}

int QTable::rowCount()
{
    if( !p_table )
    {
        return 0;
    }
    return p_table->rowCount(p_parent);
}

QTableLine QTable::row( int index, int role ) const
{
    if(!p_table)
    {
        return QTableLine();
    }

    if((index < 0) || (index >= p_table->rowCount(p_parent)))
    {
        return QTableLine();
    }

    QVector<QVariant> result;
    int count = p_table->columnCount(p_parent);
    result.resize(count);

    for( int i = 0; i < count; ++i )
    {
        result[i] = p_table->data( p_table->index( index, i, p_parent ), role );
    }

    return QTableLine( result );
}

QTableLine QTable::column( int index, int role ) const
{
    if( !p_table )
    {
        return QTableLine();
    }

    if( ( index < 0 ) || ( index >= p_table->columnCount(p_parent)))
    {
        return QTableLine();
    }

    QVector<QVariant> result;
    int count = p_table->rowCount(p_parent);
    result.resize(count);

    for(int i = 0; i < count; ++i)
    {
        result[i] = p_table->data( p_table->index( i, index, p_parent ), role );
    }

    return QTableLine( result );
}

void QTable::insertRows( int row, int count )
{
    if(!p_table)
    {
        return;
    }

    bool nullColumn = p_table->columnCount(p_parent) == 0;
    p_table->insertRows( row, count, p_parent );

    if(nullColumn && (p_table->columnCount(p_parent) == 1))
    {
        p_table->removeColumn(0,p_parent);
    }
}

void QTable::insertRows( int row, QList<QTableLine> rows, int role )
{
    if( !p_table )
    {
        return;
    }

    if( rows.size() == 0 )
    {
        return;
    }

    int columns = p_table->columnCount(p_parent);
    p_table->insertRows( row, rows.size(), p_parent );

    if((columns == 0) && (p_table->columnCount(p_parent) == 1))
    {
        p_table->removeColumn(0,p_parent);
    }

    columns = qMin( columns, rows[0].cells().size() );

    for( int irow = 0; irow < rows.size(); ++irow )
    {
        for( int icolumn = 0; icolumn < columns; ++icolumn)
        {
            p_table->setData( p_table->index( row+irow, icolumn, p_parent ), rows[irow].at(icolumn), role );
        }
    }
}

void QTable::insertRow(int row, QTableLine data, int role )
{
    insertRows(row, QList<QTableLine>() << data, role);
}

void QTable::appendRows(int count)
{
    insertRows(rowCount(), count);
}

void QTable::appendRows(QList<QTableLine> rows, int role)
{
    insertRows(rowCount(), rows, role );
}

void QTable::appendRow(QTableLine row, int role)
{
    insertRows(rowCount(), QList<QTableLine>() << row, role );
}

void QTable::prependRows(int count)
{
    insertRows( 0, count );
}

void QTable::prependRows( QList<QTableLine> rows, int role )
{
    insertRows( 0, rows, role );
}

void QTable::prependRow( QTableLine row, int role )
{
    insertRows( 0, QList<QTableLine>() << row, role );
}

void QTable::removeRows( int row, int count )
{
    if( !p_table )
    {
        return;
    }
    p_table->removeRows( row, count, p_parent );
}

void QTable::removeRow( int row )
{
    if( !p_table )
    {
        return;
    }
    p_table->removeRows( row, 1, p_parent );
}

void QTable::setRows( int row, QList<QTableLine> rows, int role )
{
    if( !p_table )
        return;
    if( rows.size() == 0 )
        return;

    int rcount = qMin( rows.size(), p_table->rowCount(p_parent)-row );
    int columns = qMin( rows[0].cells().size(), p_table->columnCount(p_parent));

    for( int r = 0; r < rcount; ++r )
    {
        for( int c = 0; c < columns; ++c )
        {
            p_table->setData( p_table->index( row+r, c, p_parent ), rows[r].at(c), role );
        }
    }
}

void QTable::setRow( int row, QTableLine data, int role )
{
    setRows( row, QList<QTableLine>() << data, role );
}

void QTable::replaceRows( int row, QList<QTableLine> rows, int role )
{
    setRows( row, rows, role );
}

void QTable::replaceRow( int row, QTableLine data, int role )
{
    setRows( row, QList<QTableLine>() << data, role );
}

void QTable::setRowCount( int count )
{
    if( !p_table ) return;
    int rows = rowCount();
    if( count > rows ) appendRows( count-rows );
    if( count < rows ) removeRows( count, rows-count );
}

int QTable::columnCount()
{
    if( !p_table ) return 0;
    return p_table->columnCount(p_parent);
}

void QTable::insertColumns( int column, int count )
{
    if( !p_table ) return;
    bool nullRow = p_table->rowCount(p_parent) == 0;
    p_table->insertColumns( column, count, p_parent );
    if( nullRow && ( p_table->rowCount(p_parent) == 1 ) ) p_table->removeRow(0,p_parent);
}

void QTable::insertColumns( int column, QList<QTableLine> columns, int role )
{
    if( !p_table ) return;
    if( columns.size() == 0 ) return;
    int rows = p_table->rowCount(p_parent);
    p_table->insertColumns( column, columns.size(), p_parent );
    if( ( rows == 0 ) && ( p_table->rowCount(p_parent) == 1 ) ) p_table->removeRow(0,p_parent);
    rows = qMin( rows, columns[0].cells().size() );
    for( int icolumn = 0; icolumn < columns.size(); ++icolumn )
        for( int irow = 0; irow < rows; ++irow  )
            p_table->setData( p_table->index( irow, column+icolumn, p_parent ), columns[icolumn].at(irow), role );
}

void QTable::insertColumn( int column, QTableLine data, int role )
{
    insertColumns( column, QList<QTableLine>() << data, role );
}

void QTable::appendColumns( int count )
{
    insertColumns( columnCount(), count );
}

void QTable::appendColumns( QList<QTableLine> columns, int role )
{
    insertColumns( columnCount(), columns, role );
}

void QTable::appendColumn( QTableLine column, int role )
{
    insertColumns( columnCount(), QList<QTableLine>() << column, role );
}

void QTable::appendColumn()
{
    insertColumns( columnCount(), 1 );
}

void QTable::prependColumns( int count )
{
    insertColumns( 0, count );
}

void QTable::prependColumns( QList<QTableLine> columns, int role )
{
    insertColumns( 0, columns, role );
}

void QTable::prependColumn( QTableLine column, int role )
{
    insertColumns( 0, QList<QTableLine>() << column, role );
}

void QTable::prependColumn()
{
    insertColumns( 0, 1 );
}

void QTable::removeColumns( int column, int count )
{
    if( !p_table ) return;
    p_table->removeColumns( column, count, p_parent );
}

void QTable::removeColumn( int column )
{
    if( !p_table ) return;
    p_table->removeColumns( column, 1, p_parent );
}

void QTable::setColumns( int column, QList<QTableLine> columns, int role )
{
    if( !p_table ) return;
    if( columns.size() == 0 ) return;
    int ccount = qMin( columns.size(), p_table->columnCount(p_parent)-column );
    int rows = qMin( columns[0].cells().size(), p_table->rowCount(p_parent) );
    for( int c = 0; c < ccount; ++c )
        for( int r = 0; r < rows; ++r )
            p_table->setData( p_table->index( r, c+column, p_parent ), columns[c].at(r), role );
}

void QTable::setColumn( int column, QTableLine data, int role )
{
    setColumns( column, QList<QTableLine>() << data, role );
}

void QTable::replaceColumns( int column, QList<QTableLine> columns, int role )
{
    setColumns( column, columns, role );
}

void QTable::replaceColumn( int column, QTableLine data, int role )
{
    setColumns( column, QList<QTableLine>() << data, role );
}

void QTable::setColumnCount( int count )
{
    if( !p_table ) return;
    int columns = columnCount();
    if( count > columns ) appendColumns( count-columns );
    if( count < columns ) removeColumns( count, columns-count );
}

QVariant QTable::rowHeader( int row, int role )
{
    if( !p_table ) return QVariant();
    return p_table->headerData( row, Qt::Vertical, role );
}

QVariant QTable::columnHeader( int column, int role )
{
    if( !p_table ) return QVariant();
    return p_table->headerData( column, Qt::Horizontal, role );
}

void QTable::setRowHeader( int row, QVariant header, int role )
{
    if( !p_table ) return;
    p_table->setHeaderData( row, Qt::Vertical, header, role );
}

void QTable::setColumnHeader( int column, QVariant header, int role )
{
    if( !p_table ) return;
    p_table->setHeaderData( column, Qt::Horizontal, header, role );
}

void QTable::setColumnHeaders( QTableLine list, int role )
{
    for( int i = 0; i < list.cells().size(); ++i )
        setColumnHeader( i, list.at(i), role );
}

void QTable::setRowHeaders( QTableLine list, int role )
{
    for( int i = 0; i < list.cells().size(); ++i )
        setRowHeader( i, list.at(i), role );
}
