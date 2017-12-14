#include "workstation.h"
#include "ui_workstation.h"
#include "uiweatherinfo.h"
#include "uiinterfacemanager.h"
#include "uiapplicationmanager.h"

#include <QMenu>
#include <QtCore/QFile>
#include <QtCore/QEvent>
#include <QtCore/QDebug>
#include <QActionGroup>

#define SIGNATURE "�༭����ǩ��"

WorkStation *WorkStation::mWorkStation = NULL;

WorkStation::WorkStation(QWidget *parent)
    : UiImsBaseDialog(parent)
{	
	ui = new Ui::WorkStation();
	ui->setupUi(this);

	mWorkStation		= this;	
	mLoginScreen		= NULL;
	mWeatherInfo		= NULL;
	mSystemTrayIcon		= NULL;
	mInterfaceManager	= NULL;	
	mApplicationManager	= NULL;
	
	ui->lineEditSignature->setLabelPic(CImsResource::iconSignatureEdit());
	ui->lineEditSignature->setVisible(false);

	createStyleSheet();
	mBroudGroundWidget = this;
	mBroudGroundPixmap = new QPixmap(CImsResource::mainAppBackground());

	createTitleBar(ui->widgetTitle,WindowToolSkin | WindowToolMin | WindowToolClose,"QQ2013");

	ui->labelPixmap->setScaledContents(true);
	ui->labelPixmap->setFrameShape(QFrame::StyledPanel);
	ui->labelPixmap->setPixmap(QPixmap(CImsResource::userHeadImage()));	
	ui->lineEditSearch->setLabelPic(CImsResource::icomSearchEdit());
	
	ui->labelPixmap->installEventFilter(this);
	ui->labelWeather->installEventFilter(this);
	ui->labelSignature->installEventFilter(this);
	ui->toolButtonMainMenu->installEventFilter(this);

	mUserState = Ims::StateOffline;	
	mLoginScreen = NULL;
	mSystemTrayIcon = NULL;	

	createSystemTrayIcon();

	connect(ui->widgetUserInfoApp,SIGNAL(customContextMenuRequested(const QPoint & )),
		this,SLOT(doCustomContextMenuRequestedInterManager(const QPoint &)));
	connect(ui->pushButtonContact,	SIGNAL(clicked()),this,SLOT(doPushButtonContact()));
	connect(ui->pushButtonGroup,	SIGNAL(clicked()),this,SLOT(doPushButtonGroup()));
	connect(ui->pushButtonZone,		SIGNAL(clicked()),this,SLOT(doPushButtonZone()));
	connect(ui->pushButtonBlog,		SIGNAL(clicked()),this,SLOT(doPushButtonBlog()));
	connect(ui->pushButtonLast,		SIGNAL(clicked()),this,SLOT(doPushButtonLast()));
	connect(ui->lineEditSignature,SIGNAL(editingFinished()),this,SLOT(doEditingFinishedSign()));
}

WorkStation::~WorkStation()
{
	if (mWeatherInfo)
    {
        delete mWeatherInfo;
    }
    mWeatherInfo = NULL;

	if (mSystemTrayIcon)
    {
        delete mSystemTrayIcon;
    }
    mSystemTrayIcon = NULL;

	if (mLoginScreen)
    {
        delete mLoginScreen;
    }
    mLoginScreen = NULL;

	if (mInterfaceManager)
    {
        delete mInterfaceManager;
    }
    mInterfaceManager = NULL;

	if (mApplicationManager)
    {
        delete mApplicationManager;
    }
    mApplicationManager = NULL;

	delete ui;	
}

bool WorkStation::eventFilter(QObject *object, QEvent *event)
{
	if (object == ui->labelWeather)
	{
		if (event->type() == QEvent::Enter)
		{
			if (mWeatherInfo == NULL)
            {
                createWeather();
            }
            QPoint pos = this->pos();

			if (pos.x() > mWeatherInfo->width())
            {
                mWeatherInfo->move(pos.x() - mWeatherInfo->width(),pos.y());
            }
            else
            {
                mWeatherInfo->move(pos.x() + this->width(),pos.y());
            }
            mWeatherInfo->show();
		}
		else if (event->type() == QEvent::Leave)
		{
			if (mWeatherInfo)
            {
                mWeatherInfo->hideWeatherWidget();
            }
        }
	}
	else if (object == ui->labelSignature)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			doToolButtonSignature();
		}
	}
	else if (object == ui->toolButtonMainMenu)
	{
		if (event->type() == QEvent::Enter)
        {
            ui->toolButtonMainMenu->setIcon(CImsResource::iconMainMenuEnter());
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->toolButtonMainMenu->setIcon(CImsResource::iconMainMenuLeave());
        }
    }

	return UiImsBaseDialog::eventFilter(object,event);
}

