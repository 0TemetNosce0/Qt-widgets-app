#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    label=new CTwinkleLabel(this);
    label->setGeometry(QRect(0,0,639,479));

    label->show();

    label->setText("fafafa");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(Res()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(Res1()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Res()
{
     label->setTwinkle(true);
}
void MainWindow::Res1()
{
     label->setTwinkle(false);
}
