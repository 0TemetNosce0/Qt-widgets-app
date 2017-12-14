/*
 * TableView Preview & Print demo
 * Copyright (C) 2004-2008 by Gordos Kund / QnD Co Bt.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact gordos.kund@gmail.com with any questions on this license.
 */

#include "tableprinterexample.h"
#include "custommodel.h"
#include <QMessageBox>
#include <QDebug>

TablePrinterExample::TablePrinterExample( QWidget* parent) : QWidget( parent)
{
	grid=TDPreviewDialog::NoGrid;
        ui.setupUi(this);
	printer= new QPrinter(QPrinter::HighResolution);
	CustomModel *model=new CustomModel(this);
	ui.tableView->setModel(model);
}

//========================================

TablePrinterExample::~TablePrinterExample()
{
}

//========================================

void TablePrinterExample::on_printPushButton_clicked()
{
	TDPreviewDialog *dialog = new TDPreviewDialog(ui.tableView,printer,this);
	dialog->setGridMode(grid);
	dialog->print();
	delete dialog;
}

//========================================

void TablePrinterExample::on_previewPushButton_clicked()
{
	TDPreviewDialog *dialog = new TDPreviewDialog(ui.tableView,printer,this);
	dialog->setGridMode(grid);
	dialog->exec();
	//do printing here...
	//...
	delete dialog;
}

//========================================

void TablePrinterExample::on_comboBox_currentIndexChanged ( int index ) 
{
	switch (index)
	{
		case 0:
			grid=TDPreviewDialog::NoGrid;
			break;
		case 1:
			grid=TDPreviewDialog::NormalGrid;
			break;
		case 2:
			grid=TDPreviewDialog::AlternateColor;
			break;
		case 3:
			grid= TDPreviewDialog::AlternateWithGrid;
	}
}
