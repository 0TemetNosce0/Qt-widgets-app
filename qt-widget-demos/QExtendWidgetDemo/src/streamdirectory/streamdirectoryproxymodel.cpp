#include "streamdirectoryproxymodel.h"

streamDirectoryProxyModel::streamDirectoryProxyModel(streamDirectoryModel *parent)
    : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setSortRole(Qt::UserRole);
    QSortFilterProxyModel::setSourceModel(parent);
}

streamDirectoryProxyModel::~streamDirectoryProxyModel()
{

}

bool streamDirectoryProxyModel::hasChildren(const QModelIndex & parent) const
{
    return sourceModel()->hasChildren(mapToSource(parent));
}

void streamDirectoryProxyModel::setSourceModel(QAbstractItemModel *)
{

}
