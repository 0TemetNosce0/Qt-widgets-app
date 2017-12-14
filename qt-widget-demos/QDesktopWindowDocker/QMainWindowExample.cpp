/*
 *
 * Copyright (C) 2010 by Mateusz Wojcik <mewojcik@gmail.com>
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 */

#include "QMainWindowExample.h"
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QEvent>


/*
 * Ctor.
 */
QMainWindowExample::QMainWindowExample( QWidget *parent) throw (std::bad_alloc) : 	QMainWindow(parent),
																					m_pWindowDocker( 0 )
{
	this->resize(500,500);

	m_pWindowDocker = new QDesktopWindowDocker( this, TOP_RIGHT_CORNER );
	m_pWindowDocker->enable();

	this->hide();

	connect(m_pWindowDocker, SIGNAL( edgeReached( const int& ) ), this, SLOT( QMainWindowDockerSlot( const int & ) ) );
}

/*
 * Dtor.
 */
QMainWindowExample::~QMainWindowExample()
{
	delete m_pWindowDocker;
}

/*
 * Slot for edgeREached signal.
 */
void QMainWindowExample::QMainWindowDockerSlot( const int &rDesktopDockType )
{
	
	qDebug() << "Got edgeReached slot, edge: " << rDesktopDockType;
	QRect screenRect =	QApplication::desktop()->availableGeometry();

	//TOP_RIGHT_CORNER
	this->move( screenRect.topRight().x() - this->width(), screenRect.topRight().y() );
	
	//BOTTOM_RIGHT_CORNER
	//this->move( screenRect.topRight().x() - this->width(), screenRect.bottomRight().y() - this->height() );

	//TOP_LEFT_CORNER
	//this->move( screenRect.topLeft().x(), screenRect.topLeft().y() );
	
	//BOTTOM_LEFT_CORNER
	//this->move( screenRect.topLeft().x(), screenRect.bottomLeft().y() - this->height() );

	//CENTER_TOP
	//this->move( screenRect.width()/2 - this->width()/2, 0 );

	//CENTER_BOTTOM
	//this->move( screenRect.width()/2 - this->width()/2, screenRect.height() - this->height() );

	this->show();
}

/*
 * Leave event.
 */
void QMainWindowExample::leaveEvent( QEvent *pEvent )
{
	this->hide();
}

