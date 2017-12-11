#include "kjmodel.h"
#include <QBrush>
#include <QDebug>
#include <QFont>
#include <QTime>
#include <QTimer>

KJModel::KJModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

int KJModel::rowCount(const QModelIndex &parent) const
{
    //qDebug() << "row count: " << parent.row() << parent.column() << ":" << _data.count();
    return m_data.count();
}

int KJModel::columnCount(const QModelIndex &parent) const
{
    //qDebug() << "col count: " << parent.row() << parent.column();
    return 1;
}

QVariant KJModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant("Messages");
}

QVariant KJModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch (role)
    {
    case Qt::DisplayRole:
        return QString ("Row%1, Column%2").arg(row+1).arg(col+1);
        break;

    case Qt::FontRole:
        if (row == 0 && col == 0)
        {
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
        break;

    case Qt::BackgroundRole:
        if (row == 1 && col == 2)
        {
            QBrush redBG(Qt::red);
            return redBG;
        }
        break;

    case Qt::TextAlignmentRole:
        if (row == 1 && col == 1)
        {
            return Qt::AlignRight + Qt::AlignHCenter;
        }
        break;

    case Qt::CheckStateRole:
        if (row == 1 && col == 0)
        {
            return Qt::Checked;
        }
        break;
    }

    return QVariant();
}

Qt::ItemFlags KJModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void KJModel::reloadData()
{
    emit dataChanged(this->index(0, 0), this->index(m_data.count(), 0));
    emit layoutChanged();
}

void KJModel::addItem()
{
    m_data.append(QString("Row: %1").arg(m_data.count()));
}

void KJModel::removeItem()
{
    if (m_data.length() > 0)
    {
        m_data.removeLast();
    }
}
