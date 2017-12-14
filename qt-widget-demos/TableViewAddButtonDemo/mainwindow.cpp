#include "mainwindow.h"

#include "tableview.h"
#include "tablemodel.h"

#include <QLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    init();
}

MainWindow::~MainWindow()
{
    delete tv;
}

void MainWindow::init()
{
    this->resize(800, 600);
    tv = new TableView(this);
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(tv);
    this->setLayout(layout);
}

