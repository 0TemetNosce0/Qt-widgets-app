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


#include "mytransactionslist.h"
#include <QApplication>
#include <QPainter>


MyTransactionsList::MyTransactionsList(QWidget* parent)
    : QTreeWidget(parent)
{
	setSelectionMode(QAbstractItemView::NoSelection);
	setAllColumnsShowFocus(true);
	setUniformRowHeights(true);
	setWordWrap(false); 
}


MyTransactionsList::~MyTransactionsList()
{

}

void MyTransactionsList::drawBranches(QPainter * painter, const QRect & rect, const QModelIndex & index ) const
{
	QTreeWidgetItem *item = itemFromIndex(index);
	if(item->type() == SYS_TYPE)
    {
        return;
    }

	QTreeWidget::drawBranches(painter, rect, index);
	/*if((item->type() == INC_TYPE) || (item->type() == EXC_TYPE))
	{
	    QStyleOptionViewItemV3 opt;
	
	    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
	    painter->save();
	    painter->setPen(QPen(color));
	
	    int right = rect.right();
	    painter->drawLine(right, rect.x(), right, rect.bottom());
		
	    painter->restore();
	}*/
}


void MyTransactionsList::drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyleOptionViewItemV3 opt = option;
	
	QTreeWidgetItem *item = itemFromIndex(index);
	
    if(item->type() == SYS_TYPE)
    {
        //const QColor c = option.palette.color(QPalette::Dark);
		QFont font = option.font;
		font.setBold(true);
		
		opt.font = font;
		opt.showDecorationSelected = false;
		opt.decorationSize = QSize(opt.decorationSize.width()+3,opt.decorationSize.height()+3);
		QLinearGradient grd(0,0,0,option.rect.bottom());
		grd.setColorAt(0, QColor("#6799B3"));
		grd.setColorAt(0.3, QColor("#377a90"));
		grd.setColorAt(0.31, QColor("#0e5e73"));
		grd.setColorAt(1, QColor("#4b8598"));;
		painter->fillRect(option.rect, QBrush(grd));

		opt.palette.setBrush(QPalette::Background, QBrush(grd));
		opt.palette.setBrush(QPalette::Text, QBrush(Qt::white));
    }
    else if(item->type() == INC_TYPE)
    {
		opt.showDecorationSelected = false;
        QColor c("#B8FFBB");
		painter->fillRect(option.rect, c);
		opt.palette.setColor(QPalette::Base, c);
    }
    else if(item->type() == EXC_TYPE)
    {
		opt.showDecorationSelected = false;
		QColor c("#FFFFDE");
		painter->fillRect(option.rect, c);
		opt.palette.setColor(QPalette::Base, c);
	}
	
	opt.font.setPointSize(opt.font.pointSize()+1);
		
	QTreeWidget::drawRow(painter, opt, index);
	QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
	painter->save();
	painter->setPen(QPen(color));
	painter->drawLine(opt.rect.x(), opt.rect.bottom(), opt.rect.right(), opt.rect.bottom());
	
    if((item->type() == INC_TYPE) || (item->type() == EXC_TYPE))
    {
        int cs = 0;//draw vertical lines

        for(int i = 0; i<columnCount(); i++)
        {
            cs += columnWidth(i);
			painter->drawLine(opt.rect.x()+cs,opt.rect.top(), opt.rect.x()+cs, opt.rect.bottom());
		}
	}		

	painter->restore();
}
