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

#include "parametersdlgimpl.h"

#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QFile>

ParametersDlgImpl::ParametersDlgImpl(QWidget *parent)
    : QDialog(parent)
    , bnew(false)
{
    setupUi(this);

    label1->setText(tr("Acount"));
    label2->setText(tr("Password"));
    lineEdit1->setEchoMode(QLineEdit::Password);
    comboBox->setEditable(false);
	
    setWindowTitle(tr("Authorization"));
    setWindowIcon(QIcon(":/img/password.png"));

    okBtn->setText(tr("Login"));
    cancelBtn->setText(tr("Exit"));
    
    connect(okBtn, SIGNAL(clicked()), this, SLOT(slot_ok()));
    connect(chNewAc, SIGNAL(clicked(bool )),this, SLOT(setEditable(bool)));
}

void ParametersDlgImpl::get_data(QString& value1, QString& value2)
{
    value1 = comboBox->currentText();
    value2 = lineEdit1->text();
}

void ParametersDlgImpl::slot_ok()
{
    QString s;
    
    s = comboBox->currentText();
    s = s.simplified();
    
    if(s == "")
    {
        QMessageBox::information(0,tr("Information"), tr("Please enter name account."));
        return;
    }

    if(bnew)
    {
        if(QFile::exists(QApplication::applicationDirPath()+"/"+comboBox->currentText()+".db"))
        {
            QMessageBox::information(0,tr("Information"), tr("Account is exist."));
            return;
        }
    }

    accept();
}

void ParametersDlgImpl::setEditable(bool b)
{
    comboBox->setEditable(b);
    lineEdit1->setVisible(!b);
    label2->setVisible(!b);
    comboBox->setEditText("");

    if (b)
    {
        comboBox->setFocus();
    }

    bnew = b;
}
