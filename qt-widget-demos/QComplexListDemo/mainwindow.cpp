#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "layertableview.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LayerTableView* pTable = new LayerTableView(this);

    QVBoxLayout* pLayout = new QVBoxLayout(this);

    pLayout->addWidget(pTable);

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
