#include "student.h"
#include <QDebug>

Student::Student(int num, QString name, int id,
                 QString phone, QString level, QString desc, bool checked)
    : m_num(num)
    , m_name(name)
    , m_id(id)
    , m_phone(phone)
    , m_level(level)
    , m_desc(desc)
    , m_checked(checked)
{

}

CustomModel::CustomModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

void CustomModel::setStudenetList(const QList<Student>& list)
{
    m_list = list;
}

int CustomModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return m_list.count();
}

int CustomModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return 7;
}

QVariant CustomModel::data(const QModelIndex & index, int role) const
{
    if (index == QModelIndex() || role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (index.column() == 0)
    {
        int num = m_list[index.row()].m_num;
        return QVariant(num);
    }

    if (index.column() == 1)
    {
        QString name = m_list[index.row()].m_name;
        return QVariant(name);
    }

    if (index.column() == 2)
    {
        int id = m_list[index.row()].m_id;
        return QVariant(id);
    }

    if (index.column() == 3)
    {
        QString phone = m_list[index.row()].m_phone;
        return QVariant(phone);
    }

    if (index.column() == 4)
    {
        QString level = m_list[index.row()].m_level;
        return QVariant(level);
    }

    if (index.column() == 5)
    {
        QString desc = m_list[index.row()].m_desc;
        return QVariant(desc);
    }

    if (index.column() == 6)
    {
        bool checked = m_list[index.row()].m_checked;
        return QVariant(checked);
    }

    return QVariant();
}

bool CustomModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role != Qt::EditRole)
    {
        return false;
    }

    if (index.column() == 0)
    {
        m_list[index.row()].m_num = value.toInt();
        return true;
    }

    if (index.column() == 1)
    {
        m_list[index.row()].m_name = value.toString();
        return true;
    }

    if (index.column() == 2)
    {
        m_list[index.row()].m_id = value.toInt();
        return true;
    }

    if (index.column() == 3)
    {
        m_list[index.row()].m_phone = value.toString();
        return true;
    }

    if (index.column() == 4)
    {
        m_list[index.row()].m_level = value.toString();
        return true;
    }

    if (index.column() == 5)
    {
        m_list[index.row()].m_desc = value.toString();
        return true;
    }

    if (index.column() == 6)
    {
        m_list[index.row()].m_checked = value.toBool();
        return true;
    }

    return false;
}

Qt::ItemFlags CustomModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool CustomModel::insertRows(int position, int rows, const QModelIndex &index)
{
    beginInsertRows(index, position, position + rows - 1);
    Student s(0, "", 0, "", "", "");
    m_list.insert(position, s);
    endInsertRows();
    return true;
}

bool CustomModel::removeRows(int position, int rows, const QModelIndex &index)
{
    beginRemoveRows(index, position, position + rows - 1);
    m_list.removeAt(position);
    endRemoveRows();
    return true;
}

void CustomModel::unselect()
{
    beginResetModel();

    int rows = this->rowCount();
    for(int i = 0; i < rows; ++i)
    {
        QModelIndex index = this->index(i, this->columnCount() - 1);
        bool checked = this->data(index).toBool();
        this->setData(index, !checked);
    }

    endResetModel();
}

void CustomModel::selectAll()
{
    beginResetModel();

    int rows = this->rowCount();
    for(int i = 0; i < rows; ++i)
    {
        QModelIndex index = this->index(i, this->columnCount() - 1);
        this->setData(index, true);
    }

    endResetModel();
}
