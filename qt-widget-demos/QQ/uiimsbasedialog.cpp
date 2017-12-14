#include "uiimsbasedialog.h"

#include <QStyle>
#include <QMouseEvent>
#include <QApplication>

UiImsBaseDialog::UiImsBaseDialog(QWidget *parent)
	: QDialog(parent)
{
	mMoveing			= false;
	mLabelIcon			= NULL;
	mLabelTitle			= NULL;	
	mToolButtonClose	= NULL;
	mToolButtonMax		= NULL;
	mToolButtonMin		= NULL;
	mToolButtonNor		= NULL;
	mToolButtonSkin		= NULL;
	mToolButtonSet		= NULL;
	mBroudGroundPixmap	= NULL;
	mBroudGroundWidget	= NULL;
	mMovePosition		= QPoint(0,0);
	setFocusPolicy(Qt::ClickFocus);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool );
}

UiImsBaseDialog::~UiImsBaseDialog()
{
	if (mBroudGroundPixmap)
		delete mBroudGroundPixmap;
	mBroudGroundPixmap = NULL;

	if (mLabelIcon)
		delete mLabelIcon;
	mLabelIcon = NULL;

	if (mLabelTitle)
		delete mLabelTitle;
	mLabelTitle = NULL;

	if (mToolButtonClose)
		delete mToolButtonClose;
	mToolButtonClose = NULL;

	if (mToolButtonMax)
		delete mToolButtonMax;
	mToolButtonMax = NULL;

	if (mToolButtonMin)
		delete mToolButtonMin;
	mToolButtonMin = NULL;

	if (mToolButtonNor)
		delete mToolButtonNor;
	mToolButtonNor = NULL;

	if (mToolButtonSkin)
		delete mToolButtonSkin;
	mToolButtonSkin = NULL;

	if (mToolButtonSet)
		delete mToolButtonSet;
	mToolButtonSet = NULL;
}

void UiImsBaseDialog::resizeEvent( QResizeEvent *event )
{
	if (mBroudGroundWidget && mBroudGroundPixmap)
	{
		QPalette palette(mBroudGroundWidget->palette());
		palette.setBrush(QPalette::Window,QBrush(mBroudGroundPixmap->scaled(mBroudGroundWidget->size(),
																			Qt::IgnoreAspectRatio,
																			Qt::SmoothTransformation)));
		mBroudGroundWidget->setPalette(palette);
	}	

	//ÉèÖÃÔ²½Ç¾ØÐÎ
	QPainterPath path;
	path.addRoundedRect(rect(),5,5);
	setMask(QRegion(path.toFillPolygon().toPolygon()));
	return QDialog::resizeEvent(event);
}

void UiImsBaseDialog::mousePressEvent( QMouseEvent *event )
{
	mMoveing = true;
	mMovePosition = event->globalPos() - pos();
	return QDialog::mousePressEvent(event);
}

void UiImsBaseDialog::mouseMoveEvent( QMouseEvent *event )
{
	if (mMoveing && (event->buttons() && Qt::LeftButton)
		&& (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance()) 
	{  
		move(event->globalPos()-mMovePosition);
		mMovePosition = event->globalPos() - pos();
	}
	return QDialog::mouseMoveEvent(event);
}

void UiImsBaseDialog::mouseReleaseEvent(QMouseEvent *event)
{
	mMoveing = false;
}

void UiImsBaseDialog::createTitleBar(QWidget *parent,uint flag,QString title /* = "" */)
{
	if (parent == NULL)
		return;
	parent->setMaximumHeight(20);
	parent->setMinimumHeight(20);
	QHBoxLayout *layout = new QHBoxLayout(parent);	

	if ((flag & WindowToolIcon) == WindowToolIcon)
	{
		mLabelIcon = new QLabel(parent);
		mLabelIcon->setPixmap(QPixmap(CImsResource::mainWindowIcon()).scaled(20,20));
		layout->addWidget(mLabelIcon);
	}

	if(!title.isEmpty())
	{
		mLabelTitle = new QLabel(title,parent);
		layout->addWidget(mLabelTitle);
	}	

	layout->addSpacerItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum));	

	if ((flag & WindowToolSet) == WindowToolSet)
	{
		mToolButtonSet = new QToolButton(parent);
		mToolButtonSet->setObjectName("toolButtonSet");
		mToolButtonSet->setAutoRaise(true);
		connect(mToolButtonSet,SIGNAL(clicked()),this,SLOT(doToolButtonSet()));
		layout->addWidget(mToolButtonSet);
	}	

	if ((flag & WindowToolSkin) == WindowToolSkin)
	{
		mToolButtonSkin = new QToolButton(parent);
		mToolButtonSkin->setObjectName("toolButtonSkin");
		mToolButtonSkin->setAutoRaise(true);
		connect(mToolButtonSkin,SIGNAL(clicked()),this,SLOT(doToolButtonSkin()));
		layout->addWidget(mToolButtonSkin);
	}	

	if ((flag & WindowToolMin) == WindowToolMin)
	{
		mToolButtonMin = new QToolButton(parent);
		mToolButtonMin->setObjectName("toolButtonMin");
		mToolButtonMin->setAutoRaise(true);
		connect(mToolButtonMin,SIGNAL(clicked()),this,SLOT(hide()));
		layout->addWidget(mToolButtonMin);
	}	

	if ((flag & WindowToolNor) == WindowToolNor)
	{
		mToolButtonNor = new QToolButton(parent);
		mToolButtonNor->setObjectName("toolButtonNor");
		mToolButtonNor->setAutoRaise(true);
		connect(mToolButtonNor,SIGNAL(clicked()),this,SLOT(doToolButtonNor()));
		layout->addWidget(mToolButtonNor);
	}	

	if ((flag & WindowToolMax) == WindowToolMax)
	{
		mToolButtonMax = new QToolButton(parent);
		mToolButtonMax->setObjectName("toolButtonMax");
		mToolButtonMax->setAutoRaise(true);
		connect(mToolButtonMax,SIGNAL(clicked()),this,SLOT(doToolButtonMax()));
		layout->addWidget(mToolButtonMax);
	}	

	if ((flag & WindowToolClose) == WindowToolClose)
	{
		mToolButtonClose = new QToolButton(parent);
		mToolButtonClose->setObjectName("toolButtonClose");
		mToolButtonClose->setAutoRaise(true);
		connect(mToolButtonClose,SIGNAL(clicked()),this,SLOT(doToolButtonClose()));
		layout->addWidget(mToolButtonClose);
	}	

	layout->setSpacing(0);
	layout->setContentsMargins(6,0,0,0);
	parent->setLayout(layout);
}

void UiImsBaseDialog::doToolButtonMax()
{
	mToolButtonMax->setVisible(false);
	mToolButtonNor->setVisible(true);
	showMaximized();
}

void UiImsBaseDialog::doToolButtonNor()
{
	mToolButtonMax->setVisible(true);
	mToolButtonNor->setVisible(false);
	showNormal();
}

void UiImsBaseDialog::doToolButtonClose()
{
	close();
}
