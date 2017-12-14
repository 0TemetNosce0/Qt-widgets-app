#include "MTableModel.h"
#include <QDebug>
#include <QIcon>

MTableModel::MTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    headData << "" << QStringLiteral("������") << QStringLiteral("ר��") << QStringLiteral("��ز���");
}

int MTableModel::rowCount(const QModelIndex &parent) const
{
    return dataList->count();
}

int MTableModel::columnCount(const QModelIndex &parent) const
{
    return headData.count();
}

QVariant MTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal && headData.size() >section)
        {
            return headData.at(section);
        }
    }

    return QVariant();
}

QVariant MTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    }

    if (role == Qt::CheckStateRole &&index.column() == 0)
    {
        if (checkStateMap.contains(index.row()))
        {
            return checkStateMap[index.row()] == Qt::Checked ? Qt::Checked: Qt::Unchecked;
        }

        return Qt::Unchecked;
    }

    // �����ʩ
    if (role == Qt::DisplayRole && index.column() != 0 && index.column()< dataList->at(index.row()).count())
    {
        return dataList->at(index.row()).at(index.column());
    }

    // �����ʩ
    if (role == Qt::DecorationRole && index.column() == 3 && dataList->at(index.row()).count())
    {
        return dataList->at(index.row()).at(0);
    }

    return QVariant();
}

Qt::ItemFlags MTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    if (index.column() == 0)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable; // ���븴ѡ��
    }
    else
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable; // ��Ԫ�񲻿ɱ��޸�
    }
}

void MTableModel::setModelData(QList<QStringList> *data)
{
    dataList = data;
}

bool MTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }

    if (role == Qt::CheckStateRole && index.column() == 0)
    {
        checkStateMap[index.row()] = (value == Qt::Checked ? Qt::Checked : Qt::Unchecked);
    }

    return true;
}

void MTableModel::changeChecked(const QModelIndex &index)
{
    checkStateMap[index.row()] = Qt::Checked;
    QModelIndex temp = index.model()->index(index.row(), 0);
    setData(temp, checkStateMap[index.row()] , Qt::CheckStateRole);
}

void MTableModel::addRows(QList<QStringList> *data)
{
    int row = dataList->size() +1;
    beginInsertRows(QModelIndex(), row, row + data->size()+1);

    dataList->operator +=(*data);

    endInsertRows();
}

bool MTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, 0, 0);

    endInsertRows();

    beginRemoveRows(parent, 0, 0);
    endRemoveRows();

    return true;
}
