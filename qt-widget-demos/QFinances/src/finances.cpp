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


#include <QTextBrowser>
#include <QDate>
#include <QCheckBox>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QSettings>
#include <QTranslator>
#include <QDockWidget>
#include <QToolButton>
#include <QMenu>
#include <QInputDialog>
#include <QMessageBox>
#include <QShowEvent>

#include "finances.h"
#include "transactiondlgimpl.h"
#include "mortgagordlgimpl.h"
#include "mystatusbar.h"
#include "preferencesdlgImpl.h"
#include "filterdlgimpl.h"
#include "helpbrowser.h"
#include "mytransactionslist.h"
#include "titlebar.h"

/////////////////////////////////////////////////////

PrintDialog::PrintDialog(const QString& src, QWidget* parent)
	:QDialog(parent)
{
	QPushButton *printB = new QPushButton(tr("Print.."));
	QPushButton *printPrv = new QPushButton(tr("Print preview.."));
	QPushButton *saveB = new QPushButton(tr("Save to file.."));
	QPushButton *closeB = new QPushButton(tr("Close"));
	ptxtBrowser = new QTextBrowser;
	bchek = new QCheckBox(tr("Save with images"));
    bchek->setChecked(true);
		
	ptxtBrowser->setText(src);
	srcTxt = src;
	
	connect(printPrv, SIGNAL(clicked()),this, SLOT(slot_print_preview()));
	connect(printB,SIGNAL(clicked()),this,SLOT(slot_print()));
	connect(saveB,SIGNAL(clicked()),this,SLOT(slot_print_to_file()));
	connect(closeB,SIGNAL(clicked()),this,SLOT(slot_close()));
	
	QVBoxLayout *pvbxLayout = new QVBoxLayout;
	QHBoxLayout *phbxLayout = new QHBoxLayout;
	phbxLayout->addWidget(printB);
	phbxLayout->addWidget(printPrv);
	phbxLayout->addStretch(7);
	phbxLayout->addWidget(saveB);
	phbxLayout->addWidget(bchek);
	phbxLayout->addStretch(100);
	phbxLayout->addWidget(closeB);
	pvbxLayout->addWidget(ptxtBrowser);
	pvbxLayout->addLayout(phbxLayout);
	setLayout(pvbxLayout);
	
	setWindowTitle(tr("Preview to print"));
	
	setMinimumSize(750,500);
}

PrintDialog::~PrintDialog()
{
	delete ptxtBrowser;
}

void PrintDialog::slot_print_preview()
{
    #ifndef QT_NO_PRINTER
	QPrinter printer(QPrinter::HighResolution);
	QPrintPreviewDialog preview(&printer, this);
	connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(printPreview(QPrinter *)));
        preview.exec();
    #endif
        accept();

}

void PrintDialog::printPreview(QPrinter *printer)
{
	ptxtBrowser->print(printer);
}

void PrintDialog::slot_print()
{
#ifndef QT_NO_PRINTER
	QPrinter printer;

	QPrintDialog *dialog = new QPrintDialog(&printer, this);
	dialog->setWindowTitle(tr("Print report"));
	
    if (dialog->exec() != QDialog::Accepted) {
		return;
    }

    ptxtBrowser->print(&printer);
#endif

    accept();
}

