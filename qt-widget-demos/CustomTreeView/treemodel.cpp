#include "treeitem.h"
#include "treemodel.h"
#include <QStringList>
#include <QIcon>

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Title";
    rootItem = new TreeItem(rootData);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

void TreeModel::setXML(QString xmlFile)
{
    toolList = Util::parse(xmlFile);
    setupModelData(rootItem);
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    ToolUtil toolUtil;
    for (int i = 0; i < toolList.count(); ++i)
    {
        toolUtil = toolList.at(i);
        if (toolUtil.id == item->data(0))
        {
            break;
        }
    }

    if (role == Qt::DisplayRole)
    {
        return toolUtil.text;
    }
    else if (role == Qt::DecorationRole)
    {
        return QIcon(Util::exePath() + "\\Resources\\toolicon\\" + toolUtil.toolicon);
    }
    else if (role == Qt::ToolTipRole)
    {
        return toolUtil.tooltip;
    }
    else
    {
        return QVariant();
    }
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return rootItem->data(section);
    }

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    TreeItem *parentItem;

    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    TreeItem *childItem = parentItem->child(row);

    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
    {
        return 0;
    }

    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

TreeItem * TreeModel::item(TreeItem* item, ToolUtil tool)
{
    TreeItem *treeItem = NULL;
    if (item == NULL)
    {
        return treeItem;
    }

    int parentId = tool.parentId;

    if (item->data(0) == parentId)
    {
        treeItem = item;
    }
    else
    {
        for (int j = 0; j < item->childCount(); ++j)
        {
            TreeItem *childItem = item->child(j);
            TreeItem *item2 = this->item(childItem, tool);
            if (item2)
            {
                treeItem = item2;
                break;
            }
        }
    }

    return treeItem;
}

void TreeModel::setupModelData(TreeItem *parent)
{
    QList<TreeItem*> parents;
    parents << parent;

    for (int i = 0; i < toolList.count(); ++i)
    {
        ToolUtil tool = toolList.at(i);
        QList<QVariant> columnData;
        columnData << tool.id;

        for(int j = 0; j < parents.count(); ++j)
        {

            TreeItem* item = this->item(parents.at(j), tool);

            if (item)
            {
                item->appendChild(new TreeItem(columnData, item));
            }
            else
            {
                parents.last()->appendChild(new TreeItem(columnData, parents.last()));
            }
        }
    }
}
