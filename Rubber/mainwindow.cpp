#include "mainwindow.h"
#include "rubber.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Rubber*  s=  new Rubber(this);
//    s->show();
}

MainWindow::~MainWindow()
{

}
