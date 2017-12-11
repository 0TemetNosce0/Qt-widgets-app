#ifndef CPROXYMODELWITHHEADERMODELS_H
#define CPROXYMODELWITHHEADERMODELS_H

#include <QIdentityProxyModel>
#include "ccustomheaderview.h"

class cProxyModelWithHeaderModels : public QIdentityProxyModel
{
    Q_OBJECT

public:
    explicit cProxyModelWithHeaderModels(QObject *parent = 0);

    void setHorizontalHeaderModel(QAbstractItemModel *model);
    void setVerticalHeaderModel(QAbstractItemModel *model);

protected:
    QVariant data(const QModelIndex &index, int role) const;

private:
    QAbstractItemModel *m_HorizontalHeaderModel;
    QAbstractItemModel *m_VerticalHeaderModel;
};

#endif // CPROXYMODELWITHHEADERMODELS_H
