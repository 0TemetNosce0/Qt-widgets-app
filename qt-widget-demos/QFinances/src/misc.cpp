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

#include "misc.h"
#include "fdatabase.h"
#include <QSqlDatabase>
#include <QtWidgets/QMessageBox>
#include <QDebug>
#include <QFile>
#include <QDir>

//btype - connect to account or currency
bool connectDB(QString const& dbName, const QString& user, const QString& passwrd, bool btype)
{
	QSqlDatabase database;
	
    if( QSqlDatabase::database().databaseName() != dbName)
    {
        database = QSqlDatabase::addDatabase("QSQLITE", dbName);
		database.setDatabaseName(dbName);
		database.setUserName(user);
		database.setPassword(passwrd);
    }
    else
    {
        database = QSqlDatabase::database();
        if (database.isOpen())
        {
			return true;
        }
    }

    if (!database.open())
    {
        QMessageBox::critical(0, "MyFinances",
				      QObject::tr("Unable to establish a database connection.")+"\n"+
                              QObject::tr("MyFinances needs SQLite support. Please read "
						      "the Qt SQL driver documentation for information how "
						      "to build it."), QMessageBox::Cancel,
	    QMessageBox::NoButton);
		
		database = QSqlDatabase();
		QSqlDatabase::removeDatabase(dbName);
				
		return false;
	}

	QStringList tabl = database.tables(); //get count tables database
	
		
    if (btype)
    {
        if (tabl.size() == 3)
        {
            if ( !check_password(dbName,passwrd))
            {
                QMessageBox::critical(0, "MyFinances",QObject::tr("Access denieded. Password incorrect"));
				return false;
			}			
			return true;
		}

        if (!create_db_accounts(dbName,passwrd))
        {
            return false;
        }
    }
    else
    {
        if (tabl.size() == 2)
        {
            return true;
        }
		
        if (!create_db_cash_rate(dbName))
        {
			return false;
        }
	}	

    return true;
}

QString documentsDir()
{
    QString documents("myFinances");
    QDir home = QDir::home();
    home.setFilter(QDir::Files);

    if(!home.exists(documents) && !home.mkdir(documents))
    {
        QMessageBox::critical(0, "MyFinances",QObject::tr("Can't create documents directory"));
        return QString("");
    }

    home.cd(documents);

    return home.absolutePath() + "/";
}

QString stringFromResource(const QString &resName)
{
	QFile file(resName);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream ts(&file);
	return ts.readAll();
}
