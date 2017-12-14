#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractItemModel>

class DataNode;

class DataModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    DataModel(QObject *parent = 0);
    ~DataModel();

    //设置模型数据
    void setRootNode(DataNode *node);

	virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    DataNode* m_rootNode;
    DataNode* nodeFromIndex(const QModelIndex &index) const;
};

#endif // DATAMODEL_H
