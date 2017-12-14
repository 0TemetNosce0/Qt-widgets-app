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

#include <QtGui>

#include "globals.h"
#include "customsqlmodel.h"

//QDbfSqlModel
// TODO:test
QDbfSqlModel::QDbfSqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
    charFields.clear();
    currencyFields.clear();
    numericFields.clear();
    dateFields.clear();
    timeFields.clear();
    doubleFields.clear();
    intFields.clear();
    logicalFields.clear();
    memoFields.clear();
    memo4Fields.clear();
    generalFields.clear();
}

void QDbfSqlModel::addCharField(int i)
{
    charFields.append(i);
}

void QDbfSqlModel::addCurrencyField(int i)
{
    currencyFields.append(i);
}

void QDbfSqlModel::addNumericField(int i)
{
    numericFields.append(i);
}

void QDbfSqlModel::addDateField(int i)
{
    dateFields.append(i);
}

void QDbfSqlModel::addTimeField(int i)
{
    timeFields.append(i);
}

void QDbfSqlModel::addDoubleField(int i)
{
    doubleFields.append(i);
}

void QDbfSqlModel::addIntField(int i)
{
    intFields.append(i);
}

void QDbfSqlModel::addLogicalField(int i)
{
    logicalFields.append(i);
}

void QDbfSqlModel::addMemoField(int i)
{
    memoFields.append(i);
}

void QDbfSqlModel::addMemo4Field(int i)
{
    memo4Fields.append(i);
}

void QDbfSqlModel::addGeneralField(int i)
{
    generalFields.append(i);
}

