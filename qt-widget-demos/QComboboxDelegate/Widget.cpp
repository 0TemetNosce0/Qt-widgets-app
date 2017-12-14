#include "widget.h"
#include "ui_Widget.h"
#include "ItemDelegate.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ItemDelegate *pDelegate = new ItemDelegate(this);
    ui->comboBox->setItemDelegate(pDelegate);
    ui->comboBox->setStyleSheet("QComboBox QAbstractItemView::item {min-height: 60px; min-width:60px;}");
    ui->comboBox->setStyleSheet("QComboBox QListView::item{color:green; font:13px;}");

    connect(pDelegate, SIGNAL(deleteItem(QModelIndex)), this, SLOT(deleteItem(QModelIndex)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::deleteItem(const QModelIndex &index)
{
    if (QMessageBox::question(this, QStringLiteral("提示"), QStringLiteral("确认要删除所选账号吗？"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
    {
        ui->comboBox->removeItem(index.row());
    }
}
