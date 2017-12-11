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

#include "dockwidg.h"
#include "fdatabase.h"

#include <QTreeWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>

DockWidg::DockWidg(QWidget *parent)
    : QDialog(parent)
{
    listCred = new QTreeWidget(this);
    NewBtn = new QPushButton(this);
    infBtn  = new QPushButton(this);
    RemBtn = new QPushButton(this);

    QVBoxLayout *pvbxLayout = new QVBoxLayout;
    QHBoxLayout *phbxLayout = new QHBoxLayout;
    pvbxLayout->addWidget(listCred);
    phbxLayout->addWidget(NewBtn);
    phbxLayout->addWidget(infBtn);
    phbxLayout->addWidget(RemBtn);
    pvbxLayout->addLayout(phbxLayout);
    setLayout(pvbxLayout);

    reload_ui();

    listCred->setDragEnabled(false);
    listCred->setSelectionMode(QAbstractItemView::ExtendedSelection);

    load_data();
}

DockWidg::~DockWidg()
{

}

void DockWidg::reload_ui()
{
    NewBtn->setText(tr("New mortgagor..."));
    infBtn->setText(tr("About  mortgagor..."));
    RemBtn->setText(tr("Paying off..."));
    QStringList labels;
    labels << tr("Name mortgagors") << tr("Count") << tr("Date");
    listCred->setHeaderLabels(labels);
}

void DockWidg::load_data()
{
    listCred->clear();

    QList<Db_dat> list = load_data_from_creditors();

    QTreeWidgetItem *item = 0;

    for (int i = 0; i < list.size(); ++i)
    {
        Db_dat dat = list.at(i);

        item = new QTreeWidgetItem();

        item->setText(2, dat.date);

        QString s;
        s = s.number(dat.count_d,'F',2);
        item->setText(1, s + " " + dat.currency);

        item->setText(0, dat.Name);

        listCred->addTopLevelItem(item);
    }
}
