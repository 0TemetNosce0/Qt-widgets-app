#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include "customshadoweffect.h"
#include <QGraphicsDropShadowEffect>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   /* QPushButton **/ btn = new QPushButton(this);
    QPushButton * btn2 = new QPushButton(this);
    btn->setGeometry(100,100,100,100);
    btn->setText("test");
    btn2->setGeometry(230,100,100,100);
    btn2->setText("test2");
    CustomShadowEffect *bodyShadow = new CustomShadowEffect(this);//四周都有阴影
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 80));
    btn->setGraphicsEffect(bodyShadow);

    QGraphicsDropShadowEffect *bodyShadow2 = new QGraphicsDropShadowEffect(this);//只有下边和右边有阴影
    bodyShadow2->setBlurRadius(20.0);
//    bodyShadow2->setDistance(6.0);
    bodyShadow2->setColor(QColor(0, 0, 0, 80));
    btn2->setGraphicsEffect(bodyShadow2);
    connect(btn,&QPushButton::clicked,this,&MainWindow::on_btn_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_clicked()
{
    m_paintTool = new QDialog(this);

    m_paintTool->move(10,10);
    m_paintTool->show();
}