void PrintDialog::slot_print_to_file()
{
	QString fn = QFileDialog::getSaveFileName(this, tr("Save report..."),
											  QString(), tr("HTML-Files (*.htm *.html)"));
    if (fn.isEmpty()) {
		return;
    }

    if (fn.indexOf(".") == -1) {
		fn+=".html";
    }

    if (bchek->isChecked())	{
        QPixmap pix1(":/img/cash-add.png");
		QPixmap pix2(":/img/cash-delete.png");
				
		QString path = fn.mid(0,fn.lastIndexOf("/"));
		QString name = fn.section("/",-1);
		name.remove(".");
		QDir dir(path);
		dir.mkdir(name+"_files");
								
		pix1.save(dir.path()+"/"+name+"_files/add.png","PNG");
		pix2.save(dir.path()+"/"+name+"_files/rem.png","PNG");
		
		srcTxt.replace(":/img/cash-add.png",name+"_files/add.png");
		srcTxt.replace(":/img/cash-delete.png",name+"_files/rem.png");
    } else {
		srcTxt.remove("<img src=\":/img/cash-add.png\">");
		srcTxt.remove("<img src=\":/img/cash-delete.png\">");
	}
	
	QFile file(fn);
    if (!file.open(QFile::WriteOnly)) {
        return;
    }

	QTextStream ts(&file);
	ts.setCodec(QTextCodec::codecForName("UTF-8"));
	ts << srcTxt;
	file.close();
	
	accept();
}

void PrintDialog::slot_close()
{
	reject();
}


//////////////////////////////////////////////
Finances::Finances(QTranslator *tarnslator, QTranslator *qt_translator, bool bnew)
    :b_show_first_conf_dlg(bnew)
{
    iYear = QDate::currentDate().year();
    create_gui();
    init_connections();
    QSettings settings(PreferencesDlgImpl::company, PreferencesDlgImpl::key);

    if (settings.contains("state")) {
        restoreState(settings.value("state").toByteArray());
    }

    load_data_ui();
    ltr = tarnslator;
    qttr = qt_translator;
    if (!bnew) {
        reset_filter();
    }
}

Finances::~Finances()
{
    QSettings settings(PreferencesDlgImpl::company, PreferencesDlgImpl::key);
    settings.setValue("state",saveState());
	 
    ltr = NULL;
    qttr = NULL;
}

void Finances::set_lang()
{
    QSettings settings(PreferencesDlgImpl::company, PreferencesDlgImpl::key);
    QString s = settings.value("lang",QString("English")).toString();

    //QTranslator trans;
    QString s1 = documentsDir()+"lang";
    qApp->removeTranslator(ltr);
    ltr->load(s+".qm",s1);
    qApp->installTranslator(ltr);
	 
    if(s == "German") {
		 s = "Deutsch";
    }

    qApp->removeTranslator(qttr);
    qttr->load("qt_"+s.mid(0,2).toLower()+".qm",s1);
    qApp->installTranslator(qttr);
	 
    //reload language help
    s1 = documentsDir() + "doc/";
    s1 += s;
    if (!QFile::exists(s1)) {
         s1 = documentsDir()+"doc/English";
    }

    helpB->load_source(s1);

    load_data_ui();
}

void Finances::load_data_ui()
{
    title1->setTitleText(tr("Cash panel"));
    title2->setTitleText(tr("Mortgagors panel"));
    title3->setTitleText(tr("Help browser"));
    dock1->setWindowTitle(tr("Cash panel"));
    dock2->setWindowTitle(tr("Mortgagors panel"));
    dock3->setWindowTitle(tr("Help browser"));

    addBtn->setText(tr("Add operation"));
    viewT->setText(tr("View"));
    printT->setText(tr("Print report"));
    confBtn->setText(tr("Preferences"));
    helpBtn->setText(tr("Help"));

    aSelYer->setText(tr("Select Year transaction"));
    aCusFlt->setText(tr("Custom filter"));
    aResFlt->setText(tr("Reset filter"));
    aAbFn->setText(tr("About myFinaces"));
    aAbQt->setText(tr("About Qt"));

    QStringList labels;
    labels << tr("Type") << tr("Date") << tr("Count") << tr("Description");
    listTransactions->setHeaderLabels(labels);

    toolsDlg->reload_ui();
    accountPanel->reload_ui();
    helpB->reload_ui();

    //reset_filter(QString::number(iYear));
}

