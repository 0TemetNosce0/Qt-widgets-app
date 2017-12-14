#include "widget.h"
#include "ui_widget.h"
#include "QMultiComboBox.h"

#include <QVBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QMultiComboBox* pMultiComboBox = new QMultiComboBox(this);
    pMultiComboBox->setDisplayText("MultiItemChoose");

    for (int i = 0; i < 20; i++)
    {
        pMultiComboBox->addItem(QString("Item %1").arg(i), QVariant(true));
    }

    QVBoxLayout* pLayout = new QVBoxLayout(this);
    pLayout->addWidget(pMultiComboBox);
    pLayout->addSpacing(300);

    setLayout(pLayout);
}

Widget::~Widget()
{
    delete ui;
}
