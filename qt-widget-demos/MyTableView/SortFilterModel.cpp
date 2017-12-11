
#include "SortFilterModel.h"

SortFilterModel::SortFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

bool SortFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    return true;
}

bool SortFilterModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return true;
}
