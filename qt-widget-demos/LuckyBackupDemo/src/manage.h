/* ---------------------------------- manage.h ---------------------------------------------------------------------------
 header file used by manage.cpp

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
 last modified 		: 01 Sep 2010
===============================================================================================================================
===============================================================================================================================
*/

#ifndef MANAGE_H
#define MANAGE_H

#include "ui_manage.h"

class CalcDiffThread;

//==============================================================================================================
//Declaration of manageDialog class (this is the dialog that manages existing backups of a task)

class manageDialog : public QDialog
{
	Q_OBJECT
	
	public:
		manageDialog (QDialog *parent=0);

	private slots:
		void cancel();		// close the manage dialog
		void logView();		// view the log file
		void restoreBackup();	// launch the restore wizard
		void deleteBackup();	// launch the delete wizard
		void fixGui();		// makes some changes to the gui according to various stuff
		void SnapshotsListSelected();	//Triggered when selection changes
		void hideSourceStuff();		// hide -show source stuff
		
		void calculateDifferences();	// calculate differences between source and snapshot
		void calcDiffEnd();	// diffs have been calculated - update viewer with new text
		void refreshDifWindow(const QString &, const bool &);	// update window with text concerning diff calculations
		
	private:
		Ui::manageDialog uiG;
		
		QString source;
		QString sourceLast;
		QString dest;
		QString time;
		QString CurrentSnapshotString;	// This is the current snapshot in YYYYmmddHHmmss format
		QString CurrentSnapshotDirectory ;	// This is the full path of the current snapshot directory
		int CurrentSnapshotNo;		// This is the current snapshot number (order in list). Becomes 0,1,2 .... currentSnaps
		int currentSnaps;		// this is the current number of already created snapshots
		int count;			//simple count variable
		bool syncTYPE;			// This will become true if it is a sync task
		bool abortCalcThread;	// This will become true if the calculations thread is aborted
		bool sourceVisible,viewLogVisible,deleteVisible,restoreVisible;		// Helps to hide/show source stuff
		QStringList calculatedDifferences;// Text of calculated deifferences is stored here for each snapshot
		QList<bool> snapCalculated;	// becomes true if differences have been calculated for a snapshot
		
		void updateSnapshots();
		
		CalcDiffThread * calcdiffthread;	//thread to calculate differences between snap & source
		
	protected:
		void closeEvent(QCloseEvent *event);
}; 

#endif

// end of manage.h ---------------------------------------------------------------------------
