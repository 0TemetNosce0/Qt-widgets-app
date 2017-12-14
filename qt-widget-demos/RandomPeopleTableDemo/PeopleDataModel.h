#pragma once
#include <QSql>
#include <QString>
#include <QDateTime>
#include <QSqlTableModel>


class PeopleDataModel : public QSqlTableModel {
private:
    int mSortColumn;
    Qt::SortOrder mSortOrder;
    QString mUpArrowSymbol;
    QString mDownArrowSymbol;
    QStringList mColumnNames;

private:
    bool createTable();
    bool populateTable(int recordCount );
    bool initRandomData();
    QString getInsertQueryString();

public:
    PeopleDataModel( QObject * parent, QSqlDatabase db );
    bool select();
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    bool removeRows ( int row, int count, const QModelIndex & parent = QModelIndex() );
    void sortByColumn( int col );
    Qt::SortOrder getCurrentSortOrder();
    bool addRecord();
};
