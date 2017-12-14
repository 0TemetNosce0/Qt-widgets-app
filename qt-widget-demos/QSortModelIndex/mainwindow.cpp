#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <assert.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QModelIndex index = ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::compareModelIndex(const QModelIndex &index1, const QModelIndex &index2)
{
    assert(index1 != index2);

    if(index1.row() < index2.row())
    {
        return true;
    }
    else if(index1.row() > index2.row())
    {
        return false;
    }
    else
    {
        if(index1.column() < index1.column())
        {
            return true;
        }
        else if(index1.column() > index1.column())
        {
            return false;
        }
    }
}
