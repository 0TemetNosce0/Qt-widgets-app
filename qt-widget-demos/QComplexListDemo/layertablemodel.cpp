#include "layertablemodel.h"

LayerTableModel::LayerTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    QImage image("images/sample.jpg");
    layerList.reserve(3);
    selectedRow = 0;
    for (int i = 0; i < 5; i++)
    {
        addItem(QString(), image, true);
    }
}

LayerTableModel::~LayerTableModel()
{

}

QVariant LayerTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    int column = index.column();

    if (column == 0)
    {
        if(role ==  Qt::CheckStateRole)
        {
            return layerList.at(index.row()).isShow ? Qt::Checked : Qt::Unchecked;
        }

        if (role == Qt::SizeHintRole)
        {
            return QSize(20, 50);
        }
    }
    else
    {
        if (role == Qt::EditRole)
        {
            return QVariant(layerList.at(index.row()).layerName);
        }

        if (role == Qt::DisplayRole)
        {
            return QVariant(layerList.at(index.row()).layerName);
        }

        if (role == Qt::DecorationRole)
        {
            if (layerList.at(index.row()).thumbnail.isNull())
            {
                return  layerList.at(index.row()).thumbnail;
            }
            else
            {
                return  layerList.at(index.row()).thumbnail.scaledToHeight(40);

            }
        }

        if (role == Qt::SizeHintRole)
        {
            return QSize(200, 50);
        }

        if (role == Qt::TextAlignmentRole)
        {
            return int(Qt::AlignVCenter);
        }
    }

    return QVariant();
}

int LayerTableModel::rowCount(const QModelIndex &parent) const
{
    return (parent.isValid() && parent.column() != 0) ? 0 : layerList.size();
}

int LayerTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant LayerTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return QString::number(section);
    }
    //if (role == Qt::DecorationRole)
        //return QVariant::fromValue(services);
    return QAbstractItemModel::headerData(section, orientation, role);
}

Qt::ItemFlags LayerTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    if (index.column() == 0)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
    }

    return  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool LayerTableModel::setData(const QModelIndex &index, const
    QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }

    if (role == Qt::CheckStateRole && value.type() == QVariant::Bool)
    {
        layerList[index.row()].isShow = value.toBool();
        emit(dataChanged(index, index));
        return true;
    }

    if (role == Qt::EditRole && index.column() == 1)
    {
        layerList[index.row()].layerName = value.toString();
        emit(dataChanged(index, index));
        return true;
    }

    return false;;
}

void LayerTableModel::changeLayerVisibility(const QModelIndex& index)
{
    if (index.isValid()&&index.column() == 0)
    {
        setData(index, !(layerList.at(index.row()).isShow), Qt::CheckStateRole);
    }
}

void LayerTableModel::deleteItem(int index)
{
    QList<LayerItem>::iterator it = layerList.begin();
    layerList.erase(it + index);
}

void LayerTableModel::addItem(QString &name, QImage &thumb, bool show)
{
    LayerItem item;

    if (name.size() == 0)
    {
        item.layerName = QString("Layer ") + QString::number(layerList.size());
    }
    else
    {
        item.layerName = name;
    }

    item.isShow = show;

    item.thumbnail = thumb;
    layerList.append(item);
    //this->insertRow()
    //emit(dataChanged(index, index));
    qDebug() << layerList.size();
}

void LayerTableModel::refreshModel()
{
    beginResetModel();
    endResetModel();
    //emit updateCount(this->rowCount(QModelIndex()));
}

QModelIndex& LayerTableModel::selecttedIndex(int row)
{
    return createIndex(row, 1);
}

void LayerTableModel::setSelecttedRow(int row)
{
    selectedRow = row;
}

int LayerTableModel::getSelecttedRow() const
{
    return selectedRow;
}

