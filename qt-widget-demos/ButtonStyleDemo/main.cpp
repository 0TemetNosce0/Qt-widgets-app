/****************************************************************************
**
** Copyright (C) 2013 Yigit Agabeyli.
**
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
