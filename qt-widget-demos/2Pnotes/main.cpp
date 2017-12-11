/* Application 2Pnotes V 2.0.5, Protect your Private notes, formerly pbase
   FILE: main.cpp

   This program is written using the qt 4.4.0 library. You can use it
   to keep private data, like the numbers of your creditcards or
   passwords, etc. into an encrypted file. It saves your data encrypted
   by using the secure blowfish algorithm. I use the free C++ class implementation
   of the blowfish encryption algorithm by Bruce Schneier converted
   to C++ class 5/96 by Jim Conger. Thanks for it.

   More about blowfish: http://www.schneier.com/blowfish.html

     Copyright (C) 2001 - 2013
     J. Schulze-Wenck
     message@jschulze-wenck.de

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License V. 2 as published by
   the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include "pbase.h"

QString path2me;    //path to this applicatiom
QString myName;     //name of this application
bool fileChanged;   //Flag for file changed and not saved

int main( int argc, char ** argv )
{
    fileChanged = false;
    myName = "2Pnotes-2.0.5";

    QApplication a( argc, argv );
    path2me = a.applicationDirPath();     //absolute path of application

    QString locale = QLocale::system().name();

    //tranlator for the strings which are components of qt
    QTranslator qtranslator;
    // load the translations from $QTDIR/translations
    if(qtranslator.load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    {
        a.installTranslator(&qtranslator);
    }

    //translator for the strings in this application
    QTranslator translator;
    if(translator.load("2Pnotes-2.0.5_" + locale, path2me))
    {
        a.installTranslator(&translator);
    }

    pbase *p = new pbase;
    p->show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    
    return a.exec();
}

