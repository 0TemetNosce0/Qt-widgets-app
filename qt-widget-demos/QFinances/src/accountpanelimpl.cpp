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

#include "accountpanelimpl.h"
#include "fdatabase.h"

#include <QtGui>

AccountPanelImpl::AccountPanelImpl(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    reload_ui();

    QHeaderView *h = list_curency->header();
    h->setSectionResizeMode(QHeaderView::ResizeToContents);
    h->setSectionsMovable(false);
    list_curency->setDragEnabled(false);

    QDoubleValidator *dv = new QDoubleValidator(0.00, 9999999999.99, 2, this);
    eUnit1->setValidator(dv);
    eUnit2->setReadOnly(true);

    init_connections();
}

void AccountPanelImpl::reload_ui()
{
    retranslateUi(this);

    QStringList labels;
    labels << tr("Currency") << " " <<tr("Rate");
    list_curency->setHeaderLabels(labels);
}

void AccountPanelImpl::load_data(const QString& sHeader,const QList<data_curs>& list)
{
    c_cash_select->clear();
    comboBox1->clear();
    comboBox2->clear();
    list_curency->clear();
    eUnit2->clear();

    //add cash to panel
    QStringList sl = sHeader.split("|");

    bank_cash->setText(sl.at(0)+" "+sl.at(1));
    old_s_cash=s_cash = sl.at(1);
    e_income_cash->setText(sl.at(2));
    e_outgoes_cash->setText(sl.at(3));

    QString s = QString("%1 %2 %3").arg(tr("Income state on:")).arg(sl.at(4)).arg(tr("Year"));
    income_label->setText(s);
    s = QString("%1 %2 %3").arg(tr("Expenses state on:")).arg(sl.at(4)).arg(tr("Year"));
    outgoes_label->setText(s);

    for(int i=0; i<list.size();i++)
    {
        data_curs data = (data_curs)list.at(i);

        c_cash_select->addItem(data.name_curency);
        comboBox1->addItem(data.name_curency);
        comboBox2->addItem(data.name_curency);

        if(data.name_curency == s_cash)
        {
            rate_cash = data.curs;
        }
    }

    QTreeWidgetItem *item = 0;
    for(int i=0; i<list.size();i++)
    {
        data_curs data = (data_curs)list.at(i);
        item = new QTreeWidgetItem();

        double d_rate_currency = rate_cash/data.curs;

        item->setText(0,"1 "+data.name_curency);
        item->setText(1,"=");
        item->setText(2,QString::number(d_rate_currency,'F',6)+" "+s_cash);
        list_curency->addTopLevelItem(item);
    }

    c_cash_select->setCurrentIndex(c_cash_select->findText(s_cash));
}

void AccountPanelImpl::clear_data()
{
    list_curency->clear();
    c_cash_select->clear();
}

void AccountPanelImpl::init_connections()
{
    connect(eUnit1,SIGNAL(textChanged(const QString& )),this,SLOT(slot_edit_change(const QString& )));
    connect(comboBox1,SIGNAL(currentIndexChanged(const QString& )),this,SLOT(slot_unit1_change(const QString&)));
    connect(comboBox2,SIGNAL(currentIndexChanged(const QString& )),this,SLOT(slot_unit2_change(const QString&)));
    connect(c_cash_select,SIGNAL(currentIndexChanged(const QString& )),this,SLOT(slot_main_combo_change(const QString&)));
}

double AccountPanelImpl::get_rate_currency(const QString& name_currency)
{
    QList<QTreeWidgetItem *>list = list_curency->findItems("1 "+name_currency,Qt::MatchFixedString);

    if (list.isEmpty())
    {
        return 0;
    }

    QTreeWidgetItem *item = list.at(0);
    QString s = item->text(2);
    s.remove(" " + s_cash);

    return s.toDouble();
}

void AccountPanelImpl::slot_edit_change(const QString& text)
{
    if (text.isEmpty())
    {
        return;
    }

    QString fromUnit1 = comboBox1->currentText();
    QString toUnit2 = comboBox2->currentText();

    double d_rate = convert_currency(text.toDouble(), fromUnit1, toUnit2);

    eUnit2->setText(QString::number(d_rate,'F',2));
}

void AccountPanelImpl::slot_unit1_change(const QString& text)
{
    QString fromUnit1 = text;
    QString toUnit2 = comboBox2->currentText();

    double d_rate = eUnit1->text().toDouble();

    if(!d_rate)
    {
        return;
    }

    d_rate = convert_currency(d_rate, fromUnit1, toUnit2);
    eUnit2->setText(QString::number(d_rate,'F',2));
}

void AccountPanelImpl::slot_unit2_change(const QString& text)
{
    QString fromUnit1 = comboBox1->currentText();
    QString toUnit2 = text;

    double d_rate = eUnit1->text().toDouble();

    if(!d_rate)
    {
        return;
    }

    d_rate = convert_currency(d_rate, fromUnit1, toUnit2);
    eUnit2->setText(QString::number(d_rate,'F',2));
}

void AccountPanelImpl::slot_main_combo_change(const QString& text)
{
    double d_rate2 = get_rate_currency(text);
    double d_rate1 = get_rate_currency(old_s_cash);

    if(!d_rate1 || !d_rate2)
    {
        return;
    }

    QString sMainCash = bank_cash->text();
    QString s_income_cash = e_income_cash->text();
    QString s_outgoes_cash = e_outgoes_cash->text();

    sMainCash.remove(" "+old_s_cash);
    s_income_cash.remove(" "+old_s_cash);
    s_outgoes_cash.remove(" "+old_s_cash);

    double dMainCash = sMainCash.toDouble();
    double d_income_cash = s_income_cash.toDouble();
    double d_outgoes_cash = s_outgoes_cash.toDouble();

    dMainCash *= d_rate1/d_rate2;
    d_income_cash *= d_rate1/d_rate2;
    d_outgoes_cash *= d_rate1/d_rate2;

    sMainCash = QString::number(dMainCash,'F',2);
    s_income_cash = QString::number(d_income_cash,'F',2);
    s_outgoes_cash = QString::number(d_outgoes_cash,'F',2);

    bank_cash->setText(sMainCash+" "+text);
    e_income_cash->setText(s_income_cash+" "+text);
    e_outgoes_cash->setText(s_outgoes_cash+" "+text);

    old_s_cash = text;
}
