/* ---------------------------------- readLogFile.cpp ---------------------------------------------------------------------------
 Class to read a logfile from disk in a seperate thread

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
 last modified 		: 27 Aug 2009
===============================================================================================================================
===============================================================================================================================
*/


#include "readLogFile.h"

// class ReadLogFile Constructor=================================================================================================
ReadLogFile::ReadLogFile(QObject *parent) : QThread(parent)
{
	text = "";
	errorsTotal = 0;
}

// class ReadLogFile Destructor=================================================================================================
ReadLogFile::~ReadLogFile ()
{
	logfile.close();
}

// run the QThread=================================================================================================
void ReadLogFile::run ()
{
	if (logUrl == "file:Does_not_exist")			// if the logfile does not exist for a reason display a message
	{
		text = tr("Could not locate the logfile") + "!!";
		emit error(text);
		return;
	}
	else
	{
		if (!logfile.open(QIODevice::ReadOnly | QIODevice::Text))	//if it exists try to open it
		{
			text = tr("Could not open the logfile") + "!!<br><font color=red>"+ logfile.errorString() + "</font>";
			emit error(text);
			return;
		}
		else
			readFile();
	}
}

// set the log url=================================================================================================
void ReadLogFile::setLogUrl(QString logurl)
{
	this -> logUrl = logurl;
}

// Return the total errors found =================================================================================================
int ReadLogFile::TotalErrors()
{
	return errorsTotal;
}

// Read the logfile from disk ===============================================================================================
void ReadLogFile::readFile()
{
	QTextStream in(&logfile);
	
	QString readLine = "";
	int countLines = 0;
	while (!in.atEnd())	// read the logfile line by line
	{
		readLine = in.readLine();
		countLines++;
		
		if (readLine.startsWith("<a name=\"error"))	// if the line is an error increase the total errors
			errorsTotal++;
		
		text.append(readLine + "<br>");
	
		if ((countLines > 2000) || (in.atEnd()))		//when 5000 lines are read or file is at end, append text to the logviewer
		{
			emit newText(text);
			text = "";
			countLines = 0;
		}
	}
}

// end of readLogFile.cpp ---------------------------------------------------------------------------

