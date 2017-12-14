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

#include "filterdlgimpl.h"
#include "fdatabase.h"
#include "querytable.h"

#include <QtGui>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

FilterDlgImpl::FilterDlgImpl(QWidget* parent)
    : QDialog(parent)
{
    _setupUi();
	
    m_query->setRootIsDecorated(false);
    m_query->setSelectionMode(QAbstractItemView::NoSelection);
	
	QStandardItemModel *model = new QStandardItemModel(0, 5, this);

	model->setHeaderData(0, Qt::Horizontal, QObject::tr("Column"));
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("Condition1"));
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("Pattern1"));
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("Condition2"));
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("Pattern2"));
	
	model->insertRow(0);
	model->insertRow(1);
	model->insertRow(2);
	model->setData(model->index(0, 0), tr("Date"));
	model->setData(model->index(0, 1), "=");
	model->setData(model->index(1, 0), tr("Count"));
	model->setData(model->index(1, 1), "=");
	model->setData(model->index(2, 0), tr("Description"));
		
    m_query->setModel(model);
		
    setMinimumSize(680,100);
}


FilterDlgImpl::~FilterDlgImpl()
{
}

void FilterDlgImpl::slot_filter()
{
	/*int flags = 0;
	flags |= (date_check->isChecked()) << 1;
	if(date_check->isChecked())
	   flags |= (whole_check_date->isChecked()) << 2;
	
	flags |= (count_check->isChecked()) << 3;
	if(count_check->isChecked())
	{
	    s = comboBox1->currentText();
	    
	    if(s == "<")
		    flags |= 1 << 4;
	    else if(s == "<=")
		    flags |= 1 << 5;
	    else if(s == ">")
		    flags |= 1 << 6;
	    else if(s == ">=")
		    flags |= 1 << 7;
	    else if(s == "=")
		    flags |= 1 << 8;
	    s = comboBox2->currentText();
	    
	    if(!s.isEmpty() && !linefind2->text().isEmpty())
	    {
		 if(s == "<")
		    flags |= 1 << 9;
	         else if(s == "<=")
		    flags |= 1 << 10;
	         else if(s == ">")
		    flags |= 1 << 11;
	         else if(s == ">=")
		    flags |= 1 << 12;
	    }
	}
	*/
	
    QStandardItemModel* model = (QStandardItemModel*)m_query->model();
	
	QString qery, sCondition1;
    int icur = m_typeTrasnaction->currentIndex();
	
    if( icur == 1 ) {
		qery = "(type_op like 'income')";
    } else if( icur == 2 ) {
        qery += " and (type_op like 'outgoes')";
    }

    //get date item
    sCondition1 = model->data(model->index(0,1), Qt::EditRole).toString();
    QString sPattern1 = model->data(model->index(0,2), Qt::EditRole).toString();
    QString sCondition2 = model->data(model->index(0,3), Qt::EditRole).toString();
    QString sPattern2 = model->data(model->index(0,4), Qt::EditRole).toString();
    sCondition1 = sCondition1.simplified();
    sCondition2 = sCondition2.simplified();
    sPattern2 = sPattern2.simplified();
    sPattern1 = sPattern1.simplified();
	     
    if((sCondition2 == ">") || (sCondition2 == "<=")) {
        sPattern2 += " 23:59";
    } else {
        sPattern2 += " 00:00";
    }
	     
    if((sCondition1 == ">") || (sCondition1 == "<=")) {
        sPattern1 += " 23:59";
    } else {
        sPattern1 += " 00:00";
    }

    sPattern2 = convert_date_format(sPattern2, false);
    sPattern1 = convert_date_format(sPattern1, false);
	     
    if (!sPattern1.isEmpty()) {
        qery += form_qery(sCondition1, sPattern1, "date_s");
    }

    if((!sPattern2.isEmpty()) && (!sCondition2.isEmpty()) && (sCondition1 != "=")) {
        qery += form_qery(sCondition2, sPattern2, "date_s");
    }

    sCondition1 = model->data(model->index(1,1), Qt::EditRole).toString();
    sPattern1 = model->data(model->index(1,2), Qt::EditRole).toString();
    sCondition2 = model->data(model->index(1,3), Qt::EditRole).toString();
    sPattern2 = model->data(model->index(1,4), Qt::EditRole).toString();
    sCondition1 = sCondition1.simplified();
    sCondition2 = sCondition2.simplified();
    sPattern2 = sPattern2.simplified();
    sPattern1 = sPattern1.simplified();

    if(!sPattern1.isEmpty()) {
        qery += form_qery(sCondition1, sPattern1, "count");
    }

    if((!sPattern2.isEmpty()) && (!sCondition2.isEmpty()) && (sCondition1 != "=")) {
        qery += form_qery(sCondition2, sPattern2, "count");
    }

    sPattern1 = model->data(model->index(2,1), Qt::EditRole).toString();
    if(!sPattern1.isEmpty()) {
        qery += " and (description like '%"+sPattern1+"%')";
    }

    if(qery.left(4) == " and") {
        qery.remove(0,5);
    }
	     
    m_query_string = qery;
	accept();
}

