// QTableModel - editable table model with embedded table of QVariant's
// Licence: LGPL (see http://www.gnu.org/licenses/lgpl.html)
// Author:
// chemmalion (email: chemmalion@gmail.com, PLEASE use "QTable" at start of mail topic name)
//
// Brief usage:
//
// static QTableModel model;
// ui->table_view->setModel( &model );
// model.insertColumns( 0, 3 );
// model.setData( model.index( 0,0 ), "one" );
// model.setData( model.index( 0,1 ), "two" );
// model.setData( model.index( 0,2 ), "three" );
//

#ifndef QTABLEMODEL_H
#define QTABLEMODEL_H

#include <QtCore>
#include <QtGui>

typedef QVector<QVariant> QTableModelColumn;

class QTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit QTableModel( QObject *parent = 0 );
    QTableModel( int rows, int columns, QObject *parent = 0 );
    virtual ~QTableModel();

    void setReadOnly( bool state );
    bool isReadOnly();

    virtual int	columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    virtual int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    bool hasIndex ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    virtual QModelIndex	index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;

    virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;

    virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    virtual bool setHeaderData ( int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole );

    virtual bool insertColumns ( int column, int count, const QModelIndex & parent = QModelIndex() );
    virtual bool insertRows ( int row, int count, const QModelIndex & parent = QModelIndex() );
    virtual bool removeColumns ( int column, int count, const QModelIndex & parent = QModelIndex() );
    virtual bool removeRows ( int row, int count, const QModelIndex & parent = QModelIndex() );

signals:

public slots:

private:
    bool p_readOnly;
    int p_rows;
    int p_columns;
    QList<QTableModelColumn> p_table;
    QVector<QVariant> p_horHeaders;
    QVector<QVariant> p_vertHeaders;

};

#endif // QTABLE_H
