/****************************************************************************
**
** Copyright (C) 2010 Richard Steffen and/or its subsidiary(-ies).
** All rights reserved.
** Contact: rsteffen@messbild.de, rsteffen@uni-bonn.de
**
** Observe the License Information
**
****************************************************************************/

#include "QMultiComboBox.h"

#include <QApplication>
#include <QtGui>

int main(int argc, char* argv[])
{
    
    QApplication app(argc, argv);

    QMultiComboBox* cb = new QMultiComboBox();
    cb->SetDisplayText("MultiItemChoose");
    for (int i=0; i<50; i++)
    {
        cb->addItem(QString("Item %1").arg(i), QVariant(true));
    }
    QWidget* w = new QWidget();
    w->resize(200,300);
    QVBoxLayout* lay = new QVBoxLayout();
    lay->addWidget(cb);
    lay->addSpacing(300);

    w->setLayout(lay);
    w->show();
    
    int ret = app.exec();

    w->hide();


    // read the settings
    for (int r=0; r<cb->count(); r++)
    {
        cout << cb->itemText(r).toStdString() << " " << cb->itemData(r).toBool() << endl;
    }

    cout << "Return Code: " << ret << endl;

    return ret;
}
