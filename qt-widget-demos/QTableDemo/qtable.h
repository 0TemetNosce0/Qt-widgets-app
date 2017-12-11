// QTable - table wrapper for models
// Licence: LGPL (see http://www.gnu.org/licenses/lgpl.html)
// Author:
// chemmalion (email: chemmalion@gmail.com, PLEASE use "QTable" at start of mail topic name)
//
// Brief usage:
//
// static QTable table;
// ui->tableView->setModel( table.model() );
// table.setColumnCount(3);
// table.setColumnHeaders( QTableLine( "Name", "Product", "Cost" ) );
// table.appendRow( QTableLine( "V. Pupkin", "Car", "22000" ) );
// table.appendRow( QTableLine( "I. Ivanov", "T-Shirt", "15" ) );
// int sum = table.value(0,2).toInt() + table.value(1,2).toInt();
// 

#ifndef QTABLE_H
#define QTABLE_H

#include <QtGui>
#include <QtCore>

#include "qtablemodel.h"

class QTableLine
{
public:
    explicit QTableLine();
    explicit QTableLine( QVector<QVariant> cells );
    explicit QTableLine( QVariant cell0 );
    explicit QTableLine( QVariant cell0, QVariant cell1 );
    explicit QTableLine( QVariant cell0, QVariant cell1, QVariant cell2 );
    explicit QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3 );
    explicit QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3, QVariant cell4 );
    explicit QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3, QVariant cell4, QVariant cell5 );
    explicit QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3, QVariant cell4, QVariant cell5, QVariant cell6 );
    explicit QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3, QVariant cell4, QVariant cell5, QVariant cell6, QVariant cell7 );
    explicit QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3, QVariant cell4, QVariant cell5, QVariant cell6, QVariant cell7, QVariant cell8 );
    explicit QTableLine( QVariant cell0, QVariant cell1, QVariant cell2, QVariant cell3, QVariant cell4, QVariant cell5, QVariant cell6, QVariant cell7, QVariant cell8, QVariant cell9 );
    virtual ~QTableLine();

    void setCells( QVector<QVariant> cells );
    void setValue( int index, QVariant value );
    QVector<QVariant> cells() const;
    QVariant at( int index ) const;
    QVariant value( int index ) const;

    QTableLine& operator =(const QTableLine& value);

private:
    QVector<QVariant> p_cells;
};

class QTable : public QObject
{
    Q_OBJECT

public:
    explicit QTable(QObject *parent = 0);
    explicit QTable(QAbstractItemModel *model, QObject *parent = 0);
    explicit QTable( int rows, int columns, QAbstractItemModel *model = 0, QObject *parent = 0);
    virtual ~QTable();

    void setModel( QAbstractItemModel *model );
    QAbstractItemModel *model();

    void setParent( QPersistentModelIndex parent );
    QPersistentModelIndex parent();

    QVariant value ( int row, int column, int role = Qt::DisplayRole ) const;
    void set ( int row, int column, const QVariant & value, int role = Qt::EditRole );

    int rowCount();
    void insertRows( int row, int count );
    int columnCount();
    void insertColumns( int column, int count );

    QVariant rowHeader( int row, int role = Qt::DisplayRole );
    QVariant columnHeader( int column, int role = Qt::DisplayRole );
    void setRowHeader( int row, QVariant header, int role = Qt::EditRole );
    void setColumnHeader( int column, QVariant header, int role = Qt::EditRole );

    // Overloadings
    QVariant at ( int row, int column, int role = Qt::DisplayRole ) const;
    void replace ( int row, int column, const QVariant & value, int role = Qt::EditRole );

    QTableLine row( int index, int role = Qt::DisplayRole ) const;
    QTableLine column( int index, int role = Qt::DisplayRole ) const;

    void insertRows( int row, QList<QTableLine> rows, int role = Qt::EditRole );
    void insertRow( int row, QTableLine data, int role = Qt::EditRole );
    void appendRows( int count );
    void appendRows( QList<QTableLine> rows, int role = Qt::EditRole );
    void appendRow( QTableLine row, int role = Qt::EditRole );
    void appendRow();
    void prependRows( int count );
    void prependRows( QList<QTableLine> rows, int role = Qt::EditRole );
    void prependRow( QTableLine row, int role = Qt::EditRole );
    void prependRow();
    void removeRows( int row, int count );
    void removeRow( int row );
    void setRows( int row, QList<QTableLine> rows, int role = Qt::EditRole );
    void setRow( int row, QTableLine data, int role = Qt::EditRole );
    void replaceRows( int row, QList<QTableLine> rows, int role = Qt::EditRole );
    void replaceRow( int row, QTableLine data, int role = Qt::EditRole );
    void setRowCount( int count );

    void insertColumns( int column, QList<QTableLine> columns, int role = Qt::EditRole );
    void insertColumn( int column, QTableLine data, int role = Qt::EditRole );
    void appendColumns( int count );
    void appendColumns( QList<QTableLine> columns, int role = Qt::EditRole );
    void appendColumn( QTableLine column, int role = Qt::EditRole );
    void appendColumn();
    void prependColumns( int count );
    void prependColumns( QList<QTableLine> columns, int role = Qt::EditRole );
    void prependColumn( QTableLine column, int role = Qt::EditRole );
    void prependColumn();
    void removeColumns( int column, int count );
    void removeColumn( int column );
    void setColumns( int column, QList<QTableLine> columns, int role = Qt::EditRole );
    void setColumn( int column, QTableLine data, int role = Qt::EditRole );
    void replaceColumns( int column, QList<QTableLine> columns, int role = Qt::EditRole );
    void replaceColumn( int column, QTableLine data, int role = Qt::EditRole );
    void setColumnCount( int count );

    void setColumnHeaders( QTableLine list, int role = Qt::EditRole );
    void setRowHeaders( QTableLine list, int role = Qt::EditRole );

signals:

public slots:

private:
    QAbstractItemModel *p_table;
    QPersistentModelIndex p_parent;
};

#endif // QTABLE_H
