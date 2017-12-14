#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QIcon>


/**
 * @brief ͨ�����νṹ��
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
     * ���ݵ�ǰ�ڵ�״̬,������Ӧ��ͼ��
     */
    QIcon icon() const;
    void setIcon(bool status);

private:
    // �����
    TreeItem *parentItem;
    // �ӽ���б�
    QList<TreeItem*> childItems;
    // �ӽڵ��Ӧ����
    QList<QVariant> itemData;
    // ������ʶ��ǰͼ���ǿ�/��״̬
    bool isOpen;
};

#endif // TREEITEM_H
