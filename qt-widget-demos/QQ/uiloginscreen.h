#ifndef UILOGINSCREEN_H
#define UILOGINSCREEN_H

#include "uiimsbasedialog.h"

namespace Ui {class UiLoginScreen;};

class UiLoginScreen : public UiImsBaseDialog
{
	Q_OBJECT

public:
	UiLoginScreen(QWidget *parent = 0);
	~UiLoginScreen();

	quint32 loginState();
	bool isLogin(){return mLogin;}
protected slots:
	void doToolButtonSet();
	void doToolButtonClose();
	void doPushButtonLogin();
	void doImageClickedAccount();
	void doImageClickedPassword();
private:
	bool mLogin;
	Ui::UiLoginScreen *ui;
};

#endif // UILOGINSCREEN_H
