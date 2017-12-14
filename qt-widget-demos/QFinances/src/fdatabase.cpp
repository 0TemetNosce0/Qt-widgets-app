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

#include "fdatabase.h"

#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QDateTime>

user_data data_u;
const char* format_data = "yyyy.MM.dd hh:mm";

void set_user_data(user_data data)
{
    data_u.NameDB = data.NameDB;
    data_u.NameDBc = data.NameDBc;
}

QString get_display_format()
{
    return QString("dd.MM.yyyy hh:mm");
}

QString convert_date_format(const QString& date, bool toDisplay)
{
	QString sRet;
	
    if (toDisplay)
    {
	  sRet = (QDateTime::fromString(date,format_data)).toString(get_display_format());
    }
    else
    {
	  sRet = (QDateTime::fromString(date,get_display_format())).toString(format_data);
    }
		
	return sRet;	
}


bool get_data_from_bank(double& count, QString& name_currency)
{
	QSqlQuery query(QSqlDatabase::database(data_u.NameDB));
       
	QString s_cash;
	double d_count=0;
	        
	query.prepare("select * from bank where 1");
    if (!query.exec())
    {
        qDebug() << "Failed to execute Table Bank: SELECT * FROM BANK WHERE 1";
        return false;
    }
	
    while (query.next())
    {
        d_count = query.value(0).toDouble();
        s_cash = query.value(1).toString();
	}
	
	count = d_count;
	name_currency = s_cash;
		
	return true;
}

bool set_data_to_bank(double count, const QString& name_currency)
{
	QSqlQuery query(QSqlDatabase::database(data_u.NameDB));
	
	query.prepare("update bank set count_c=:count, currency=:currency where 1");
	query.bindValue(":count", count);
	query.bindValue(":currency", name_currency);
	
    if (!query.exec())
    {
		qDebug() << "Failed to execute Table Bank: UPDATE BANK SET count_c=:count, currency=:currency WHERE 1";
		return false;
	}
	
	return true;
}

QList<Db_dat> load_data_from_creditors()
{
    QList<Db_dat> sRet;
    
    Db_dat data;

    QSqlQuery query(QSqlDatabase::database(data_u.NameDB));
    query.prepare("select * from creditors where 1");
    query.exec();
    while (query.next())
    {
	    QString date = query.value(0).toString();
	    
	    data.date = date;
		
	    QString sName = query.value(1).toString();
	    data.Name = sName;
		
        double icount = query.value(2).toDouble();
	    data.count_d = icount;
		
	    data.currency = query.value(3).toString();
	    data.descr = query.value(4).toString();
	    	    
	    sRet.append(data);
    }

    return sRet;
}

QString load_data_from_operation(QList<Db_dat>& list_op, const QString& sY)
{
    QString s_Ret;
	Db_dat data;    
    QString s_cash;

    double n_C=0;
	
    get_data_from_bank(n_C,s_cash);

    s_Ret = QString::number(n_C,'F',2)+"|"+s_cash+"|";
    double *d_income = new double;
    double *d_outgoes = new double;

	QString querys = "";
    if(sY != "all")
    {
        //if set filter year
        querys = "(date_s like '%"+sY+"%')";
    }
    else
    {
	    querys = "1";
    }
	
	bool bfindet=false;
	
    list_op = load_operation_with_filter(querys, bfindet, d_income, d_outgoes);
	
    if (list_op.isEmpty())
    {
        data.date = "-";
        data.count_d = 0.00;
        data.descr = QObject::tr("No transactions");
        data.type = "-";
        list_op.append(data);
    }

    s_Ret += QString::number(*d_income,'F',2)+" "+s_cash+"|";
    s_Ret += QString::number(*d_outgoes,'F',2)+" "+s_cash;
	
	delete d_income;
	delete d_outgoes;
	    
	return s_Ret;
}

QList<Db_dat> load_operation_with_filter(const QString& str, bool& bRet, double *d_income, double *d_outgoes)
{
	QList<Db_dat> lRet;
	Db_dat data;
	bRet = false;
	
	double i_income = 0.00;
	double i_outgoes = 0.00;
	
	QSqlQuery query(QSqlDatabase::database(data_u.NameDB));
	
	QString querystring = "select * from operation where "+str;
	
    if (!query.exec(querystring))
    {
		QSqlError er = query.lastError();//"Failed to execute filter: select * from operation where date_s like";
		data.descr = er.text();
		return lRet;
	}
	
    while (query.next())
    {
		data.date = query.value(0).toString();
		
		data.type = query.value(1).toString();//get type operation
		
        double icount = query.value(2).toDouble(); //get count cash operation
		if(data.type == "income")
        {
            i_income += icount;
        }
        else if(data.type == "outgoes")
        {
            i_outgoes += icount;
        }
        data.count_d = icount;
		
		data.currency = query.value(3).toString();
		data.descr = query.value(4).toString();//get description operation
                   		   
		bRet=true;
		lRet.append(data);
	}
	
    if(d_income && d_outgoes)
    {
	   *d_income = i_income;
	   *d_outgoes = i_outgoes;
	}
	
	return lRet;
}

