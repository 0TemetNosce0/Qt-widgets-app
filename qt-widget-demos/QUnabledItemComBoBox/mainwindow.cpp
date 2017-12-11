#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ccombobox.h"
#include "accountitem.h"

#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    accountComboBox = new CComboBox(ui->centralWidget);
    accountComboBox->setGeometry(10, 10, 200, 25);

    listWidget = new QListWidget();
    accountComboBox->setModel(listWidget->model());
    accountComboBox->setView(listWidget);
    accountComboBox->setEditable(true); //设置QComboBox可编辑


    for(int i = 0; i < 3; i++)
    {
        AccountItem *accountItem = new AccountItem();
        accountItem->setAccountNumber(QString("safe_") + QString::number(i, 10) + QString("@sina.com"));
        connect(accountItem, SIGNAL(showAccount(QString)), this, SLOT(showAccount(QString)));
        connect(accountItem, SIGNAL(removeAccount(QString)), this, SLOT(removeAccount(QString)));
        QListWidgetItem* listItem = new QListWidgetItem(listWidget);
        listWidget->setItemWidget(listItem, accountItem);
    }

    accountComboBox->setItemEnable(listWidget, 2, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAccount(QString account)
{
    accountComboBox->setEditText(account);
    accountComboBox->hidePopup();
}

void MainWindow::removeAccount(QString account)
{
    accountComboBox->hidePopup();
    if(QDialog::Accepted ==  QMessageBox::question(this, QStringLiteral("提示"), QStringLiteral("是否删除？"),
                                                   QMessageBox::AcceptRole | QMessageBox::RejectRole, QMessageBox::AcceptRole))
    {
        int listCount = listWidget->count();
        for(int i = 0; i < listCount; i++)
        {
            QListWidgetItem* item = listWidget->item(i);
            AccountItem* account_item = (AccountItem *)(listWidget->itemWidget(item));
            QString accountNumber = account_item->getAccountNumber();
            if(account == accountNumber)
            {
                listWidget->takeItem(i);
                delete item;
                break;
            }
        }
    }
}
