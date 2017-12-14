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

#ifndef QJSONVIEW_H
#define QJSONVIEW_H

#include <QTreeWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class QJsonView : public QTreeWidget
{
    Q_OBJECT
public:
    explicit QJsonView(QWidget *parent = 0);

     void setJson(const QString& text);

private:
    enum{TYPE_ITEM_OBJECT = 1, TYPE_ITEM_ARRAY};
    void buildObject(const QString& name, const QJsonObject& object, QTreeWidgetItem* parent = 0);
    void buildArray(const QString& name, const QJsonArray& object, QTreeWidgetItem* parent = 0);
    void addItem(const QString& name, const QJsonValue& value, QTreeWidgetItem* item);

    QTreeWidgetItem* createItem(const QString& name, QTreeWidgetItem *parent, int type = 0);
};

#endif // QJSONVIEW_H
