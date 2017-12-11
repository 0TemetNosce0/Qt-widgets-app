#include "mainwindow.h"
#include "TagTreeModel.h"
#include <QHeaderView>

TreeView::TreeView(QWidget *parent)
    :QTreeView(parent)
{
    pModel = new TagTreeModel();

    this->setModel(pModel);
    this->resizeColumnToContents(0);
    this->setAlternatingRowColors(true);
    this->setGeometry(300, 300, 500, 500);
    this->setWindowTitle(QStringLiteral("树形折叠展开"));
    // 选择一行中的某一个，默认选中一行
    // this->setSelectionBehavior(QAbstractItemView::SelectItems);

    this->setStyleSheet("QTreeView::item{height: 25px;show-decoration-selected: 0;}"
                        "QTreeView::item:selected{background: #00C8FF;}"
                       );

    connect(this, SIGNAL(expanded(const QModelIndex &)), this, SLOT(expand(const QModelIndex &)));
    connect(this, SIGNAL(collapsed(const QModelIndex &)), this, SLOT(collapse(const QModelIndex &)));
}

TreeView::~TreeView()
{
    if(pModel)
    {
        delete pModel;
    }
}

void TreeView::expand(const QModelIndex &index)
{
    pModel->setData(index, true, Qt::DecorationRole);
}

void TreeView::collapse(const QModelIndex &index)
{
    pModel->setData(index, false, Qt::DecorationRole);
}

