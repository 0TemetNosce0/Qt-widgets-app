/* ---------------------------------- manageWizard.h ---------------------------------------------------------------------------
 header file used by manageWizard.cpp

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

 developer 		: Loukas Avgeriou 
 last modified 		: 18 May 2011
===============================================================================================================================
===============================================================================================================================
*/

#ifndef MANAGEWIZARD_H
#define MANAGEWIZARD_H

#include "ui_manageWizard.h"

//==============================================================================================================
//Declaration of manageWizard class (this is the dialog that launches a restore,delete backup wizard)

class manageWizard : public QDialog
{
    Q_OBJECT
    
    public:
        manageWizard (QString, QString, QString, int, QWidget *parent=0);
        
    private slots:
        void cancelPressed();	// close the wizard
        void startAction();		// start the action (restore/delete)
        void procFinished();	// actions when a process has finished
        void appendCommandOutput();	// update browser with command running data
        void abortAction();		//abort the execution of commands
        void deleteAfterChanged();	// DeleteAfter checkbox state changed
        void prevError();		//jumb to previous error
        void nextError();		//jumb to next error
        void changeRestorePath();	//Change the restore path

    private:
        Ui::manageWizard uiW;
        
        QString source;		// holds the full path of the original source
        QString sourceLast;	// holds the last child directory of the original source
        QString dest;		// holds the full path of the original destination
        QString time;		// holds the execution time of the selected snapshot in yyyyMMddhhmmss format
        QString timeReadable; // holds the execution time of the selected snapshot in "yyyy/MM/dd - hh:mm:ss" format
        int currentSnap;	// holds the current snapshot number in the snapshot's list
        int snapshotsNo;	// holds the snapshots number
        QString wizard_type;//	holds the type of the wizard (restore or delete)
        QStringList commandArguments;	// holds the command arguments
        
        QString outputString;	// holds the standard output of the commands to display at browser
        QString outputError;	// holds the standard error of the commands to display at browser
        bool procRunning;		// this becomes true if a process is running
        bool procKilled;		// this becomes true if a process is aborted
        int errorCount;			// count the errors of the command execution
        bool DRYrun;			// become true if dry-run is checked
        bool MainRun;			// becomes true when main rsync is run. False when the specific backed up snapshot files are transfered
        bool DeleteAfter;		// becomes true if "delete files on the source" is checked
        bool firstScroll;		// becomes false if first time next button pressed
        bool snapSpecificDirExists;	// becomes true if the snapshots specific directory exists
        int count;			// simple count variable
        int snapToRestore;      // holds the current snapshot that is restored
        
        void calcCommandArgs();	// function to calculate command arguments for RESTORE purposes
        void runProcess();	//function to run the desired processes
        void guiInitialize();	//initialize the gui
        
    protected:
        void closeEvent(QCloseEvent *event);
}; 


#endif

// end of manageWizard.h ---------------------------------------------------------------------------
