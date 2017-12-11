#include "mainwindow.h"
#include "qfindedit.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFindEdit* edit = new QFindEdit(this);

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(edit);
    centralWidget()->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
