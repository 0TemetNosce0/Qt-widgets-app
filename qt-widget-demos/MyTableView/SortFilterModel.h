#ifndef SORTFILTERMODEL_H_
#define SORTFILTERMODEL_H_

#include <QDate>
#include <QSortFilterProxyModel>

//! [0]
class SortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortFilterModel(QObject *parent = 0);


protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:

};

#endif