void add_operation(bool bAdd, Db_dat data, bool bsys_op)
{

    QSqlQuery query(QSqlDatabase::database(data_u.NameDB));
	
	double idata;
	QString s_cash;
	
	get_data_from_bank(idata, s_cash);
	
	query.prepare("INSERT INTO operation (date_s, type_op, count, currency_name, description) "
			"VALUES (:date_s, :type_op, :count, :currency_name, :description)");
	
    if(bAdd)
    {
        query.bindValue(":type_op", "income");
        if(!bsys_op)
        {
		  idata += data.count_d;
        }
    }
    else
    {
        query.bindValue(":type_op", "outgoes");
        if(!bsys_op)
        {
            idata -= data.count_d;
        }
    }
	
    if(bsys_op)
    {
		query.bindValue(":type_op", "sys");
	}
	
    if (idata < 0)
    {
		QMessageBox::information(0,QObject::tr("Erorr operation"),QObject::tr("No cash"));
		return;	
	}
	
	QDateTime date = QDateTime::fromString(data.date,get_display_format());
	
	query.bindValue(":date_s", date.toString(format_data));
		
	query.bindValue(":count", data.count_d);
	query.bindValue(":currency_name", s_cash);
	query.bindValue(":description", data.descr);
	
    if (!query.exec())
    {
		qDebug() << query.lastError() << " Table Operation";
    }
	
    if (!bsys_op)
    {
		set_data_to_bank(idata, s_cash);
    }
}

void set_data_creditor(Db_dat data)
{
    QSqlQuery query(QSqlDatabase::database(data_u.NameDB));
	
    double idata = 0;
	QString s_cash, s_cash_credit;
	get_data_from_bank(idata, s_cash);
	
	query.prepare("select * from creditors where 1");
	query.exec();
	
	bool b=false;//find record id finded - change, else create new
	
    while (query.next())
    {
		QSqlQuery query_in(QSqlDatabase::database(data_u.NameDB));
        if(data.date == query.value(0).toString())
        {
            s_cash_credit = query.value(3).toString();
            double n = query.value(2).toDouble()-data.count_d;

            if (n > 0)
            {
			   query_in.prepare("update creditors set count=:count where (date_c=:date_c)");
			   query_in.bindValue(":count", n);
			   query_in.bindValue(":date_c", data.date);
            }
            else
            {
				query_in.prepare("delete from creditors where (date_c=:date_c)");
				query_in.bindValue(":date_c", data.date);
			}
			
            if (!query_in.exec())
            {
				qDebug() << query_in.lastError();
				return;
			}
			
            b = true;
			break;
		}
	}
	
    if (!b)
    {
        //create new credit
        idata -= data.count_d;//check many in count

        if(idata<0)
        {
            QMessageBox::information(0,QObject::tr("Erorr operation"),QObject::tr("No cash"));
			return;	
		}
		
		
		query.prepare("INSERT INTO creditors (date_c, name_c, count,"
				"currency_name, percent, type, description, date_incr) "
				"VALUES (:date_c, :name, :count, :currency_name, :percent,"
				":type, :description, :date_incr)");
		query.bindValue(":count", data.count_d);
		query.bindValue(":currency_name", s_cash);
		query.bindValue(":percent", data.percent);
		query.bindValue(":type", data.type);
		query.bindValue(":date_c", data.date);
		query.bindValue(":name", data.Name);
		query.bindValue(":description", data.descr);
		query.bindValue(":date_incr", data.date_incr);
		
        if (!query.exec())
        {
		   qDebug() << query.lastError();
		   return;
		}
	}
		
	Db_dat data_o;
	
	QString s_h = "<b>%1</b> <b>%2:</b>";
	bool bconverted = false;
	double d_c_cash= data.count_d;
	
    if(b)
    {

        if(s_cash == s_cash_credit)
        {
            //convert cash if currency bank
		    idata += data.count_d; // not equable with currency credit
        }
        else
        {
		    d_c_cash = convert_currency(data.count_d,s_cash_credit,s_cash);
		    idata += d_c_cash;
		    bconverted = true;
		}
		
		data_o.descr = s_h.arg(QObject::tr("Credit amortiazation")).arg(QObject::tr("debtor"))+data.Name;
		
        if (bconverted)
        {
		    data_o.descr+="<br><b><font color=\"red\">"+QObject::tr("Cash automatically converted: from")
					+" "+QString::number(data.count_d)+" "+s_cash_credit
					+" "+QObject::tr("to")+" "
                    +QString::number(d_c_cash)+""+s_cash+"</font></b>";
        }
        else
        {
            data_o.descr = data.descr;
        }
    }

	data_o.date = data.date;
	data_o.currency = s_cash;
	data_o.count_d = d_c_cash;
	add_operation(b, data_o);
	set_data_to_bank(idata, s_cash);
}


