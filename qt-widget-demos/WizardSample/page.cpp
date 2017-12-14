#include "page.h"

Page::Page(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

Page::~Page()
{

}

void Page::initialize(int value)
{
    ui.timeEductaionSpinBox->setValue(value);
}

int Page::returnTimeEducationSpinBoxValue() const
{
    return ui.timeEductaionSpinBox->value();
}

bool Page::returnFlagHowToWork() const
{
    return ui.FlagHowToWork->isChecked();
}
