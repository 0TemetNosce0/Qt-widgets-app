#include "uiloginscreen.h"
#include "ui_uiloginscreen.h"

UiLoginScreen::UiLoginScreen(QWidget *parent)
	:UiImsBaseDialog(parent)
{
	ui = new Ui::UiLoginScreen();
	ui->setupUi(this);	

	mLogin = false;
	mBroudGroundWidget = ui->widgetParam;
	mBroudGroundPixmap = new QPixmap(CImsResource::loginBackground());

	createTitleBar(ui->widgetTitle,WindowToolSet | WindowToolMin | WindowToolClose);

	ui->labelPixmap->setScaledContents(true);
	ui->labelPixmap->setFrameShape(QFrame::StyledPanel);
	ui->labelPixmap->setPixmap(QPixmap(CImsResource::userHeadImage()));	
	ui->widgetParam->setAutoFillBackground(true);

	ui->lineEditAccount->setLabelPic(":/WorkStation/Resources/theme/ChatFrame/btnright_normal.png");
	ui->lineEditPass->setLabelPic(CImsResource::icomPassWordEdit());
	connect(ui->pushButtonLogin,SIGNAL(clicked()),this,SLOT(doPushButtonLogin()));
}

UiLoginScreen::~UiLoginScreen()
{
	delete ui;
}

void UiLoginScreen::doToolButtonSet()
{

}

void UiLoginScreen::doToolButtonClose()
{
	qApp->quit();
}

void UiLoginScreen::doPushButtonLogin()
{
	mLogin = true;
	return done(QDialog::Accepted);
}

void UiLoginScreen::doImageClickedAccount()
{
	ui->lineEditAccount->setLabelPic(":/WorkStation/Resources/theme/ChatFrame/btnright_focus_down.png");
}

void UiLoginScreen::doImageClickedPassword()
{
	
}

quint32 UiLoginScreen::loginState()
{
	return ui->labelPixmap->currentState();
}
