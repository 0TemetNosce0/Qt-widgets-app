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
	//一个button要被移除了，移除之后actions的数量才会减少
	if (e->removed() && actions().size() ==1)
	{
		hide();
	}
}
