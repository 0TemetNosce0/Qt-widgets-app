#include <QStringList>
#include "treeitem.h"

TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
{
    parentItem = parent;
    itemData = data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

/**
 * @brief       添加孩子TreeItem节点
 * @param item
 */
void TreeItem::appendChild(TreeItem *item)
{
    childItems.append(item);
}

/**
 * @brief       返回指定行的数据
 * @param row   行号
 * @return      一条TreeItem
 */
TreeItem *TreeItem::child(int row)
{
    return childItems.value(row);
}

/**
 * @brief       child Item的个数
 * @return
 */
int TreeItem::childCount() const
{
    return childItems.count();
}

/**
 * @brief       某个TreeItem中的数据列数
 * @return
 */
int TreeItem::columnCount() const
{
    return itemData.count();
}

/**
 * @brief       返回指定列的数据
 * @param column
 * @return
 */
QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}

/**
 * @brief       返回某个TreeItem的父节点
 * @return
 */
TreeItem *TreeItem::parent()
{
    return parentItem;
}

/**
 * @brief       某个TreeItem在其父列表中的位置
 * @return
 */
int TreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
