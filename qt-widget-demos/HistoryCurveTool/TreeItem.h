#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QIcon>


/**
 * @brief 通用树形结构类
 */
class TreeItem
{
public:
    TreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
    ~TreeItem();

    void appendChild(TreeItem* child);
    TreeItem* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parent();

    /**
     * 根据当前节点状态,返回相应的图标
     */
    QIcon icon() const;
    void setIcon(bool status);

private:
    // 父结点
    TreeItem *parentItem;
    // 子结点列表
    QList<TreeItem*> childItems;
    // 子节点对应数据
    QList<QVariant> itemData;
    // 用来标识当前图标是开/合状态
    bool isOpen;
};

#endif // TREEITEM_H
