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

#include "mortgagordlgimpl.h"
#include "fdatabase.h"

#include <QtWidgets/QMessageBox>
#include <QGroupBox>

MortgagorDlgImpl::MortgagorDlgImpl(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    dateTimeEdit->setMinimumDate(QDate::currentDate().addDays(-365));
	dateTimeEdit->setMaximumDate(QDate::currentDate().addDays(365));
	
	dateTimeEdit->setMinimumTime(QTime::currentTime().addMSecs(70));
	dateTimeEdit->setMaximumTime(QTime::currentTime().addMSecs(70));
	
	dateTimeEdit->setDateTime(QDateTime::currentDateTime());
	
	dateTimeEdit->setDisplayFormat(get_display_format());
    //groupBox->setShown(false);
	
	QString name_currency;
	double d;
	get_data_from_bank(d, name_currency);
	
	count_cr->setSuffix(name_currency);
	
	connect(okBtn, SIGNAL(clicked()), this, SLOT(slot_ok()));
}


MortgagorDlgImpl::~MortgagorDlgImpl()
{

}

void MortgagorDlgImpl::slot_ok()
{    
    if (!count_cr->value())
    {
        QMessageBox::information(this,tr("info"),tr("Please enter count mortgagor"));
        return;
    }
    
    if (name_debtor_e->text().isEmpty())
    {
        QMessageBox::information(this,tr("info"),tr("Please enter name mortgagor"));
	    return;
    }

    accept();
}

void MortgagorDlgImpl::set_info_data(const QString& sdata)
{
    Db_dat data = info_creditor(sdata);

    dateTimeEdit->setDateTime(QDateTime::fromString(data.date,get_display_format()));

    name_debtor_e->setReadOnly(true);
    count_cr->setReadOnly(true);
    textEdit->setReadOnly(true);

    okBtn->setVisible(false);
    percent_spin->setVisible(false);
    label_3->setVisible(false);

	name_debtor_e->setText(data.Name);
	count_cr->setSuffix(data.currency);
	count_cr->setValue(data.count_d);
	textEdit->setText(data.descr);
	
    if(data.type == "Year")
    {
	   typeBox->setCurrentIndex(1);
    }
    else
    {
	   typeBox->setCurrentIndex(0);
    }

    canBtn->setText(tr("Close"));
    setWindowTitle(tr("Info mortgagor"));
}

Db_dat MortgagorDlgImpl::get_data()
{
	Db_dat data;
	data.date = dateTimeEdit->dateTime().toString(get_display_format());
	data.date_incr = data.date;
	data.count_d = count_cr->value();
	data.Name = name_debtor_e->text();
	data.currency = count_cr->suffix();
	int i = percent_spin->value();
	double res = (double)data.count_d*i/100;//calculate parcent
	data.percent = res;
	
	QString s = typeBox->currentText();
	
    if(s == tr("Year"))
    {
		s = "Year";
    }
    else
    {
		s = "Month";
    }

	data.type = s;
	
	s = textEdit->toPlainText();
	QString s_h = "<b>%1</b> <b>%2:</b>";
	
	QString format = s_h.arg(tr("Credit")).arg(tr("debtor"))
			+data.Name+QString("<br><font color=\"blue\"><b>%1:</b></font><br>")
			.arg(tr("Info"))+" "
			+QString("<b>%1:</b> %2<br><b>%3:</b> %4 %<br><b>%5:</b> %6")
			.arg(tr("Percent stake")).arg(QString::number(res,'g'))
			.arg(tr("Percent")).arg(QString::number(i))
			.arg(tr("Count borrowing")).arg(QString::number(data.count_d,'F',2))
			+" "+data.currency+"<br>";

    if (!s.isEmpty())
    {
        format += QString("<b>%1:</b> %2").arg(tr("Note")).arg(s);
    }

	data.descr = format;		
	
	return data;
}
