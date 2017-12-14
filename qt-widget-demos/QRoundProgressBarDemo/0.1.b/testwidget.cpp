#include "testwidget.h"
#include "ui_testwidget.h"
#include "QRoundProgressBar.h"

TestWidget::TestWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestWidget)
{
    qApp->setStyle("fusion");

    ui->setupUi(this);

    ui->RoundBar1->setFormat("%v");
    ui->RoundBar1->setDecimals(0);
    ui->RoundBar1->setRange(ui->Slider->minimum(), ui->Slider->maximum());
    ui->RoundBar1->setValue(ui->Slider->value());
    connect(ui->Slider, SIGNAL(valueChanged(int)), ui->RoundBar1, SLOT(setValue(int)));

    ui->RoundBar2->setNullPosition(QRoundProgressBar::PositionRight);
    ui->RoundBar2->setBarStyle(QRoundProgressBar::StylePie);
    ui->RoundBar2->setRange(ui->Slider->minimum(), ui->Slider->maximum());
    ui->RoundBar2->setValue(ui->Slider->value());
    connect(ui->Slider, SIGNAL(valueChanged(int)), ui->RoundBar2, SLOT(setValue(int)));

    ui->RoundBar3->setFormat("%m");
    ui->RoundBar3->setBarStyle(QRoundProgressBar::StyleLine);
    ui->RoundBar3->setRange(ui->Slider->minimum(), ui->Slider->maximum());
    ui->RoundBar3->setValue(ui->Slider->value());
    connect(ui->Slider, SIGNAL(valueChanged(int)), ui->RoundBar3, SLOT(setValue(int)));

    ui->RoundBar4->setDecimals(2);
    ui->RoundBar4->setBarStyle(QRoundProgressBar::StyleLine);
    ui->RoundBar4->setOutlinePenWidth(18);
    ui->RoundBar4->setDataPenWidth(10);
    ui->RoundBar4->setRange(ui->Slider->minimum(), ui->Slider->maximum());
    ui->RoundBar4->setValue(ui->Slider->value());
    connect(ui->Slider, SIGNAL(valueChanged(int)), ui->RoundBar4, SLOT(setValue(int)));

    ui->RoundBar5->setNullPosition(QRoundProgressBar::PositionBottom);
    ui->RoundBar5->setRange(-1, 1);
    ui->RoundBar5->setValue(-0.25);
}

TestWidget::~TestWidget()
{
    delete ui;
}