void WorkStation::createStyleSheet()
{
	QFile file(":/qss/Resources/theme.css");

	if (file.open(QIODevice::ReadOnly))
	{
		qApp->setStyleSheet(file.readAll());
	}

	file.close();
}

void WorkStation::createUserStateMenu()
{
	QMenu *pStateMenu = ui->toolButtonState->menu();
	if (pStateMenu == NULL)
	{
		pStateMenu = new QMenu(ui->toolButtonState);
		ui->toolButtonState->setMenu(pStateMenu);
	}
	pStateMenu->clear();
	addStateAction(pStateMenu);
    pStateMenu->addAction(QStringLiteral("ϵͳ����..."));
    pStateMenu->addAction(QStringLiteral("�ҵ�����..."));
    pStateMenu->addAction(QStringLiteral("�ҵ�QQ����"));
	ui->toolButtonState->setIcon(CImsResource::stateIconByCode(mUserState));
}

void WorkStation::createSystemTrayIcon()
{
	QMenu *trayIconMenu = new QMenu(this);	

	if (mLoginScreen && mLoginScreen->isLogin())
    {
        addStateAction(trayIconMenu);
    }
    trayIconMenu->addAction(QStringLiteral("��������"),this,SLOT(doActionShowLogin()));
	trayIconMenu->addSeparator();
    trayIconMenu->addAction(QStringLiteral("�˳�"),qApp, SLOT(quit()));

	if (mSystemTrayIcon == NULL)
	{
		mSystemTrayIcon = new QSystemTrayIcon(this);
		connect(mSystemTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
			this,SLOT(doTrayIconActivated(QSystemTrayIcon::ActivationReason)));
	}
	mSystemTrayIcon->setContextMenu(trayIconMenu);
	changeSystemTrayIcon();
	mSystemTrayIcon->setVisible(true);
}

int WorkStation::createLoginScreen()
{
	hide();
	if (mLoginScreen == NULL)
		mLoginScreen = new UiLoginScreen;
	return mLoginScreen->exec();
}

void WorkStation::createShowScreen()
{
	mUserState = (Ims::ImsState)mLoginScreen->loginState();
	createUserStateMenu();
	createSystemTrayIcon();
	createWeather();
	doActionShowLogin();
}

void WorkStation::createInterFaceManager()
{
	if (mInterfaceManager)
		return;

	mInterfaceManager = new UiInterfaceManager(this);
	connect(mInterfaceManager,SIGNAL(interToolMove(int,bool)),
		this,SLOT(doInterToolMove(int,bool)));
	connect(mInterfaceManager,SIGNAL(interToolVisibleChanged(int,bool)),
		this,SLOT(doInterToolVisibleChanged(int,bool)));
	connect(mInterfaceManager,SIGNAL(mainTabVisibleChanged(int,bool)),
		this,SLOT(doMainTabVisibleChanged(int,bool)));
}

void WorkStation::createWeather()
{
	if (mWeatherInfo == NULL)
		mWeatherInfo = new UiWeatherInfo(this);
	mWeatherInfo->createWeatherInfo();
	mWeatherInfo->hide();
}

void WorkStation::changeUserStateIcon()
{	
	ui->toolButtonState->setIcon(CImsResource::stateIconByCode(mUserState));	
}

void WorkStation::changeSystemTrayIcon()
{
	QIcon icon = CImsResource::trayIconByCode(mUserState);
	icon.actualSize(QSize(32,32));
	mSystemTrayIcon->setIcon(icon);
}

