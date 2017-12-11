// ---------------------------------- readLogFile.h ---------------------------------------------------------------------------
// Header file for readLogFile.cpp
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
 last modified 		: 27 Aug 2010
===============================================================================================================================
===============================================================================================================================
*/

#ifndef READLOGFILE_H
#define READLOGFILE_H

#include <QThread>
//==============================================================================================================
//Declaration of readLogFile class (this will read a log file from disk in a seperate thread)
class ReadLogFile : public QThread
{
	Q_OBJECT
	
	public:
		explicit ReadLogFile(QObject *parent = 0);
		~ReadLogFile();
		
		void setLogUrl(QString logUrl);		//set the url of the logfile
		int TotalErrors();				//return the total number of errors found

	protected:
		void run();
		void readFile();

	signals:
		void error(const QString &message );
		void newText(const QString &logLine);
    
	private:
		//QString logFileName;
		QString logUrl;
		QString text;
		int errorsTotal;
};

#endif

// end of readLogfile.h ---------------------------------------------------------------------------
