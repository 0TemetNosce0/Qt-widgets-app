#include "cproxymodelwithheadermodels.h"

cProxyModelWithHeaderModels::cProxyModelWithHeaderModels(QObject *parent)
    : m_HorizontalHeaderModel(0)
    , m_VerticalHeaderModel(0)
    , QIdentityProxyModel(parent)
{

}

void cProxyModelWithHeaderModels::setHorizontalHeaderModel(QAbstractItemModel *model)
{
    int cnt;
    m_HorizontalHeaderModel = model;

    if(cnt = sourceModel()->columnCount())
    {
        emit(headerDataChanged(Qt::Horizontal, 0, cnt - 1));
    }
}

void cProxyModelWithHeaderModels::setVerticalHeaderModel(QAbstractItemModel *model)
{
    int rnt;
    m_VerticalHeaderModel = model;

    if ((rnt = sourceModel()->rowCount()))
    {
        emit(headerDataChanged(Qt::Vertical, 0, rnt - 1));
    }
}

QVariant cProxyModelWithHeaderModels::data(const QModelIndex &index, int role) const
{
    QVariant variant;

    if(role == cCustomHeaderView::HorizontalHeaderDataRole)
    {
        variant.setValue(static_cast<QObject *>(m_HorizontalHeaderModel));
        return variant;
    }
    else if(role == cCustomHeaderView::VerticalHeaderDataRole)
    {
        variant.setValue(static_cast<QObject *>(m_VerticalHeaderModel));
        return variant;
    }

    return QIdentityProxyModel::data(index, role);
}

