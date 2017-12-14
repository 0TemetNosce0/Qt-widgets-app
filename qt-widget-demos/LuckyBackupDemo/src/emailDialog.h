/* ---------------------------------- emailDialog.h ---------------------------------------------------------------------------
 header file used by emailDialog.cpp

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


 project version    : Please see "main.cpp" for project version

 developer          : luckyb 
 last modified      : 06 Feb 2014
===============================================================================================================================
===============================================================================================================================
*/

#ifndef EMAILDIALOG_H
#define EMAILDIALOG_H

#include "ui_emailDialog.h"

//==============================================================================================================
//Declaration of emailDialog class
// accessor function getGoOn returns TRUE or FALSE
class emailDialog : public QDialog
{
    Q_OBJECT
    
    public:
        emailDialog (QDialog *parent=0);
        int getGoOn();
        QString getCommand();
        
    private slots:
        void okay();                    // Okay pressed
        void cancel();                  // Cancel pressed
        void revertDefault(const int);  // SLOT to revert a field to the default value
        void emailTest();               // Send an email now, using current fields
        void enableTLS();               // Enable/disable the TLS option

    private:
        Ui::emailDialog uiE;
        
        bool checkFields();         // Function to check if all fields are ok
        
        int GoOn;                   // return an integer according to exit status
        void fillWindow();          // Fill all gui fields from variables
        void fillVariables();       // Fill relevant variables from gui fields
        QString warningMessage;     // Warning message to display if the fields are not ok

    protected:
        void closeEvent(QCloseEvent *);
}; 

#endif

// end of emailDialog.h ---------------------------------------------------------------------------
