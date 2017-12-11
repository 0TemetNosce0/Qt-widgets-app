/***************************************************************************
 *   Copyright (C) 2014 by Peter Komar                                     *
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

#include "qjsonview.h"

#include <QJsonDocument>
#include <QHeaderView>
#include <QJsonArray>

QJsonView::QJsonView(QWidget *parent)
    : QTreeWidget(parent)
{
    QStringList params;
    params << "Key" << "Value";
    setHeaderLabels(params);
    setColumnWidth(0, 300);

    setUniformRowHeights(false);
    setAllColumnsShowFocus(true);
    setRootIsDecorated(true);
    setAlternatingRowColors(true);
    header()->setCascadingSectionResizes(true);
    header()->setHighlightSections(false);
    header()->setStretchLastSection(true);
}

void QJsonView::setJson(const QString &text)
{
    clear();
    QJsonDocument document = QJsonDocument::fromJson(text.toUtf8());

    if(document.isArray())
    {
        buildArray("", document.array());
    }
    else if(document.isObject())
    {
        buildObject("", document.object());
    }
    else
    {
        throw -1;
    }
}

void QJsonView::buildObject(const QString& name, const QJsonObject &obj, QTreeWidgetItem *parent)
{
   QTreeWidgetItem *item = createItem(name + (!name.isEmpty()? " " : "") + "{...}", parent, TYPE_ITEM_OBJECT);
   QJsonObject::const_iterator iterator = obj.begin();

   while(iterator != obj.end())
   {
       addItem(iterator.key(), iterator.value(), item);
       ++iterator;
   }
}

void QJsonView::buildArray(const QString& name, const QJsonArray &arr, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = createItem(
                name + (!name.isEmpty()? " " : "") + QString("[%1]").arg(arr.count()),
                parent,
                TYPE_ITEM_ARRAY
                );
    int i = 0;

    foreach (QJsonValue var, arr)
    {
        addItem(QString("[%1]").arg(i++), var, item);
    }
}

void QJsonView::addItem(const QString& name, const QJsonValue& val, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = 0;

    if(val.isDouble())
    {
        item = createItem(name, parent);
        item->setText(1, QString::number(val.toDouble()));
    }
    else if(val.isString())
    {
        item = createItem(name, parent);
        item->setText(1, val.toString());
    }
    else if(val.isObject())
    {
        buildObject(name, val.toObject(), parent);
    }
    else if(val.isArray())
    {
        buildArray(name, val.toArray(), parent);
    }
    else if(val.isBool())
    {
        item = createItem(name, parent);
        item->setText(1, val.toBool()? "True" : "False");
    }
    else if(val.isNull())
    {
        item = createItem(name, parent);
        item->setText(1, "null");
    }
}

QTreeWidgetItem* QJsonView::createItem(const QString& name, QTreeWidgetItem *parent, int type)
{
    QTreeWidgetItem *item = 0;

    if(parent)
    {
        item = new QTreeWidgetItem(parent, type);
    }
    else
    {
        item = new QTreeWidgetItem(this, type);
    }

    item->setText(0, name);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    expandItem(item);

    return item;
}

