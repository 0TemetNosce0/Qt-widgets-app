#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtCheckHeaderView.h"

#include <QTableView>
#include <QVBoxLayout>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(this);
    QTableView *tableView = new QTableView();
    tableView->setModel(model);

    QtCheckHeaderView *header = new QtCheckHeaderView(Qt::Horizontal, tableView);
    QtCheckHeaderView *vheader = new QtCheckHeaderView(Qt::Vertical, tableView);

    tableView->setHorizontalHeader(header);
    tableView->setVerticalHeader(vheader);

    QStandardItem *root = model->invisibleRootItem();
    QList<QList<QStandardItem *> > items;
    for (int i = 0; i < 10; ++i)
    {
        bool isBool = qrand() % 2;
        QList<QStandardItem *> res;
        for (int j = 0; j < 10; ++j)
        {
            res.append(new QStandardItem(QString("(%1,%2)").arg(j).arg(i)));
            if (isBool)
            {
                res.at(j)->setCheckable(true);
                res.at(j)->setCheckState(Qt::CheckState(qrand()%3));
                res.at(j)->setTristate(true);
            }
        }
        items.append(res);
        root->appendColumn(res);

        if (isBool)
            header->addCheckable(i);
    }

    vheader->addCheckable(5);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(tableView);

    ui->centralWidget->setLayout(pLayout);

}

MainWindow::~MainWindow()
{
    delete ui;
}
