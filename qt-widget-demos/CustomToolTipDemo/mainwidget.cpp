#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "itemwidget.h"
#include "ctooltip.h"

#include <QListWidgetItem>

CToolTip *g_toolTip;

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    //    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    ui->setupUi(this);
    ctoolTip = new CToolTip();
    // ����ȫ�ֵ�ToolTip������ʹ��
    g_toolTip = ctoolTip;

    // ���д�����Ҫ���ListWidgetItem�Ҽ����ʱ����Ч��
    ui->listWidget->setMouseTracking(true);

    // ��Ӳ�������
    for (int i = 0; i < 10; i++)
    {
        ItemWidget *itemWidget = new ItemWidget(ui->listWidget);
        itemWidget->setText(QPixmap(QString(":/images/%1").arg(i+1)),
                            QStringLiteral("����"), QStringLiteral("д��ʲô��: %1?").arg(i));
        QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
        // �˴���size���������,���汻ѹ���˿�����ItemWidget��Ч��,�߶�һ��Ҫ����
        listItem->setSizeHint(QSize(200, 40));
        ui->listWidget->setItemWidget(listItem, itemWidget);
    }
}

MainWidget::~MainWidget()
{
    delete ui;
}

