#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

TableModel::~TableModel()
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return m_HorizontalHeader.count();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        int ncol = index.column();
        int nrow =  index.row();
        QStringList values = m_data.at(nrow);

        if (values.size() > ncol)
        {
            return values.at(ncol);
        }
        else
        {
            return QVariant();
        }
    }

    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    Qt::ItemFlags flag = QAbstractItemModel::flags(index);

    // flag|=Qt::ItemIsEditable // 设置单元格可编辑,此处注释,单元格无法被编辑
    return flag;
}

void TableModel::setHorizontalHeader(const QStringList &headers)
{
    m_HorizontalHeader =  headers;
}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        return m_HorizontalHeader.at(section);
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

void TableModel::setData(const QVector<QStringList> &data)
{
    m_data = data;
}
