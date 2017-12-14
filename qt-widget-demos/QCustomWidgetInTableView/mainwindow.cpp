#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "installedappmodel.h"
#include "installedappdelegate.h"
#include <QTableView>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTableView* pTableView = new QTableView(this);
    pTableView->setItemDelegate(new InstalledAppDelegate);
    pTableView->setModel(new InstalledAppModel);
    pTableView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->addWidget(pTableView);

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
