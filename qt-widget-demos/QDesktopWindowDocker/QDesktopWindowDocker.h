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
#ifndef __QDESKTOP_WINDOW_DOCKER_H__
#define __QDESKTOP_WINDOW_DOCKER_H__

#include <QDialog>
#include <QWidget>


class QEvent;


/*
 * Provides basic docking types.
 */
enum DesktopDockType
{
    TOP_RIGHT_CORNER 	= 0x01,
    BOTTOM_RIGHT_CORNER	= 0x02,
    TOP_LEFT_CORNER		= 0x03,
    BOTTOM_LEFT_CORNER	= 0x04,
    CENTER_TOP			= 0x10,
    CENTER_BOTTOM		= 0x20/*,
    CENTER_RIGHT		= 0x30,
    CENTER_LEFT			= 0x40*/
};

const char 	DOCKING_TYPE_NON_CENTER_MASK 		= 0x0F;
const char	DEFAULT_HEIGHT_OR_WIDTH_OF_WINDOW	= 4;
/**
 * @class QDesktopWindowDocker
 * \brief Provides simplest window docking mechanism across desktop.
 */
class QDesktopWindowDocker : public QDialog
{
    Q_OBJECT

public:

    /**
         * Constructor.
         * @param _to_be_docked widget to be docked in desktop.
         */
    explicit QDesktopWindowDocker( QWidget *pToBeDocked, const DesktopDockType aDockType = TOP_RIGHT_CORNER );

    /**
         * Destructor.
         */
    ~QDesktopWindowDocker();

    /**
         * \brief returns enable status.
         * @return true if docker is enabled, false - otherwise.
         */
    bool isEnabled() const;

    /**
         * \brief enables or disables docker.
         * @param [in] _to_be_enabled flag indicating if docker should be
         * enabled or not (true by default).
         */
    void enable( const bool _to_be_enabled = true );

    /**
         * \brief sets dock type.
         * @param [in] rDesktopType type of dock to be applied.
         */
    void setDockType( const DesktopDockType &rDesktopDockType );


protected:
    /*
         * \brief enter envent handler.
         * @param [in] pEvent event handled.
         */
    void enterEvent( QEvent *pEvent );

private:

    /*
         * \brief calculate proper size and position of docker depending on docking type.
         */
    void resizeAndMove();

    bool 	 			m_aEnabled;				/**< Flag indicating if docker is enabled. 	*/
    DesktopDockType 	m_aDockType;			/**< Docking type.							*/
    QWidget 		   *m_pDockedObject;		/**< Object that needs to be docked.		*/

signals:

    /*
         * \brief signal definition, emited when edge of screen is reached.
         * @param [in] rDesktopDockType type of docking applied.
         */
    void edgeReached( const int &rDesktopDockType );


};


/*
 * Checks if docker is enabled.
 */
inline bool QDesktopWindowDocker::isEnabled() const
{
    return m_aEnabled;
}

/*
 * Enables or disables docker.
 */
inline void QDesktopWindowDocker::enable( const bool _to_be_enabled ) 
{
    m_aEnabled = _to_be_enabled;
}

/*
 * Sets docking type.
 */
inline void QDesktopWindowDocker::setDockType( const DesktopDockType &rDesktopDockType )
{
    m_aDockType = rDesktopDockType;
}


#endif /* __QDESKTOP_WINDOW_DOCKER_H__ */

