#include "menuview.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MenuView *pMenu = new MenuView(QStringLiteral("menu"),this);
    ui->menuBar->addMenu(pMenu);
//    QVBoxLayout *pLayout = new QVBoxLayout(this);
//    pLayout->addWidget(pMenu);

//    centralWidget()->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
