/* ---------------------------------- calcDiffThread.cpp ---------------------------------------------------------------------------
 Class to calculate the differences between source & snapshot in a seperate thread

===============================================================================================================================
===============================================================================================================================
     This file is part of "luckyBackup" project
     Copyright 2008-2012, Loukas Avgeriou
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
 last modified      : 07 Jun 2011
===============================================================================================================================
===============================================================================================================================
*/


#include "calcDiffThread.h"

// class CalcDiffThread Constructor=================================================================================================
CalcDiffThread::CalcDiffThread(QObject *parent) : QThread(parent)
{
    //initialize variables
    returnString = "";
    dirToReadString 	= "";
    dest 	= "";
    CurrentSnapshotDirectory = "";
    CurrentSnapshotString 	= "";
    sourceLast 	= "";
    source 	= "";
    CurrentSnapshotNo 	= 0;
    currentSnaps 	= 0;
    syncTYPE 	= FALSE;
    abortNOW	= FALSE;
}

// class CalcDiffThread Destructor=================================================================================================
CalcDiffThread::~CalcDiffThread ()
{
    wait();
}

// run the QThread=================================================================================================
void CalcDiffThread::run ()
{
    returnString = "";
    emit updateViewer(tr("Scanning destination") + "\n\n..." + tr("Please wait"), FALSE);
    QFileInfoList returnDirContents = readRecursive(dirToReadString);		//this is the destination as a Qfileinfo list
    
    int countDirEntries=0, countReturnEntries=0;

    // Remove the "luckybackup snapshots root" directory from the returnDirContents list
    countReturnEntries = 0;
    while ( (countReturnEntries < returnDirContents.size())  && (!syncTYPE) )
    {
        QFileInfo localFileInfo = returnDirContents.at(countReturnEntries);
        if ( (localFileInfo.filePath()+SLASH).contains((dest + snapDefaultDir)) )
            returnDirContents.removeAt(countReturnEntries);
        else
            countReturnEntries++;
        
        if (abortNOW)
            return;
    }

    
    // Remove files/dirs listed at changes.file from the QFileInfo list (destination)
    QStringList removedFiles;
    removedFiles.clear();
    count = CurrentSnapshotNo+1;
    while ( (count < currentSnaps)  && (!syncTYPE) )
    {
        snapchangesfilename = snapChangesDir + profileName + "-" + Operation[currentOperation] -> GetName() + "-" +
                    (Operation[currentOperation] -> GetSnapshotsListItem(count)) + ".changes.log";
        snapfile.setFileName(snapchangesfilename);
        snapfile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&snapfile);
        while (!in.atEnd())
            removedFiles.append(in.readLine());
            
        snapfile.close();
        
        count++;
    }
    countReturnEntries = 0;
    
    while ( (countReturnEntries < returnDirContents.size())  && (!syncTYPE) )
    {
        QFileInfo localFileInfo = returnDirContents.at(countReturnEntries);
        QString destFile = localFileInfo.filePath();
        destFile.remove(dest, Qt::CaseSensitive);
        
        countDirEntries = 0;
        bool removed = FALSE;
        while (countDirEntries < removedFiles.size())
        {
            if ( (destFile == removedFiles.at(countDirEntries)) || ((destFile+SLASH) == removedFiles.at(countDirEntries)) )
            {
                removed = TRUE;
                returnDirContents.removeAt(countReturnEntries);
            }
            countDirEntries++;
        }
        if (removed)
            removed = FALSE;
        else
            countReturnEntries++;
    }

    // Replace destination directory data with snapshot data - NOT in sync mode
    // Do this for every snapshot from the current to the last one going back
    count = currentSnaps-2;
    while ( (count >= CurrentSnapshotNo) && (!syncTYPE) )
    {
        QString SnapshotDirectoryStringToRead = Operation[currentOperation] -> GetSnapshotsListItem (count);
        QString SnapshotDirectoryToRead = dest + snapDefaultDir + SnapshotDirectoryStringToRead + SLASH + sourceLast;
		
        QDir currentsnapdir(SnapshotDirectoryToRead);
        if ( (currentsnapdir.exists()) && (!syncTYPE) )
        {
            emit updateViewer(tr("Scanning snapshot") + " " + SnapshotDirectoryStringToRead + "\n\n..." + tr("Please wait"), FALSE);
            QFileInfoList currentsnapdirContents = readRecursive(SnapshotDirectoryToRead); // this is the snapshots directory currently read as a QFileInfo list
            countDirEntries = 0;
            
            while (countDirEntries < currentsnapdirContents.size())
            {
                //strip off beginning of snapshot file path
                QFileInfo snapFileInfo = currentsnapdirContents.at(countDirEntries);
                QString snapFile = snapFileInfo.filePath();
                snapFile.remove(SnapshotDirectoryToRead, Qt::CaseSensitive);

                countReturnEntries = 0;
                bool replaced = FALSE;
                while (countReturnEntries < returnDirContents.size())
                {
                    QFileInfo localFileInfo = returnDirContents.at(countReturnEntries);
                    QString destFile = localFileInfo.filePath();
                    for (int count3=CurrentSnapshotNo; count3 < currentSnaps-1; count3++) // if the destFile belongs to a "later" snapFile
                    {
                        QString IlostTrack = Operation[currentOperation] -> GetSnapshotsListItem (count3);
                        if (destFile.startsWith(dest + snapDefaultDir + IlostTrack) )
                            destFile.remove(dest + snapDefaultDir + IlostTrack + SLASH + sourceLast, Qt::CaseSensitive);
                    }
                    destFile.remove(dest, Qt::CaseSensitive);

                    if (snapFile == destFile)
                    {
                        returnDirContents.removeAt(countReturnEntries);
                        returnDirContents.insert(countReturnEntries,snapFileInfo);
                        replaced = TRUE;
                    }
                    countReturnEntries++;
                }
                if ( (!replaced) && (!removedFiles.contains(snapFile,Qt::CaseSensitive )) )
                    returnDirContents.append(snapFileInfo);

                countDirEntries++;
                
                if (abortNOW)
                    return;
            }
        }
        count--;
    }
    // Calculate differences between snapshot and source
    QFileInfoList changedFiles, existingSource, existingSnap;
    changedFiles.clear();	existingSource.clear();	existingSnap.clear();
    QString changedfiles="", existingsource = "", existingsnap = "";
    QList<bool> snapMatchesSource;
    snapMatchesSource.clear();

    emit updateViewer(tr("Scanning source") + "\n\n..." + tr("Please wait"), FALSE);
    QFileInfoList sourceDirAsList = readRecursive(source);	// This is source as a QFileInfo list

    QString calcInfoText = tr("Calculating differences") + "\n\n..." + tr("Please wait") + "\n\n";
    QString sourceDirAsListSize = countStr.setNum(sourceDirAsList.size());

    countDirEntries = 0;
    while (countDirEntries < sourceDirAsList.size())
    {
        bool foundMatchSourceToSnap = FALSE;	// If a file with some filename exists at the source and the snapshot
        // strip off beginning of source file path
        QFileInfo sourceFileInfo = sourceDirAsList.at(countDirEntries);
        QString sourceFile = sourceFileInfo.filePath();
        if (sourceFile.startsWith(source))
            sourceFile.remove(source, Qt::CaseSensitive);
        
        emit updateViewer(calcInfoText + countStr.setNum(countDirEntries) + " / " + sourceDirAsListSize, FALSE);		// Give the user sth to watch counting
        if (abortNOW)
            return;
        
        // compare with every file in snapshot
        countReturnEntries = 0;
        while (countReturnEntries < returnDirContents.size())
        {
            if (countDirEntries == 0)
                snapMatchesSource.append(FALSE); // build a <bool> list

            //strip off beginning of snapshot file path
            QFileInfo snapFileInfo = returnDirContents.at(countReturnEntries);
            QString snapFile = snapFileInfo.filePath();
// ********************* TO EDIT ***************************************************************************************
            for (count=currentSnaps-2; count >= CurrentSnapshotNo; count--)
            {
                QString SnapshotDirectoryStringToRead = Operation[currentOperation] -> GetSnapshotsListItem (count);
                if (snapFile.startsWith(dest + snapDefaultDir + SnapshotDirectoryStringToRead) )
                    snapFile.remove(dest + snapDefaultDir + SnapshotDirectoryStringToRead + SLASH + sourceLast, Qt::CaseSensitive);
                //if (snapFile.startsWith(dest + snapDefaultDir + CurrentSnapshotString) )
                //    snapFile.remove(dest + snapDefaultDir + CurrentSnapshotString + SLASH + sourceLast, Qt::CaseSensitive);
            }
// ********************* TO EDIT ***************************************************************************************

            if (snapFile.startsWith(dest))
                snapFile.remove(dest, Qt::CaseSensitive);
            
            // 1. Data that have changed at source.
            //	The snapshot data will replace the relevant source data, at RESTORE
            if (snapFile == sourceFile)
            {
                snapMatchesSource.replace(countReturnEntries, TRUE);
                foundMatchSourceToSnap = TRUE;
                if ((snapFileInfo.lastModified() != sourceFileInfo.lastModified()) ||
                (snapFileInfo.size() != sourceFileInfo.size()))
                {
                    changedFiles.append(snapFileInfo);
                    
                    // Do not add anything if it's a directory!!
                    if (snapFileInfo.isDir())
                        snapFile.append(SLASH);
                    else
                    if (changedfiles.size() < 10000)
                        changedfiles.append("* <b>" + snapFile + "</b> - " + snapFileInfo.lastModified().toString("yyyy MMM dd - hh:mm:ss") + "<br>");
                    
                    //else
                    //	break;
                }
            }
            
            countReturnEntries++;
        }

        // 2. Data that exist at the source but not at the snapshot
        //	These will be deleted at RESTORE if "delete existing source data that do not exist at the backup" is checked
        if (!foundMatchSourceToSnap)
        {
            existingSource.append(sourceFileInfo);
            if (sourceFileInfo.isDir())
                sourceFile.append(SLASH);
            if (existingsource.size() < 10000)
                existingsource.append("* <b>" + sourceFile + "</b> - " + sourceFileInfo.lastModified().toString("yyyy MMM dd - hh:mm:ss") + "<br>");
        }
        
        countDirEntries++;
    }

    // 3. Data that exist at the snapshot but not at the source.
    // 	These will be transfered over at RESTORE
    countReturnEntries = 0;
    while (countReturnEntries < snapMatchesSource.size())
    {
        if (!snapMatchesSource.at(countReturnEntries))
        {
            QFileInfo snapFileInfo = returnDirContents.at(countReturnEntries);
            QString snapFile = snapFileInfo.filePath();
// ********************* TO EDIT ***************************************************************************************            
            for (count=currentSnaps-2; count >= CurrentSnapshotNo; count--)
            {
                QString SnapshotDirectoryStringToRead = Operation[currentOperation] -> GetSnapshotsListItem (count);
                if (snapFile.startsWith(dest + snapDefaultDir + SnapshotDirectoryStringToRead) )
                    snapFile.remove(dest + snapDefaultDir + SnapshotDirectoryStringToRead + SLASH + sourceLast, Qt::CaseSensitive);
            }
// ********************* TO EDIT ***************************************************************************************

            if (snapFile.startsWith(dest))
                snapFile.remove(dest, Qt::CaseSensitive);
            if (snapFileInfo.isDir())
                snapFile.append(SLASH);
            
            existingSnap.append(snapFileInfo);
            if (existingsnap.size() < 10000)
                existingsnap.append("* <b>" + snapFile + "</b> - " + snapFileInfo.lastModified().toString("yyyy MMM dd - hh:mm:ss") + "<br>");
        }
        countReturnEntries++;
    }

    // Build the text to display to user
    returnString.append("<font color=red><p align=\"center\">");
    if (syncTYPE)
        returnString.append("		<b>" + tr("Sync dir A & B differences") + "</b><br>");
    else
        returnString.append("		<b>" + tr("Snapshot and source differences") + "</b><br>");
    returnString.append("_______________________________________________________</p>");
    if (changedfiles != "")
    {
        returnString.append("</font><font color=blue><p align=\"center\">");
        if (syncTYPE)
            returnString.append(" " + tr("Sync dir B data that also exists at sync dir A and is different") + "</p>");
        else
        {
            returnString.append(" " + tr("Snapshot data that also exists at the source and is different") + "<br>");
            returnString.append(" " + tr("The snapshot data will replace the source data during RESTORE") + "</p>");
        }
        returnString.append(changedfiles);
        if (changedfiles.size() > 9900)
            returnString.append(" <br>" + tr("Data amount is huge. Displaying only first entries") + "<br>");
        returnString.append("_______________________________________________________<br>");
    }
    if (existingsnap != "")
    {
        returnString.append("</font><font color=green><p align=\"center\">");
        if (syncTYPE)
            returnString.append(" " + tr("Sync dir B data that do NOT exist at sync dir A") + "</p>");
        else
        {
            returnString.append(" " + tr("Snapshot data that do NOT exist at the source") + "<br>");
            returnString.append(" " + tr("These will be transfered over at the source during RESTORE") + "</p>");
        }
        returnString.append(existingsnap);
        if (existingsnap.size() > 9900)
            returnString.append(" <br>" + tr("Data amount is huge. Displaying only first entries") + "<br>");
        returnString.append("_______________________________________________________<br>");
    }
    if (existingsource != "")
    {
        returnString.append("</font><font color=magenta><p align=\"center\">");
        if (syncTYPE)
            returnString.append(" " + tr("Sync dir A data that do NOT exist at sync dir B") + "</p>");
        else
        {
            returnString.append(" " + tr("Source data that do NOT exist at the snapshot") + "<br>");
            returnString.append(" " + tr("These will be deleted during RESTORE only if you enable the option:") + "<br>");
            returnString.append(" \"<b>" + tr("delete existing source data that do not exist at the backup") + "</b>\"</p>");
        }
        returnString.append(existingsource);
        if (existingsource.size() > 9900)
            returnString.append(" <br>" + tr("Data amount is huge. Displaying only first entries") + "<br>");
        returnString.append("_________________________________________________________________<br>");
    }
    returnString.append("</font>");
}

