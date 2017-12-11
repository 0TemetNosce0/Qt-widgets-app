#include "custommodel.h"

CustomModel::CustomModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

void CustomModel::setModel(const QList<bool> &list)
{
    this->list = list;
}

int CustomModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return list.count();
}

int CustomModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 10;
}

QVariant CustomModel::data(const QModelIndex &index, int role) const
{
    if (index == QModelIndex() || role != Qt::DisplayRole)
    {
        return QVariant();
    }
    else
    {
        bool value = list[index.row()];
        return QVariant(value);
    }
}
