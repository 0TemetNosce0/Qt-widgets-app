#include "TreeItem.h"

TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
    :itemData(data)
    , parentItem(parent)
	,isOpen(false)/*Ä¬ÈÏÎªÕÛµþÍ¼±ê*/
{

}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    childItems.append(item);
}

TreeItem* TreeItem::child(int row)
{
    return childItems.value(row);
}

int TreeItem::childCount() const
{
    return childItems.count();
}

int TreeItem::columnCount() const
{
    return itemData.count();
}

QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}

int TreeItem::row() const
{
    if(parentItem)
    {
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));
    }

    return 0;
}


TreeItem *TreeItem::parent()
{
    return parentItem;
}


QIcon TreeItem::icon() const
{
    if(isOpen)
    {
        return QIcon(":/images/open.png");
    }

    return QIcon(":/images/collapse.png");
}


void TreeItem::setIcon(bool status)
{
    isOpen = status;
}

