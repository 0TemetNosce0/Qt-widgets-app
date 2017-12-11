#ifndef UIIMSBASEDIALOG_H
#define UIIMSBASEDIALOG_H

#include <QLabel>
#include <QPixmap>
#include <QDialog>
#include <QToolButton>
#include <QHBoxLayout>
#include "imsresoursce.h"

class UiImsBaseDialog : public QDialog
{
	Q_OBJECT

public:
	enum ImsWindowFlag{
		WindowToolClose		= 0x00000001,
		WindowToolMax		= 0x00000002,
		WindowToolMin		= 0x00000004,
		WindowToolNor		= 0x00000008,
		WindowToolSkin		= 0x00000010,
		WindowToolSet		= 0x00000020,
		WindowToolIcon		= 0x00000040,
	};

	enum ImsMainTab{
		MainTabContact	= 1,//好友
		MainTabGroup	= 2,//群/讨论组
		MainTabLast		= 3,//历史会话记录
		MainTabBlog		= 4,//微博
		MainTabZone		= 5,//空间-特别关心		
		MainTabWeather	= 6,//天气
	};
	enum ImsInterTool{
		InterToolZone		= 1,//空间
		InterToolBlog		= 2,//微博
		InterToolMail		= 3,//邮箱
		InterToolFrined		= 4,//朋友网
		InterToolShopping	= 5,//我的购物
		InterToolWallet		= 6,//我的钱包
		InterToolSoso		= 7,//搜搜问问个人中心
		InterToolNews		= 8,//我的资讯
		InterToolQQVip		= 9,//QQ会员信息中心
		InterToolArel		= 10,//界面管理器
	};
	UiImsBaseDialog(QWidget *parent = 0);
	~UiImsBaseDialog();

protected:
	virtual void createTitleBar(QWidget *parent,uint flag,QString title = "");
	virtual void resizeEvent(QResizeEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
protected slots:	
	virtual void doToolButtonMax();
	virtual void doToolButtonNor();
	virtual void doToolButtonClose();
	virtual void doToolButtonSet(){}
	virtual void doToolButtonSkin(){}
protected:
	bool		mMoveing;
	QPoint	    mMovePosition;
	QLabel		*mLabelIcon;
	QLabel		*mLabelTitle;
	QToolButton *mToolButtonClose;
	QToolButton *mToolButtonMax;
	QToolButton *mToolButtonMin;
	QToolButton *mToolButtonNor;
	QToolButton *mToolButtonSkin;
	QToolButton *mToolButtonSet;
	QPixmap		*mBroudGroundPixmap;
	QWidget		*mBroudGroundWidget;
};

#endif // UIIMSBASEDIALOG_H
