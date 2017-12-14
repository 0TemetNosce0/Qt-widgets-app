#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(size()); //�����ڴ�С�̶�����

    ui->treeWidget->expandAll();
}


MainWindow::~MainWindow()
{
    delete ui;
}