QVariant QDbfSqlModel::data(const QModelIndex &index, int role) const
{

    QVariant value = QSqlQueryModel::data(index, role);
    int i,j,k;

    QByteArray tempDateArray;
    QDate tempDate;
    QTime tempTime;
    quint32 l;
    qint32 l1;
    qint64 l2;
    double db;
    bool ok;
    QString currency;
    //QLocale clocale(QLocale::German);
    QLocale clocale(QLocale::C);
    quint8 r,g,b;
    QByteArray tempByteArray;

    //QList<int> charFields;
    for (i=0;i<charFields.count();i++)
    {
        if (index.column() == charFields.at(i))
        {
            switch (role)
            {
                case Qt::DisplayRole:
                    break;
                case Qt::TextAlignmentRole:
                    value = QVariant(Qt::AlignLeft | Qt::AlignVCenter);
                    break;
                case Qt::TextColorRole:
                    tempByteArray.append(charFieldColorString);
                    tempByteArray = QByteArray::fromHex(tempByteArray);
                    r = tempByteArray.at(0);
                    g = tempByteArray.at(1);
                    b = tempByteArray.at(2);
                    QColor tempColor(r,g,b);
                    value = qVariantFromValue(tempColor);
                    break;
            }
        }
    }

    //QList<int> currencyFields;
    for (i=0;i<currencyFields.count();i++)
    {
        if (index.column() == currencyFields.at(i))
        {
            switch (role)
            {
            case Qt::DisplayRole:
                tempDateArray = value.toByteArray();
                tempDateArray = QByteArray::fromHex(tempDateArray);

                l2 = *(qint64 *)tempDateArray.data();

                db = l2;
                currency.setNum(db/10000,'f',4);

                value = clocale.toString(db/10000,'f',4);
                break;
            case Qt::TextAlignmentRole:
                value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
                break;
            case Qt::TextColorRole:
                tempByteArray.append(currencyFieldColorString);
                tempByteArray = QByteArray::fromHex(tempByteArray);
                r = tempByteArray.at(0);
                g = tempByteArray.at(1);
                b = tempByteArray.at(2);
                QColor tempColor(r,g,b);
                value = qVariantFromValue(tempColor);
                break;
            }
        }
    }

    //QList<int> numericFields;
    for (i=0;i<numericFields.count();i++)
    {
        if (index.column() == numericFields.at(i))
        {
            switch (role)
            {
            case Qt::DisplayRole:
                currency=value.toString().simplified();
                k=currency.count()-1;
                j=0;
                ok=false;
                while (k>0)
                {
                    if (currency.at(k) == '.')
                    {
                        ok = true;
                        break;
                    }
                    k--;
                    j++;
                }
                if (!ok) j=0;
                value = clocale.toString(currency.toDouble(&ok),'f',j);
                break;
            case Qt::TextAlignmentRole:
                value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
                break;
            case Qt::TextColorRole:
                tempByteArray.append(numericFieldColorString);
                tempByteArray = QByteArray::fromHex(tempByteArray);
                r = tempByteArray.at(0);
                g = tempByteArray.at(1);
                b = tempByteArray.at(2);
                QColor tempColor(r,g,b);
                value = qVariantFromValue(tempColor);
                break;
            }
        }
    }

    //QList<int> dateFields;
    for (i=0;i<dateFields.count();i++)
    {
        if (index.column() == dateFields.at(i))
        {
            switch (role)
            {
            case Qt::DisplayRole:
                value = value.toDate().toString("dd.MM.yyyy");
                break;
            case Qt::TextAlignmentRole:
                value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
                break;
            case Qt::TextColorRole:
                tempByteArray.append(dateFieldColorString);
                tempByteArray = QByteArray::fromHex(tempByteArray);
                r = tempByteArray.at(0);
                g = tempByteArray.at(1);
                b = tempByteArray.at(2);
                QColor tempColor(r,g,b);
                value = qVariantFromValue(tempColor);
                break;
            }
        }
    }

    //QList<int> timeFields;
    for (i=0;i<timeFields.count();i++)
    {
        if (index.column() == timeFields.at(i))
        {
            switch (role)
            {
            case Qt::DisplayRole:
                tempDateArray = value.toByteArray();
                tempDateArray = QByteArray::fromHex(tempDateArray);

                l = *(quint32 *)tempDateArray.data();

                tempDate = QDate::fromJulianDay(l);

                l = *(quint32 *)(tempDateArray.data()+4);

                tempTime.setHMS(0,0,0);
                tempTime = tempTime.addMSecs(l);

                value = tempDate.toString("dd.MM.yyyy")+" "+tempTime.toString("hh:mm:ss.zzz");

                break;
            case Qt::TextAlignmentRole:
                value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
                break;
            case Qt::TextColorRole:
                tempByteArray.append(timeFieldColorString);
                tempByteArray = QByteArray::fromHex(tempByteArray);
                r = tempByteArray.at(0);
                g = tempByteArray.at(1);
                b = tempByteArray.at(2);
                QColor tempColor(r,g,b);
                value = qVariantFromValue(tempColor);
                break;
            }
        }
    }

    //QList<int> doubleFields;
    for (i=0;i<doubleFields.count();i++)
    {
        if (index.column() == doubleFields.at(i))
        {
            switch (role)
            {
            case Qt::DisplayRole:
                tempDateArray = value.toByteArray();
                tempDateArray = QByteArray::fromHex(tempDateArray);

                db = *(double *)tempDateArray.data();

                value = db;
                //value = clocale.toString(db,'f',4);
                break;
            case Qt::TextAlignmentRole:
                value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
                break;
            case Qt::TextColorRole:
                tempByteArray.append(doubleFieldColorString);
                tempByteArray = QByteArray::fromHex(tempByteArray);
                r = tempByteArray.at(0);
                g = tempByteArray.at(1);
                b = tempByteArray.at(2);
                QColor tempColor(r,g,b);
                value = qVariantFromValue(tempColor);
                break;
            }
        }
    }

    //QList<int> intFields;
    for (i=0;i<intFields.count();i++)
    {
        if (index.column() == intFields.at(i))
        {
            switch (role)
            {
            case Qt::DisplayRole:
                tempDateArray = value.toByteArray();
                tempDateArray = QByteArray::fromHex(tempDateArray);

                l1 = *(quint32 *)tempDateArray.data();

                value = l1;

                break;
            case Qt::TextAlignmentRole:
                value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
                break;
            case Qt::TextColorRole:
                tempByteArray.append(intFieldColorString);
                tempByteArray = QByteArray::fromHex(tempByteArray);
                r = tempByteArray.at(0);
                g = tempByteArray.at(1);
                b = tempByteArray.at(2);
                QColor tempColor(r,g,b);
                value = qVariantFromValue(tempColor);
                break;
            }
        }
    }

    //QList<int> logicalFields;
    for (i=0;i<logicalFields.count();i++)
    {
        if (index.column() == logicalFields.at(i))
        {
            switch (role)
            {
            case Qt::DisplayRole:
                break;
            case Qt::TextAlignmentRole:
                value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
                break;
            case Qt::TextColorRole:
                tempByteArray.append(logicalFieldColorString);
                tempByteArray = QByteArray::fromHex(tempByteArray);
                r = tempByteArray.at(0);
                g = tempByteArray.at(1);
                b = tempByteArray.at(2);
                QColor tempColor(r,g,b);
                value = qVariantFromValue(tempColor);
                break;
            }
        }
    }

    //QList<int> memoFields;
    for (i=0;i<memoFields.count();i++)
    {
        if (index.column() == memoFields.at(i))
        {
            switch (role)
            {
            case Qt::DisplayRole:
                break;
            case Qt::TextAlignmentRole:
                value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
                break;
            case Qt::TextColorRole:
                tempByteArray.append(memoFieldColorString);
                tempByteArray = QByteArray::fromHex(tempByteArray);
                r = tempByteArray.at(0);
                g = tempByteArray.at(1);
                b = tempByteArray.at(2);
                QColor tempColor(r,g,b);
                value = qVariantFromValue(tempColor);
                break;
            }
        }
    }
    //QList<int> memo4Fields;
    for (i=0;i<memo4Fields.count();i++)
    {
        if (index.column() == memo4Fields.at(i))
        {
            switch (role)
            {
            case Qt::DisplayRole:
                tempDateArray = value.toByteArray();
                tempDateArray = QByteArray::fromHex(tempDateArray);

                l = *(quint32 *)tempDateArray.data();

                value = l;

                break;
            case Qt::TextAlignmentRole:
                value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
                break;
            case Qt::TextColorRole:
                tempByteArray.append(memo4FieldColorString);
                tempByteArray = QByteArray::fromHex(tempByteArray);
                r = tempByteArray.at(0);
                g = tempByteArray.at(1);
                b = tempByteArray.at(2);
                QColor tempColor(r,g,b);
                value = qVariantFromValue(tempColor);
                break;
            }
        }
    }
    //QList<int> generalFields;
    for (i=0;i<generalFields.count();i++)
    {
        if (index.column() == generalFields.at(i))
        {
            switch (role)
            {
            case Qt::DisplayRole:
                break;
            case Qt::TextAlignmentRole:
                value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
                break;
            case Qt::TextColorRole:
                tempByteArray.append(generalFieldColorString);
                tempByteArray = QByteArray::fromHex(tempByteArray);
                r = tempByteArray.at(0);
                g = tempByteArray.at(1);
                b = tempByteArray.at(2);
                QColor tempColor(r,g,b);
                value = qVariantFromValue(tempColor);
                break;
            }
        }
    }
    return value;
}


