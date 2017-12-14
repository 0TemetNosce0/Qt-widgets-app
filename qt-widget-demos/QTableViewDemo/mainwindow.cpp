#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "proxystyle.h"
#include "nofocusdelegate.h"
#include "booleandelegate.h"
#include "scrollproxystyle.h"

#include <QFile>
#include <QScrollBar>
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //15 Rows and 2 Columns
    QStandardItemModel *model = new QStandardItemModel(/*20, 10, */this);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column1")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Column2")));
    //model->setHorizontalHeaderItem(2, new QStandardItem(QString("Column3 Header")));

    //QStandardItem *firstRow = new QStandardItem(QString("Value"));
    //model->setItem(0, 0, firstRow);

    for (int nRow = 0; nRow < 20; ++nRow)
    {
        QList<QStandardItem *> itemList;
        for (int nCol = 0; nCol < 10; ++nCol)
        {
            itemList.append(new QStandardItem(QString::number(nRow) + " Row " + QString::number(nCol) + " Col"));
        }

        model->appendRow(itemList);
    }


    ptableView = new QTableView();
    ptableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);


    // �����п���Ӧ��ǰ����
    //ptableView->resizeColumnsToContents();

    // ���ñ�ͷ�Ƿ������ק�͵��
    ptableView->horizontalHeader()->setSectionsMovable(true);
    ptableView->horizontalHeader()->setSectionsClickable(true);

    // ������ѡ
    ptableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ptableView->setAlternatingRowColors(false);

    // �Ƿ�������ק
    ptableView->horizontalHeader()->setDragEnabled(true);
    ptableView->horizontalHeader()->setDragDropMode(QAbstractItemView::DragOnly);

    /*����ѡ���ѡ*/
    ptableView->setSelectionMode(QAbstractItemView::ContiguousSelection);

    // ��������ʱ��,���Ҳ����ͬ�����ڱ����仯����,�����ֿհ�
    ptableView->setModel(model);
    //ptableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);// �����о��ɽ�������
    ptableView->horizontalHeader()->setStretchLastSection(true);// ֻ�����һ�н�������,�����л���ԭ��
    //ptableView->horizontalHeader()->resizeSections(QHeaderView::Stretch);// ���ú�������

    ptableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ptableView->setEditTriggers(QAbstractItemView::AnyKeyPressed);

    //ptableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //ptableView->horizontalHeader()->setSortIndicatorShown(false);
    ptableView->setSortingEnabled(true);

    ptableView->setSpan(1, 2, 3, 3);

    /*��tableview�е�2���з���checkbox*/
    //BooleanDelegate *isNullableDelegate = new BooleanDelegate(this);
    //ptableView->setItemDelegateForColumn(1, isNullableDelegate);


    /*������ʽ*/
    //    ptableView->setAlternatingRowColors(false);
    //    QFile file(":/qss/tableview.qss");
    //    if (!file.open(QFile::ReadOnly))
    //    {
    //        return;
    //    }
    //    QString strQss = QString::fromLatin1(file.readAll());
    //    ptableView->setStyleSheet(strQss);
    //    file.close();


    // ѡ�и��Ӻ�,ȥ�����߿�.�������д����������һ�ַ�ʽ����
    //ptableView->setItemDelegate(new NoFocusDelegate);
    //ptableView->setStyle(new CustomProxyStyle);

    // ���ù�������ʽ
    //ptableView->horizontalScrollBar()->setStyle(new ScrollProxyStyle);
    //ptableView->verticalScrollBar()->setStyle(new ScrollProxyStyle);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(ptableView);

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
