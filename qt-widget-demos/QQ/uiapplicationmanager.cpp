#include "uiapplicationmanager.h"
#include "ui_uiapplicationmanager.h"

UiApplicationManager::UiApplicationManager(QWidget *parent)
	: UiImsBaseDialog(parent)
{
	ui = new Ui::UiApplicationManager();
	ui->setupUi(this);
}

UiApplicationManager::~UiApplicationManager()
{
	delete ui;
}

