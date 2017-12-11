#ifndef STREAMDIRECTORYMODEL_H
#define STREAMDIRECTORYMODEL_H

#include <QIcon>
#include <QAbstractItemModel>
#include "streamdirectoryentry_root.h"

class streamDirectoryModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit streamDirectoryModel(QObject *parent, const QString & genreIconFileName = QString());
    virtual ~streamDirectoryModel();

    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex & index) const;
    virtual bool hasChildren(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;
    virtual QModelIndex index (int row, int column,
                               const QModelIndex & parent = QModelIndex()) const;
    virtual QStringList mimeTypes() const;
    virtual QMimeData *mimeData(const QModelIndexList & indexes) const;
    virtual QModelIndex parent(const QModelIndex & index) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

protected:
    streamDirectoryEntry_root *rootEntry;

private:
    QIcon genreIcon;
};

#endif
