#include "QDockSideBar.h"
#include <QChildEvent>

QDockSideBar::QDockSideBar(QWidget *parent)
	: QToolBar(parent)
{

}

QDockSideBar::~QDockSideBar()
{

}

void QDockSideBar::childEvent(QChildEvent *e)
{
	//һ��buttonҪ���Ƴ��ˣ��Ƴ�֮��actions�������Ż����
	if (e->removed() && actions().size() ==1)
	{
		hide();
	}
}
