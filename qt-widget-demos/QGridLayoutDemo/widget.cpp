#include "Widget.h"
#include "ui_Widget.h"
#include "SearchButton.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    new SearchButton(QStringLiteral("ËÑË÷"), ui->lineEdit_1);
}

Widget::~Widget()
{
    delete ui;
}
