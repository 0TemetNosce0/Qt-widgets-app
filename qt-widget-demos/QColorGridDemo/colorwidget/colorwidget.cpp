#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
    , ui(new Ui::ColorWidget)
{
    ui->setupUi(this);
    
    ui->colorBtn1->setPickModeLeft(ColorButton::PM_COLORDIALOG);

    ui->colorBtn2->setColor(Qt::cyan);
    ui->colorBtn2->setPickModeLeft(ColorButton::PM_COLORGRID);

    ui->cellWidth->setValue(ui->colorWidget->widthInCells());
    ui->cellSize->setValue(ui->colorWidget->cellSize());
}

ColorWidget::~ColorWidget()
{

}

void ColorWidget::on_colorWidget_highlighted(const QColor &color)
{
    ui->highLightedColorEdit->setText(color.name());
}

void ColorWidget::on_colorWidget_picked(const QColor &color)
{
    ui->pickedColorEdit->setText(color.name());
}

void ColorWidget::on_slCellSize_valueChanged(int v)
{
    ui->colorWidget->setCellSize(v);
    adjustSize();
}

void ColorWidget::on_slCellWidth_valueChanged(int v)
{
    ui->colorWidget->setWidthInCells(v);
    adjustSize();
}

void ColorWidget::on_cbScheme_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->colorWidget->setScheme(ColorGrid::defaultColors());
        break;
    case 1:
        ui->colorWidget->setScheme(ColorGrid::baseColors());
        break;
    case 2:
        ui->colorWidget->setScheme(ColorGrid::namedColors());
        break;
    default:;
    }
    
    adjustSize();
}
