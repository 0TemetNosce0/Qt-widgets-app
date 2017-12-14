/* ---------------------------------- logDialog.cpp ---------------------------------------------------------------------------
 Class to display the "view log" dialog

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

 developer          : luckyb 
 last modified      : 27 Aug 2009
===============================================================================================================================
===============================================================================================================================
*/


#include "logDialog.h"
#include "readLogFile.cpp"

// class logDialog Constructor=================================================================================================

logDialog::logDialog (QUrl logUrl, QWidget *parent) : QDialog (parent)
{
	uiL.setupUi(this);
	logText = "";
	errorCount = 0;
	totalErrors = 0;
	
	readlogfile = new ReadLogFile(this);
	connect( readlogfile, SIGNAL(error(const QString)), this, SLOT(refreshWindowError(const QString &)) );
	connect( readlogfile, SIGNAL(newText(const QString)), this, SLOT(refreshWindow(const QString &)) );
	connect( readlogfile, SIGNAL(terminated()), this, SLOT(logReadEnd()));
	connect( readlogfile, SIGNAL(finished()), this, SLOT(logReadEnd()));
	
	(uiL.logView->document())->setMaximumBlockCount(50000);	// set maximum blocks to avoid freeze

	connect ( uiL.button_close, SIGNAL( clicked() ), this, SLOT( closeLog() ) );	//connect close pushButton SLOT ----------------
	connect ( uiL.button_previous, SIGNAL( clicked() ), this, SLOT( prevError() ) );	//connect previous pushButton SLOT
	connect ( uiL.button_next, SIGNAL( clicked() ), this, SLOT( nextError() ) );	//connect next pushButton SLOT

	readlogfile -> setLogUrl(logUrl.toString());
	QTimer::singleShot(500, this, SLOT(readLogFileNOW()));	// allow some time for the dialog to appear
}

// readLogFileNOW =====================================================================================================
//Start a new thread to read the logfile
void logDialog::readLogFileNOW()
{
	uiL.logView -> setText(tr("loading logfile..."));
	uiL.button_close -> setText(tr("wait"));
	readlogfile -> start();
}

// refreshWindow =====================================================================================================
//Refresh the log window with text
void logDialog::refreshWindow(const QString &newText)
{
	if (uiL.logView -> toPlainText() == "loading logfile...")
		uiL.logView -> clear();
	uiL.logView -> append(newText);
	totalErrors = readlogfile -> TotalErrors();
//	QCoreApplication::processEvents();
}

// logReadEnd =====================================================================================================
//Do some stuff when finished reading log
void logDialog::logReadEnd()
{
	if (totalErrors > 0)
		uiL.button_next -> setEnabled(TRUE);
	uiL.button_close -> setText(tr("close"));
	uiL.button_close -> setEnabled(TRUE);
	errorCount = 0;		//set current error to be the first of the logfile
	firstScroll=TRUE;
}

// refreshWindowError =====================================================================================================
//Refresh the log window with Error text
void logDialog::refreshWindowError(const QString &errorText)
{
	uiL.logView -> setText(errorText);
	uiL.button_next -> setEnabled(FALSE);
	uiL.button_previous -> setEnabled(FALSE);
	uiL.button_close -> setText(tr("close"));
	uiL.button_close -> setEnabled(TRUE);
}

// close button pressed=====================================================================================================
void logDialog::closeLog()
{
	close();	//emmit a QcloseEvent
}

// previous button pressed=====================================================================================================
void logDialog::prevError()
{
	errorCount--;		//decrease the current error by one

	if (errorCount == 0 )		// if the current error is the first within the logfile disable the previous button
		uiL.button_previous -> setEnabled(FALSE);
	
	if (errorCount < totalErrors-1)	//if the current error is less than the last one within the logfile enable the next button
		uiL.button_next -> setEnabled(TRUE);
	
	uiL.logView -> scrollToAnchor("error" + countStr.setNum(errorCount+1));
}

// next button pressed=====================================================================================================
void logDialog::nextError()
{
	if (!firstScroll)
		errorCount++;	// increase the current error by one
	firstScroll = FALSE;
	
	if (errorCount == totalErrors-1)		// If the current error is the last within the logfile disable the next button
		uiL.button_next -> setEnabled(FALSE);
	
	if (errorCount > 0)				// if the current error is greater than the first one within the logfile enable the previous button
		uiL.button_previous -> setEnabled(TRUE);
	
	uiL.logView -> scrollToAnchor("error" + countStr.setNum(errorCount+1));	//scroll to the current error
}

// end of logDialog.cpp ---------------------------------------------------------------------------

