#include "TagTreeModel.h"

TagTreeModel::TagTreeModel(QObject *parent)
    :QAbstractItemModel(parent)
    ,rootItem(NULL)
{
    updateData();
}

TagTreeModel::~TagTreeModel()
{
    delete rootItem;
}

void TagTreeModel::updateData()
{
    // 废弃旧的模型数据
    if(rootItem)
    {
        delete rootItem;
        rootItem = NULL;
    }

    QList<QVariant> rootData;
    rootData << "Tag" << "Type";

    rootItem = new TreeItem(rootData);
    setupModelData(rootItem);

    // 刷新模型
    // reset();
}

QVariant TagTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    // 添加图标
    if(role == Qt::DecorationRole && index.column() == 0)
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return item->icon();
    }

    // 显示节点数据值
    if(role == Qt::DisplayRole)
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return item->data(index.column());
    }

    return QVariant();
}

Qt::ItemFlags TagTreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return 0;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TagTreeModel::headerData(int section, Qt::Orientation orientation,int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return rootItem->data(section);
    }

    return QVariant();
}

QModelIndex TagTreeModel::index(int row, int column,const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent))
    {
        return QModelIndex();
    }

    TreeItem *parentItem;

    if(!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    TreeItem *childItem = parentItem->child(row);

    if(childItem)
    {
        // 展开树形,为子节点建立索引
        return createIndex(row,column,childItem);
    }
    else
    {
        return QModelIndex();
    }

}

QModelIndex TagTreeModel::parent(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return QModelIndex();
    }

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    // 顶层节点,直接返回空索引
    if(parentItem == rootItem)
    {
        return QModelIndex();
    }

    // 为父结点建立索引
    return createIndex(parentItem->row(),0,parentItem);
}

int TagTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;

    if(!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount(); // 返回父结点下子结点数目
}

int TagTreeModel::columnCount(const QModelIndex &parent ) const
{
    Q_UNUSED(parent);
    return rootItem->columnCount();
}

// 设置模型数据,构建包含10个根结点,每个根结点包含两个子节点的树形结构
void TagTreeModel::setupModelData(TreeItem *parent)
{
    for(int i = 0; i < 10; i++)
    {
        QList<QVariant> datas;
        datas << QString("equirement-%1").arg(i+1) << QString("type-%1").arg(i+1);

        // 主结点下挂两个孩子节点
        TreeItem *primary = new TreeItem(datas,parent);
        parent->appendChild(primary);

        for(int j = 0; j < 2;j++)
        {
            QList<QVariant> ds;
            ds << QString("subEquirement-%1").arg(j+1) << QString("subType-%1").arg(j+1);

            primary->appendChild(new TreeItem(ds,primary));
        }
    }
}

bool TagTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::DecorationRole)
    {
        bool pStatus = value.toBool();

        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        item->setIcon(pStatus);

        emit dataChanged(index, index);
        return true;
    }

    return false;
}

