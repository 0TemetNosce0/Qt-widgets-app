/* ---------------------------------- winDialog.h ---------------------------------------------------------------------------
header file used by winDialog.cpp

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
 last modified 	: 16 Jan 2012
===============================================================================================================================
===============================================================================================================================
*/

#ifndef WINDIALOG_H
#define WINDIALOG_H

#include "ui_winDialog.h"

//==============================================================================================================
//Declaration of winDialog class
class winDialog : public QDialog
{
    Q_OBJECT
    
    public:
        winDialog (QWidget *parent=0);
        QString modifySlashes(QString);  // function to change / to \ for OS2 & windows (normaly when file dialog is used)

    private slots:
        void okay();
        void cancel();
        void browse(const int);     //SLOT to browse for a directory or file to use at the lineEdits
        void useDefault(const int);     //SLOT to revert the lineEdits to their default values

    private:
        Ui::winDialog uiD;

    protected:
        void closeEvent(QCloseEvent*);
}; 

#endif

// end of winDialog.h ---------------------------------------------------------------------------
