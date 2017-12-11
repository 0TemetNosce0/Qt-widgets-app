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

#ifndef PREFDLGIMPL_H
#define PREFDLGIMPL_H

#include <QtWidgets/QDialog>
#include "ui_preferences.h"

class CurrencyDlg : public QDialog
{
Q_OBJECT
public:
    CurrencyDlg(QWidget *parent=0);
    void set_data(const QString& name, const QString& rate);
    bool get_data(QString& name, QString& rate);
private:
    QLineEdit *m_name;
    QLineEdit *m_rate;
};

class PreferencesDlgImpl : public QDialog, public Ui::PreferencesDlg
{
    Q_OBJECT
public:
    PreferencesDlgImpl(bool bfirst_show=false, QWidget *parent=0);
private slots:
    void slot_ok();
    void slot_add_currency();
    void slot_rem_currency();
    void slot_ch_currency();
    void slot_set_main_currency();
private:
    bool bfirst;
    QString old_lang;
public:
       static const char* company;
       static const char* key;

};

#endif // PREFDLGIMPL_H
