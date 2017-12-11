#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(size()); //将窗口大小固定起来

    ui->treeWidget->expandAll();
}


MainWindow::~MainWindow()
{
    delete ui;
}
