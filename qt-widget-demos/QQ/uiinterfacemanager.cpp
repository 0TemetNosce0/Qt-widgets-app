#include "uiinterfacemanager.h"
#include "ui_uiinterfacemanager.h"

#include <QCheckBox>

UiInterfaceManager::UiInterfaceManager(QWidget *parent)
	: UiImsBaseDialog(parent)
{
	ui = new Ui::UiInterfaceManager();
	ui->setupUi(this);	
	createTitleBar(ui->widgetTitle,WindowToolIcon | WindowToolClose,"更改外观");	
	mBroudGroundWidget = this;	
	mBroudGroundPixmap = new QPixmap(CImsResource::mainAppBackground());

	ui->tableWidgetInter->setColumnWidth(0,30);
	ui->tableWidgetInter->setColumnWidth(1,30);
	ui->tableWidgetMainTab->setColumnWidth(0,30);
	ui->tableWidgetMainTab->setColumnWidth(1,30);
	
	int i = 0 ;
	for ( i = 0 ; i < ui->tableWidgetInter->rowCount() ; i++)
	{
		ui->tableWidgetInter->setRowHeight(i,30);
		ui->tableWidgetInter->item(i,1)->setData(Qt::UserRole,i+1);
	}
	for (int i = 0 ; i < ui->tableWidgetMainTab->rowCount() ; i++)
	{
		ui->tableWidgetMainTab->setRowHeight(i,30);
		ui->tableWidgetMainTab->item(i,1)->setData(Qt::UserRole,i+1);
	}

	connect(ui->pushButtonSkin,		SIGNAL(clicked()),this,SLOT(doPushButtonSkin()));
	connect(ui->pushButtonInter,	SIGNAL(clicked()),this,SLOT(doPushButtonInter()));
	connect(ui->pushButtonCover,	SIGNAL(clicked()),this,SLOT(doPushButtonCover()));
	connect(ui->pushButtonClassic,	SIGNAL(clicked()),this,SLOT(doPushButtonClassic()));
	connect(ui->pushButtonMoveUp,	SIGNAL(clicked()),this,SLOT(doPushButtonMoveUp()));
	connect(ui->pushButtonMoveDown,	SIGNAL(clicked()),this,SLOT(doPushButtonMoveDown()));
	connect(ui->tableWidgetInter,	SIGNAL(itemSelectionChanged()),this,SLOT(doInterItemSelectionChanged()));
	connect(ui->tableWidgetInter,	SIGNAL(itemChanged(QTableWidgetItem *)),
		this,SLOT(doInteritemChanged(QTableWidgetItem *)));
	connect(ui->tableWidgetMainTab,	SIGNAL(itemChanged(QTableWidgetItem *)),
		this,SLOT(doMainTabitemChanged(QTableWidgetItem *)));
	ui->tableWidgetInter->setCurrentItem(ui->tableWidgetInter->item(0,0));
	doInterItemSelectionChanged();
}

UiInterfaceManager::~UiInterfaceManager()
{
	delete ui;
}

void UiInterfaceManager::showSkin()
{
	doPushButtonSkin();
	ui->pushButtonSkin->setChecked(true);	
	show();
}

void UiInterfaceManager::showInterManager()
{
	doPushButtonInter();
	ui->pushButtonInter->setChecked(true);
	show();
}

void UiInterfaceManager::doPushButtonSkin()
{	
	ui->tabWidgetIterFace->setCurrentWidget(ui->tabSkin);	
	ui->toolButton->setVisible(true);
	ui->pushButtonSkinSuit->setVisible(true);
	ui->pushButtonMoreSkin->setVisible(true);	
}

void UiInterfaceManager::doPushButtonInter()
{
	ui->toolButton->setVisible(false);
	ui->tabWidgetIterFace->setCurrentWidget(ui->tabInter);
	ui->pushButtonSkinSuit->setVisible(false);
	ui->pushButtonMoreSkin->setVisible(false);	
}

void UiInterfaceManager::doPushButtonClassic()
{
	ui->labelSkinPreview->setPixmap(CImsResource::interfaceClassic());
}

void UiInterfaceManager::doPushButtonCover()
{
	ui->labelSkinPreview->setPixmap(CImsResource::interfaceCover());
}

void UiInterfaceManager::doPushButtonMoveUp()
{
	int nRow = ui->tableWidgetInter->currentRow();
	int nRowCount = ui->tableWidgetInter->rowCount() - 1;
	if (nRow <= 0  || nRow == nRowCount)
		return;
	QTableWidgetItem *item = ui->tableWidgetInter->item(nRow,1);
	int nIndex = item->data(Qt::UserRole).toInt();
	emit interToolMove(nIndex,true);
}

void UiInterfaceManager::doPushButtonMoveDown()
{
	int nRow = ui->tableWidgetInter->currentRow();
	int nRowCount = ui->tableWidgetInter->rowCount() - 1;
	if (nRow == -1 || nRow >= nRowCount-1)
		return;
	QTableWidgetItem *item = ui->tableWidgetInter->item(nRow,1);
	int nIndex = item->data(Qt::UserRole).toInt();
	emit interToolMove(nIndex,false);
}

void UiInterfaceManager::doInterItemSelectionChanged()
{		
	int nRow = ui->tableWidgetInter->currentRow();
	int nRowCount = ui->tableWidgetInter->rowCount() - 1;

	ui->pushButtonMoveUp->setEnabled(!(nRow == 0 || nRow == nRowCount));
	ui->pushButtonMoveDown->setEnabled(nRow < nRowCount - 1);
}

void UiInterfaceManager::doInteritemChanged( QTableWidgetItem * item )
{
	if(item->column() == 1)
	{
		int nIndex = item->data(Qt::UserRole).toInt();
		emit interToolVisibleChanged(nIndex,(item->checkState() == Qt::Checked));
	}
}

void UiInterfaceManager::doMainTabitemChanged( QTableWidgetItem * item )
{
	if(item->column() == 1)
	{
		int nIndex = item->data(Qt::UserRole).toInt();
		emit mainTabVisibleChanged(nIndex,(item->checkState() == Qt::Checked));
	}
}
