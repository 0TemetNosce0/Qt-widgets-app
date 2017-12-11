#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bfwidget.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    BFWidget *pWidget = new BFWidget(this);

    QVBoxLayout *pLayout  =  new QVBoxLayout(this);
    pLayout->addWidget(pWidget);

    centralWidget()->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