QString FilterDlgImpl::form_qery(const QString& str1, const QString& str2, const QString& patt)
{
	char c = '\'';
    if(patt == "count") {
		c = ' ';
    }
	
	QString sRet;
    if(str1 == ">") {
		sRet += " and ("+patt+" > "+c+str2+c+")";
    } else if(str1 == ">=") {
		sRet += " and ("+patt+" >= "+c+str2+c+")";
    } else if(str1 == "<") {
		sRet += " and ("+patt+" < "+c+str2+c+")";
    } else if(str1 == "<=") {
		sRet += " and ("+patt+" <= "+c+str2+c+")";
    } else if((str1 == "=") && (patt == "count")) {
		sRet += " and ("+patt+" = "+str2+")";
    } else if((str1 == "=") && (patt == "date_s")) {
		QString s = str2;
		s.remove(" 00:00");
		sRet += " and ("+patt+" like '"+s+" __:__')";
	}
	
	return sRet;
}

QString FilterDlgImpl::get_filter_data()
{
    if(m_query_string.isEmpty()) {
        m_query_string = " 1";
    }
	
    return m_query_string;
}

void FilterDlgImpl::_setupUi()
{
    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

    QLabel *label = new QLabel(tr("Filtred type operations:"), this);
    horizontalLayout->addWidget(label);

    m_typeTrasnaction = new QComboBox(this);

    QIcon icon;
    icon.addFile(QStringLiteral(":/img/cash2.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_typeTrasnaction->addItem(icon, tr("All"));

    QIcon icon1;
    icon1.addFile(QStringLiteral(":/img/cash-add.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_typeTrasnaction->addItem(icon1, tr("Income"));

    QIcon icon2;
    icon2.addFile(QStringLiteral(":/img/cash-delete.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_typeTrasnaction->addItem(icon2, tr("Expense"));

    horizontalLayout->addWidget(m_typeTrasnaction);

    gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

    QPushButton *filterBtn = new QPushButton(tr("Filter"), this);
    filterBtn->setDefault(true);

    gridLayout->addWidget(filterBtn, 0, 1, 1, 1);

    m_query = new QueryTable(this);
    gridLayout->addWidget(m_query, 1, 0, 2, 1);

    QPushButton *closeBtn = new QPushButton(tr("Close"), this);
    closeBtn->setAutoDefault(true);
    closeBtn->setDefault(false);
    gridLayout->addWidget(closeBtn, 1, 1, 1, 1);

    QSpacerItem *verticalSpacer = new QSpacerItem(20, 194, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);

    QWidget::setTabOrder(filterBtn, closeBtn);

    connect(closeBtn, SIGNAL(clicked()), this, SLOT(reject()));
    connect(filterBtn, SIGNAL(clicked()), this, SLOT(slot_filter()));
}
