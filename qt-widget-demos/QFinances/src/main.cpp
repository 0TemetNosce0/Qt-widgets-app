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


#include <QtWidgets/QApplication>
#include <QSettings>
#include <QTranslator>
#include <QDir>

#include "finances.h"
#include "parametersdlgimpl.h"
#include "preferencesdlgImpl.h"

int main(int argc, char *argv[])
{
  Q_INIT_RESOURCE(application);
  QApplication app(argc, argv);

  QLocale::setDefault(QLocale::c());

  int return_code = -1;

  QString s_db_cash = documentsDir()+"qcashdata.db";

  if(!connectDB(s_db_cash, "","",false)) {
      QSqlDatabase::database(s_db_cash).close();
      QSqlDatabase::removeDatabase(s_db_cash);
      return return_code;
  }

  forever {
      QSettings settings( PreferencesDlgImpl::company, PreferencesDlgImpl::key );
      QString s = settings.value("lang").toString();
      QString s1 = documentsDir()+"lang";

      QTranslator *trans = new QTranslator;
      trans->load(s+".qm",s1);
      QTranslator *qttr = new QTranslator;

      if(s == "German") {
        s = "Deutsch";
      }

      qttr->load("qt_"+s.mid(0,2).toLower()+".qm",s1);
      app.installTranslator(trans);
      app.installTranslator(qttr);

      app.setStyle("plastique");

      QString name, password;
      QDir dir(documentsDir());

      dir.setFilter(QDir::Files);
      dir.setNameFilters(QStringList () << "*.db");
      QFileInfoList list = dir.entryInfoList();

      QStringList list1;
      for (int i = 0; i < list.size(); ++i) {
         QFileInfo fileInfo = list.at(i);
         if(fileInfo.baseName() != "qcashdata") {
             list1 += fileInfo.baseName();
         }
       }

      ParametersDlgImpl *logdlg = new ParametersDlgImpl();
      logdlg->setStyleSheet(stringFromResource(":/style/style.qss"));
      logdlg->set_data(list1);
      logdlg->exec();
      if(QDialog::Accepted != logdlg->result()) {
          return_code = 0;
          break;
      }

      logdlg->get_data(name,password);
      bool bnew = logdlg->is_new_account();

      delete logdlg;
      QString path_db = documentsDir()+name+".db";

      user_data data_u;
      data_u.NameDBc = s_db_cash;
      data_u.NameDB = path_db;
      set_user_data(data_u);//set names basedate: cash and operation, for query objects

      if (!connectDB(path_db, name, password)) {
          QSqlDatabase::database(path_db).close();
          QSqlDatabase::removeDatabase(path_db);
          continue;
      }

      increment_debt();

      Finances *wv = new Finances(trans, qttr, bnew);
      wv->setStyleSheet(stringFromResource(":/style/style.qss"));
      wv->setMinimumSize(1024,768);
      wv->showMaximized();

      return_code = app.exec();

      delete wv;
      delete trans;
      delete qttr;

      QSqlDatabase::database(path_db).close();
      QSqlDatabase::removeDatabase(path_db);
  }

  QSqlDatabase::database(s_db_cash).close();
  QSqlDatabase::removeDatabase(s_db_cash);

  return return_code;
}

