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

#ifndef FILTERDLGIMPL_H
#define FILTERDLGIMPL_H

#include <QtWidgets/QDialog>
#include <QString>

class QueryTable;
class QComboBox;

class FilterDlgImpl : public QDialog
{
Q_OBJECT
public:
    FilterDlgImpl(QWidget* parent=0);

    ~FilterDlgImpl();
    QString get_filter_data();

private slots:
    void slot_filter();
 
private:
   // int filterFlags;
   QString m_query_string;

   //ui
   QueryTable *m_query;
   QComboBox *m_typeTrasnaction;

   QString form_qery(const QString& str1, const QString& str2, const QString& patt);
   void _setupUi();
};

#endif
