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
 * @brief       ��Ӻ���TreeItem�ڵ�
 * @param item
 */
void TreeItem::appendChild(TreeItem *item)
{
    childItems.append(item);
}

/**
 * @brief       ����ָ���е�����
 * @param row   �к�
 * @return      һ��TreeItem
 */
TreeItem *TreeItem::child(int row)
{
    return childItems.value(row);
}

/**
 * @brief       child Item�ĸ���
 * @return
 */
int TreeItem::childCount() const
{
    return childItems.count();
}

/**
 * @brief       ĳ��TreeItem�е���������
 * @return
 */
int TreeItem::columnCount() const
{
    return itemData.count();
}

/**
 * @brief       ����ָ���е�����
 * @param column
 * @return
 */
QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}

/**
 * @brief       ����ĳ��TreeItem�ĸ��ڵ�
 * @return
 */
TreeItem *TreeItem::parent()
{
    return parentItem;
}

/**
 * @brief       ĳ��TreeItem���丸�б��е�λ��
 * @return
 */
int TreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
