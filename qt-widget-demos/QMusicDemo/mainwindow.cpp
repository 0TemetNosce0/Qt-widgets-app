#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mtablemodel.h"
#include "mtabledelegate.h"

#include <QFile>
#include <QTableView>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QStringList> *modelData = new QList<QStringList>;

    QStringList list1;
    list1 << "1" << "2" << "3";

    QStringList list2;
    list1 << "4" << "5" << "6";

    modelData->append(list1);
    modelData->append(list2);

    QTableView *pTableView = new QTableView(this);
    MTableModel *pModel = new MTableModel(this);
    pModel->setModelData(modelData);

    pTableView->setModel(pModel);
    pTableView->setItemDelegate(new MTableDelegate);


    QFile file(":/qheaderview.qss");
    if (!file.open(QFile::ReadOnly))
    {
        return;
    }
    QString strQss = QString::fromLatin1(file.readAll());
    pTableView->setStyleSheet(strQss);
    file.close();

    QVBoxLayout *pLayout = new QVBoxLayout(this);
    pLayout->addWidget(pTableView);
    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
