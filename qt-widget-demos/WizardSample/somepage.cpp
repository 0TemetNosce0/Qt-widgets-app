#include "somepage.h"

SomePage::SomePage(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

SomePage::~SomePage()
{

}

void SomePage::initialize(int someData)
{
    ui.someDataSpinBox->setValue(someData);

}

int SomePage::someData() const
{
    return ui.someDataSpinBox->value();
}
