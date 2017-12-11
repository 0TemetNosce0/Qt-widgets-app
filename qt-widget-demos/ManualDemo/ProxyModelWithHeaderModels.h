#ifndef PROXY_MODEL_WITH_HEADER_MODELS
#define PROXY_MODEL_WITH_HEADER_MODELS

#include <QPointer>
#include <QSortFilterProxyModel>

#include "HierarchicalHeaderView.h"

class ProxyModelWithHeaderModels: public QSortFilterProxyModel
{
    Q_OBJECT

public:
    ProxyModelWithHeaderModels(QObject* parent=0);

    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const;

    void setHorizontalHeaderModel(QAbstractItemModel* model);

    void setVerticalHeaderModel(QAbstractItemModel* model);

private:
    QPointer<QAbstractItemModel> _horizontalHeaderModel;
    QPointer<QAbstractItemModel> _verticalHeaderModel;
};

#endif
