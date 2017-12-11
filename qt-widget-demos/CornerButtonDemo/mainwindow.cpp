#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GCornerTableView.h"

#include <QVBoxLayout>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GCornerTableView *pCornerTableView = new GCornerTableView(this);

    QStandardItemModel *pModel = new QStandardItemModel(10, 10, pCornerTableView);
    pCornerTableView->setModel(pModel);

    pCornerTableView->setCornerButtonText(QStringLiteral("²âÊÔ"));

    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->addWidget(pCornerTableView);

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
