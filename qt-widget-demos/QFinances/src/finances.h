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


#ifndef GELD2C_H
#define GELD2C_H

#include <QtWidgets/QDialog>
#include <QMainWindow>

class QTextBrowser;
class QPrinter;
class QCheckBox;

class PrintDialog : public QDialog
{
	Q_OBJECT
	public:
		PrintDialog(const QString& src, QWidget* parent=0);
		~PrintDialog();
	public slots:
		void slot_print();
		void slot_print_preview();
		void printPreview(QPrinter *printer);
		void slot_print_to_file();
		void slot_close();
	private:
		QTextBrowser *ptxtBrowser;
		QString srcTxt;
		QCheckBox *bchek;
};

#include "dockwidg.h"
#include "topheader.h"
#include "accountpanelimpl.h"
#include "fdatabase.h"

class QTreeWidget;
class QToolButton;
class QTranslator;
class HelpBrowser;
class MyTransactionsList;
class TitleBar;

class Finances : public QMainWindow
{
      Q_OBJECT
public:
    Finances(QTranslator *tarnslator, QTranslator *qt_translator, bool bnew = false);
    ~Finances();
	
    void set_lang();

public slots:
    void add_op();
    void del_ac();
    void new_ac();
    void info_credit();

private:
    void init_connections();
    void create_gui();
    void load_list_operation(QList<Db_dat>& list, const QString& sHeader);
    void create_dock_widgets();
    QString format_doc_to_print();
    void load_data_ui();
               
    TopHeader *topw;
    MyTransactionsList *listTransactions;
    DockWidg *toolsDlg;
    AccountPanelImpl *accountPanel;
    HelpBrowser *helpB;
    QDockWidget *dock1;
    QDockWidget *dock2;
    QDockWidget *dock3;
    TitleBar *title1;
    TitleBar *title2;
    TitleBar *title3;
    QAction *aSelYer;
    QAction *aCusFlt;
    QAction *aResFlt;
    QAction *aAbFn;
    QAction *aAbQt;

    int iYear;

    QString nameDB;
    //buttos
    QToolButton* addBtn;
    QToolButton* viewT;
    QToolButton* printT;
    QToolButton* confBtn;
    QToolButton* helpBtn;
    bool b_show_first_conf_dlg;
	QTranslator *ltr;
	QTranslator *qttr;

private slots:
    void reset_filter(const QString& sYear = "current");
    void show_configDlg();
    void set_filter();
    void slot_print();
    void set_custom_filter();
    void slot_about();
    void slot_qt();
protected:
    void showEvent( QShowEvent * event );
};

#endif
