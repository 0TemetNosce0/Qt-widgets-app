#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "positioningmenubar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    PositioningMenuBar *menuBar = new PositioningMenuBar(ui->menuBar);

    QMenu *menuOptions = menuBar->addMenu(QLatin1Literal("&Options"));
    menuOptions->addAction(QLatin1Literal("About Qt"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
