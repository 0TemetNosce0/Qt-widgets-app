/*
 * Table View Print & Preview dialog
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

#ifndef TDPREVIEWDIALOG_H
#define TDPREVIEWDIALOG_H

#include <ui_tdpreviewdialog.h>
#include <QDialog>
#include <QPrinter>
#include <QTableView>
#include <QTextLength>
#include <QFileDialog>
#include <QGraphicsView>

/*! \class TDPreviewDialog
 *  \brief TDPreviewDialog dialog
 *  \author Kund Gordos
 *  \version 0.12
 *  \date     2008
 */

class QGraphicsScene;
class QAbstractItemModel;

// Text preview widget
class TDPreviewDialog : public QDialog
{
    Q_OBJECT
    Q_ENUMS (Grids)
public:
    enum Grids
    {
        NoGrid=0x0,
        NormalGrid=0x1,
        AlternateColor=0x2,
        AlternateWithGrid=0x3
    };

    TDPreviewDialog(QTableView *p_tableView, QPrinter * p_printer,  QWidget *parent=0);
    virtual ~TDPreviewDialog();
    virtual void setHeaderText(const QString &text);
    virtual void setGridMode(Grids);
    virtual void print();
    virtual int exec();
    virtual void exportPdf(const QString &filename);

private slots:
    virtual void on_setupToolButton_clicked();
    virtual void on_zoomInToolButton_clicked();
    virtual void on_zoomOutToolButton_clicked();
    virtual void on_pageSpinBox_valueChanged(int value);

private:
    Ui_TDPreviewDialog ui;
    virtual void setupPage();
    virtual void paintPage(int pagenum);
    virtual void setupSpinBox();
    QGraphicsView *view;
    QTableView *tableView;
    QPrinter *printer;
    TDPreviewDialog::Grids gridMode;
    int lines;
    int pages;
    int leftMargin;
    int rightMargin;
    int topMargin;
    int bottomMargin;
    int spacing;
    int headerSize;
    int footerSize;
    int sceneZoomFactor;
    double columnZoomFactor;
    double rowHeight;
    double columnMultiplier;
    QString headerText;
    QString footerText;
    QVector<QTextLength> colSizes;
    QAbstractItemModel *model;
    QGraphicsScene pageScene;
    QFont titleFont;
    QFont headerFont;
    QFont font;
    QFontMetrics *titleFmt;
    QFontMetrics *headerFmt;
    QFontMetrics *fmt;
    QString headerStdText;
};

#endif
