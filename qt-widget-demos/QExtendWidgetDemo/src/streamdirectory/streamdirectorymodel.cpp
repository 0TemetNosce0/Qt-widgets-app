#include <QUrl>
#include <QLocale>
#include <QMimeData>
#include "streamdirectoryentry.h"
#include "streamdirectorymodel.h"

streamDirectoryModel::streamDirectoryModel(QObject *parent, const QString & genreIconFileName)
    : QAbstractItemModel(parent)
{
    rootEntry = new streamDirectoryEntry_root();
    genreIcon = QIcon(genreIconFileName);
//    setSupportedDragActions(Qt::CopyAction);
}

streamDirectoryModel::~streamDirectoryModel()
{
    delete rootEntry;
}

QModelIndex streamDirectoryModel::parent(const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    streamDirectoryEntry *childItem = static_cast<streamDirectoryEntry *>(index.internalPointer());
    streamDirectoryEntry *parentItem = childItem->parent();
    if (parentItem == rootEntry)
    {
        return QModelIndex();
    }
    else
    {
        return createIndex(parentItem->row(), 0, parentItem);
    }
}

QModelIndex streamDirectoryModel::index(int row, int column, const QModelIndex &parent) const
{
    streamDirectoryEntry *parentItem;
    streamDirectoryEntry *childItem;

    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    if (!parent.isValid())
    {
        parentItem = rootEntry;
    }
    else
    {
        parentItem = static_cast<streamDirectoryEntry *>(parent.internalPointer());
    }

    childItem = parentItem->child(row);

    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }
}

int streamDirectoryModel::rowCount(const QModelIndex &parent) const
{
    streamDirectoryEntry *parentItem;

    if (parent.column() > 0)
    {
        return 0;
    }

    if (!parent.isValid())
    {
        parentItem = rootEntry;
    }
    else
    {
        parentItem = static_cast<streamDirectoryEntry *>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int streamDirectoryModel::columnCount(const QModelIndex &) const
{
    return 5;
}

QVariant streamDirectoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole && role != Qt::UserRole)
    {
        return QVariant();
    }

    streamDirectoryEntry *item = static_cast<streamDirectoryEntry *>(index.internalPointer());

    if (role == Qt::DisplayRole)
    {
        return item->data(index.column());
    }
    else
    {
        return item->rawData(index.column());
    };
}

QVariant streamDirectoryModel::headerData(int section,
                                          Qt::Orientation orientation,
                                          int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QString("stream name");
        case 1:
            return QString("data format");
        case 2:
            return QString("bit rate");
        case 3:
            return QString("track information");
        case 4:
            return QString("URL");
        }
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

bool streamDirectoryModel::hasChildren(const QModelIndex & parent) const
{
    if (parent.isValid())
    {
        return (static_cast<streamDirectoryEntry *>(parent.internalPointer()))->hasChildren();
    }
    else
    {
        return rootEntry->hasChildren();
    }
}

Qt::ItemFlags streamDirectoryModel::flags(const QModelIndex & index) const
{
    Qt::ItemFlags returnValue;

    returnValue = QAbstractItemModel::flags(index);
    if (index.isValid())
    {
        returnValue = returnValue | Qt::ItemIsDragEnabled;
    }
    return returnValue;
}

QStringList streamDirectoryModel::mimeTypes() const
{
    QStringList types;

    types << "text/uri-list";
    return types;
}

QMimeData *streamDirectoryModel::mimeData(const QModelIndexList & indexes) const
{
    QMimeData *returnValue;
    QList<QUrl> list;

    if (indexes.size() == 0)
    {
        returnValue = 0;
    }
    else
    {
        returnValue = new QMimeData();
        foreach (const QModelIndex & index, indexes)
        {
            if (index.isValid() && (index.column() == 0))
            {
                list.append(QUrl(static_cast<streamDirectoryEntry *>(index.internalPointer())->value()));
            }
        }
        returnValue->setUrls(list);
    }

    return returnValue;
}