void Finances::create_gui()
{
    QDockWidget *dock = new QDockWidget(this);
    dock->setObjectName("Top");
    dock->setFloating(false);
    dock->setTitleBarWidget(new QWidget);
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);

    topw = new TopHeader;
	dock->setWidget(topw);
    addDockWidget(Qt::TopDockWidgetArea, dock);

    listTransactions = new MyTransactionsList(this);
    setCentralWidget(listTransactions);

    //buttos
    addBtn = new QToolButton(topw);
    addBtn->setIcon(QIcon(":/img/add.png"));
    addBtn->setIconSize(QSize(100,100));
    addBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addBtn->setToolTip(tr("Add new finance operation"));
    addBtn->setStatusTip(addBtn->toolTip());
    addBtn->move(280,79);
    addBtn->setFocusPolicy(Qt::NoFocus);
    addBtn->setProperty("kind","toolbar");

    viewT = new QToolButton(topw);
    viewT->setIcon(QIcon(":/img/view.png"));
    viewT->setIconSize(QSize(100,100));
    viewT->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    viewT->setToolTip(tr("Show selected year transactions"));
    viewT->setStatusTip(viewT->toolTip());
    viewT->move(390,79);
    viewT->setProperty("kind","toolbar");

    printT = new QToolButton(topw);
    printT->setIcon(QIcon(":/img/print.png"));
    printT->setIconSize(QSize(100,100));
    printT->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    printT->setToolTip(tr("Print report transaction"));
    printT->setStatusTip(printT->toolTip());
    printT->move(500,79);
    printT->setProperty("kind","toolbar");

    confBtn = new QToolButton(topw);
    confBtn->setIcon(QIcon(":/img/preferences.png"));
    confBtn->setIconSize(QSize(100,100));
    confBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    confBtn->setToolTip(tr("Configure Personal finances"));
    confBtn->setStatusTip(confBtn->toolTip());
    confBtn->move(610,79);
    confBtn->setProperty("kind","toolbar");

    helpBtn = new QToolButton(topw);
    helpBtn->setIcon(QIcon(":/img/help.png"));
    helpBtn->setIconSize(QSize(100,100));
    helpBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    helpBtn->setToolTip(tr("Show about dialog"));
    helpBtn->setStatusTip(helpBtn->toolTip());
    helpBtn->move(720,79);
    helpBtn->setProperty("kind","toolbar");
        
    //actions
    aSelYer = new QAction(this);
    aCusFlt = new QAction(this);
    aResFlt = new QAction(this);
    aAbFn = new QAction(this);
    aAbQt = new QAction(this);

    //menus
    QMenu *menu = new QMenu(this);
    menu->addAction(aSelYer);
    menu->addAction(aCusFlt);
    menu->addAction(aResFlt);
    menu->addSeparator();
    viewT->setMenu(menu);
    viewT->setPopupMode(QToolButton::InstantPopup);

    menu = new QMenu(this);
    menu->addAction(aAbFn);
    menu->addAction(aAbQt);
    helpBtn->setMenu(menu);
    helpBtn->setPopupMode(QToolButton::InstantPopup);
	
    create_dock_widgets();
}

void Finances::add_op()
{
    TransactionDlgImpl *dlg = new TransactionDlgImpl(this);
    dlg->exec();
	
    if (QDialog::Accepted == dlg->result())	{
        Db_dat data;

        data.date = dlg->dateTimeEdit->dateTime().toString(get_display_format());
        data.descr = dlg->textEdit->toPlainText();
        data.count_d = dlg->lineEdit->value();
        add_operation(dlg->isAdded(), data);
        reset_filter(QString::number(iYear));
	}		
    delete dlg;
}

void Finances::del_ac()
{
	QTreeWidgetItem *item = toolsDlg->listCred->currentItem();
	
    if (!item) {
        return;
    }
	
	QString s = QString("%1: %2. %3:").arg(tr("Debtor")).arg(item->text(0)).arg(tr("Currency"));
	
	QString s1 = item->text(1);
    double d1  = 1.00;
	
	QStringList l = s1.split(" ");
	
    if(l.size() == 2) {
	    s += " "+l.at(1);
	    QString s2 = l.at(0);
	    d1 = s2.toDouble();
	}
	
	bool ok;
	double dtext = QInputDialog::getDouble(this, tr("Paying off credit"), s,
					     d1, 1.00, 9999999.99, 2, &ok);
    if (ok)	{
        Db_dat data;
		data.Name = item->text(0);
		data.count_d = dtext;
		data.date = item->text(2);
		set_data_creditor(data);
		
        reset_filter(QString::number(iYear));
		toolsDlg->load_data();
	}
}

