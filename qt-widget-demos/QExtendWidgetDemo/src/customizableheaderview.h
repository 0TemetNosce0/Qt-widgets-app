/*
    Copyright (C) 2008  Tim Fechtner < urwald at users dot sourceforge dot net >

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License or (at your option) version 3 or any later version
    accepted by the membership of KDE e.V. (or its successor approved
    by the membership of KDE e.V.), which shall act as a proxy
    defined in Section 14 of version 3 of the license.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CUSTOMIZABLEHEADERVIEW_H
#define CUSTOMIZABLEHEADERVIEW_H

/** \def KDE4_SUPPORT
  * %KDE4_SUPPORT is defined by default to enable support for the the KDE 4 libraries in the class
  * CustomizableHeaderView.
  *
  * You can comment out this macro to get a Qt only class, but you
  * will loose some functionality. */
#define KDE4_SUPPORT

#include <QPointer>
#include <QHeaderView>

/** \brief An enhaced QHeaderView providing a context menu where the user can choose
  *        which rows/columns to display and which not.
  *
  * Each time a context menu is requested by the user, a new context menu is created
  * with the actual data (column/row header names and maybe a menu title).
  *
  * This class uses by default KMenu from the kdelibs (KDEUI) for the context menu,
  * which gives support for visible
  * menu titles. However when you want a Qt-only version of %CustomizableHeaderView,
  * just remove the defination
  * #KDE4_SUPPORT from
  * the header file. (In this case, the property #contextMenuTitle will no longer be available.) */
class CustomizableHeaderView : public QHeaderView
{

    Q_OBJECT

#ifdef KDE4_SUPPORT
    /** This property holds the title of the context menu. If empty (which is default),
    * no title is displayed.
    * \li \e read: \code const QString contextMenuTitle() \endcode
    * \li \e write: \code void setContextMenuTitle(const QString & title) \endcode
    * \li \e reset: \code void resetContextMenuTitle() \endcode
    *
    * This property is only available when #KDE4_SUPPORT is defined - what is the default.
    * \sa m_contextMenuTitle
    * \sa KDE4_SUPPORT
    */
    Q_PROPERTY(QString contextMenuTitle
               READ contextMenuTitle
               WRITE setContextMenuTitle
               RESET resetContextMenuTitle)
#endif

public:
    /*!
      * Creates a new generic header.
      * @param orientation Qt::Horizontal or Qt::Vertical
      * @param parent      parent widget
      */
    explicit CustomizableHeaderView(Qt::Orientation orientation, QWidget * parent = 0);
    /** Generic destructor. */
    virtual ~CustomizableHeaderView();

#ifdef KDE4_SUPPORT
    /** See property #contextMenuTitle. */
    QString contextMenuTitle() const;
    /** See property #contextMenuTitle. */
    void resetContextMenuTitle();
    /** See property #contextMenuTitle. */
    void setContextMenuTitle(const QString & title);
#endif

signals:
    /** This signal is emitted immediately before hiding a row or column
      * because the user used the context menu. It is \e not emitted when hideSection() or
      * setSectionHidden() was called.
      * @param index index of the row or column that will be hidden.
      * @param orientation The orientation of the header. If Qt::Horizontal,
      *                    than a column will be hidden, if Qt::Vertical,
      *                    a row will be hidden. */
    void sectionAboutToBeHidden(int index, Qt::Orientation orientation);
    /** This signal is emitted immediately before showing a row or column
      * because the user used the context menu. It is \e not emitted when
      * setSectionHidden() was called.
      * @param index index of the row or column that will be shown.
      * @param orientation The orientation of the header. If Qt::Horizontal,
      *                    than a column will be shown, if Qt::Vertical,
      *                    a row will be shown. */
    void sectionAboutToBeShown(int index, Qt::Orientation orientation);
    /** This signal is emitted immediately after hiding a row or column
      * because the user used the context menu. It is \e not emitted when hideSection() or
      * setSectionHidden() was called.
      * @param index index of the row or column that has been hidden.
      * @param orientation The orientation of the header. If Qt::Horizontal,
      *                    than a column was hidden, if Qt::Vertical,
      *                    a row was hidden. */
    void sectionHidden(int index, Qt::Orientation orientation);
    /** This signal is emitted immediately after showing a row or column
      * because the user used the context menu. It is \e not emitted when
      * setSectionHidden() was called.
      * @param index index of the row or column that has been shown.
      * @param orientation The orientation of the header. If Qt::Horizontal,
      *                    than a column was shown, if Qt::Vertical,
      *                    a row was shown. */
    void sectionShown(int index, Qt::Orientation orientation);

protected:
    /** Displays the context menu.
      *
      * Reimplemented from class QAbstractScrollArea. */
    virtual void contextMenuEvent (QContextMenuEvent *e);

private:
#ifdef KDE4_SUPPORT
    /** Used internally to store the property #contextMenuTitle. */
    QString m_contextMenuTitle;
#endif
};

#endif
