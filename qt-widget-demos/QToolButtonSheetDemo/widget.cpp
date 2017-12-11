#include "widget.h"
#include "ui_widget.h"
#include "customtoolbutton.h"

#include <QVBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    CustomToolButton* pButton = new CustomToolButton(this, 20, 20, 20, 10);

    QVBoxLayout* pLayout = new QVBoxLayout(this);

    pLayout->addWidget(pButton);

    setLayout(pLayout);
}

Widget::~Widget()
{
    delete ui;
}