void Finances::new_ac()
{
    MortgagorDlgImpl *dlg = new MortgagorDlgImpl(this);
	dlg->exec();	
    if (QDialog::Accepted == dlg->result())	{
        Db_dat data;
        data = dlg->get_data();
        set_data_creditor(data);
        toolsDlg->load_data();
        reset_filter(QString::number(iYear));
    }

    delete dlg;
}

void Finances::show_configDlg()
{
    PreferencesDlgImpl *dlg = new PreferencesDlgImpl(b_show_first_conf_dlg,this);
	dlg->exec();

    if (QDialog::Accepted == dlg->result()) {
        reset_filter(QString::number(iYear));
        set_lang();
    }

	delete dlg;       
}

void Finances::init_connections()
{
    connect(toolsDlg->NewBtn,SIGNAL(clicked()),this,SLOT(new_ac()));
    connect(toolsDlg->infBtn,SIGNAL(clicked()),this,SLOT(info_credit()));
    connect(toolsDlg->RemBtn,SIGNAL(clicked()),this,SLOT(del_ac()));
    connect(toolsDlg->listCred, SIGNAL(itemDoubleClicked(QTreeWidgetItem * , int )), this,
                                                                      SLOT(info_credit()));
    connect(addBtn,SIGNAL(clicked()),this,SLOT(add_op()));
    connect(confBtn,SIGNAL(clicked()),this,SLOT(show_configDlg()));
    connect(printT,SIGNAL(clicked()),this,SLOT(slot_print()));
    //actions
    connect(aSelYer,SIGNAL(triggered()),this,SLOT(set_filter()));
    connect(aCusFlt,SIGNAL(triggered()),this,SLOT(set_custom_filter()));
    connect(aResFlt,SIGNAL(triggered()),this,SLOT(reset_filter()));
    connect(aAbFn,SIGNAL(triggered()),this,SLOT(slot_about()));
    connect(aAbQt,SIGNAL(triggered()),this,SLOT(slot_qt()));
}

void Finances::info_credit()
{
    QTreeWidgetItem *item = toolsDlg->listCred->currentItem();	
    if (!item) {
        return;
    }
        
    MortgagorDlgImpl *dlg = new MortgagorDlgImpl(this);
    dlg->set_info_data(item->text(2));
    dlg->exec();
    delete dlg;
}

void Finances::reset_filter(const QString& sYear)
{
    QString s = sYear;
    if(s == "current") {
        QDate date = QDate::currentDate();
        iYear = date.year();
        s = QString::number(iYear);
    }

    QString sHeader;
    QList<Db_dat> list;
    
    sHeader = load_data_from_operation(list,s)+"|"+s;
    
    QList<data_curs> list_cur = get_curs_curency();

    accountPanel->load_data(sHeader, list_cur);
    list_cur.clear();
    s  = QString("%1 %2 %3").arg(tr("New")).arg(iYear).arg(tr("finance year"));
    load_list_operation(list,s);
}

void Finances::set_filter()
{
    bool ok;
    iYear = QInputDialog::getInt(this, tr("Filter"), tr("Select Year transaction"), iYear, 1900,
                                           2147483647, 1, &ok);
    if (ok)	{
        QString s = QString::number(iYear);
        reset_filter(s);
    }
}

void Finances::slot_print()
{
    QString s = format_doc_to_print();
    PrintDialog *dlg = new PrintDialog(s,this);
    dlg->exec();
    delete dlg;
}

