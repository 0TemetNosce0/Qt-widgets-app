#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "diagtableheader.h"

#include <QTablewidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //15 Rows and 2 Columns
    QStandardItemModel *model = new QStandardItemModel(1500, 2, this);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column1")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Column2")));
    //model->setHorizontalHeaderItem(2, new QStandardItem(QString("Column3 Header")));


    QStandardItem *firstRow = new QStandardItem(QString("Value"));
    model->setItem(0, 0, firstRow);

    QTableWidget *ptableView = new QTableWidget();
    ptableView->setHorizontalHeaderItem(0,new QTableWidgetItem("ltz"));
    ptableView->setHorizontalHeaderItem(1, new QTableWidgetItem("chenm"));
    ptableView->setHorizontalHeader(new DiagTableHeader(this));
    ptableView->horizontalHeader()->setSectionsMovable(true);
    ptableView->horizontalHeader()->setSectionsClickable(false);

    // 设置行选
    ptableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ptableView->setAlternatingRowColors(false);

    // 是否允许拖拽
    ptableView->horizontalHeader()->setDragEnabled(true);
    ptableView->horizontalHeader()->setDragDropMode(QAbstractItemView::DragOnly);


    //ptableView->setModel(model);
    ptableView->setRowCount(15);
    ptableView->setColumnCount(2);
    ptableView->horizontalHeader()->setStretchLastSection(true);// 只有最后一列进行拉伸,其余列还是原样

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(ptableView);

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