void WorkStation::addStateAction(QMenu *menu)
{
	if (menu == NULL)
		return;
	QAction *action = NULL;
	QStringList list;
    list<<QStringLiteral("����")<<QStringLiteral("Q�Ұ�")<<QStringLiteral("�뿪")<<QStringLiteral("æµ")
        <<QStringLiteral("�������")<<QStringLiteral("����")<<QStringLiteral("����");
	for (unsigned int i = 1 ; i <= 7 ; i++)
	{
		action = menu->addAction(CImsResource::stateIconByCode((Ims::ImsState)i),
			list.at(i-1),this, SLOT(doActionChangeState()));
		action->setData(i);		
	}
    menu->addAction(QStringLiteral("���״̬��Ϣ"));
	menu->addSeparator();
    menu->addAction(QStringLiteral("�ر���������"));
    menu->addAction(QStringLiteral("�ر�ͷ������(������)"));
	menu->addSeparator();
    action = menu->addAction(QStringLiteral("����QQ   Ctrl+Alt+L"),this,SLOT(doActionLock()));
	menu->addSeparator();
}

void WorkStation::doActionShowLogin()
{
	QWidget *widet = this;
	if (!mLoginScreen || !mLoginScreen->isLogin())
		widet = mLoginScreen;	
	widet->showNormal();
	widet->raise();
}

void WorkStation::doActionChangeState()
{
	QAction *action = (QAction *)sender();
	uint nState = action->data().toUInt();
	if ((Ims::ImsState)nState == mUserState)
		return;
	mUserState = (Ims::ImsState)nState;
	changeUserStateIcon();
	changeSystemTrayIcon();
}

void WorkStation::doTrayIconActivated( QSystemTrayIcon::ActivationReason reason )
{
	QMenu *pSystemTrayIconMenu =  mSystemTrayIcon->contextMenu();
	if(pSystemTrayIconMenu)
	{
		pSystemTrayIconMenu->exec(QCursor::pos());
		pSystemTrayIconMenu->raise();
	}
}

void WorkStation::doToolButtonSkin()
{
	createInterFaceManager();
	mInterfaceManager->showSkin();
}

void WorkStation::doToolButtonClose()
{
	qApp->quit();
}

void WorkStation::doActionInfoApp()
{
	createInterFaceManager();
	mInterfaceManager->showInterManager();
}

void WorkStation::doToolButtonAppManager()
{
	if (mApplicationManager == NULL)
		mApplicationManager = new UiApplicationManager;
	mApplicationManager->show();
}

void WorkStation::doToolButtonSignature()
{
	QString sSignature = ui->labelSignature->text();
	if (sSignature != SIGNATURE)
		ui->lineEditSignature->setText(sSignature);
	ui->labelSignature->setVisible(false);
	ui->lineEditSignature->setVisible(true);
}

void WorkStation::doEditingFinishedSign()
{
	QString sSignature = ui->lineEditSignature->text();
	if (sSignature.isEmpty())
		sSignature = SIGNATURE;
	ui->labelSignature->setText(sSignature);
	ui->labelSignature->setVisible(true);
	ui->lineEditSignature->setVisible(false);
}

void WorkStation::doCustomContextMenuRequestedInterManager( const QPoint & pos )
{
	QMenu menu;
    menu.addAction(QIcon(CImsResource::iconInterManager()),QStringLiteral("�򿪽��������"),this,SLOT(doActionInfoApp()));
	menu.exec(QCursor::pos());
}

void WorkStation::setCurrentWeather(QPixmap &pix)
{
	ui->labelWeather->setPixmap(pix);
}

void WorkStation::doActionLock()
{

}

