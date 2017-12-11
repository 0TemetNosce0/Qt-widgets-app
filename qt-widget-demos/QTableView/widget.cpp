#include "widget.h"
#include "ui_widget.h"

#include "qcomboboxitemdelegate.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initModel();
    setupUi();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initModel()
{
    itemModel = new QStandardItemModel(5, 5, this);
    for (int i = 0; i < 5; ++i)
    {
        itemModel->setHeaderData(i, Qt::Horizontal, 1, Qt::UserRole);
    }

//    for (int i = 0; i < 5; ++i)
//    {
//        QStandardItem *itemName = new QStandardItem(QString("name %1").arg(i));
//        QStandardItem *itemTime = new QStandardItem(QString("time %1").arg(i));

//        QString status;

//        if (i % 2 == 0)
//        {
//            status = "Enabled";
//        }
//        else
//        {
//            status = "Disabled";
//        }

//        QStandardItem *itemStatus = new QStandardItem(status);

//        QList<QStandardItem*> row;
//        row << itemName << itemTime << itemStatus;

//        itemModel->appendRow(row);
//    }
}

void Widget::setupUi()
{
    this->setWindowTitle("QAlarmClock");
//    QStringList labelList;
//    labelList << "Alarm Name" << "Time" << "Enabled";
//    itemModel->setHorizontalHeaderLabels(labelList);
    ui->tableView->setModel(itemModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ButtonColumnDelegate *delegate = new ButtonColumnDelegate(ui->tableView);
    ui->tableView->setItemDelegate(delegate);
    ui->tableView->setStyleSheet("selection-background-color: red");
    ui->tableView->setStyleSheet("QTableView::Item{background-color:#FF3EFF}");
}

//void Widget::on_actionNew_triggered()
//{
//    alarmDialog = new AlarmDialog(this);
//    connect(alarmDialog, SIGNAL(on_close()), this, SLOT(on_alarmDialog_close()));
//    alarmDialog->exec();
//}

//void Widget::on_alarmDialog_close()
//{
//    QString alarmName = alarmDialog->getAlarmName();
//    QDateTime alarmDateTime = alarmDialog->getDateTime();

//    itemModel->insertRow(itemModel->rowCount());
//    int rowCount = itemModel->rowCount();

//    // Alarm Name
//    QStandardItem* alarmItem = new QStandardItem(QIcon("res/alarmclock.ico"),  alarmName);
//    itemModel->setItem(rowCount - 1 , 0, alarmItem);

//    // Date Time
//    QStandardItem* dateTimeItem = new QStandardItem();
//    dateTimeItem->setText(alarmDateTime.toString());
//    dateTimeItem->setEditable(false);
//    itemModel->setItem(rowCount - 1, 1, dateTimeItem);

//    // Enabled
//    QStandardItem* enabledItem = new QStandardItem();
//    QList<QStandardItem*> optionList;
//    optionList << new QStandardItem("Enabled") << new QStandardItem("Disabled");
//    enabledItem->appendRows(optionList);
//    itemModel->setItem(rowCount - 1, 2, enabledItem);
//}
