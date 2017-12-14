#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colorcombox.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ColorCombox* combox = new ColorCombox(this);
    combox->resize(200,300);
    QVBoxLayout* pLayout = new QVBoxLayout(this);

    pLayout->addWidget(combox);

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
