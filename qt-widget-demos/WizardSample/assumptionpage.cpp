#include "assumptionpage.h"

AssumptionPage::AssumptionPage(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

AssumptionPage::~AssumptionPage()
{

}

void AssumptionPage::initialize(int educationMonthCount, bool willWorkHard)
{
    ui.educationMonthCountSpinBox->setValue(educationMonthCount);
    ui.willWorkHardCheckBox->setChecked(willWorkHard);
}

int AssumptionPage::educationMonthCount() const
{
    return ui.educationMonthCountSpinBox->value();
}

bool AssumptionPage::willWorkHard() const
{
    return ui.willWorkHardCheckBox->isChecked();
}
