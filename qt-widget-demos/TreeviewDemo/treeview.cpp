#include "treeview.h"
#include "ui_treeview.h"
#include <QDebug>

TreeView::TreeView() : QTreeView()
{
    model = new QStandardItemModel(4,2);
    model->setHeaderData(0, Qt::Horizontal, tr("Service"));
    model->setHeaderData(1, Qt::Horizontal, tr("Details"));

    QStandardItem *item1 = new QStandardItem("avahi-daemon");
    item1->setIcon(QIcon("gparted.png"));

    QStandardItem *item2 = new QStandardItem("bluetooth");
    item2->setIcon(QIcon("gparted.png"));

    QStandardItem *item3 = new QStandardItem("crond");
    item3->setIcon(QIcon("gparted.png"));

    QStandardItem *item4 = new QStandardItem("cups");
    item4->setIcon(QIcon("gparted.png"));

    model->setItem(0, 0, item1);
    model->setItem(1, 0, item2);
    model->setItem(2, 0, item3);
    model->setItem(3, 0, item4);

    QStandardItem *item5 = new QStandardItem("fifth");
    item4->appendRow(item5);

    QModelIndex parent;

    for (int i = 0; i < 4; ++i)
    {
        parent = model->index(0, 0, parent);
        model->insertRows(0, 1, parent);
        model->insertColumns(0, 1, parent);
        QModelIndex index = model->index(0, 0, parent);
        model->setData(index, i);
    }

    this->setModel(model);
}

QList<QStandardItem*> TreeView::returnTheItems()
{
    return model->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}

void TreeView::iterateOverItems()
{
    QList<QStandardItem*> list = returnTheItems();

    foreach (QStandardItem* item, list)
    {
        qDebug() << item->text();
    }
}

void TreeView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QModelIndex index = currentIndex();
        qDebug() << index.data().toString();
        qDebug() << this->visualRect(currentIndex());
        qDebug() << this->visualRect(currentIndex()).center();
        qDebug() << this->mapToGlobal(this->visualRect(currentIndex()).center());
        QModelIndex x = this->indexAt(this->mapToGlobal(this->visualRect(currentIndex()).center()));
        this->setCurrentIndex(x);
    }
}
