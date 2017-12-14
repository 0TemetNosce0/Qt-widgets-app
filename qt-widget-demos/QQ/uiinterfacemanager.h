#ifndef UIINTERFACEMANAGER_H
#define UIINTERFACEMANAGER_H

#include "uiimsbasedialog.h"
namespace Ui {class UiInterfaceManager;};

class QTableWidgetItem;
class UiInterfaceManager : public UiImsBaseDialog
{
	Q_OBJECT

public:
	UiInterfaceManager(QWidget *parent = 0);
	~UiInterfaceManager();
signals:
	void interToolMove(int index,bool up);
	void interToolVisibleChanged(int index,bool visible);
	void mainTabVisibleChanged(int index,bool visible);
public slots:
	void showSkin();
	void showInterManager();
protected slots:
	void doPushButtonSkin();
	void doPushButtonInter();
	void doPushButtonClassic();
	void doPushButtonCover();	
	void doPushButtonMoveUp();
	void doPushButtonMoveDown();
	void doInterItemSelectionChanged();
	void doInteritemChanged(QTableWidgetItem * item);
	void doMainTabitemChanged(QTableWidgetItem * item);	
private:
	Ui::UiInterfaceManager *ui;
};

#endif // UIINTERFACEMANAGER_H
