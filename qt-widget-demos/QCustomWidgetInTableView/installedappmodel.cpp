#include "installedappmodel.h"
#include <QDebug>

InstalledAppModel::InstalledAppModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_rowCount(20)
{
    // m_name = QString::fromLocal8Bit("ÃÏµÿ≈˘ˆ®”Œœ¿");
    m_checked = false;
    m_selectionModel = new QItemSelectionModel(this);
    // connect(m_selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
    // this, SLOT(handleSelectionChanged(QItemSelection, QItemSelection)));
    for (int i = 0; i < 20; ++i)
    {
        beginInsertRows(QModelIndex(), 0, 0);
        m_name << QString::number(i);
        endInsertRows();
    }
}

void InstalledAppModel::remove()
{
    qDebug() << "installed app model remove" << endl;
    beginRemoveRows(QModelIndex(), 0, 0);
    m_name.pop_front();
    endRemoveRows();
}

QVariant InstalledAppModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    switch (role)
    {
    case AppName:
        return m_name[index.row()];
    case AppIcon:
        return QString("app.png");
    case Qt::CheckStateRole:
        return m_selectionModel->isSelected(index);
    }

    return QVariant();
}

bool InstalledAppModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }

    switch (index.column())
    {
    case 0:
        if (role == Qt::CheckStateRole)
        {
            m_checked = value.toBool();
        }
        break;
    }
    emit dataChanged(this->index(0, 0), this->index(rowCount(QModelIndex())-1, columnCount(QModelIndex())-1));
    return true;
}

int InstalledAppModel::rowCount(const QModelIndex &parent) const
{
    return m_name.count();
}

int InstalledAppModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

void InstalledAppModel::changeName()
{
    //m_name = "my name";
    emit dataChanged(index(0, 1), index(3, 1));
}

void InstalledAppModel::changeChecked()
{
    m_checked = !m_checked;
    emit dataChanged(this->index(0, 0), this->index(3, 0));
}

void InstalledAppModel::setSelectionModel(QItemSelectionModel *model)
{
    m_selectionModel = model;
    connect(m_selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(handleSelectionChanged(QItemSelection, QItemSelection)));
}

void InstalledAppModel::handleSelectionChanged(QItemSelection select, QItemSelection deselect)
{
    emit dataChanged(this->index(0, 0), this->index(rowCount(QModelIndex())-1, columnCount(QModelIndex())-1));
}
