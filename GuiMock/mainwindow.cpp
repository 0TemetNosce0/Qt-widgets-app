#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    DragWidget *drag = new DragWidget;
    this->setCentralWidget(drag);
    drag->show();
}

MainWindow::~MainWindow() {
}
