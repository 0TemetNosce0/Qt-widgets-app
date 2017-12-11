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

#include "customizableheaderview.h"

#include <QMenu>
#include <QAction>
#include <QPointer>
#include <QContextMenuEvent>

CustomizableHeaderView::CustomizableHeaderView(Qt::Orientation orientation, QWidget * parent)
    : QHeaderView(orientation, parent)
{

}

CustomizableHeaderView::~CustomizableHeaderView()
{

}

#ifdef KDE4_SUPPORT

#include <QMenu>

QString CustomizableHeaderView::contextMenuTitle() const
{
    return m_contextMenuTitle;
}

void CustomizableHeaderView::setContextMenuTitle(const QString & title)
{
    m_contextMenuTitle = title;      // update property storage
}

void CustomizableHeaderView::resetContextMenuTitle()
{
    setContextMenuTitle("");
}

#endif

void CustomizableHeaderView::contextMenuEvent(QContextMenuEvent * e)
{
    int sectionCount;
    int i;
    QPointer<QAction> temp_action;
    QPointer<QAction> activated_action;
    bool isOkay;
    int index;

#ifdef KDE4_SUPPORT
    QMenu m_contextMenu(this);
    if (contextMenuTitle().isEmpty())
    {
        m_contextMenu.setTitle(contextMenuTitle());
    }
#else
    QMenu m_contextMenu(this);
#endif

    // The menu is contructed each time again, because the numer of columns/rows in the model
    // could have changed since the last call.

    if (orientation() == Qt::Horizontal)
    {
        sectionCount = model()->columnCount();
    }
    else
    {
        sectionCount = model()->rowCount();
    }

    for (i=0; i < sectionCount; ++i)
    {
        temp_action = new QAction(model()->headerData(i,
                                                      orientation(),
                                                      Qt::DisplayRole).toString(),
                                  &m_contextMenu);  // because m_contextMenu is parent of the
        // actions, all of them will be deleted
        // automatically when this function stops.
        temp_action->setCheckable(true);
        temp_action->setChecked(!isSectionHidden(i));
        temp_action->setData(i);
        m_contextMenu.addAction(temp_action);
    }
    activated_action = 0;
    activated_action = m_contextMenu.exec(e->globalPos());
    // process QAction after closing menu
    if (! (activated_action == 0))
    {
        isOkay = 1;  // following the doc for QVariant, the return type of QAction::data(),
        // isOkay must be non-null for that an value is set.
        index = activated_action->data().toInt(&isOkay);
        if (isOkay)
        {
            if (isSectionHidden(index))
            {
                emit sectionAboutToBeShown(index, orientation());
                setSectionHidden(index, false);
                emit sectionShown(index, orientation());
            }
            else
            {
                emit sectionAboutToBeHidden(index, orientation());
                setSectionHidden(index, true);
                emit sectionHidden(index, orientation());
            }
        }
    }
}
