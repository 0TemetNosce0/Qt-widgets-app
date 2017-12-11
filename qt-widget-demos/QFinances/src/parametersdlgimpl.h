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

#ifndef MDIALOGIMPL_H
#define MDIALOGIMPL_H

#include <QtWidgets/QDialog>
#include "ui_parameters.h"

class ParametersDlgImpl : public QDialog, public Ui::ParametersDlg
{
    Q_OBJECT

public:
    ParametersDlgImpl(QWidget *parent=0);
    void set_data(const QStringList& value1) {comboBox->addItems(value1);}
    void get_data(QString& value1, QString& value2);
    bool is_new_account() {return bnew; }

private:
    bool bnew;

private slots:
    void slot_ok();
    void setEditable(bool );	
};

#endif // MDIALOGIMPL_H
