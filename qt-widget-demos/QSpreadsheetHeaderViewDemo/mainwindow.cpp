#include "mainwindow.h"
#include "TableModel.h"
#include "ui_mainwindow.h"
#include "QSpreadsheetHeaderView.h"
#include "tableview.h"

#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSpreadsheetHeaderView *headView = new QSpreadsheetHeaderView(Qt::Horizontal, this);
    headView->setSectionsClickable(true);
    headView->setHighlightSections(true);
    TableModel *model = new TableModel(this);
    TableView *tableView = new TableView(this);

    tableView->setModel(model);
    tableView->setHorizontalHeader(headView);
    tableView->horizontalHeader()->setStretchLastSection(true);

    setCentralWidget(tableView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
