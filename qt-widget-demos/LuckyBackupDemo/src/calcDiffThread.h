// ---------------------------------- calcDiffThread.h ---------------------------------------------------------------------------
// Header file for calcDiffThread.cpp
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
 last modified 		: 01 Sep 2010
===============================================================================================================================
===============================================================================================================================
*/

#ifndef CALCDIFFTHREAD_H
#define CALCDIFFTHREAD_H

#include <QThread>
#include <QFileInfo>
//==============================================================================================================
//Declaration of class CalcDiffThread
// Calculate the differences between source & snapshot in a seperate thread
class CalcDiffThread : public QThread
{
	Q_OBJECT
	
	public:
		explicit CalcDiffThread(QObject *parent = 0);
		~CalcDiffThread();

		void passParams(QString dirtoreadstring, QString desti, QString currentsnapshotdirectory, QString currentsnapshotstring, QString sourcelast, QString sourcei,
						int currentsnapshotno, int currentsnaps, bool synctype);			//set all variables needed for the calculations
		QString returnResult();				//return the resulting text of calculated stuff
		QFileInfoList readRecursive(QString dirToReadString);
		void setAbort(bool abortset);

	protected:
		void run();

	signals:
		void updateViewer(const QString &viewText, const bool &appendText);
    
	private:
		QString dirToReadString, dest, CurrentSnapshotDirectory, CurrentSnapshotString, sourceLast, source;
		int count, CurrentSnapshotNo, currentSnaps;
		bool syncTYPE;
		bool abortNOW;
		
		QString returnString;
};

#endif

// end of calcDiffThread.h ---------------------------------------------------------------------------
