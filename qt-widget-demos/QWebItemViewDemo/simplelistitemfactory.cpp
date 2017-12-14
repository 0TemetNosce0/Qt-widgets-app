#include "simplelistitemfactory.h"

QString SimpleListItemFactory::pageHeader()
{
    return QString();
}

QString SimpleListItemFactory::itemTemplate(const QModelIndex& index)
{
    return index.data(Qt::DisplayRole).toString();
}

int SimpleListItemFactory::itemHeight(const QModelIndex& index)
{
    Q_UNUSED(index);
    return 20;
}

bool SimpleListItemFactory::recreateItemOnDataChange(const QModelIndex&) const
{
    return true;
}

