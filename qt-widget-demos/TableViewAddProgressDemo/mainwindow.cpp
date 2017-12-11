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
    initTimer();
}

MainWindow::~MainWindow()
{
    delete tv;
    delete timer;
}

void MainWindow::init()
{
    this->resize(800, 600);
    tv = new TableView(this);
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(tv);
    this->setLayout(layout);
    //this->layout()->addWidget(tv);
}

void MainWindow::initTimer()
{
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressValue()));
    timer->start();
}

void MainWindow::updateProgressValue()
{
    TableModel *model = tv->tableModel();
    QVector<QStringList>& data = model->DataVector();

    foreach (QStringList v, data)
    {
        int value = v.at(1).toInt();
        qDebug() << value;

        if (value < 100)
        {
            value += 2;
            qDebug() << value;
            v[1] = QString::number(value);
            emit model->layoutChanged();
        }
    }
}
