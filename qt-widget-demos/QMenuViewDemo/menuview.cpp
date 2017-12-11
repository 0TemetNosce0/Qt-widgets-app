/***************************************************************************
 *   Copyright (C) 2009 by Weinzierl Stefan                                *
 *   Stefan@Weinzierl-Stefan.de                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "menuview.h"

MenuView::MenuView(const QString &title, QWidget *parent)
    : QMenu(title, parent)
    , m_model(0)
    , m_recursive(false)
{
    m_indexes.insert(this, QModelIndex());

    connect(this, SIGNAL(aboutToShow()), this, SLOT(showMenu()));
    connect(this, SIGNAL(aboutToHide()), this, SLOT(hideMenu()));
}

MenuView::~MenuView()
{

}

void MenuView::setModel(QAbstractItemModel *model, bool recursive)
{
    m_model = model;
    m_recursive = recursive;
}

void MenuView::showMenu()
{
    QMenu *menu = dynamic_cast<QMenu*>(sender());

    if (m_model && menu && menu->isEmpty())
    {
        QModelIndex parent = m_indexes.value(menu);

        int rows = m_model->rowCount(parent);
        for (int i=0; i<rows; i++)
        {
            QAction *act;
            QModelIndex child = m_model->index(i, 0, parent);
            QVariant data = child.data(Qt::DisplayRole);

            if (m_recursive && m_model->canFetchMore(child))
            {
                m_model->fetchMore(child);
            }

            if (m_recursive && m_model->hasChildren(child))
            {
                QMenu *newMenu = menu->addMenu(data.toString());
                act = newMenu->menuAction();
                m_indexes.insert(newMenu, child);
                connect(newMenu, SIGNAL(destroyed(QObject *)), this, SLOT(menuDestroyed(QObject *)));
                connect(newMenu, SIGNAL(aboutToShow()), this, SLOT(showMenu()));
                connect(newMenu, SIGNAL(aboutToHide()), this, SLOT(hideMenu()));
            }
            else
            {
                act = menu->addAction(data.toString());
                m_actions.insert(act, child);
                connect(act, SIGNAL(destroyed(QObject *)), this, SLOT(actionDestroyed(QObject *)));
            }

            Qt::ItemFlags flags = child.flags();

            act->setEnabled(flags & Qt::ItemIsEnabled);

            if (flags & Qt::ItemIsUserCheckable)
            {
                act->setCheckable(true);
                data = child.data(Qt::CheckStateRole);
                act->setChecked(data.toInt()==Qt::Checked);
            }

            data = child.data(Qt::DecorationRole);
            if (data.type()==QVariant::Icon)
            {
                act->setIcon(data.value<QIcon>());
            }

            data = child.data(Qt::ToolTipRole);
            if (data.isValid())
            {
                act->setToolTip(data.toString());
            }

            data = child.data(Qt::WhatsThisRole);
            if (data.isValid())
            {
                act->setWhatsThis(data.toString());
            }

            data = child.data(Qt::StatusTipRole);
            if (data.isValid())
            {
                act->setStatusTip(data.toString());
            }

            connect(act, SIGNAL(triggered(bool)), this, SLOT(triggered()));
            connect(act, SIGNAL(hovered()), this, SLOT(hovered()));
        }
    }
}

void MenuView::hideMenu()
{
    QMenu *menu = dynamic_cast<QMenu*>(sender());
    if (menu)
    {
        foreach (QAction *act, menu->actions())
        {
            act->deleteLater();
        }
    }
}

void MenuView::menuDestroyed(QObject *obj)
{
    m_indexes.remove(dynamic_cast<QMenu*>(obj));
}

void MenuView::actionDestroyed(QObject *obj)
{
    m_actions.remove(dynamic_cast<QAction*>(obj));
}

QModelIndex MenuView::indexForAction(QAction *act) const
{
    return m_actions.value(act);
}

void MenuView::hovered()
{
    QAction *action = dynamic_cast<QAction*>(sender());
    if (action)
    {
        QModelIndex index = m_actions.value(action);
        if (index.isValid())
        {
            emit hovered(index);
        }
    }
}

void MenuView::triggered()
{
    QAction *action = dynamic_cast<QAction*>(sender());
    if (action)
    {
        QModelIndex index = m_actions.value(action);
        if (index.isValid())
        {
            emit triggered(index);
        }
    }
}


