#ifndef TAGTREEMODEL_H
#define TAGTREEMODEL_H

#include <QAbstractItemModel>
#include "TreeItem.h"

class TagTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TagTreeModel(QObject *parent = 0);
    ~TagTreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    // ����ģ������
    void setupModelData(TreeItem *parent);

    // ����ģ������
    void updateData();

private:
    TreeItem *rootItem; // ��ײ㶥���ڵ�(һ����Ч��QModelIndex)
};

#endif // TAGTREEMODEL_H
