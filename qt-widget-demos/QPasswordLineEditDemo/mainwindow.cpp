#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "passwordlineedit.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPasswordLineEdit *pLineEdit = new QPasswordLineEdit(this);

    QVBoxLayout *pLayout = new QVBoxLayout(this);
    pLayout->addWidget(pLineEdit);

    centralWidget()->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
