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
		MainTabContact	= 1,//����
		MainTabGroup	= 2,//Ⱥ/������
		MainTabLast		= 3,//��ʷ�Ự��¼
		MainTabBlog		= 4,//΢��
		MainTabZone		= 5,//�ռ�-�ر����		
		MainTabWeather	= 6,//����
	};
	enum ImsInterTool{
		InterToolZone		= 1,//�ռ�
		InterToolBlog		= 2,//΢��
		InterToolMail		= 3,//����
		InterToolFrined		= 4,//������
		InterToolShopping	= 5,//�ҵĹ���
		InterToolWallet		= 6,//�ҵ�Ǯ��
		InterToolSoso		= 7,//�������ʸ�������
		InterToolNews		= 8,//�ҵ���Ѷ
		InterToolQQVip		= 9,//QQ��Ա��Ϣ����
		InterToolArel		= 10,//���������
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
