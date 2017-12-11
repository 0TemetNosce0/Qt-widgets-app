#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class ListItem;

class TagMngrListModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TagMngrListModel(const QString &data, QObject *parent = 0);
    ~TagMngrListModel();

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
    /**
     * Reimplemented methods for handling drag-n-drop, encoding and deconding
     * mime types
     */
    Qt::DropActions supportedDropActions() const;
    QStringList mimeTypes() const;
    QMimeData* mimeData(const QModelIndexList &indexes);
    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent);

private:
    void setupModelData(const QStringList &lines);

    ListItem *rootItem;
};


#endif // LISTMODEL_H