void Finances::set_custom_filter()
{
	FilterDlgImpl *dlg = new FilterDlgImpl(this);
	dlg->exec();
    if(QDialog::Accepted != dlg->result()) {
        return;
    }
	
    QString query = dlg->get_filter_data();
	delete dlg;
	
    if(query.isEmpty()) {
		return;
    }
	
    listTransactions->clear();
		
	QList<Db_dat> list;
	
	bool bRet = false;
	
    list = load_operation_with_filter(query, bRet);
	
	Db_dat dat;
    if( !bRet && !list.isEmpty()) {
        dat = list.at(0);
        QMessageBox::about(this, tr("Information"), dat.descr);
        return;
	}
	
    if(query == " 1") {
        query = tr(" All years");
    }
	
    query = QString("%1 %2").arg(tr("Show operations with custom filter:")).arg(query);
    load_list_operation(list,query);
}

void Finances::showEvent( QShowEvent * event )
{
    if (b_show_first_conf_dlg) {
        show_configDlg();
    }

	b_show_first_conf_dlg=false;
	event->accept();
}

void Finances::load_list_operation(QList<Db_dat>& list, const QString& sHeader)
{
    listTransactions->clear();
    
    QTreeWidgetItem *item = new QTreeWidgetItem(SYS_TYPE);
    QString s;
    item->setText(3,sHeader);
    listTransactions->addTopLevelItem(item);

    for (int i = 0; i < list.size(); ++i) {
        Db_dat dat = list.at(i);
        if(dat.type == "sys") {
            item = new QTreeWidgetItem(SYS_TYPE);
            item->setText(1,convert_date_format(dat.date));
            item->setText(3,dat.descr);
            item->setToolTip(3,dat.descr);
            listTransactions->addTopLevelItem(item);
            continue;
        } else if(dat.type == "income") {
            item = new QTreeWidgetItem(INC_TYPE);
            item->setIcon(0, QIcon(":/img/cash-add.png"));
            s = tr("Income");
            item->setText(0,s);
            item->setToolTip(0,s);
        } else if(dat.type == "outgoes") {
            item = new QTreeWidgetItem(EXC_TYPE);
            item->setIcon(0, QIcon(":/img/cash-delete.png"));
            s = tr("Expense");
        }

        item->setText(1,convert_date_format(dat.date));
        item->setText(0,s);
        item->setToolTip(0,s);
		
        item->setTextColor(0,QColor(Qt::blue));
        item->setTextColor(1,QColor("#5D77B6"));
        QFont f(QApplication::font().family(), (int)(QApplication::font().pointSizeF()), QFont::Bold);
        item->setFont(2,f);
        s = QString::number(dat.count_d,'F' ,2)+" "+dat.currency;

        if(dat.count_d) {
            item->setText(2,s);
            item->setToolTip(2,s);
        }
		
        item->setText(3,dat.descr);
        item->setToolTip(3,dat.descr);

        listTransactions->addTopLevelItem(item);
    }
       
    listTransactions->resizeColumnToContents(0);
    listTransactions->resizeColumnToContents(1);
    listTransactions->resizeColumnToContents(2);
    listTransactions->setColumnWidth(0,listTransactions->columnWidth(0)+20);
    listTransactions->setColumnWidth(1,listTransactions->columnWidth(1)+30);
    listTransactions->setColumnWidth(2,listTransactions->columnWidth(2)+20);
	
    list.clear();
}

void Finances::slot_about()
{
	QMessageBox::about(this,
		tr("About myFinances"),
                tr("<b>myFinances 1.0.1.qt5 PE </b> - personal home finances manager.<br>") +
                tr("Copyright (C) 2008-2015 Peter Komar"));
}


/*!
    \fn Finances::slot_qt()
 */
void Finances::slot_qt()
{
    QMessageBox::aboutQt(this,"myFinances");
}


/*!
    \fn Finances::create_dock_widgets()
 */
