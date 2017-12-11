#include "mainwindow.h"
#include "GTableWidget.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TableWidget *pTableWidget = new TableWidget(3, 3,this);
    pTableWidget->setStyleSheet("QTableCornerButton::section{background-color: red;}");
    pTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background: green}");
    pTableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background: green}");

    QVBoxLayout *pLayout = new QVBoxLayout(this);
    pLayout->addWidget(pTableWidget);

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
