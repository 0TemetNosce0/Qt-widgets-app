/***************************************************************************
 *   Copyright (C) 2007 by Peter Komar                                     *
 *   udldevel@gmail.com                                                    *
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

#ifndef DOCKWIDG_H
#define DOCKWIDG_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>

class QTreeWidget;
class QPushButton;

class DockWidg : public QDialog
{
    Q_OBJECT

public:
    DockWidg(QWidget *parent = 0);

    ~DockWidg();
    void load_data();
    void reload_ui();

    QTreeWidget *listCred;
    QPushButton *NewBtn;
    QPushButton *infBtn;
    QPushButton *RemBtn;
};

#endif
