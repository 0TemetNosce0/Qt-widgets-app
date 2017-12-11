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

#include "preferencesdlgImpl.h"
#include "fdatabase.h"

#include <QSettings>
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>


/////////////////////parameters dialog/////////////////////////////////////////
CurrencyDlg::CurrencyDlg(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("New currency"));

    QPushButton *okBtn = new QPushButton(tr("OK"));
    QPushButton *cancelBtn = new QPushButton(tr("Cancel"));

    m_name = new QLineEdit(this);
    m_rate = new QLineEdit(this);
    m_rate->setValidator(new QDoubleValidator(0.00,99999.99,2,this));

    QLabel *lab_name = new QLabel(tr("Name currency:"), this);
    QLabel *lab_rate = new QLabel(tr("Rate:"), this);

    connect(okBtn,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(reject()));

    QGridLayout *gLayout = new QGridLayout(this);
    gLayout->addWidget(lab_name,0,0 );
    gLayout->addWidget(m_name,0,1);
    gLayout->addWidget(okBtn,0,2);
    gLayout->addWidget(lab_rate,1,0,Qt::AlignRight);
    gLayout->addWidget(m_rate,1,1);
    gLayout->addWidget(cancelBtn,1,2);
    setLayout(gLayout);

    setMinimumSize(QSize(425, 115));
    setMaximumSize(QSize(425, 115));
}

void CurrencyDlg::set_data(const QString& name, const QString& rate)
{
    m_name->setText(name);
    m_name->setReadOnly(true);
    m_rate->setText(rate);

    setWindowTitle(tr("Change currency rate"));
}

bool CurrencyDlg::get_data(QString& name, QString& rate)
{
    name = m_name->text().simplified();
    rate = m_rate->text().simplified();

    if (name.isEmpty() || rate.isEmpty())
    {
       return false;
    }

    return true;
}


////////////////////////////////////////////////////////////////////

const char* PreferencesDlgImpl::company = "UaDevLab";
const char* PreferencesDlgImpl::key = "myfinances";

PreferencesDlgImpl::PreferencesDlgImpl(bool bfirs_show, QWidget *parent)
    : QDialog(parent)
    , bfirst(bfirs_show)
{
    setupUi(this);

    currencylist->setAllColumnsShowFocus(true);
    currencylist->setAlternatingRowColors(true);
    QStringList labels;
    labels << tr("Name currency") << tr("Rate");
    currencylist->setHeaderLabels(labels);
    
    QList<data_curs>listc = get_curs_curency();
   
    QTreeWidgetItem *pItem = new QTreeWidgetItem;
        
    for(int i=0;i<listc.size();i++)
    {
        data_curs d = (data_curs)listc.at(i);

        if(d.b_main)
        {
            pItem->setText(0,d.name_curency);
        }
        else
        {
            QTreeWidgetItem *item = new QTreeWidgetItem;
            item->setText(0,d.name_curency);
            item->setText(1,QString::number(d.curs,'F',6));
            pItem->addChild(item);
        }

	    currencyCombo->addItem(d.name_curency);
    }

    double* d = new double;
    QString s;
    
    get_data_from_bank(*d, s);
    delete d;
    
    currencyCombo->setCurrentIndex(currencyCombo->findText(s));
    
    currencylist->insertTopLevelItem(0,pItem);
    currencylist->expandItem(pItem);
        
    listc.clear();
    
    QDir dir(documentsDir()+"lang");
    dir.setNameFilters(QStringList () << "*.qm");
    QFileInfoList list = dir.entryInfoList();
    QStringList list1;
    list1<< "English";
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);

        if(fileInfo.baseName().left(3) != "qt_")
        {
            list1 += fileInfo.baseName();
        }
    }

    comboBox->addItems(list1);

    QSettings settings(PreferencesDlgImpl::company, PreferencesDlgImpl::key);
    old_lang = settings.value("lang",QString("English")).toString();
    comboBox->setCurrentIndex(comboBox->findText(old_lang));
    
    connect(okBtn, SIGNAL(clicked()), this, SLOT(slot_ok()));
    connect(addBtn, SIGNAL(clicked()), this, SLOT(slot_add_currency()));
    connect(remBtn, SIGNAL(clicked()), this, SLOT(slot_rem_currency()));
    connect(changeBtn, SIGNAL(clicked()), this, SLOT(slot_ch_currency()));
    connect(setmBtn, SIGNAL(clicked()), this, SLOT(slot_set_main_currency()));
    
    if (bfirs_show)
    {
        tabWidget->setCurrentIndex(1);
        label_3->setVisible(false);
        eold_pass->setVisible(false);
		label_4->setText(tr("Password"));
	}
}

