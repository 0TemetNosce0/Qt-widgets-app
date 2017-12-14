/*
 * CSV Exporter demo
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

#include "custommodel.h"
#include "csvexporter.h"
#include "csvexporterexample.h"

CSVExporterExample::CSVExporterExample(QWidget* parent)
    : QWidget( parent)
{
    ui.setupUi(this);
    CustomModel *model=new CustomModel(this);
    ui.tableView->setModel(model);
}

CSVExporterExample::~CSVExporterExample()
{

}

void CSVExporterExample::on_exportPushButton_clicked()
{
    CSVExporter *dialog = new CSVExporter(ui.tableView,this);
    dialog->exec();
}
