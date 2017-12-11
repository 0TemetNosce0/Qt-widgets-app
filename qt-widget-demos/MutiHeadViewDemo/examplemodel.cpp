#include "examplemodel.h"
#include "HierarchicalHeaderView.h"

ExampleModel::ExampleModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    fillHeaderModel(_horizontalHeaderModel);
    fillHeaderModel(_verticalHeaderModel);
}

int ExampleModel::rowCount(const QModelIndex& /*parent*/) const
{
    return 5;
}

int ExampleModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 4;
}

QVariant ExampleModel::data(const QModelIndex& index, int role) const
{
    if(role == HierarchicalHeaderView::HorizontalHeaderDataRole)
    {
        QVariant v;
        v.setValue((QObject*)&_horizontalHeaderModel);
        return v;
    }

    if(role == HierarchicalHeaderView::VerticalHeaderDataRole)
    {
        QVariant v;
        v.setValue((QObject*)&_verticalHeaderModel);
        return v;
    }

    if(role == Qt::DisplayRole && index.isValid())
    {
        return QString("index(%1, %2)").arg(index.row()).arg(index.column());
    }

    return QVariant();
}

Qt::ItemFlags ExampleModel::flags(const QModelIndex & index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void ExampleModel::fillHeaderModel(QStandardItemModel& headerModel)
{
    QStandardItem* rootItem = new QStandardItem("root");
    QList<QStandardItem*> l;

    QStandardItem* rotatedTextCell = new QStandardItem("Rotated text");
    rotatedTextCell->setData(1, Qt::UserRole);
    l.push_back(rotatedTextCell);
    rootItem->appendColumn(l);

    l.clear();

    QStandardItem* cell = new QStandardItem("level 2");
    l.push_back(cell);
    rootItem->appendColumn(l);

    l.clear();

    l.push_back(new QStandardItem("level 3"));
    cell->appendColumn(l);

    l.clear();

    l.push_back(new QStandardItem("level 3"));
    cell->appendColumn(l);

    l.clear();

    l.push_back(new QStandardItem("level 2"));
    rootItem->appendColumn(l);

    headerModel.setItem(0, 0, rootItem);
}
