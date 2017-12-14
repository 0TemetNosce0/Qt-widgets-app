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

#ifndef TABLEPRINTEREXAMPLE_H
#define TABLEPRINTEREXAMPLE_H
#include <QMainWindow>
#include <QMdiArea>
#include <QObject>
#include "tdpreviewdialog.h"
#include <ui_tableprinterexample.h>

/*! \class TablePrinterExample
 *  \brief TablePrinterExample
 *  \author Kund Gordos
 *  \version 0.12
 *  \date     2008
 */

class TablePrinterExample;
class TablePrinterExample : public QWidget
{
        Q_OBJECT

public:
        TablePrinterExample( QWidget* parent = 0);
        ~TablePrinterExample();

private:
        Ui_TablePrinterExample ui;
	QPrinter *printer;
	TDPreviewDialog::Grids grid;

private slots:
	virtual void on_printPushButton_clicked();
	virtual void on_previewPushButton_clicked();
	virtual void on_comboBox_currentIndexChanged ( int index );
};
#endif