Db_dat info_creditor(const QString& Name /*data set credit*/)
{
    Db_dat data;

    QSqlQuery query(QSqlDatabase::database(data_u.NameDB));
		
	query.prepare("select * from creditors where 1");
	query.exec();
	
    while (query.next())
    {
        if (Name == query.value(0).toString())
        {
            data.date = query.value(0).toString();// get data credit
			data.Name = query.value(1).toString();//get name creditor
			data.count_d = query.value(2).toDouble();//get count credit
			data.currency = query.value(3).toString();//get name currency credit
			//data.percent = query.value(4).toInt();//get percent credit
			data.type = query.value(5).toString(); //get type percent credit
			data.descr = query.value(6).toString(); //get description
			
			break;
		}	
	}
	
	return data;
}

void increment_debt()
{
	QSqlQuery query(QSqlDatabase::database(data_u.NameDB));
	
	QDateTime date = QDateTime::currentDateTime();
		
	query.prepare("select * from creditors where percent>0");
	query.exec();
	
    while (query.next())
    {
		QSqlQuery query_in(QSqlDatabase::database(data_u.NameDB));
		QDateTime debt_data = QDateTime::fromString(query.value(7).toString(),
				     get_display_format());//get data last increment
		
		int imonthy=0, i_debet_montsy=0, iY1=0, iY2=0;
		
        if(query.value(5).toString() == "Year")
        {//type debt
		     imonthy = date.date().year();//current year
		     i_debet_montsy = debt_data.date().year();

             if(imonthy<i_debet_montsy)
             {
			     return;//if system data is chenget or credit in future set
             }
        }
        else
        {
            imonthy = date.date().month();//current month
		    i_debet_montsy = debt_data.date().month();
            iY1 = date.date().year();//current year
            iY2 = debt_data.date().year();
        }
		
		double res = (double)(imonthy-i_debet_montsy); //if program all year not running
		
		int res_year = iY1-iY2;
		
        if((res_year<0))
        {
			QMessageBox::information(0,"What You doing!?","Stop change system date.<br>"
					"Or don't set debt in future. :)");
			return;
        }
        else if(res_year >= 0)
        {
            res = (double)(12*res_year+res);
            //zminna RES moge buty i -  i +
            //se dozvolit virahuvati pravilno kilkist
            //misjaziw jaki minuli iz misjazja ostanjogo inkrementu
		}
				
        if (res>0)
        {
			double cur_cr = query.value(2).toDouble();
			double percent = query.value(4).toDouble();
			
			cur_cr+=(double)(res*percent); //increment debt
			
			query_in.prepare("update creditors set count=:count,"
					"date_incr=:date_incr where (date_c=:date_c)");
			query_in.bindValue(":count", cur_cr);
			query_in.bindValue(":date_c", query.value(0).toString());
			query_in.bindValue(":date_incr",date.toString(get_display_format()));
				
            if ( !query_in.exec() )
            {
				qDebug() << query_in.lastError();
				return;
			}
		}
	}
}

QList<data_curs> get_curs_curency()
{
    QList<data_curs> lRet;

    data_curs data;

    QSqlQuery query(QSqlDatabase::database(data_u.NameDBc));
    query.prepare("select * from currency where 1");
    query.exec();
    while (query.next())
    {
        data.name_curency = query.value(0).toString();
        data.curs = query.value(1).toDouble();
        data.b_main = false;
        lRet.append(data);
    }

    query.prepare("select * from primary_currency where 1");
    query.exec();
    QString s;
    while (query.next())
    {
        s = query.value(0).toString();
    }

    for (int i = 0; i < lRet.size(); ++i)
    {
        data = lRet.takeAt(i);

        if(data.name_curency == s)
        {
            data.b_main = true;
		    lRet.insert(0,data);
		    break;
		}
    }

    return lRet;
}

