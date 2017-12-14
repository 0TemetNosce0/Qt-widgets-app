#include "imsimagelabel.h"
#include "imsresoursce.h"

#include <QMenu>
#include <QToolButton>

ImsImageLabel::ImsImageLabel( QWidget * parent /*= 0*/, Qt::WindowFlags f /*= 0 */ )
	:QLabel(parent,f)
{
	mToolButton = NULL;
	mCurrentState = Ims::StateOnline;
	init();
}

ImsImageLabel::ImsImageLabel( const QString & text, QWidget * parent /*= 0*/, Qt::WindowFlags f /*= 0 */ )
	:QLabel(text,parent,f)
{
	mToolButton = NULL;
	mCurrentState = Ims::StateOnline;
	init();
}

ImsImageLabel::~ImsImageLabel()
{
	if (mToolButton)
		delete mToolButton;
	mToolButton = NULL;
}

void ImsImageLabel::init()
{
	if(mToolButton == NULL)
	{
		mToolButton = new QToolButton(this);
		mToolButton->setObjectName("imageLabel");
		connect(mToolButton,SIGNAL(clicked()),this,SLOT(doToolButton()));
	}
	mToolButton->setAutoRaise(true);
	mToolButton->setGeometry(70,70,17,17);
	mToolButton->setIcon(CImsResource::stateIconByCode((Ims::ImsState)mCurrentState));

	mToolButton->show();
}

void ImsImageLabel::doToolButton()
{
	QMenu menu;	
    QAction *action = menu.addAction(CImsResource::stateIconByCode(Ims::StateOnline),QStringLiteral("我在线上"),
		this,SLOT(doActionState()));
	action->setData(Ims::StateOnline);

    action = menu.addAction(CImsResource::stateIconByCode(Ims::StateQMy),QStringLiteral("Q我吧"),
		this,SLOT(doActionState()));
	action->setData(Ims::StateQMy);

	menu.addSeparator();

    action = menu.addAction(CImsResource::stateIconByCode(Ims::StateLeave),QStringLiteral("离开"),
		this,SLOT(doActionState()));
	action->setData(Ims::StateLeave);

    action = menu.addAction(CImsResource::stateIconByCode(Ims::StateBusy),QStringLiteral("忙碌"),
		this,SLOT(doActionState()));
	action->setData(Ims::StateBusy);

    action = menu.addAction(CImsResource::stateIconByCode(Ims::StateNoDisturb),QStringLiteral("请勿打扰"),
		this,SLOT(doActionState()));
	action->setData(Ims::StateNoDisturb);

	menu.addSeparator();

    action = menu.addAction(CImsResource::stateIconByCode(Ims::StateStealth),QStringLiteral("隐身"),this,
		SLOT(doActionState()));
	action->setData(Ims::StateStealth);

	QPoint point = mapToGlobal(QPoint(mToolButton->pos().x(),mToolButton->pos().y()+13));
	menu.exec(point);
}

void ImsImageLabel::doActionState()
{
	QAction *action  = (QAction *)sender();
	mCurrentState = action->data().toUInt();
	mToolButton->setIcon(CImsResource::stateIconByCode((Ims::ImsState)mCurrentState));	
}
