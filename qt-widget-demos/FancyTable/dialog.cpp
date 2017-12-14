#include <QDebug>
#include <QSettings>
#include <QStringList>
#include <QStandardItem>
#include <QStandardItemModel>

#include "dialog.h"
#include "ui_dialog.h"
#include "ccustomtableview.h"
#include "ccustomheaderview.h"
#include "ccustomheadermodel.h"
#include "cdefaultitemdelegate.h"
#include "ccheckboxitemdelegate.h"
#include "cproxymodelwithheadermodels.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // model
    QStandardItemModel *dataModel = new QStandardItemModel(10, 10);
    cCustomHeaderModel *horizontalHeaderModel = new cCustomHeaderModel(2, 10, this);
    cProxyModelWithHeaderModels *pProxyModel = new cProxyModelWithHeaderModels(this);
    // delegate
    cDefaultItemDelegate *defaultItemDelegate = new cDefaultItemDelegate;
    cCheckBoxItemDelegate *checkBoxItemDelegate = new cCheckBoxItemDelegate;
    // view
    cCustomHeaderView *horizontalHeaderView = new cCustomHeaderView(ui->tableView);

    initHorizontalHeaderModel(horizontalHeaderModel);

    initProxyModel(pProxyModel, dataModel, horizontalHeaderModel);

    setUpTableView(horizontalHeaderView, pProxyModel, checkBoxItemDelegate, defaultItemDelegate);

    setUpTableWidget(checkBoxItemDelegate);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::closeEvent(QCloseEvent *e)
{
    qDebug() << "saving geometry";
    QSettings settings("MyCompany", "MyApp");
    settings.setValue("geometry", ui->tableView->horizontalHeader()->saveState());
    QWidget::closeEvent(e);
}

void Dialog::initHorizontalHeaderModel(cCustomHeaderModel *horizontalHeaderModel)
{
    horizontalHeaderModel->setItem(0, 0, new QStandardItem(QString::fromUtf8("item(0, 0)")));
    horizontalHeaderModel->setItem(1, 0, new QStandardItem(QString::fromUtf8("item(1, 0)")));

    horizontalHeaderModel->setItem(0, 1, new QStandardItem(QString::fromUtf8("item(0, 1)")));
    horizontalHeaderModel->setItem(0, 2, new QStandardItem(QString::fromUtf8("item(0, 2)")));

    // horizontalHeaderModel->setItem(1,1, new QStandardItem(QString::fromUtf8("column spanned item(1,1)")));
    horizontalHeaderModel->setItem(1, 1, new QStandardItem(QString::fromUtf8("item(1, 1)")));

    horizontalHeaderModel->setItem(0, 3, new QStandardItem(QString::fromUtf8("item(0, 3)")));
    horizontalHeaderModel->setItem(1, 3, new QStandardItem(QString::fromUtf8("item(1, 3)")));

    horizontalHeaderModel->setItem(0, 4, new QStandardItem(QString::fromUtf8("item(0, 4)")));
    horizontalHeaderModel->setItem(1, 4, new QStandardItem(QString::fromUtf8("item(1, 4)")));

    horizontalHeaderModel->setItem(0, 5, new QStandardItem(QString::fromUtf8("item(0, 5)")));
    horizontalHeaderModel->setItem(1, 5, new QStandardItem(QString::fromUtf8("item(1, 5)")));

    // horizontalHeaderModel->setItem(0,6, new QStandardItem(QString::fromUtf8("column spanned item(0,6)")));
    horizontalHeaderModel->setItem(0, 6, new QStandardItem(QString::fromUtf8("item(0, 6)")));
    horizontalHeaderModel->setItem(1, 6, new QStandardItem(QString::fromUtf8("item(1, 6)")));
    horizontalHeaderModel->setItem(1, 7, new QStandardItem(QString::fromUtf8("item(1, 7)")));

    horizontalHeaderModel->setItem(0, 8, new QStandardItem(QString::fromUtf8("item(0, 8)")));
    horizontalHeaderModel->setItem(1, 8, new QStandardItem(QString::fromUtf8("item(1, 8)")));

    // horizontalHeaderModel->setItem(0,9, new QStandardItem(QString::fromUtf8("row item(0,9)")));
    horizontalHeaderModel->setItem(0, 9, new QStandardItem(QString::fromUtf8("item(0, 9)")));


    //horizontalHeaderModel->setSpan(0,0,1,2); // 4 spanned columns
    //horizontalHeaderModel->setSpan(0,3,2,1); // 2 spanned rows

    horizontalHeaderModel->setSpan(1, 1, 1, 3); // 4 spanned columns x,y,rowSpan,colSpan
    horizontalHeaderModel->setSpan(0, 6, 1, 2); // 4 spanned columns
    horizontalHeaderModel->setSpan(0, 9, 2, 1); // 2 spanned rows
    // horizontalHeaderModel->setSpan(0,7,2,1); // 2 spanned rows
    // horizontalHeaderModel->setSpan(0,8,2,1); // 2 spanned rows
    // horizontalHeaderModel->setSpan(0,9,2,1); // 2 spanned rows
}

void Dialog::initProxyModel(cProxyModelWithHeaderModels * pProxyModel, QStandardItemModel * dataModel, 
                             cCustomHeaderModel * horizontalHeaderModel)
{
    pProxyModel->setSourceModel(dataModel);
    pProxyModel->setHorizontalHeaderModel(horizontalHeaderModel);
}

void Dialog::setUpTableView(cCustomHeaderView * horizontalHeaderView, cProxyModelWithHeaderModels * pProxyModel, 
                            cCheckBoxItemDelegate* checkBoxItemDelegate, cDefaultItemDelegate *defaultItemDelegate)
{
    ui->tableView->setHorizontalHeader(horizontalHeaderView);
    ui->tableView->setModel(pProxyModel);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    qDebug() << "restoring geometry";
    QSettings settings("MyCompany", "MyApp");
    ui->tableView->horizontalHeader()->restoreState(settings.value("geometry").toByteArray());

    for (unsigned int i = 0; i < pProxyModel->sourceModel()->columnCount(); ++i)
    {
        if (9 == i)
        {
            ui->tableView->setItemDelegateForColumn(i, checkBoxItemDelegate);
        }
        else
        {
            ui->tableView->setItemDelegateForColumn(i ,defaultItemDelegate);
        }
    }

    //ui->tableView->setItemDelegateForColumn(9, checkBoxItemDelegate);
    //ui->tableView->setItemDelegate(defaultItemDelegate);
}

void Dialog::setUpTableWidget(cCheckBoxItemDelegate * checkBoxItemDelegate)
{
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setItemDelegateForColumn(9, checkBoxItemDelegate);

    for (int row = 0; row < ui->tableWidget->rowCount(); row = row + 2)
    {
        ui->tableWidget->setSpan(row, 1, 1, 2);
        ui->tableWidget->setSpan(row, 9, 2, 1);
    }
    ui->tableWidget->setCurrentIndex(ui->tableWidget->model()->index(0, 1));
}
