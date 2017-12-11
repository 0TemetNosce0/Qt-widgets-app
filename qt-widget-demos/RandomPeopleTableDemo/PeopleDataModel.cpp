#include "PeopleDataModel.h"
#include <QtCore>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QApplication>
#include <QMessageBox>
#include <QFileIconProvider>
#include "RandomGenerator.h"

#define PREPOPULATE_DATA_ENTRIES 1000

#define TABLE_NAME "people"

#define TABLE_COL_KEY_1 "_id"
#define TABLE_COL_KEY_2 "passpn"
#define TABLE_COL_KEY_3 "cntry"
#define TABLE_COL_KEY_4 "name"
#define TABLE_COL_KEY_5 "surn"
#define TABLE_COL_KEY_6 "brthd"
#define TABLE_COL_KEY_7 "phn"

#define TABLE_COL_NAME_1 "#"
#define TABLE_COL_NAME_2 "Passport Number"
#define TABLE_COL_NAME_3 "Country"
#define TABLE_COL_NAME_4 "First Name"
#define TABLE_COL_NAME_5 "Family Name"
#define TABLE_COL_NAME_6 "Birth date"
#define TABLE_COL_NAME_7 "Phone number"

#define TABLE_COL_TYPE_1 "integer not null primary key"
#define TABLE_COL_TYPE_2 "varchar(20)"
#define TABLE_COL_TYPE_3 "varchar(2)"
#define TABLE_COL_TYPE_4 "varchar(24)"
#define TABLE_COL_TYPE_5 "varchar(24)"
#define TABLE_COL_TYPE_6 "date"
#define TABLE_COL_TYPE_7 "varchar(16)"

PeopleDataModel::PeopleDataModel(QObject * parent, QSqlDatabase db) :
QSqlTableModel(parent,db) 
{
    mSortColumn = -1;
    mSortOrder = Qt::AscendingOrder;
    mColumnNames = 
        QStringList() << 
        TABLE_COL_NAME_1<<TABLE_COL_NAME_2<<TABLE_COL_NAME_3<<TABLE_COL_NAME_4<<
        TABLE_COL_NAME_5<<TABLE_COL_NAME_6<<TABLE_COL_NAME_7;
    mUpArrowSymbol = QChar(0x2191);
    mDownArrowSymbol = QChar(0x2193);
    initRandomData();
    setTable(TABLE_NAME);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

bool PeopleDataModel::createTable() {
    QSqlQuery qry;
    
    QString sQuery = 
        QString("CREATE TABLE %1 ("
        TABLE_COL_KEY_1 " " TABLE_COL_TYPE_1 ","
        TABLE_COL_KEY_2 " " TABLE_COL_TYPE_2 ","
        TABLE_COL_KEY_3 " " TABLE_COL_TYPE_3 ","
        TABLE_COL_KEY_4 " " TABLE_COL_TYPE_4 ","
        TABLE_COL_KEY_5 " " TABLE_COL_TYPE_5 ","
        TABLE_COL_KEY_6 " " TABLE_COL_TYPE_6 ","
        TABLE_COL_KEY_7 " " TABLE_COL_TYPE_7 ")").arg(TABLE_NAME);
    
    bool b = qry.exec(sQuery);
    if (!b) {
        return false;
    }

    return true;
}

QString PeopleDataModel::getInsertQueryString() {
    return QString( "INSERT INTO %1"
        "(" TABLE_COL_KEY_2 "," TABLE_COL_KEY_3 "," TABLE_COL_KEY_4 "," 
            TABLE_COL_KEY_5 "," TABLE_COL_KEY_6 "," TABLE_COL_KEY_7
        ") VALUES (?,?,?,?,?,?);").arg(TABLE_NAME);
}

bool PeopleDataModel::populateTable( int recordCount ) {
    QSqlQuery qry;
    QString sQuery, cc;
    QVariantList passportNumbers, countries, names, surnames, birthdates, phones;
    RandomGenerator gen;

    for ( int i=0; i<recordCount; ++i ) {
        cc = gen.getRandomCountryCode();
        passportNumbers << gen.getRandomPassportNumber(cc);
        countries << cc;
        names << gen.getRandomName();
        surnames << gen.getRandomSurname();
        birthdates << gen.getRandomBirthDate().toString("yyyy-MM-dd");
        phones << gen.getRandomPhoneNumber(cc);
    }

    sQuery = getInsertQueryString();
    bool b = qry.prepare(sQuery);
    if (!b) {
        QMessageBox::information(0, "Error", "prepopulateTable(): Couldn't prepare query");
        return false;
    }

    qry.addBindValue(passportNumbers);
    qry.addBindValue(countries);
    qry.addBindValue(names);
    qry.addBindValue(surnames);
    qry.addBindValue(birthdates);
    qry.addBindValue(phones);

    b = qry.execBatch();
    if (!b) {
        QMessageBox::information(0, "Error", "prepopulateTable(): Couldn't exec batch query");
        return false;
    }
    return true;
}

bool PeopleDataModel::addRecord() {
    bool bResult = populateTable(1);
    select();
    return bResult;
}

bool PeopleDataModel::select() {
     bool status = QSqlTableModel::select();
        if (!status)
            return status;
        while (canFetchMore()) {
            fetchMore();
        }
        return status;
}

bool PeopleDataModel::initRandomData() {
    if ( createTable() ) {
        QMessageBox::information(0, "Warning", "New database will be created. This may take a while...");
        populateTable(PREPOPULATE_DATA_ENTRIES);
        return true;
    }
    return false;
}

QVariant PeopleDataModel::data ( const QModelIndex & index, int role ) const
{
    int col = index.column();

    if (col == 2 ) {
        if (role== Qt::DecorationRole) {
            QString iconName(":/res/flag_" + QSqlTableModel::data( index ).toString() + ".png");
            return QIcon(iconName);
        }
        else return QVariant();
    }
    return QSqlTableModel::data( index, role );
}

bool PeopleDataModel::removeRows ( int row, int count, const QModelIndex & parent )
{
    (void)parent;

    QString sQuery;
    int rowid;
    QSqlQuery qry;
    bool b;

    for ( int i=0; i<count; ++i ) {
        rowid = record(row+i).value(TABLE_COL_KEY_1).toInt();
        sQuery = QString("DELETE FROM %1 WHERE " TABLE_COL_KEY_1 "=%2;").arg(TABLE_NAME).arg(rowid);
        qDebug()<<"REMOVE ROW "<<rowid;
        b = qry.exec(sQuery);
        if (!b) {
            QMessageBox::information(0, "Error", "Cannot delete from table");
            return false;
        }
    }

    return true;
}

void PeopleDataModel::sortByColumn(int col) {
    if ( col==mSortColumn ) {
        mSortOrder = (mSortOrder==Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
    }
    else {
        mSortOrder = Qt::AscendingOrder;
        mSortColumn = col;
    }

    for ( int i=0; i<mColumnNames.size(); ++i ) {
        QString prefix("");
        if ( i==mSortColumn ) prefix = (mSortOrder==Qt::AscendingOrder) ? mUpArrowSymbol : mDownArrowSymbol;
        setHeaderData(i, Qt::Horizontal, prefix+" "+mColumnNames.at(i));
    }
}

Qt::SortOrder PeopleDataModel::getCurrentSortOrder() {
    return mSortOrder;
}
