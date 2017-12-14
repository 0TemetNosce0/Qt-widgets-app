#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nightcharts.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(760, 760);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent * e)
{
    QWidget::paintEvent(e);
    QPainter painter;
    painter.begin(this);
    Nightcharts PieChart;
    PieChart.setType(Nightcharts::Dpie);//{Histogramm,Pie,Dpie};
    PieChart.setLegendType(Nightcharts::Round);//{Round,Vertical}
    PieChart.setCords(100, 100, this->width()/1.5, this->height()/1.5);
    PieChart.addPiece("Item1", QColor(200,10,50), 34);
    PieChart.addPiece("Item2", Qt::green, 27);
    PieChart.addPiece("Item3", Qt::cyan, 14);
    PieChart.addPiece("Item4", Qt::yellow, 7);
    PieChart.addPiece("Item5", Qt::blue, 4);
    PieChart.draw(&painter);
    PieChart.drawLegend(&painter);
}
