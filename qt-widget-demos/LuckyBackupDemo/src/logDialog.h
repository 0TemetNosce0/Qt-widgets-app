// ---------------------------------- logDialog.h ---------------------------------------------------------------------------
// Header file for logDialog.cpp
/*
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
 last modified 		: 28 Aug 2010
===============================================================================================================================
===============================================================================================================================
*/

#ifndef LOGDIALOG_H
#define LOGDIALOG_H

//include  header file that qmake produces from "*.ui" created with qt designer
#include "ui_logDialog.h"

class ReadLogFile;

//==============================================================================================================
//Declaration of logDialog class (this will viw a log file in a dialog)
class logDialog : public QDialog
{
	Q_OBJECT
	
	public:
		logDialog (QUrl, QWidget *parent=0);
		QString logText;
//		QStringList errorLine;
		int errorCount;
		int totalErrors;
		bool firstScroll;

	private slots:
		void closeLog();		//SLOT when button close pressed
		void prevError();		//SLOT to scroll to next error
		void nextError();		//SLOT to scroll to next error
		void refreshWindow(const QString &);	//SLOT to refresh the log window
		void refreshWindowError(const QString &);	//SLOT to refresh the log window
		void readLogFileNOW();	// SLOT to read the logfile in a new thread
		void logReadEnd();	//SLOT when finished reading logfile from disk

	private:
		Ui::logDialog uiL;
		ReadLogFile *readlogfile;	// QThread that will read the logfile
};

#endif

// end of logDialog.h ---------------------------------------------------------------------------
