#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->wContainer->appedWidget(new QLabel("any text"));
	ui->wContainer->appedWidget(new QPushButton("any button"));
	ui->wContainer->appedWidget(new QSpinBox);
	ui->wContainer->appedWidget(new QDateTimeEdit);
	ui->wContainer->appedWidget(new QTextEdit("any big text"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
