#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "medalwallwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MedalWallWidget* pWidget = new MedalWallWidget(this);

    QVBoxLayout* pLayout = new QVBoxLayout(this);

    pLayout->addWidget(pWidget);

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
