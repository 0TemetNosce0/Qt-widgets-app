#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <QMap>
#include <QSystemTrayIcon>

#include "uiloginscreen.h"
#include "imsdefine.h"

namespace Ui {class WorkStation;};

class QMenu;
class QToolButton;
class UiWeatherInfo;
class UiInterfaceManager;
class UiApplicationManager;
class WorkStation : public UiImsBaseDialog
{
	Q_OBJECT

public:
	WorkStation(QWidget *parent = 0);
	~WorkStation();

	static WorkStation *workStation(){return mWorkStation;}
	int createLoginScreen();
	void createShowScreen();
	void setCurrentWeather(QPixmap &pix);
protected:	
	virtual bool eventFilter(QObject *object, QEvent *event);
protected:
	void createStyleSheet();
	void createUserStateMenu();
	void createSystemTrayIcon();
	void createInterFaceManager();
	void createWeather();
	void changeUserStateIcon();
	void changeSystemTrayIcon();
	void addStateAction(QMenu *menu);
	QToolButton *userInfoAppToolButton(int index);
protected slots:
	void doTrayIconActivated(QSystemTrayIcon::ActivationReason reason );
	void doActionChangeState();
	void doActionShowLogin();
	void doActionLock();
	void doActionInfoApp();
	void doToolButtonSkin();
	void doToolButtonClose();
	void doPushButtonContact();
	void doPushButtonGroup();
	void doPushButtonZone();
	void doPushButtonBlog();
	void doPushButtonLast();
	void doToolButtonAppManager();
	void doToolButtonSignature();
	void doEditingFinishedSign();
	void doInterToolMove(int index,bool up);
	void doInterToolVisibleChanged(int index,bool visible);
	void doMainTabVisibleChanged(int index,bool visible);
	void doCustomContextMenuRequestedInterManager(const QPoint & pos );
protected:
	static WorkStation *mWorkStation;
private:	
	Ui::WorkStation *ui;		
	Ims::ImsState		 mUserState;
	UiWeatherInfo		 *mWeatherInfo;
	UiLoginScreen		 *mLoginScreen;
	QSystemTrayIcon		 *mSystemTrayIcon;
	UiInterfaceManager	 *mInterfaceManager;
	UiApplicationManager *mApplicationManager;
};

#endif // WORKSTATION_H
