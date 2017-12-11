#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CompleteLineEdit.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();

    ui->centralWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    QStringList sl = QStringList() << "Biao" << "Bin" << "Huang" << "Hua" << "Hello" << "BinBin" << "Hallo";

    edit = new CompleteLineEdit(sl);
    button = new QPushButton("Button");

    layout = new QHBoxLayout();
    layout->addWidget(edit);
    layout->addWidget(button);
}
