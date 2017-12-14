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

#include "QDesktopWindowDocker.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QEvent>


#include <QDebug>

/*
 * Sorry for that, Windows seems to be working somehow different then unixlike
 * machines. At the moment I've got no idea how to enforce on Windows proper
 * behaviour. If you will find solution, please let m know =).
 */
#ifdef Q_OS_WIN32
#include <qt_windows.h>
#endif


/*
 * Construction.
 */
QDesktopWindowDocker::QDesktopWindowDocker( QWidget *pToBeDocked, const DesktopDockType aDockType ) : 	m_aEnabled( true ),
    m_aDockType( aDockType ),
    m_pDockedObject( pToBeDocked )

{

    // [1] At first set properly window flag to make window transparent across
    // all platforms,
    this->setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint );

#ifdef Q_OS_WIN32

    // Again... sorry sorry sorry for this.
    this->setAttribute( Qt::WA_NoSystemBackground, true);

    // Set proper window style.
    HWND hWnd = (HWND)this->winId();
    long windowStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
    windowStyle |= WS_EX_TOOLWINDOW;
    windowStyle &= ~WS_EX_APPWINDOW;

    SetWindowLong(hWnd, GWL_EXSTYLE, windowStyle );
    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE ) | WS_EX_LAYERED );
    SetLayeredWindowAttributes(hWnd, 0, 1, LWA_ALPHA );

#else

    this->setAttribute	( Qt::WA_TranslucentBackground, true );
    this->setStyleSheet ( "background: transparent; border: 0px;" );

#endif

    // [2] Now set proper size depending on docking type and move docker
    // window to proper position.
    resizeAndMove();

    // [3] At this point we're ready to show transparent window.
    this->show();
}

/*
 * Destruction.
 */
QDesktopWindowDocker::~QDesktopWindowDocker()
{
}

/*
 * Calculates proper docker size depending on docking type.
 */
void QDesktopWindowDocker::resizeAndMove()
{

    // [1] Get screen geometry.
    QRect screenRect = QApplication::desktop()->availableGeometry();


    if ( 0 != ( m_aDockType & DOCKING_TYPE_NON_CENTER_MASK ) )
    {
        // Covers following cases:
        // 1. TOP_RIGHT_CORNER
        // 2. BOTTOM_RIGHT_CORNER
        // 3. TOP_LEFT_CORNER
        // 4. BOTTOM_LEFT_CORNER

        // Set maximum size of docker window to have at least 2 px width
        // and height as 'to be docked' object.
        this->setFixedSize( DEFAULT_HEIGHT_OR_WIDTH_OF_WINDOW, m_pDockedObject->frameGeometry().height() );

        switch ( m_aDockType )
        {
        case TOP_RIGHT_CORNER:
            this->move( screenRect.topRight().x() - DEFAULT_HEIGHT_OR_WIDTH_OF_WINDOW, screenRect.topRight().y() );
            break;
        case BOTTOM_RIGHT_CORNER:
            this->move( screenRect.topRight().x() - DEFAULT_HEIGHT_OR_WIDTH_OF_WINDOW, screenRect.bottomRight().y() - this->height() );
            break;
        case TOP_LEFT_CORNER:
            this->move( screenRect.topLeft().x() + DEFAULT_HEIGHT_OR_WIDTH_OF_WINDOW, screenRect.topLeft().y() );
            break;
        case BOTTOM_LEFT_CORNER:
            this->move( screenRect.topLeft().x() + DEFAULT_HEIGHT_OR_WIDTH_OF_WINDOW, screenRect.bottomLeft().y() + this->height() );
            break;
        default:
            //error. shouldn't happen.
            break;
        }
    }
    else
    {
        // Covers following cases:
        // 1. CENTER_TOP
        // 2. CENTER_BOTTOM
        // 3. CENTER_RIGHT
        // 4. CENTER_LEFT

        this->setFixedSize( m_pDockedObject->frameGeometry().width(), DEFAULT_HEIGHT_OR_WIDTH_OF_WINDOW );

        // todo!
        switch ( m_aDockType )
        {
        case CENTER_TOP:
            this->move( screenRect.width()/2 - this->width()/2, 0 );
            break;
        case CENTER_BOTTOM:
            this->move( screenRect.width()/2 - this->width()/2, screenRect.bottomLeft().y() );
            break;
        default:
            // error. shouldn't happen.
            break;
        }

        // Set maximum size of docker window to have at least 2 px height
        // and width as 'to be docked' object.
        this->setMaximumSize( m_pDockedObject->width(), 2 );
    }
}


/*
 * Slot for enter event.
 */
void QDesktopWindowDocker::enterEvent( QEvent *pEvent )
{
    if ( true == m_aEnabled )
    {
        emit edgeReached( m_aDockType );
    }
}