void PreferencesDlgImpl::slot_ok()
{
    QTreeWidgetItem *pItem = currencylist->topLevelItem(0);
    
    if (!pItem)
    {
        QMessageBox::critical(this,tr("Fatal error"),tr("Database currency is corrupted."));
        reject();
    }

    QList<data_curs> list;
    
    data_curs data;
    data.b_main = true;
    data.name_curency = pItem->text(0);
    data.curs = 1;
    list.append(data);

    for(int i=0; i<pItem->childCount(); i++)
    {
        QTreeWidgetItem* item = pItem->child(i);
        data.name_curency = item->text(0);
        data.curs = item->text(1).toDouble();
        data.b_main = false;
        list.append(data);
    }

    save_curs(list);
    list.clear();

    QString name = comboBox->currentText();

    if (name != old_lang)
    {
        QSettings settings(PreferencesDlgImpl::company, PreferencesDlgImpl::key);
        settings.setValue("lang", name);
    }

    name = currencyCombo->currentText();
    convert_currency_account(name,bfirst);
    
    QString s1 = eold_pass->text();
    QString s2 = enew_pass1->text();
    QString s3 = enew_pass2->text();
    
    if (!(s1.isEmpty()) || !(s2.isEmpty()) || !(s3.isEmpty()))
    {
        if(s1 != get_password())
        {
            QMessageBox::critical(this, tr("Error password"), tr("Old password is incorrect."));
            return;
        }

        if (s2 != s3)
        {
            QMessageBox::critical(this, tr("Error password"), tr("Passwords is not equable.."));
            return;
	    }
	    
	    set_password(s2);
    }
    
    accept();
}

void PreferencesDlgImpl::slot_add_currency()
{
    CurrencyDlg *dlg = new CurrencyDlg(this);

    dlg->exec();
    QString s1,s2;
    bool res = dlg->get_data(s1,s2);
    delete dlg;

    if ((QDialog::Accepted != dlg->result()) || !res)
    {
        return;
    }
    
    QTreeWidgetItem *pTreeWidgetItem =currencylist->topLevelItem(0);
    if (!pTreeWidgetItem)
    {
        QMessageBox::critical(this,tr("Fatal error"),tr("Database currency is corrupted."));
	    return;
    }

    int ifind = currencyCombo->findText(s1);

    if (ifind < 0)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(pTreeWidgetItem);
        item->setText(0,s1);
        item->setText(1,s2);
        pTreeWidgetItem->addChild(item);
        currencyCombo->addItem(s1);
    }
    else
    {
        QMessageBox::information(this,tr("Currency"),
                                     tr("Currency <b>%1</b> is really exist").arg(s1));
    }
}

void PreferencesDlgImpl::slot_rem_currency()
{
    QTreeWidgetItem *item = currencylist->currentItem();
    
    if ( !item || !item->parent()) {
	    return;
    }

    int ifind, i = QMessageBox::question(this, tr("Delete cash"),
                                tr("Confirm delete currency <b>%1</b>?").arg(item->text(0)),
                                QMessageBox::Yes | QMessageBox::No);

    if ((i == QMessageBox::Yes) && (ifind = currencyCombo->findText(item->text(0))) >= 0)
    {
        currencyCombo->removeItem(ifind);
        delete item;
    }
}

void PreferencesDlgImpl::slot_ch_currency()
{    
	QTreeWidgetItem *item = currencylist->currentItem();

    if (!item || !item->parent())
    {
		return;
    }

    CurrencyDlg *dlg = new CurrencyDlg(this);
	
    QString s1,s2;

    dlg->set_data(item->text(0),item->text(1));
	dlg->exec();

    if (QDialog::Accepted == dlg->result() && dlg->get_data(s1,s2))
    {
        item->setText(0,s1);
        item->setText(1,s2);
    }

	delete dlg;
}

void PreferencesDlgImpl::slot_set_main_currency()
{
	QTreeWidgetItem *pitem = currencylist->currentItem();

    if (!pitem || !pitem->parent())
    {
		return;
    }

    QTreeWidgetItem *mItem = pitem->parent();
	
    double rdata = pitem->text(1).toDouble();
	pitem->setText(1,"");
	
	currencylist->takeTopLevelItem(0);
	
	int cIndex = mItem->indexOfChild(pitem);
	mItem->takeChild(cIndex);
	
	currencylist->insertTopLevelItem(0,pitem);
	
	pitem->addChild(mItem);
	double d = 1/rdata;
    mItem->setText(1,QString::number(d,'F',6));
	
	int i = 0;
	
    while (mItem->childCount() > 0)
    {
		QTreeWidgetItem* chItem = mItem->takeChild(i);
		
        double dt = chItem->text(1).toDouble();
		dt /= rdata;
        chItem->setText(1,QString::number(dt,'F',6));
				
		pitem->addChild(chItem);
	}
	
	currencylist->expandItem(pitem);
}
