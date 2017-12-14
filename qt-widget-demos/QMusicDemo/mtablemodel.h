/*
 *  功能: 自定义表格模型。。实现复选框
 *
 *
 *
 */
#ifndef MTABLEMODEL_H
#define MTABLEMODEL_H

#include <QMap>
#include <QList>
#include <QStringList>
#include <QAbstractTableModel>

class MTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MTableModel(QObject *parent = 0);

    void setModelData(QList<QStringList> *data);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    void changeChecked(const QModelIndex &index);

    void addRows(QList<QStringList> *data);

    bool insertRows(int row, int count, const QModelIndex &parent);

private:
    QList<QStringList> *dataList;
    QStringList headData;

    QMap<int, int> checkStateMap; // 存放复选框是否被选中

};

#endif // MTABLEMODEL_H
