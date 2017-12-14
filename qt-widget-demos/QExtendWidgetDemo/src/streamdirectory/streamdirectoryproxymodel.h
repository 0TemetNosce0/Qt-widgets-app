#ifndef STREAMDIRECTORYPROXYMODEL_H
#define STREAMDIRECTORYPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "streamdirectorymodel.h"

class streamDirectoryProxyModel : public QSortFilterProxyModel
{
public:
    explicit streamDirectoryProxyModel(streamDirectoryModel *parent);
    virtual ~streamDirectoryProxyModel();
    virtual bool hasChildren(const QModelIndex & parent) const;
    virtual void setSourceModel(QAbstractItemModel *sourceModel);
};

#endif