void Finances::create_dock_widgets()
{
    dock1 = new QDockWidget(this);
    dock1->setObjectName("Account_panel");
    dock1->setAllowedAreas(Qt::BottomDockWidgetArea);

    accountPanel = new AccountPanelImpl;
    title1 = new TitleBar(dock1);
    dock1->setTitleBarWidget(title1);
    dock1->setWidget(accountPanel);
    dock1->setMaximumHeight(280);
    dock1->setMinimumWidth(500);
    addDockWidget(Qt::BottomDockWidgetArea, dock1);
    viewT->menu()->addAction(dock1->toggleViewAction());

    dock2 = new QDockWidget(this);
    dock2->setObjectName("Mortgagors panel");
    dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);

    toolsDlg = new DockWidg;
    title2 = new TitleBar(dock2);
    dock2->setTitleBarWidget(title2);
    dock2->setWidget(toolsDlg);
    dock2->setMinimumWidth(450);
    addDockWidget(Qt::BottomDockWidgetArea, dock2);
    viewT->menu()->addAction(dock2->toggleViewAction());

    dock3 = new QDockWidget(tr("Help browser"),this);
    dock3->setObjectName("Help browser");
    dock3->setAllowedAreas(Qt::NoDockWidgetArea);

    title3 = new TitleBar(dock3);
    dock3->setTitleBarWidget(title3);

    QSettings settings(PreferencesDlgImpl::company, PreferencesDlgImpl::key);
    QString s1 = documentsDir()+"doc/";
    s1 += settings.value("lang",QString("English")).toString();

    if (!QFile::exists(s1)) {
        s1 = documentsDir()+"doc/English";
    }

    helpB = new HelpBrowser(dock3);
    helpB->load_source(s1);
    dock3->setWidget(helpB);
    addDockWidget(Qt::RightDockWidgetArea, dock3);
    helpBtn->menu()->addAction(dock3->toggleViewAction());

    dock3->setMinimumWidth(450);
}

QString Finances::format_doc_to_print()
{
	QString sret = "<html><head>";
	sret += "<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\">";
	sret +=	"</head><title>";
    QTreeWidgetItem *item =  listTransactions->topLevelItem(0);
	QString s = item->text(3);
	s.replace("<", "&lt;"); 
	s.replace(">", "&gt;"); 
	sret += s;
	sret += "</title>\n<body>";
	sret += "<table BORDER=1><tr><th COLSPAN=4 BGCOLOR=\"#6799B3\"><font color=\"white\">"+s+"</font></th></tr>\n";
	sret += "<tr BGCOLOR=\"#ebf5f5\"><th>"+tr("Type")+"</th><th>"+tr("Date")+"</th><th>"
			+tr("Count")+"</th><th>"+tr("Description")+"</th></tr>";
	
    for(int i = 1; i < listTransactions->topLevelItemCount();i++)	{
        item =  listTransactions->topLevelItem(i);
        if(item->text(0) == tr("Income")) {
			sret += "<tr BGCOLOR=\"#B8FFBB\">";
			sret += "<td WIDTH=10%><font color=\"blue\"><img src=\":/img/cash-add.png\">";
        } else if(item->text(0) == tr("Expense")) {
			sret += "<tr BGCOLOR=\"#FFFFDE\">";
			sret += "<td WIDTH=10%><font color=\"blue\"><img src=\":/img/cash-delete.png\">";
        } else {
			sret += "<tr BGCOLOR=\"#6799B3\">";
			sret += "<th COLSPAN=2><font color=\"#fff\">"+item->text(1)+"</font></th>\n";
			sret += "<th COLSPAN=2><font color=\"#fff\">"+item->text(3)+"</font></th>\n";
			sret += "</tr>";
			continue;
		}

		sret += item->text(0)+"</font></td>\n";
		sret += "<td WIDTH=15%><font color=\"#5D77B6\">"+item->text(1)+"</font></td>\n";
		sret += "<td WIDTH=15%><font face=\""+QApplication::font().family()+"\"><b>"+item->text(2)+"</b></font></td>\n";
		sret += "<td WIDTH=60%>"+item->text(3)+"</td>\n";
		sret += "</tr>";
	}
	
	sret += "</table>";
	sret += "</body></html>";
	
	return sret;
}
