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

#ifndef FDATABASE_H
#define FDATABASE_H

#include <QList>
#include <QString>
#include <QSqlQuery>

#include "misc.h"

struct Db_dat
{
    QString Name;
    double count_d;
	QString currency;
	QString  date;
	QString  descr;
	QString type;
	double percent;
	QString  date_incr;//data increment parcent credit
};

struct user_data
{
    QString NameDB;//path to base
    QString NameDBc;
};

struct data_curs
{
    QString name_curency;
    double curs;
    bool b_main;
};


/**
* Data base finances implementation
*/

//operations
QString load_data_from_operation(QList<Db_dat>& list_op, const QString& sYear = "all");//return heder data: count in bank
                                                                                    //and icomes and outgoes

void add_operation(bool bAdd, Db_dat data, bool bsys_op = false);
QList<Db_dat>load_operation_with_filter(const QString& str, bool& bRet, double *d_income = 0, double *d_outgoes = 0);

//bank
bool get_data_from_bank(double& count, QString& name_currency);
bool set_data_to_bank(double count, const QString& name_currency);
QString get_password();
bool set_password(const QString& password);
bool create_db_accounts(const QString& connectdbName, const QString& password);
bool create_db_cash_rate(const QString& connectdbName);
bool check_password(const QString& connectdbName, const QString& password);

//creditors
QList<Db_dat> load_data_from_creditors();
void set_data_creditor(Db_dat data);
Db_dat info_creditor(const QString& data_operation);
void increment_debt(); //increment debt after month or year

//currency
QList<data_curs> get_curs_curency();
void save_curs(const QList<data_curs>& list);

//global operation
void convert_currency_account(const QString& currency, bool bfirst=false);
double convert_currency(double value, const QString& fromUnit1, const QString& toUnit2);

//data
void set_user_data(user_data data);
QString get_display_format();
//convert date from display to database and  inversely
QString convert_date_format(const QString& date, bool toDisplay = true); 

//debug only
//void convert_old_DB(const QString& oldDBName, const QString& newDBName, const QString& user, const QString& password);

#endif
