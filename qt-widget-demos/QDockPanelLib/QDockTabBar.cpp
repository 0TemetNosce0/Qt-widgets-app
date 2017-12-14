#include "QDockTabBar.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QCursor>

QDockTabBar::QDockTabBar(QWidget *parent)
	:QTabBar(parent), isLButtonDown_(false),
	sendDragOut_(false), insertPos_(-1)
{
	setAcceptDrops(true);
}

QDockTabBar::~QDockTabBar()
{

}



void QDockTabBar::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		isLButtonDown_ = true;
		sendDragOut_ = false;
	}
	QTabBar::mousePressEvent(e);
}

void QDockTabBar::mouseReleaseEvent(QMouseEvent *e)
{
	isLButtonDown_ = false;
	QTabBar::mouseReleaseEvent(e);
	if (insertPos_ >= 0)
	{
		moveTab(currentIndex(), insertPos_);
	}

	insertPos_ = -1;
	repaint();
}

void QDockTabBar::mouseMoveEvent(QMouseEvent *e)
{
	QTabBar::mouseMoveEvent(e);
	if (!isLButtonDown_)
	{
		return;
	}

	if (!rect().contains(e->pos()))
	{
		insertPos_ = -1;
		if (!sendDragOut_)
		{
			emit dragTabOut(currentIndex());
			sendDragOut_ = true;
		}
		return;
	}

	insertPos_ = tabAt(e->pos());
	repaint();
}

void QDockTabBar::paintEvent(QPaintEvent * e)
{
	QTabBar::paintEvent(e);

	QPainter p(this);
	QRect rc = tabRect(insertPos_);
	rc.moveCenter(QPoint(rc.left(), rc.center().y()));

	p.setBrush(QBrush(QColor(0, 0, 255, 100)));
	p.setPen(QPen(Qt::blue));
	p.drawRect(rc);
}


void QDockTabBar::dragEnter()
{
	//？？？
}

void QDockTabBar::dragLeave()
{
	insertPos_ = -1;
	repaint();
}

void QDockTabBar::dragMove(const QPoint& pos)
{
	//FIXME:无法插入到最后一个tab的后面
	insertPos_ = tabAt(mapFromGlobal(pos));
	repaint();
}

void QDockTabBar::drop(QWidget* from, QPoint pos)
{
	//TODO:在指定位置插入panel
}
