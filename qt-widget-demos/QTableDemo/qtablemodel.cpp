// QTableModel - editable table model with embedded table of QVariant's
// Licence: LGPL (see http://www.gnu.org/licenses/lgpl.html)
// Author:
// chemmalion (email: chemmalion@gmail.com, PLEASE use "QTable" at start of mail topic name)

#include "qtablemodel.h"

QTableModel::QTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    p_readOnly = false;
    p_rows = 0;
    p_columns = 0;
}

QTableModel::QTableModel( int rows, int columns, QObject *parent )
    : QAbstractTableModel(parent)
{
    p_readOnly = false;
    p_rows = 0;
    p_columns = 0;
    insertColumns( 0, columns );

    if( rows > 0 )
    {
        insertRows( 0, rows-1 );
    }
    else
    {
        removeRows( 0, rowCount() );
    }

    if( columns == 0 )
    {
        removeColumns( 0, columnCount());
    }
}

QTableModel::~QTableModel()
{

}

void QTableModel::setReadOnly( bool state )
{
    p_readOnly = state;
}

bool QTableModel::isReadOnly()
{
    return p_readOnly;
}

int QTableModel::columnCount ( const QModelIndex & parent ) const
{
    if( parent.isValid())
    {
        return 0;
    }

    return p_columns;
}

int QTableModel::rowCount ( const QModelIndex & parent ) const
{
    if( parent.isValid())
    {
        return 0;
    }

    return p_rows;
}

bool QTableModel::hasIndex ( int row, int column, const QModelIndex & parent ) const
{
    if( parent.isValid() )
    {
        return false;
    }

    if( ( row < 0 ) || ( column < 0 ) )
    {
        return false;
    }

    if( column >= p_columns )
    {
        return false;
    }

    if( row >= p_rows )
    {
        return false;
    }

    return true;
}

QModelIndex QTableModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if( parent.isValid())
    {
        return QModelIndex();
    }

    return createIndex(row,column);
}

QVariant QTableModel::data ( const QModelIndex & index, int role ) const
{
    if( !index.isValid() )
    {
        return QVariant();
    }

    if( ( role != Qt::DisplayRole ) && ( role != Qt::EditRole ) )
    {
        return QVariant();
    }

    int row = index.row();
    int column = index.column();

    if( !hasIndex( row, column ) )
    {
        return QVariant();
    }

    return p_table[column][row];
}

Qt::ItemFlags QTableModel::flags ( const QModelIndex & index ) const
{
    if( !index.isValid() )
    {
        return Qt::NoItemFlags;
    }

    if( !hasIndex( index.row(), index.column()))
    {
        return Qt::NoItemFlags;
    }

    Qt::ItemFlags result = Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    if( !p_readOnly)
    {
        result |= Qt::ItemIsEditable;
    }

    return result;
}

bool QTableModel::setData ( const QModelIndex & index, const QVariant & value, int role )
{
    if(p_readOnly)
    {
        return false;
    }

    if(!index.isValid())
    {
        return false;
    }

    if( role != Qt::EditRole )
    {
        return false;
    }

    int row = index.row();
    int column = index.column();

    if(!hasIndex(row, column))
    {
        return false;
    }

    p_table[column][row] = value;
    emit dataChanged(index,index);

    return true;
}

QVariant QTableModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if((role != Qt::DisplayRole) && (role != Qt::EditRole))
        return QVariant();

    switch(orientation)
    {
    case Qt::Horizontal:
        if( section >= p_horHeaders.size() )
        {
            return QVariant();
        }
        return p_horHeaders[section];
    case Qt::Vertical:
        if( section >= p_vertHeaders.size() )
        {
            return QVariant();
        }
        return p_vertHeaders[section];
    default:
        return QVariant();
    }
}

bool QTableModel::setHeaderData ( int section, Qt::Orientation orientation, const QVariant & value, int role )
{
    if( role != Qt::EditRole )
    {
        return false;
    }

    switch( orientation )
    {
    case Qt::Horizontal:

        if( section >= p_horHeaders.size() )
        {
            return false;
        }
        p_horHeaders[section] = value;
        emit headerDataChanged( orientation, section, section );
        return true;

    case Qt::Vertical:

        if( section >= p_vertHeaders.size() )
        {
            return false;
        }
        p_vertHeaders[section] = value;
        emit headerDataChanged( orientation, section, section );
        return true;

    default:
        return false;
    }
}

bool QTableModel::insertColumns ( int column, int count, const QModelIndex & parent )
{
    if(parent.isValid())
    {
        return false;
    }

    if(column < 0)
    {
        return false;
    }

    if(column > p_columns)
    {
        return false;
    }

    if(count < 1)
    {
        return false;
    }

    beginInsertColumns(parent, column, column+count - 1);
    QVector<QVariant> newColumn(p_rows);

    for( int i = 0; i < count; ++i )
    {
        p_table.insert( column+i, newColumn );

    }

    p_horHeaders.insert( column, count, QVariant() );
    p_columns += count;
    endInsertColumns();

    if( p_rows == 0 )
    {
        insertRow(0);
    }

    return true;
}

bool QTableModel::insertRows ( int row, int count, const QModelIndex & parent )
{
    if(parent.isValid())
    {
        return false;
    }

    if(row < 0)
    {
        return false;
    }

    if(row > p_rows)
    {
        return false;
    }

    if(count < 1)
    {
        return false;
    }

    beginInsertRows( parent, row, row+count-1 );

    for( int i = 0; i < p_columns; ++i )
    {
        p_table[i].insert(row, count, QVariant());
    }

    p_vertHeaders.insert(row, count, QVariant());
    p_rows += count;
    endInsertRows();

    if( p_columns == 0 )
    {
        insertColumn(0);
    }

    return true;
}

bool QTableModel::removeColumns (int column, int count, const QModelIndex &parent)
{
    if( parent.isValid() )
    {
        return false;
    }

    if( column < 0 )
    {
        return false;
    }

    if( column >= p_columns )
    {
        return false;
    }

    if( (column+count) > p_columns )
    {
        return false;
    }

    beginRemoveColumns(parent, column, column+count-1);

    for( int i = 0; i < count; ++i )
    {
        p_table.removeAt( column );
    }

    p_horHeaders.remove( column, count );
    p_columns -= count;
    endRemoveColumns();

    return true;
}

bool QTableModel::removeRows (int row, int count, const QModelIndex &parent)
{
    if( parent.isValid() )
    {
        return false;
    }

    if( row < 0 )
    {
        return false;
    }

    if( row >= p_rows )
    {
        return false;
    }

    if((row+count) > p_rows)
    {
        return false;
    }

    beginRemoveRows( parent, row, row+count-1 );

    for( int i = 0; i < count; ++i )
    {
        p_table[i].remove( row, count );
    }

    p_vertHeaders.remove( row, count );
    p_rows -= count;
    endRemoveRows();

    return true;
}
