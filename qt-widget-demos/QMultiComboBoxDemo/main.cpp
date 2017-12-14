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
#include "widget.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    
    QApplication app(argc, argv);

    Widget* w = new Widget();
    w->show();
    
    return app.exec();
}
