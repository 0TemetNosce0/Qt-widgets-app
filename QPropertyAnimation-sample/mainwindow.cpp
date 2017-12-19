#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QPropertyAnimation *pAnimation = new QPropertyAnimation();
//    pAnimation->setTargetObject(this);
//    pAnimation->setPropertyName("alpha");
//    pAnimation->setDuration(1000);
//    pAnimation->setKeyValueAt(0, 0);
//    pAnimation->setKeyValueAt(0.5, 100);
//    pAnimation->setKeyValueAt(1, 255);
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "windowOpacity");
    pAnimation->setDuration(1000);
    pAnimation->setKeyValueAt(0, 1);
    pAnimation->setKeyValueAt(0.5, 0);
    pAnimation->setKeyValueAt(1, 1);

    pAnimation->setLoopCount(-1);  //永远运行，直到stop
    pAnimation->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}
