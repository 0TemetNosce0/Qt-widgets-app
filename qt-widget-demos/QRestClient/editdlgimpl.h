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
#ifndef EDITDLGIMPL_H
#define EDITDLGIMPL_H

#include <QDialog>
#include "ui_dialog.h"

class EditDlgImpl : public QDialog, public Ui::EditDlg
{
    Q_OBJECT

public:
    explicit EditDlgImpl(QWidget *parent = 0);

public:
    QString getName() const;
    void setName(const QString& name);

    QString getValue() const;
    void setValue(const QString& value);

signals:

public slots:


};

#endif // EDITDLGIMPL_H
