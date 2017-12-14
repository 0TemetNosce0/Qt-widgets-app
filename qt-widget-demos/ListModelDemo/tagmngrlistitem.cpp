#include <QStringList>

#include "tagmngrlistitem.h"

ListItem::ListItem(const QList<QVariant> &data, ListItem *parent)
{
    parentItem = parent;
    itemData = data;
}

ListItem::~ListItem()
{
    qDeleteAll(childItems);
}

void ListItem::appendChild(ListItem *item)
{
    childItems.append(item);
}

ListItem *ListItem::child(int row)
{
    return childItems.value(row);
}

int ListItem::childCount() const
{
    return childItems.count();
}

void ListItem::deleteChild(int row)
{
    return childItems.removeAt(row);
}

void ListItem::insertChild(int row, ListItem* item)
{
    childItems.insert(row, item);
}

int ListItem::columnCount() const
{
    return itemData.count();
}

QVariant ListItem::data(int column) const
{
    return itemData.value(column);
}

void ListItem::setData(QList<QVariant> &data)
{
    itemData = data;
}

ListItem *ListItem::parent()
{
    return parentItem;
}

int ListItem::row() const
{
    if (parentItem)
    {
        return parentItem->childItems.indexOf(const_cast<ListItem*>(this));
    }

    return 0;
}
