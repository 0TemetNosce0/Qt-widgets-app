/*
 * CSV Exporter
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

#include "csvexporter.h"
#include <QDebug>

CSVExporter::CSVExporter(QTableView *p_tableView, QWidget *parent)
    : QDialog(parent)
{
    tableView = p_tableView;
    model = tableView->model();
}

int CSVExporter::exec()
{
    //GUI
    ui.setupUi(this);
    return QDialog::exec();
}

CSVExporter::~CSVExporter()
{

}

void CSVExporter::on_savePushButton_clicked()
{
    // file save dialog
    QString dialogcaption = "Export CSV";
    QString filename="document";

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("*.csv");
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setAcceptMode ( QFileDialog::AcceptSave);
    dialog.setConfirmOverwrite ( true );

    QStringList fileNames;
    if (!dialog.exec())
    {
        return;
    }
    fileNames = dialog.selectedFiles();
    QString fileName=fileNames.first();

    if (fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);

    //header
    QStringList headerNames;
    if (ui.headerCheckBox->checkState()==Qt::Checked)
    {
        //get header names
        for (int i=0; i<model->columnCount(); i++)
        {
            headerNames.append(model->headerData(i,Qt::Horizontal).toString());
        }
        out << headerNames.join(ui.delimiterLineEdit->text()) << "\n";
    }

    for (int i=0; i<model->rowCount(); i++)
    {
        QStringList row;
        row.clear();
        for (int j=0; j<model->columnCount(); j++)
        {
            row.append(model->data(model->index(i,j)).toString());
        }
        out << row.join(ui.delimiterLineEdit->text()) << "\n";
    }

    file.close();
}

