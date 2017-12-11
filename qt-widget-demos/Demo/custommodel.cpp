/*
 * Demo table model
 * Copyright (C) 2004-2008 by Gordos Kund / QnD Co Bt.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact gordos.kund@gmail.com with any questions on this license.
 */

#include <QtGui>
#include <QtCore/QDate>
#include <QtCore/QVariant>
#include "custommodel.h"

CustomModel::CustomModel(QObject *parent) : QAbstractTableModel(parent)
{
}

//======================================================================

QVariant CustomModel::data(const QModelIndex &index, int role) const
{
	if (role!=Qt::DisplayRole )
	{
		return QVariant();
	}
	
        QVariant value;
        QDate ret = QDate::currentDate();
        if (index.column() == 0) {
		ret=ret.addDays(index.row());
                value= ret.toString();
		return value;
        }

        if (index.column() == 1) {
                ret=ret.addDays(index.row());
                value= QDate::longMonthName(ret.month());
                return value;
        }

        if (index.column() == 2) {
		ret=ret.addDays(index.row());
                value= QDate::longDayName(ret.dayOfWeek());
                return value;
        }
        return value;
}

//======================================================================

int CustomModel::rowCount(const QModelIndex & /*parent*/) const
{
        return 200;
}

//======================================================================

int CustomModel::columnCount(const QModelIndex & /*parent*/) const
{
        return 3;
}
