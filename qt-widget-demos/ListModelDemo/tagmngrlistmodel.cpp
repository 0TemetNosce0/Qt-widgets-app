/****************************************************************************
 *   TagMngrListModel.cpp
 *
 *   Provides a simple tree model to show how to create and use hierarchical
 *   models.
 ***************************************************************************/

#include <QtGui>

#include "tagmngrlistitem.h"
#include "tagmngrlistmodel.h"

TagMngrListModel::TagMngrListModel(const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Title" << "Summary";
    rootItem = new ListItem(rootData);
    setupModelData(data.split(QString("\n")));
}

TagMngrListModel::~TagMngrListModel()
{
    delete rootItem;
}

int TagMngrListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

Qt::DropActions TagMngrListModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

QStringList TagMngrListModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.text.list";
    return types;
}

bool TagMngrListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);
    ListItem* parent = static_cast<ListItem*>(index.internalPointer());

    if(!parent)
    {
        qDebug() << "No node found";
        return false;
    }
    QList<QVariant> itemDa;
    itemDa << value;
    parent->appendChild(new ListItem(itemDa,parent));

    return true;
}

QMimeData *TagMngrListModel::mimeData(const QModelIndexList &indexes)
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach(const QModelIndex &index, indexes)
    {
        if(index.isValid())
        {
            qDebug() << "Exporting index" << index.row();
            stream << index.row();
        }
    }

    mimeData->setData("application/vnd.text.list", encodedData);

    return mimeData;
}

bool TagMngrListModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(column);
    Q_UNUSED(parent);

    if(action == Qt::IgnoreAction)
    {
        return true;
    }

    if(!(data->hasFormat("application/vnd.text.list")))
    {
        return false;
    }


    QByteArray encodedData = data->data("application/vnd.text.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QList<ListItem*> newItems;
    QList<ListItem*> finalItems;
    QList<int> toRemove;

    int itemPoz;
    int temp = 0;
    while(!stream.atEnd())
    {
        stream >> itemPoz;
        newItems << rootItem->child(itemPoz);

        if(itemPoz < row)
        {
            temp++;
        }

        toRemove.append(itemPoz);
        qDebug() << "Append " << rootItem->child(itemPoz)->data(Qt::DisplayRole);
    }

    row -= temp;
    emit layoutAboutToBeChanged();

    for(QList<int>::Iterator itr = toRemove.end() -1 ; itr != toRemove.begin() -1 ; --itr)
    {
        qDebug() << "Deleteting item" << *itr;
        rootItem->deleteChild(*itr);
    }
    emit layoutChanged();

    for(int it = 0; it < rootItem->childCount(); it++)
    {
        finalItems.append(rootItem->child(it));

        if(it == row)
        {
            rootItem->childItems.append(newItems);
        }
    }

    rootItem->childItems.clear();
    rootItem->childItems.append(finalItems);

    emit layoutChanged();

    for(int i =0; i< rootItem->childCount(); i++)
    {
        qDebug() << rootItem->child(i)->data(Qt::DisplayRole);
    }
    return true;
}


QVariant TagMngrListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if(role == Qt::BackgroundRole)
    {
        return QVariant(QBrush(Qt::cyan, Qt::Dense2Pattern));
    }

    if(role == Qt::SizeHintRole)
    {
        return QSize(30,30);
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    ListItem *item = static_cast<ListItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TagMngrListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

QVariant TagMngrListModel::headerData(int section,
                                      Qt::Orientation orientation,
                                      int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return rootItem->data(section);
    }

    return QVariant();
}

QModelIndex TagMngrListModel::index(int row, int column,
                                    const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    ListItem *parentItem;

    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
    {
        parentItem = static_cast<ListItem*>(parent.internalPointer());
    }

    ListItem *childItem = parentItem->child(row);

    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex TagMngrListModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    ListItem *childItem = static_cast<ListItem*>(index.internalPointer());
    ListItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int TagMngrListModel::rowCount(const QModelIndex &parent) const
{
    ListItem *parentItem;

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
        parentItem = static_cast<ListItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

void TagMngrListModel::setupModelData(const QStringList &lines)
{
    // Append a new item to the current parent's list of children.
    for(QStringList::ConstIterator it = lines.constBegin(); it != lines.constEnd(); ++it)
    {
        QList<QVariant> text;
        text << QVariant(*it);
        rootItem->appendChild(new ListItem(text, rootItem));
    }
}
