#include "ProxyModelWithHeaderModels.h"

ProxyModelWithHeaderModels::ProxyModelWithHeaderModels(QObject* parent)
    : QIdentityProxyModel(parent)
{

}

QVariant ProxyModelWithHeaderModels::data(const QModelIndex& index, int role) const
{
    if(m_horizontalHeaderModel && role == HierarchicalHeaderView::HorizontalHeaderDataRole)
	{
        QVariant variant;
        variant.setValue((QObject*)m_horizontalHeaderModel.data());
        return variant;
	}
    if(m_verticalHeaderModel && role == HierarchicalHeaderView::VerticalHeaderDataRole)
	{
        QVariant variant;
        variant.setValue((QObject*)m_verticalHeaderModel.data());
        return variant;
	}
    return QIdentityProxyModel::data(index, role);
}

void ProxyModelWithHeaderModels::setHorizontalHeaderModel(QAbstractItemModel* headerModel)
{
    m_horizontalHeaderModel = headerModel;
    int cnt = columnCount();
	if(cnt)
        emit headerDataChanged(Qt::Horizontal, 0, cnt - 1);
}

void ProxyModelWithHeaderModels::setVerticalHeaderModel(QAbstractItemModel* headerModel)
{
    m_verticalHeaderModel = headerModel;
    int cnt = rowCount();
	if(cnt)
        emit headerDataChanged(Qt::Vertical, 0, cnt - 1);
}
