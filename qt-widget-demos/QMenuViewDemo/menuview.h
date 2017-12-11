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
#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <QMenu>
#include <QModelIndex>

class QAbstractItemModel;

/**
    @author Weinzierl Stefan <Stefan@Weinzierl-Stefan.de>
*/
class MenuView : public QMenu
{
Q_OBJECT
public:
    MenuView(const QString &title, QWidget *parent=0);
    ~MenuView();

    void setModel(QAbstractItemModel *model, bool recursive=false);

    QModelIndex indexForAction(QAction *act) const;

signals:
    void hovered(const QModelIndex &index);
    void triggered(const QModelIndex &index);

protected slots:
    void showMenu();
    void hideMenu();
    void menuDestroyed(QObject *);
    void actionDestroyed(QObject *);

    void hovered();
    void triggered();

private:
    QAbstractItemModel *m_model;
    bool m_recursive;
    QMap<QMenu*, QModelIndex> m_indexes;
    QMap<QAction*, QModelIndex> m_actions;
};

#endif
