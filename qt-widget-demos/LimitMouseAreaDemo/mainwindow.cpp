#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *pModel = new QStandardItemModel(3,6);
    QTableView *pTableView = new QTableView(this);
    pTableView->setModel(pModel);

    QVBoxLayout *pLayout = new QVBoxLayout(this);
    pLayout->addWidget(pTableView);
    centralWidget()->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