void save_curs(const QList<data_curs>& list)
{
     QSqlQuery query(QSqlDatabase::database(data_u.NameDBc));
     
     QString queryString = "delete from currency where 1";
     if (!query.exec(queryString))
     {
	     qDebug() << "Failed to execute" << queryString;
	     return;
     }
     
     data_curs data;

     for (int i = 0; i < list.size(); ++i)
     {
         data = list.at(i);

         query.prepare("insert into currency (name, rate) "
                        "VALUES (:name, :rate)");

         query.bindValue(":name", data.name_curency);
         query.bindValue(":rate", data.curs);
         if (!query.exec())
         {
             qDebug() << query.lastError();
         }

         if(data.b_main)
         {
             query.prepare("update primary_currency set name=:name where 1");
             query.bindValue(":name", data.name_curency);
             if ( !query.exec() )
             {
                 qDebug() << query.lastError();
             }
         }
      }
}

QString get_password()
{
	QSqlQuery query(QSqlDatabase::database(data_u.NameDB));
	
	query.prepare("select * from bank where 1");
	query.exec();
	QString sdata;
    while (query.next())
    {
        sdata = query.value(2).toString();
    }
	
	return sdata;
}

bool set_password(const QString& password)
{
	QSqlQuery query(QSqlDatabase::database(data_u.NameDB));
	query.prepare("update bank set password=:pass where 1");
	query.bindValue(":pass", password);
	
    if (!query.exec())
    {
		qDebug() << query.lastError();
        return false;
	}
	
	return true;
}

bool check_password(const QString& connectdbName, const QString& password)
{
	QSqlQuery query(QSqlDatabase::database(connectdbName));	
	
	query.prepare("select * from bank where 1");
	query.exec();
	QString pass;
	
    while (query.next())
    {
		pass = query.value(2).toString();
    }
	    
    if (password == pass)
    {
		return true;   
    }
		
	return false;
}

void convert_currency_account(const QString& currency, bool bfirst)
{
	double d_bank;
	QString s_cahs_bank;
	
    if(!get_data_from_bank(d_bank, s_cahs_bank))
    {
		return;
    }
	
    if(currency == s_cahs_bank)
    {
		return;
    }
	
	set_data_to_bank(d_bank, currency);
	
    if(bfirst)
    {
        return;//if this first load program, do not register this operation in database
    }
	
	Db_dat data_o;
	data_o.date = QDateTime::currentDateTime().toString(get_display_format());
	data_o.currency = currency;
	data_o.count_d = d_bank;
	QString s = QString("%1 %2 %3 %4").arg(QObject::tr("Change currency bank from"))
			.arg(s_cahs_bank).arg(QObject::tr("to")).arg(currency);
	data_o.descr = s;
	add_operation(d_bank, data_o,true);
}

double get_rate_main_currency()
{
	QList<data_curs>list = get_curs_curency();
	
	data_curs data;
	double dRet=0;
	
    for(int i=0;i<list.size();i++)
    {
        data = (data_curs)list.at(i);
		
        if(data.b_main)
        {
			dRet = data.curs;
			break;
		}
	}
	
	list.clear();
	
	return dRet;
}

double get_rate_currency(const QString& name)
{
	QList<data_curs>list = get_curs_curency();
	
	data_curs data;
	double dRet=0;
	
    for(int i=0;i<list.size();i++)
    {
		data = (data_curs)list.at(i);
		
        if(name == data.name_curency)
        {
			dRet = data.curs;
			break;
		}
	}
	
	list.clear();
	
	return dRet;
}

QString get_name_main_currency()
{
	QList<data_curs>list = get_curs_curency();
	
	data_curs data;
	QString sRet;
	
    for(int i=0;i<list.size();i++)
    {
		data = (data_curs)list.at(i);
		
        if(data.b_main)
        {
			sRet = data.name_curency;
			break;
		}
	}
	
	list.clear();
	
	return sRet;
}

double convert_currency(double value, const QString& fromUnit1, const QString& toUnit2)
{
	double rate_main = get_rate_main_currency();
	
	double d_rate1 = get_rate_currency(fromUnit1);
	double d_rate2 = get_rate_currency(toUnit2);
	
    if(!d_rate1 || !d_rate2 || !rate_main)
    {
		return 0;
    }
	
	d_rate1 = rate_main/d_rate1;
	d_rate2 = rate_main/d_rate2;
	
	double d_rate = 0;
	
	d_rate = value*d_rate1/d_rate2;
	
	return d_rate;
}

