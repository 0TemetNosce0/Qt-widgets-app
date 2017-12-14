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
    // 定义全局的ToolTip，方便使用
    g_toolTip = ctoolTip;

    // 本行代码主要针对ListWidgetItem右键点击时才生效的
    ui->listWidget->setMouseTracking(true);

    // 添加测试数据
    for (int i = 0; i < 10; i++)
    {
        ItemWidget *itemWidget = new ItemWidget(ui->listWidget);
        itemWidget->setText(QPixmap(QString(":/images/%1").arg(i+1)),
                            QStringLiteral("标题"), QStringLiteral("写点什么呢: %1?").arg(i));
        QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
        // 此处的size如果不设置,界面被压缩了看不出ItemWidget的效果,高度一定要设置
        listItem->setSizeHint(QSize(200, 40));
        ui->listWidget->setItemWidget(listItem, itemWidget);
    }
}

MainWidget::~MainWidget()
{
    delete ui;
}

