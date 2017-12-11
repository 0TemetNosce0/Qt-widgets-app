/***************************************************************************
 *   Copyright (C) 2014 by peter komar                                     *
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

#include "paramslist.h"
#include "editdlgimpl.h"

#include <QPushButton>

ParamsList::ParamsList(QWidget * parent)
    : QTreeWidget(parent)
{
    QStringList params;
    params << "Name" << "Value";
    setHeaderLabels(params);

    setColumnWidth(0, 200);
    setAlternatingRowColors(true);
    setRootIsDecorated(false);
    setUniformRowHeights(false);
    setAllColumnsShowFocus(true);
    header()->setCascadingSectionResizes(true);
    header()->setHighlightSections(false);
    header()->setStretchLastSection(true);

    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int )), this, SLOT(slotEditItem()));
}

void ParamsList::slotEditItem()
{
    QPushButton *btn = static_cast<QPushButton *>(sender());
    QString name, value;
    QTreeWidgetItem *item = NULL;

    if(btn->property("add").isNull())
    {
        item = currentItem();
        if( item != NULL )
        {
            name = item->text(0);
            value = item->text(1);
        }
    }

    EditDlgImpl *dlg = new EditDlgImpl(this);
    dlg->setName(name);
    dlg->setValue(value);

    dlg->exec();

    name = dlg->getName();
    value = dlg->getValue();
    int res = dlg->result();
    delete dlg;

    if( res == QDialog::Rejected )
    {
        return;
    }

    if( item == NULL )
    {
        item = new QTreeWidgetItem(this);
    }

    item->setText(0, name);
    item->setText(1, value);
}

void ParamsList::slotDeleteItem()
{
    QTreeWidgetItem *item = currentItem();

    if( item != NULL )
    {
        delete item;
        item = NULL;
    }
}
