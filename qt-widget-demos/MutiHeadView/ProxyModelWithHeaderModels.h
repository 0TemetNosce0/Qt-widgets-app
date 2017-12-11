#ifndef PROXY_MODEL_WITH_HEADER_MODELS
#define PROXY_MODEL_WITH_HEADER_MODELS

#include <QPointer>
#include <QIdentityProxyModel>

#include "HierarchicalHeaderView.h"

class ProxyModelWithHeaderModels: public QIdentityProxyModel
{
    Q_OBJECT

public:
    ProxyModelWithHeaderModels(QObject* parent=0);

    void setHorizontalHeaderModel(QAbstractItemModel* model);

    void setVerticalHeaderModel(QAbstractItemModel* model);

protected:
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
    QPointer<QAbstractItemModel> m_horizontalHeaderModel;
    QPointer<QAbstractItemModel> m_verticalHeaderModel;
};

#endif
