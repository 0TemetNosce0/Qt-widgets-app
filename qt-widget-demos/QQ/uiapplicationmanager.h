#ifndef UIAPPLICATIONMANAGER_H
#define UIAPPLICATIONMANAGER_H

#include "uiimsbasedialog.h"
namespace Ui {class UiApplicationManager;};

class UiApplicationManager : public UiImsBaseDialog
{
	Q_OBJECT

public:
	UiApplicationManager(QWidget *parent = 0);
	~UiApplicationManager();

private:
	Ui::UiApplicationManager *ui;
};

#endif // UIAPPLICATIONMANAGER_H
