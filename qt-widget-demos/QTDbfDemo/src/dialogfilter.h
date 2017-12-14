#/********************************************************************************/
#/*                                                                              */
#/*    Copyright 2011 Alexander Vorobyev (Voral)                                 */
#/*    http://va-soft.ru/                                                        */
#/*                                                                              */
#/*    Copyright (C) 2009 Hevele Hegyi Istvan.                                   */
#/*                                                                              */
#/*    This file is part of qtDbf.                                               */
#/*                                                                              */
#/*    Basetest is free software: you can redistribute it and/or modify          */
#/*    it under the terms of the GNU General Public License as published by      */
#/*    the Free Software Foundation, either version 3 of the License, or         */
#/*    (at your option) any later version.                                       */
#/*                                                                              */
#/*    Basetest is distributed in the hope that it will be useful,               */
#/*    but WITHOUT ANY WARRANTY; without even the implied warranty of            */
#/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
#/*    GNU General Public License for more details.                              */
#/*                                                                              */
#/*    You should have received a copy of the GNU General Public License         */
#/*    along with protime.  If not, see <http://www.gnu.org/licenses/>.          */
#/*                                                                              */
#/********************************************************************************/

#ifndef DIALOGFILTER_H
#define DIALOGFILTER_H

#include <QLabel>
#include <QComboBox>
#include <QValidator>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>


#include "widgets.h"
#include "structures.h"

typedef QList<QFieldsItem*> FieldList;

class DialogFilter : public QDbfDialog
{
    Q_OBJECT
private:
    QGridLayout *laMain;
    QVBoxLayout *laButtons;
    QLabel *lbField;
    QLabel *lbExpression;
    QComboBox *cbField;
    QComboBox *cbExpression;
    QLineEdit *edExpression;
    QDialogButtonBox *buttonBox;
    FieldList fieldsCollection;
    QValidator *validator;

    QString prepare(QFieldsItem *item, QString expression, QString filter);
public:
    explicit DialogFilter(const FieldList fields, const QString &title, const QString &field, QWidget *parent = 0);
    QString getWhere();

private slots:
    void onFieldChange(int index);


};

#endif // DIALOGFILTER_H
