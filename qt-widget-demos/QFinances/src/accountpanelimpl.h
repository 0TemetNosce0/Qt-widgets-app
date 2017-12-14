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

#ifndef ACCOUNTPANELIMPL_H
#define ACCOUNTPANELIMPL_H

#include <QtWidgets/QWidget>
#include "ui_account.h"
#include "fdatabase.h"

class AccountPanelImpl : public QDialog, public Ui::AccountPanel
{
      Q_OBJECT

public:
    AccountPanelImpl(QWidget *parent=0);
    void load_data(const QString& sHeader, const QList<data_curs>& data);
    void clear_data();
    void reload_ui();

private:
    QString s_cash;
    QString old_s_cash; //for preview
    double rate_cash;
    
private:
    void init_connections();
    double get_rate_currency(const QString& name_currency);

private slots:
    void slot_edit_change(const QString& text);
    void slot_unit1_change(const QString& text);
    void slot_unit2_change(const QString& text);
    void slot_main_combo_change(const QString& text);
};

#endif // ACCOUNTPANELIMPL_H