bool create_db_accounts(const QString& connectdbName, const QString& password)
{
	QSqlQuery query(QSqlDatabase::database(connectdbName));
	QString queryString = "create table operation ("
			"date_s varchar,"
			"type_op varchar,"
			"count double(999999999,99),"
			"currency_name varchar,"
			"description mediumtext"
			")";
		
    if (!query.exec(queryString))
    {
		qDebug() << "Failed to execute" << queryString;
		return false;
	}

	queryString = "create table creditors ("
			"date_c varchar,"
			"name_c varchar,"
			"count double(999999999,99),"
			"currency_name varchar,"
			"percent double,"
			"type varchar,"
			"description mediumtext,"
			"date_incr varchar"
			")";
    if (!query.exec(queryString))
    {
		qDebug() << "Failed to execute" << queryString;
		return false;
	}
		
	queryString = "create table bank ("
			"count_c double(99999999999999,99),"
			"currency varchar,"
			"password varchar"
			")";
    if (!query.exec(queryString))
    {
		qDebug() << "Failed to execute" << queryString;
		return false;
	}
	
	QString s = get_name_main_currency();
		
    if (s.isEmpty())
    {
		s = "$";
    }
	
	query.prepare("INSERT INTO bank (count_c, currency, password)"
			"VALUES (:count_c, :currency, :password)");
	query.bindValue(":count_c", "0.00");
	query.bindValue(":currency", s);
	query.bindValue(":password", password);
	
    if (!query.exec())
    {
		qDebug() << "Failed to execute insert operator to BANK table" ;
		return false;
	}
	
	return true;
}

bool create_db_cash_rate(const QString& connectdbName)
{
	QSqlQuery query(QSqlDatabase::database(connectdbName));
	QString queryString = "create table currency ("
			"name varchar,"
			"rate double(999999999,999999)"
			")";

    if (!query.exec(queryString))
    {
		qDebug() << "Failed to execute" << queryString;
		return false;
	}
	
	query.prepare("INSERT INTO currency (name, rate) VALUES (:name_s, :rate_s)");
	query.bindValue(":name_s", "$");
	query.bindValue(":rate_s", 1);
		
    if (!query.exec())
    {
		qDebug() << "Failed to execute insert operator to CURRENCY table" ;
		return false;
	}
	
	queryString = "create table primary_currency ("
			"name varchar"
			")";
    if (!query.exec(queryString))
    {
		qDebug() << "Failed to execute" << queryString;
		return false;
	}
	
	query.prepare("INSERT INTO primary_currency (name) "
			"VALUES (:name_s)");
	query.bindValue(":name_s","$");
    if (!query.exec())
    {
		qDebug() << "Failed to execute insert operator to PRIMARY_CURRENCY table" ;
		return false;
	}
	
	return true;
}

//debug only
/*void convert_old_DB(const QString& oldDBName, const QString& newDBName, const QString& user, const QString& password)
{
	QSqlDatabase database;
	
	database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName(oldDBName);
	database.open();
	
	QList<Db_dat> lRet;
	Db_dat data;
	
	QSqlQuery query;
	
	QString querystring = "select * from operation where 1";
	
	if (!query.exec(querystring))
	{
		QSqlError er = query.lastError();//"Failed to execute filter: select * from operation where date_s like";
		QMessageBox::critical(0,"", er.text());
		return;
	}
	
	while (query.next())
	{
		data.date = query.value(0).toString();
		
		data.type = query.value(1).toString();//get type operation
		
		double icount = query.value(2).toDouble(); //get count cash operation
		data.count_d = icount;
		//data.currency = QObject::tr("Грв");
		data.descr = query.value(3).toString();//get description operation
                		
		lRet.append(data);
	}

	connectDB(newDBName, user, password);
	//create_db_accounts(newDBName,password);
	//convert_currency_account(QObject::tr("Грв"), true);
	
	for (int i = 0; i < lRet.size(); ++i) {

		Db_dat dat = lRet.at(i);
		
		bool b = false;
		
		if(dat.type == "+ Income")
		{
			b = true;
			dat.type = "income";
		}
		else
		{
			dat.type = "outgoes";
		}
		
		QDateTime date = QDateTime::fromString(dat.date);
		dat.date = date.toString(get_display_format());
		
		add_operation(b, dat);
	}

}*/
// // 
