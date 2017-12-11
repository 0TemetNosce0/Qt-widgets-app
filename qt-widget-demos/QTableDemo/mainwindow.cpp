#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableView>
#include <QVBoxLayout>
#include "qtable.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTableView *pTableView = new QTableView();

    // Making
    static QTable table;
    pTableView->setModel( table.model() );
    // Cofiguring
    table.setColumnCount(3);
    table.setColumnHeaders( QTableLine( "Name", "Product", "Cost" ) );
    // Add data
    table.appendRow( QTableLine( "V. Pupkin", "Car", "22000" ) );
    table.appendRow( QTableLine( "I. Ivanov", "T-Shirt", "15" ) );

    QVBoxLayout *pLayout = new QVBoxLayout(this);
    pLayout->addWidget(pTableView);
    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
