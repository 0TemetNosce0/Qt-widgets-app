#include "wizardsample.h"

WizardSample::WizardSample(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(this, SIGNAL(currentPageChanged(QWidget *, Direction)), SLOT(initializePage(QWidget *, Direction)));
}

WizardSample::~WizardSample()
{

}

void WizardSample::forward()
{
    changePage(ui.pagesWidget->currentWidget(), Direction::Forward);
}

void WizardSample::back()
{
    changePage(ui.pagesWidget->currentWidget(), Direction::Backward);
}

void WizardSample::changePage(QWidget *page, Direction direction)
{
    QWidget *nextPage = NULL;

    if (page == ui.page)
    {
        switch (direction)
        {
        case WizardSample::Forward:
            nextPage = ui.page_2;
            break;

        case WizardSample::Backward:
            break;

        default:
            break;
        }
    }

    if (page == ui.page_2)
    {
        switch (direction)
        {
        case WizardSample::Forward:
            break;

        case WizardSample::Backward:
            nextPage = ui.page;
            break;

        default:
            break;
        }
    }

    if (nextPage)
    {
        ui.pagesWidget->setCurrentWidget(nextPage);

        emit currentPageChanged(nextPage, direction);
    }
}

void WizardSample::initializePage(QWidget *page, Direction direction)
{
    if (page == ui.page)
    {
        switch (direction)
        {
        case WizardSample::Forward:
            break;

        case WizardSample::Backward:
            dynamic_cast<SomePage *>(page)->initialize(90);
            break;

        default:
            break;
        }
    }
}
