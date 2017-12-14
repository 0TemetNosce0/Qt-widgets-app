#include <QTableView>
#include <QApplication>
#include <QStandardItemModel>

#include "ProxyModelWithHeaderModels.h"

void BuildDataModel(QStandardItemModel& model)
{
    QString cellText("cell(%1, %2)");
    for(int i = 0; i < 4; ++i)
    {
        QList<QStandardItem*> itemList;
        for(int j = 0; j < 4; ++j)
        {
            QStandardItem* cell = new QStandardItem(cellText.arg(i).arg(j));
            itemList.push_back(cell);
        }
        model.appendRow(itemList);
    }
}

void BuildHeaderModel(QStandardItemModel& headerModel)
{
    QStandardItem* rootItem = new QStandardItem("root");
    QList<QStandardItem*> itemList;

    QStandardItem *rotatedTextCell = new QStandardItem("Rotated text");
    rotatedTextCell->setData(1, Qt::UserRole);
    itemList.push_back(rotatedTextCell);
    rootItem->appendColumn(itemList);

    itemList.clear();

    QStandardItem* cell = new QStandardItem("level 2");
    itemList.push_back(cell);
    rootItem->appendColumn(itemList);

    itemList.clear();

    itemList.push_back(new QStandardItem("level 3"));
    cell->appendColumn(itemList);

    itemList.clear();

    itemList.push_back(new QStandardItem("level 3"));
    cell->appendColumn(itemList);

    itemList.clear();

    itemList.push_back(new QStandardItem("level 2"));
    rootItem->appendColumn(itemList);

    headerModel.setItem(0, 0, rootItem);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QStandardItemModel headerModel;
    BuildHeaderModel(headerModel);

    QStandardItemModel dataModel;
    BuildDataModel(dataModel);

    ProxyModelWithHeaderModels model;
    model.setSourceModel(&dataModel);
    model.setHorizontalHeaderModel(&headerModel);
    model.setVerticalHeaderModel(&headerModel);

    QTableView tableView;
    HierarchicalHeaderView *headView = new HierarchicalHeaderView(Qt::Horizontal, &tableView);
    tableView.setHorizontalHeader(headView);

    headView = new HierarchicalHeaderView(Qt::Vertical, &tableView);
    tableView.setVerticalHeader(headView);

    tableView.setModel(&model);
    tableView.resizeColumnsToContents();
    tableView.resizeRowsToContents();
    tableView.horizontalHeader()->setStretchLastSection(true);
    tableView.verticalHeader()->setStretchLastSection(true);
    tableView.show();

    return app.exec();
}

