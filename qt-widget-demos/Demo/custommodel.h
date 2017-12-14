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

#ifndef CUSTOMSQLMODEL_H
#define CUSTOMSQLMODEL_H

#include <QAbstractTableModel>

/*! \class CustomModel
 *  \brief CustomModel for example applications
 *  \author Kund Gordos
 *  \version 1.0
 *  \date    2008
 */
class CustomModel : public QAbstractTableModel
{
        Q_OBJECT

public:
        CustomModel(QObject *parent = 0);

        QVariant data(const QModelIndex &item, int role) const;
        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent = QModelIndex()) const;
private:
};

#endif
