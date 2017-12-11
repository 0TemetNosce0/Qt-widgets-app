/* ---------------------------------- modifyDialog.h ---------------------------------------------------------------------------
 Header file for modifyDialog.cpp

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
 last modified      : 17 Feb 2011
===============================================================================================================================
===============================================================================================================================
*/

#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

//include  header file that qmake produces from "*.ui" created with qt designer
#include "ui_modifyDialog.h"
#include "operationClass.h"
#include "patternEditor.h"

//==============================================================================================================
//Declaration of rsyncDialog class (this will execute rsync and show progress in a dialog)
class modifyDialog : public QDialog
{
    Q_OBJECT
    
    public:
        modifyDialog (int, QDialog *parent=0);

        operation *fillOperationArray();	//function to fill the data of an operation array item from the window fields
        void fillModifyWindow(operation*);	//function to fill the window fields from the data of an operation array item
        void modifyTrailing();			//function to add a remove a trailing "/" at the end of the source or dest dir
        QString modifyOS2Slashes(QString);  // function to change / to \ for OS2 (normaly when file dialog is used)
        QStringList StdArguments;		//this variable holds the standard arguments used by rsync
        int ArrayPosition;			//this holds the item's position in the "operation array"
        //bool validation;			//becomes true if "validation check" button is pressed
        int count;		//simple count variable !!

    private slots:
        void advancedPressed(bool);	//SLOT when advanced buutton pressed to hide part of widget
        void cancelPressed();		//SLOT when cancel pushbutton pressed
        void okayPressed();		//SLOT when okay pushbutton pressed
        void commandPressed();		//SLOT when show command pushbutton pressed
        void addListItem(const int);	//SLOT to add an item in a list
        void removeListItem(const int);	//SLOT to remove an item from a list
        void editListItem(const int);   //SLOT to edit an item from a list
        void moveListItemUp(const int);   //SLOT to move an item from a list
        void moveListItemDown(const int);   //SLOT to move an item from a list
        void browse(const int);		//SLOT to browse for a directory or file
        void getPattern(const int);	//SLOT to launch the pattern editor and insert the pattern to a lineEdit
        void TaskTypeChanged(int);          // SLOT to act upon task type changes
        void disableExcludeTab();           // SLOT that disables the exclude tab according to include settings

    private:
        Ui::modifyDialog uiM;
        int stdWindowWidth, minWindowHeight, maxWindowHeight;	//standard window dimensions
        QString stripInvalidCharacters(QString);	//Strips off invalid filename characters from a string
        bool listItemEditMode;                      // Becomes true is any list item is edited
        QString origAddText,origRemoveText;         // This will hold a widget's original text when we need to change it for a while
        QString origAddToolTip,origRemoveToolTip;   // This will hold a widget's original tooltip when we need to change it for a while
        QString alsoExecuteTooltip;                 // This will hold the tooltip of each "also execute" command
        Qt::CheckState alsoExecuteState;            // Will hold the state of an also execute command

    protected:
        void closeEvent(QCloseEvent *event);	//when the close button of the dialog pressed

};

#endif

// end of modifyDialog.h ---------------------------------------------------------------------------