void WorkStation::doPushButtonContact()
{	
	ui->tabWidgetMain->setCurrentWidget(ui->tabContact);

	ui->pushButtonLast->setMenu(NULL);
	ui->pushButtonGroup->setMenu(NULL);
	ui->pushButtonContact->setMenu(new QMenu(ui->pushButtonContact));
	QMenu *pMenu = ui->pushButtonContact->menu();

	QAction *pAction = NULL;
	QActionGroup *pActionGroup = NULL;	
    QMenu *pChildMenu = pMenu->addMenu(QIcon(CImsResource::menuContactHeadIcon()),QStringLiteral("ͷ����ʾ"));
	pActionGroup = new QActionGroup(NULL);
    pAction = pChildMenu->addAction(QStringLiteral("��ͷ��"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);
	pAction->setChecked(true);
    pChildMenu->addAction(QStringLiteral("Сͷ��"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);
	pChildMenu->addSeparator();
    pChildMenu->addAction(QStringLiteral("ѡ��ʱ��ʾ��ͷ��"))->setEnabled(false);
	pChildMenu->addSeparator();
    pChildMenu->addAction(QStringLiteral("��ʾ�ҵ�ͷ��"))->setCheckable(true);

    pChildMenu = pMenu->addMenu(QStringLiteral("������ʾ"));
	pActionGroup = new QActionGroup(NULL);
    pAction = pChildMenu->addAction(QStringLiteral("��ʾ��ע���ǳ�"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);
	pAction->setChecked(true);
    pAction = pChildMenu->addAction(QStringLiteral("��ʾ��ע"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);
    pAction = pChildMenu->addAction(QStringLiteral("��ʾ�ǳ�"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);

    pChildMenu = pMenu->addMenu(QStringLiteral("�б���ʾ"));
	pActionGroup = new QActionGroup(NULL);
    pAction = pChildMenu->addAction(QStringLiteral("������ʾ"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);
	pAction->setChecked(true);
    pAction = pChildMenu->addAction(QStringLiteral("����ƽ��"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);
	pChildMenu->addSeparator();
    pChildMenu->addAction(QStringLiteral("��ʾ��ˬ����"))->setEnabled(true);
	pChildMenu->addSeparator();
    pChildMenu->addAction(QStringLiteral("����Ч��"))->setCheckable(true);

	pMenu->addSeparator();
    pChildMenu = pMenu->addMenu(QStringLiteral("������ʾ"));
	pActionGroup = new QActionGroup(NULL);
    pAction = pChildMenu->addAction(QStringLiteral("����ݱ�ʶ����"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);
	pAction->setChecked(true);
    pAction = pChildMenu->addAction(QStringLiteral("�������������"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);
    pChildMenu->addAction(QStringLiteral("����������"));
	pAction = pActionGroup->addAction(pAction);
	pAction->setCheckable(true);

    pMenu->addAction(QStringLiteral("ˢ�º����б�"));
	pMenu->addSeparator();
    pMenu->addAction(QStringLiteral("��ʾ������ϵ��"));
	pMenu->addSeparator();
    pMenu->addAction(QStringLiteral("��ʾ��ҵ����"));
    pMenu->addAction(QStringLiteral("��ʾİ���˷���"))->setCheckable(true);
    pMenu->addAction(QStringLiteral("��ʾ������"))->setCheckable(true);
}

void WorkStation::doPushButtonGroup()
{
	ui->tabWidgetMain->setCurrentWidget(ui->tabGroup);

	ui->pushButtonLast->setMenu(NULL);
	ui->pushButtonContact->setMenu(NULL);		
	ui->pushButtonGroup->setMenu(new QMenu(ui->pushButtonGroup));	
	QMenu *pMenu = ui->pushButtonGroup->menu();

	QAction *pAction = NULL;
	QActionGroup *pActionGroup = NULL;
    QMenu *pChildMenu = pMenu->addMenu(QIcon(CImsResource::menuContactHeadIcon()),QStringLiteral("ͼ��"));
	pActionGroup = new QActionGroup(NULL);
    pAction = pChildMenu->addAction(QStringLiteral("��ͼ��"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);
	pAction->setChecked(true);
    pAction = pChildMenu->addAction(QStringLiteral("Сͼ��"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);
	pChildMenu->addSeparator();
    pChildMenu->addAction(QStringLiteral("ѡ��ʱ��ʾ��ͼ��"))->setEnabled(true);

    pChildMenu = pMenu->addMenu(QStringLiteral("�б���ʾ"));
	pActionGroup = new QActionGroup(NULL);
    pAction = pChildMenu->addAction(QStringLiteral("������ʾ"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);
	pAction->setChecked(true);
    pChildMenu->addAction(QStringLiteral("����ƽ��"));
	pActionGroup->addAction(pAction);
	pAction->setCheckable(true);

	pMenu->addSeparator();
    pMenu->addAction(QIcon(CImsResource::menuGroupIcon()),QStringLiteral("�����ҵ�Ⱥ��ҳ"));
    pChildMenu = pMenu->addMenu(QStringLiteral("����Ⱥ��Ϣ����"));
    pChildMenu->addAction(QStringLiteral("���ղ���ʾ��Ϣ"));
    pChildMenu->addAction(QStringLiteral("����ʾ��Ϣֻ��ʾ��Ŀ"));
    pChildMenu = pChildMenu->addMenu(QStringLiteral("����Ⱥ��Ϣ��ʾ"));
    pChildMenu->addAction(QStringLiteral("15������ʾһ��"));
    pChildMenu->addAction(QStringLiteral("30������ʾһ��"));
    pChildMenu->addAction(QStringLiteral("1Сʱ��ʾһ��"));
    pChildMenu->addAction(QStringLiteral("4Сʱ��ʾһ��"));
	pChildMenu->addSeparator();
	pChildMenu->addAction("ʼ�ղ���ʾ");

	pMenu->addSeparator();
    pMenu->addAction(QStringLiteral("�������Ⱥ"));
    pMenu->addAction(QStringLiteral("����һ��Ⱥ"));
	pMenu->addSeparator();
    pMenu->addAction(QStringLiteral("���Ⱥ����"));
}

void WorkStation::doPushButtonZone()
{
	ui->tabWidgetMain->setCurrentWidget(ui->tabZone);

	ui->pushButtonLast->setMenu(NULL);
	ui->pushButtonGroup->setMenu(NULL);	
	ui->pushButtonContact->setMenu(NULL);
}

void WorkStation::doPushButtonBlog()
{
	ui->tabWidgetMain->setCurrentWidget(ui->tabBlog);

	ui->pushButtonLast->setMenu(NULL);
	ui->pushButtonGroup->setMenu(NULL);	
	ui->pushButtonContact->setMenu(NULL);
}

void WorkStation::doPushButtonLast()
{
	ui->tabWidgetMain->setCurrentWidget(ui->tabLast);

	ui->pushButtonGroup->setMenu(NULL);	
	ui->pushButtonContact->setMenu(NULL);
	ui->pushButtonLast->setMenu(new QMenu(ui->pushButtonLast));
	QMenu *pMenu = ui->pushButtonLast->menu();
	pMenu->addAction("��ջỰ�б�");
}

void WorkStation::doInterToolMove(int index,bool up)
{
	QToolButton *pToolButton = userInfoAppToolButton(index);
	QHBoxLayout *layout = (QHBoxLayout *)ui->widgetUserInfoApp->layout();
	if (layout == NULL || pToolButton == NULL)
		return;
	int nCount = layout->count();
	index = layout->indexOf(pToolButton);
	if (index == -1)
		return;
	layout->removeWidget(pToolButton);
	if (up && index > 0)
		layout->insertWidget(index-1,pToolButton);
	else if (!up && index < nCount - 1)
		layout->insertWidget(index+1,pToolButton);
}

void WorkStation::doInterToolVisibleChanged(int index,bool visible)
{
	QToolButton *pToolButton = userInfoAppToolButton(index);
	if (pToolButton)
		pToolButton->setVisible(visible);
}

void WorkStation::doMainTabVisibleChanged(int index,bool visible)
{
	switch(index)
	{
	case MainTabContact://	= 1,//����
	case MainTabGroup://	= 2,//Ⱥ/������
	case MainTabLast://		= 3,//��ʷ�Ự��¼
		break;	
	case MainTabBlog://		= 4,//΢��
		ui->pushButtonBlog->setVisible(visible);
		if (ui->tabWidgetMain->currentWidget() == ui->tabBlog)
			doPushButtonContact();
		break;
	case MainTabZone://		= 5,//�ռ�-�ر����
		ui->pushButtonZone->setVisible(visible);
		if (ui->tabWidgetMain->currentWidget() == ui->tabZone)
			doPushButtonContact();
		break;
	case MainTabWeather://	= 6,//����
		ui->labelWeather->setVisible(visible);
		break;
	}
}

QToolButton * WorkStation::userInfoAppToolButton(int index)
{
	switch(index)
	{
	case InterToolZone://		= 1,//�ռ�
		return ui->toolButtonZone;
	case InterToolBlog://		= 2,//΢��
		return ui->toolButtonBlog;
	case InterToolMail://		= 3,//����
		return ui->toolButtonMail;
	case InterToolFrined://		= 4,//������
		return ui->toolButtonFriend;
	case InterToolShopping://	= 5,//�ҵĹ���
		return ui->toolButtonShopping;
	case InterToolWallet://		= 6,//�ҵ�Ǯ��
		return ui->toolButtonWallet;
	case InterToolSoso://		= 7,//�������ʸ�������
		return ui->toolButtonSoso;
	case InterToolNews://		= 8,//�ҵ���Ѷ
		return ui->toolButtonNews;
	case InterToolQQVip://		= 9,//QQ��Ա��Ϣ����
		return ui->toolButtonQQVip;
	case InterToolArel://		= 10,//���������
		return ui->toolButtonManager;
	}
	return NULL;
}
