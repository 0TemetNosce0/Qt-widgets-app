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
#ifndef __QMAIN_WINDOW_EXAMPLE_H__
#define __QMAIN_WINDOW_EXAMPLE_H__

#include <QMainWindow>
#include <QWidget>
#include "QDesktopWindowDocker.h"
#include <stdexcept>

class QEvent;

/*
 * \class QMainWindowExample 
 * Represents sample usage of QDesktopWindowDocker with QMainWindow. 
 * Add QDesktopWindowDocker as member of QMainWindow and initialize it
 * properly. Next connect to edgeReached signal and prepare slot. 
 *
 * This example presents case when window should be hidden by default, but
 * when edgeReached signal is emited it should be shown.
 */
class QMainWindowExample : public QMainWindow 
{
	Q_OBJECT

	public:
		/*
		 * simple ctor.
		 * @throw bad_alloc, when unable to allocate memory for docker.
		 */
		QMainWindowExample( QWidget *parent = 0 ) throw (std::bad_alloc);

		/*
		 * simple dtor.
		 */
		~QMainWindowExample();

	private:
		QDesktopWindowDocker *m_pWindowDocker;		/**< window docker made member of this class. */

	protected:
		/*
		 * Mouse leave event.
		 */
		void leaveEvent( QEvent *pEvent );

	private slots:

		/*
		 * Slot for unhiding window when edge is reached.
		 */
		void QMainWindowDockerSlot( const int &rDesktopDockType );
};

#endif /* __QMAIN_WINDOW_EXAMPLE_H__ */

