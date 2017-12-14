#include "stretchdemo.h"
#include "ui_stretchdemo.h"
#include <QVBoxLayout>

StretchDemo::StretchDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StretchDemo)
{
    ui->setupUi(this);

    button1 = new QPushButton(tr("1"));
    button2 = new QPushButton(tr("2"));
    button3 = new QPushButton(tr("3"));
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(button1);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(button2);
    buttonLayout->addStretch(3);
    buttonLayout->addWidget(button3);
//    buttonLayout->addStretch(6);

    ui->centralWidget->setLayout(buttonLayout);
}

StretchDemo::~StretchDemo()
{
    delete ui;
}
