#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridwidget.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GridWidget* pWidget = new GridWidget();
    QVBoxLayout* pLayout = new QVBoxLayout(this);

    pLayout->addWidget(pWidget);

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
