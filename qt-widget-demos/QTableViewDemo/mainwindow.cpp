#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "proxystyle.h"
#include "nofocusdelegate.h"
#include "booleandelegate.h"
#include "scrollproxystyle.h"

#include <QFile>
#include <QScrollBar>
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //15 Rows and 2 Columns
    QStandardItemModel *model = new QStandardItemModel(/*20, 10, */this);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column1")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Column2")));
    //model->setHorizontalHeaderItem(2, new QStandardItem(QString("Column3 Header")));

    //QStandardItem *firstRow = new QStandardItem(QString("Value"));
    //model->setItem(0, 0, firstRow);

    for (int nRow = 0; nRow < 20; ++nRow)
    {
        QList<QStandardItem *> itemList;
        for (int nCol = 0; nCol < 10; ++nCol)
        {
            itemList.append(new QStandardItem(QString::number(nRow) + " Row " + QString::number(nCol) + " Col"));
        }

        model->appendRow(itemList);
    }


    ptableView = new QTableView();
    ptableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);


    // 调整列宽适应当前内容
    //ptableView->resizeColumnsToContents();

    // 设置表头是否可以拖拽和点击
    ptableView->horizontalHeader()->setSectionsMovable(true);
    ptableView->horizontalHeader()->setSectionsClickable(true);

    // 设置行选
    ptableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ptableView->setAlternatingRowColors(false);

    // 是否允许拖拽
    ptableView->horizontalHeader()->setDragEnabled(true);
    ptableView->horizontalHeader()->setDragDropMode(QAbstractItemView::DragOnly);

    /*允许单选或多选*/
    ptableView->setSelectionMode(QAbstractItemView::ContiguousSelection);

    // 拉动窗口时候,表格也按照同样窗口比例变化填满,不出现空白
    ptableView->setModel(model);
    //ptableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);// 所有列均可进行拉伸
    ptableView->horizontalHeader()->setStretchLastSection(true);// 只有最后一列进行拉伸,其余列还是原样
    //ptableView->horizontalHeader()->resizeSections(QHeaderView::Stretch);// 设置后不起作用

    ptableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ptableView->setEditTriggers(QAbstractItemView::AnyKeyPressed);

    //ptableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //ptableView->horizontalHeader()->setSortIndicatorShown(false);
    ptableView->setSortingEnabled(true);

    ptableView->setSpan(1, 2, 3, 3);

    /*将tableview中第2列中放置checkbox*/
    //BooleanDelegate *isNullableDelegate = new BooleanDelegate(this);
    //ptableView->setItemDelegateForColumn(1, isNullableDelegate);


    /*设置样式*/
    //    ptableView->setAlternatingRowColors(false);
    //    QFile file(":/qss/tableview.qss");
    //    if (!file.open(QFile::ReadOnly))
    //    {
    //        return;
    //    }
    //    QString strQss = QString::fromLatin1(file.readAll());
    //    ptableView->setStyleSheet(strQss);
    //    file.close();


    // 选中格子后,去除虚线框.以下两行代码采用任意一种方式均可
    //ptableView->setItemDelegate(new NoFocusDelegate);
    //ptableView->setStyle(new CustomProxyStyle);

    // 设置滚动条样式
    //ptableView->horizontalScrollBar()->setStyle(new ScrollProxyStyle);
    //ptableView->verticalScrollBar()->setStyle(new ScrollProxyStyle);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(ptableView);

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
