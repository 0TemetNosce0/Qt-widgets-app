#include "Widget.h"
#include "ui_Widget.h"
#include "PageWidget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lineEdit->setValidator(new QIntValidator(1, 10000000, this));

    // 把分页的组件加入到当前窗口
    pageWidget = new PageWidget();
    layout()->addWidget(pageWidget);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeMaxPage()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(changeMaxPage()));
}

Widget::~Widget() {
    delete ui;
}

void Widget::changeMaxPage() {
    pageWidget->setMaxPage(ui->lineEdit->text().toInt());
    pageWidget->setCurrentPage(1);
}
