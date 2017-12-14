/* ---------------------------------- helpBrowser.h ---------------------------------------------------------------------------
 header file used by helpBrowser.cpp

===============================================================================================================================
===============================================================================================================================
     This file is part of "luckyBackup" project
     Copyright, Loukas Avgeriou
     luckyBackup is distributed under the terms of the GNU General Public License
     luckyBackup is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.
 
     luckyBackup is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
 
     You should have received a copy of the GNU General Public License
     along with luckyBackup.  If not, see <http://www.gnu.org/licenses/>.


 project version	: Please see "main.cpp" for project version

 developer 		: luckyb 
 last modified 	: 12 January 2012
===============================================================================================================================
===============================================================================================================================*/

#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include "ui_helpBrowser.h"

//==============================================================================================================
//Declaration of helpBrowser class (this is the dialog with a textbrowser & 1 button)

class helpBrowser : public QDialog
{
    Q_OBJECT
    
    public:
        helpBrowser (QUrl, QWidget *parent=0);
        
        void scrollToChapter(QString chapter)                     {uiB.browser -> scrollToAnchor(chapter);}

    private slots:
        void okay();

    private:
        Ui::helpBrowser uiB;
}; 

#endif

// end of helpBrowser.h ---------------------------------------------------------------------------