// set parametres=================================================================================================
void CalcDiffThread::passParams(QString dirtoreadstring, QString desti, QString currentsnapshotdirectory, QString currentsnapshotstring, QString sourcelast, QString sourcei, int currentsnapshotno, int currentsnaps, bool synctype)
{
    this -> dirToReadString = dirtoreadstring;
    this -> dest = desti;
    this -> CurrentSnapshotDirectory = currentsnapshotdirectory;
    this -> CurrentSnapshotString 	= currentsnapshotstring;
    this -> sourceLast 	= sourcelast;
    this -> source 	= sourcei;
    this -> CurrentSnapshotNo 	= currentsnapshotno;
    this -> currentSnaps 	= currentsnaps;
    this -> syncTYPE 	= synctype;
}

// Return the resulting text=================================================================================================
QString CalcDiffThread::returnResult()
{
    return returnString;
}

// Set the abortNOW ===========================================================================================
void CalcDiffThread::setAbort(bool abortset)
{
    abortNOW = abortset;
}

// // Extract a QFileInfoList from a directory's path ===============================================================================================
QFileInfoList CalcDiffThread::readRecursive(QString dirToReadString)
{
//  QFileInfoList readRecursive(QString);	

    QDir dirToRead(dirToReadString);
    dirToRead.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
    dirToRead.setSorting(QDir::Name | QDir::DirsFirst | QDir::IgnoreCase | QDir::LocaleAware);
    
    QFileInfoList DirContentsStart = dirToRead.entryInfoList();
    QFileInfoList returnDirContentsFinal;


    QStack<QDir> dirStack;
    dirStack.push(dirToRead);
    
    while( !dirStack.empty() )
    {
        QDir lastDir = dirStack.last();
        lastDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
        lastDir.setSorting(QDir::Name | QDir::DirsFirst | QDir::IgnoreCase | QDir::LocaleAware);
        QFileInfoList flist = lastDir.entryInfoList( );
        dirStack.pop();

        foreach (QFileInfo localFileInfo, flist)
        {
            returnDirContentsFinal.append(localFileInfo);
            if (localFileInfo.isDir())
            {
                QDir dirent( localFileInfo.absoluteFilePath() );
                dirStack.push( dirent );
            }
        }
    }

    return returnDirContentsFinal;
}

// end of calcDiffThread.cpp ---------------------------------------------------------------------------

