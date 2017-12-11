/* ---------------------------------- managewizard.cpp ---------------------------------------------------------------------------
Class to launch a wizard for restore, delete a backup

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
last modified      : 10 Nov 2012
===============================================================================================================================
===============================================================================================================================
*/
#include "manageWizard.h"
//#include "logDialog.cpp"
QProcess *commandProcess;

// class manageWizard Constructor=================================================================================================
// Launches a wizard
manageWizard::manageWizard (QString type, QString SOURCE, QString DEST,  int snapshot, QWidget *parent) : QDialog (parent)
{
    // initialize variables
    currentSnap = snapshot;							// this is the current snapshot number
    snapshotsNo = Operation[currentOperation] -> GetSnapshotsListSize();	// this is the number of snapshots
    wizard_type = type;
    snapToRestore = snapshotsNo-2;  // This means the previous of the very last snapshot
    
    procRunning = FALSE;
    procKilled = FALSE;
    writeToLog = FALSE;
    DeleteAfter = FALSE;
    firstScroll = TRUE;
    MainRun = TRUE;
    
    QStringList arguments = Operation[currentOperation] -> GetArgs();
    source = SOURCE;	// the full path of the source
    if (Operation[currentOperation] -> GetTypeDirContents())
        sourceLast = "";
    else
        sourceLast = calculateLastPath(source) + SLASH; // This is the lowest dir of the source
        
    dest = DEST;		// the full path of the destination
    time = Operation[currentOperation] -> GetSnapshotsListItem(currentSnap);
    if (time == "")
        timeReadable = tr("not available","refers to a date-time");
    else
        timeReadable = time.mid(0,4) + "/" + time.mid(4,2) + "/" + time.mid(6,2) + " - " +
                    time.mid(8,2) + ":" + time.mid(10,2) + ":" + time.mid(12,2);	//QString

    QDir snapSpecificDir(dest + snapDefaultDir + time + SLASH);
    if (snapSpecificDir.exists())
        snapSpecificDirExists = TRUE;
    else
        snapSpecificDirExists = FALSE;
    
    // delete backup;if this are more than one snapshots available, set dir to delete as snapSpecificDir
    if ((wizard_type == "deleteBackup") && (snapshotsNo > 1))
        dest = snapSpecificDir.absolutePath();
    
    if (WINrunning && Operation[currentOperation] -> GetRemote())
    {
        dest.replace("/",XnixSLASH);
        if (dest.endsWith(XnixSLASH+XnixSLASH))
            dest.chop(1);
    }
    else if (notXnixRunning)        // OS2 actually !!
    {
        dest.replace("/",SLASH);
        if (dest.endsWith(SLASH+SLASH))
            dest.chop(1);
    }
    
    errorCount = 0 ;
    errorsFound = 0;
    outputString = "";
    outputError = "";
    
    uiW.setupUi(this);
    
    // initialize the gui
    this -> resize(580,300);
    guiInitialize();

    //connections ----------------
    connect ( uiW.button_cancel, SIGNAL( clicked() ), this, SLOT( cancelPressed() ) );
    connect ( uiW.button_start, SIGNAL( clicked() ), this, SLOT( startAction() ) );
    connect ( uiW.button_abort, SIGNAL( clicked() ), this, SLOT( abortAction() ) );
    connect ( uiW.checkBox_DeleteAfter, SIGNAL( stateChanged(int) ), this, SLOT( deleteAfterChanged() ) );

    commandProcess = new QProcess(this);	//create a new qprocess (for rsync) & connect signals
    connect(commandProcess, SIGNAL(readyReadStandardError()), this, SLOT(appendCommandOutput()));
    connect(commandProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(appendCommandOutput()));
    connect(commandProcess, SIGNAL (finished(int, QProcess::ExitStatus)), this, SLOT(procFinished()));
    
    connect ( uiW.button_previous, SIGNAL( clicked() ), this, SLOT( prevError() ) );	//connect previous pushButton SLOT
    connect ( uiW.button_next, SIGNAL( clicked() ), this, SLOT( nextError() ) );	//connect next pushButton SLOT
    connect ( uiW.pushButton_changeRestore, SIGNAL( clicked() ), this, SLOT( changeRestorePath() ) );	//connect change pushButton SLOT
}
// SLOTS-------------------------------------------------------------------------------------

// cancel button pressed=====================================================================================================
// emmit a QCloseEvent
void manageWizard::cancelPressed()
{
    close();	//emmit a QcloseEvent
}

// QCloseEvent emitted =====================================================================================================
//close the wizard (if a process is not running)
void manageWizard::closeEvent(QCloseEvent *event)
{
    if (procRunning)
        event->ignore();
    else
        event->accept();
}

// deleteAfterChanged()=====================================================================================================
// actions when checkbox "delete source data" state changed
void manageWizard::deleteAfterChanged()
{
    DeleteAfter = uiW.checkBox_DeleteAfter -> isChecked();	//set bool DeleteAfter according to checkbox (only applies at RESTORE)
    QString labelText = "<b><font color=red>" + tr("WARNING") + "</font></b>: ";
    if (DeleteAfter)
        labelText.append(tr("The restore directory will become identical to the backup snapshot")); 
    else
        labelText.append(tr("Existing backup files will replace the corresponding files at the restore directory",
                    "information message - line1."));
    
    labelText.append(".<br>" + tr("If the information above is correct, click <b>start</b> to begin",
                    "information message - line2.\nPlease leave tags <b></b> intact and surrounding 'start translated'") + ".");
    uiW.label_message -> setText(labelText);

    



// ********************* FOR TESTING PURPOSES **************************************************************************
/*calcCommandArgs();
QString ArgsString = "";
count=0;
while (count < commandArguments.size())
{
    if (commandArguments[count].contains("-e ssh "))
    {
        ArgsString.append("-e \"" + commandArguments[count].remove(0,3) + "\" ");
    }
    else
        ArgsString.append(commandArguments[count]+" ");
    count++;
}
labelText.append("<br><br><font color=red>" + ArgsString + "</font>");
uiW.label_message -> setText(labelText);
*/
// ********************* END TESTING PURPOSES **************************************************************************
}

// start button pressed=====================================================================================================
// start the action
void manageWizard::startAction()
{
    DeleteAfter = uiW.checkBox_DeleteAfter -> isChecked();	//set bool DeleteAfter according to checkbox (only applies at RESTORE)
    DryRun = uiW.checkBox_DryRun -> isChecked();		//set bool DeleteAfter according to checkbox (only applies at RESTORE)
    
    //change the gui
    uiW.button_next -> setVisible (TRUE);
    uiW.button_next -> setEnabled (FALSE);
    uiW.button_previous -> setVisible (TRUE);
    uiW.button_previous -> setEnabled (FALSE);
    uiW.actionView -> setVisible (TRUE);
    uiW.button_cancel -> setVisible (FALSE);
    uiW.groupBox_title -> setVisible (FALSE);
    uiW.button_abort -> setVisible (TRUE);
    uiW.checkBox_DryRun -> setVisible (FALSE);
    uiW.button_start -> setVisible (FALSE);
    
    // logfile actions if real run is performed - is always true for DELETE actions
    //This is the RESTORE/DELETE logfile
    if (!DryRun)
    {
        if (wizard_type == "restoreBackup")
            logfilename = logDir + profileName + "-" + Operation[currentOperation] -> GetName() + "-" + time + "-RESTORE" + ".log";
        else
            logfilename = logDir + profileName + "-" + Operation[currentOperation] -> GetName() + "-" + time + "-DELETE" + ".log";
        
        logfile.setFileName(logfilename); // this is the logfile
        
        if (logfile.open(QIODevice::WriteOnly | QIODevice::Text))	//create a new log file
            writeToLog = TRUE;				//& if it's ok set this to TRUE
        else
            writeToLog = FALSE;
    }
    
    runProcess();
}

// procFinished =====================================================================================================
// actions when the process is finished
void manageWizard::procFinished()
{
    procRunning = FALSE;
    if ( (wizard_type == "restoreBackup") && (snapToRestore >= currentSnap ) )
    {
        MainRun = FALSE;

        time = Operation[currentOperation] -> GetSnapshotsListItem(snapToRestore);
        QString tslash;
        if (WINrunning && Operation[currentOperation] -> GetRemote())
            tslash=XnixSLASH;
        else
            tslash=SLASH;
        QDir snapSpecificDir(dest + snapDefaultDir + time + tslash);
        
        if (snapSpecificDir.exists())
            snapSpecificDirExists = TRUE;
        else
            snapSpecificDirExists = FALSE;
        
        snapToRestore--;
        
        runProcess();
        return;
    }
    
    logfile.close();		// close the RESTORE/DELETE logfile
    
    errorsFound = errorCount;
    errorCount = 0;		// reset the error count
    uiW.button_abort -> setVisible (FALSE);
    uiW.button_cancel -> setVisible (TRUE);
    uiW.button_cancel -> setText(tr("close"));
    if (errorsFound > 0)
    {
        firstScroll=TRUE;
        uiW.button_next -> setEnabled (TRUE);
    }
    
    // if delete backup just finished normally (not ABORTED) with no errors
    if ( (wizard_type == "deleteBackup") && (errorsFound == 0) && (!procKilled) )
    {
        //delete the backup logfile
        uiW.actionView->append("<br><font color=blue><b>..." + tr("Deleting snapshot logfile",
                            "info message displayed during ...logfile deletion") +"</b></font><br>");
        QString logNameToDelete = logDir + profileName + "-" + Operation[currentOperation] -> GetName() + "-" +
                            time + ".log";
        QFile	logToDelete;
        logToDelete.setFileName(logNameToDelete); // this is the logfile of the snapshot to delete
        if (logToDelete.remove())
            uiW.actionView->append("	<font color=green>" + tr("success",
                            "info message displayed after ...logfile deletion") +"</font><br><br>");
        else
            uiW.actionView->append("	<font color=red>" + tr("failed",
                            "info message displayed after ...logfile deletion") +"</font><br><br>");
        
        //delete the .changes file
        uiW.actionView->append("<font color=blue><b>..." + tr("Deleting file that lists snapshot changes",
                            "info message displayed during ...file deletion") +"</b></font><br>");
        QString changesNameToDelete = snapChangesDir + profileName + "-" + Operation[currentOperation] -> GetName() + "-" +
                    time + ".changes.log";
        QFile	changesFileToDelete;
        changesFileToDelete.setFileName(changesNameToDelete); // this is the .changes file of the snapshot to delete
        if (changesFileToDelete.remove())
            uiW.actionView->append("	<font color=green>" + tr("success",
                            "info message displayed after ...file deletion") +"</font><br><br>");
        else
            uiW.actionView->append("	<font color=red>" + tr("failed",
                            "info message displayed after ...file deletion") +"</font><br><br>");
        
        //remove the specific snapshot from the Task
        uiW.actionView->append("<font color=blue><b>..." + tr("Updating list of snapshots"
                                ,"info message displayed during ...snaps list update") +"</b></font><br>");
        Operation[currentOperation] -> RemoveSnapshotsListItem (currentSnap);
        uiW.actionView->append("	<font color=green>" + tr("success",
                            "info message displayed after ...snapshots list update") +"</font><br><br>");

        int currentSnaps = Operation[currentOperation] -> GetSnapshotsListSize();	// this is the current number of snapshots
        bool emptySnapList = Operation[currentOperation] -> SnapshotsListIsEmpty();	// Is the list empty ??
        
        //update the last execution time to the last snapshot or to nothing if no snapshots exist
        QDateTime newTime;	// empty time variable
        if (!emptySnapList)
            newTime = QDateTime::fromString(Operation[currentOperation]-> GetSnapshotsListItem(currentSnaps-1),"yyyyMMddhhmmss");
        Operation[currentOperation] -> SetLastExecutionTime(newTime);
        
        //update the last execution errors to "-1" (not available)
        Operation[currentOperation] -> SetLastExecutionErrors(-1);
    }
    

    QString InfoMessage = "<br><font color=magenta>=====================================<br><b>... ";
    if (procKilled)
        InfoMessage.append(tr("Aborted") );
    else
        InfoMessage.append(tr("Finished") );
    
    if (DryRun)
        InfoMessage.append(" (" + tr("simulation") + ")");
    
    InfoMessage.append("</b></font><br>");
    
    if (errorsFound ==0 )
        InfoMessage.append("<font color=green><b>" + tr("no errors") + "</b></font>");
    else
        InfoMessage.append("<font color=red><b>" + tr("errors found") + "</b></font>");
    uiW.actionView->append(InfoMessage);
}

// abort button pressed=====================================================================================================
// abort the action
void manageWizard::abortAction()
{
    if (commandProcess->state() == QProcess::Running)
    {
        procKilled = TRUE;
        MainRun = FALSE;
        commandProcess -> kill();	//kill commandProcess
        commandProcess -> waitForFinished();
    }
    else
        procFinished();		// the process might not be running for some weird reason, so call procFinished !!
}
// appendCommandOutput =====================================================================================================
//update dialog with new data (text - progressbar) - also update logfile
void manageWizard::appendCommandOutput()
{
    //update textBrowser ------------------------------------------------------------------------------------------------------
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    outputString = codec->toUnicode(commandProcess -> readAllStandardOutput());
    outputError = codec->toUnicode(commandProcess -> readAllStandardError());

    uiW.actionView->append(outputString);
    logFileUpdate("rsync-standard", outputString, 0);
    
    if (outputError !="")
    {
        errorCount++;
        errorsFound++;
        uiW.actionView->append(logFileUpdate("rsync-error", outputError, 0));
    }
}

// change  button pressed=====================================================================================================
// Change the restore directory
void manageWizard::changeRestorePath()
{
    QString newRestore = QFileDialog::getExistingDirectory (this, tr("Select new restore directory", "directory selection dialog title"),
                    source, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    
    //'if something is selected indeed 
    if (newRestore != "")
    {
        //if the new restore dir does not end with /
        if (!newRestore.endsWith(SLASH))
            newRestore.append(SLASH);
        source = newRestore;
    }
    guiInitialize();
}

// previous error  button pressed=====================================================================================================
// jumb to previous error
void manageWizard::prevError()
{
    errorCount--;		//decrease the current error by one

    if (errorCount == 0 )		// if the current error is the first disable the previous button
        uiW.button_previous -> setEnabled(FALSE);
    
    if (errorCount < errorsFound-1)	//if the current error is less than the last one, enable the next button
        uiW.button_next -> setEnabled(TRUE);
    
    uiW.actionView -> scrollToAnchor("error" + countStr.setNum(errorCount+1));
}

// next error  button pressed=====================================================================================================
// jumb to next error
void manageWizard::nextError()
{
    if (!firstScroll)
        errorCount++;	// increase the current error by one
    firstScroll = FALSE;
    
    if (errorCount == errorsFound-1)		// If the current error is the last, disable the next button
        uiW.button_next -> setEnabled(FALSE);
    
    if (errorCount > 0)				// if the current error is greater than the first one enable the previous button
        uiW.button_previous -> setEnabled(TRUE);
    
    uiW.actionView -> scrollToAnchor("error" + countStr.setNum(errorCount+1));
}

// FUNCTIONS-------------------------------------------------------------------------------------

// guiInitialize()=====================================================================================================
// Initialize the gui
void manageWizard::guiInitialize()
{
    uiW.button_next -> setVisible (FALSE);
    uiW.button_previous -> setVisible (FALSE);
    uiW.button_abort -> setVisible (FALSE);
    uiW.actionView -> setVisible (FALSE);
    
    if (wizard_type == "deleteBackup")
    {	
        uiW.pushButton_logo -> setIcon (QIcon(":/luckyPrefix/remove.png"));
        uiW.groupBox_title -> setTitle(tr("Delete backup","this is the title of a wizard"));
        uiW.label_time -> setText(tr("Date & time","simple label of the wizard gui") + ": <font color=magenta><b>" + timeReadable + "</b></font>");
        uiW.label_paths	-> setText(tr("Path","...is a directory path") + ": <font color=blue><b>" + dest + "</b></font>");
        uiW.label_message -> setText("<b><font color=red>" + tr("WARNING") + "</font></b>: " +
                    tr("You are about to delete backup data","information message - line1") + ".<br>" +
                    tr("If the information above is correct, click <b>start</b> to begin",
                    "information message - line2.\nPlease leave tags <b></b> intact and surrounding 'start' translated") +
                    ".");
        uiW.checkBox_DryRun -> setVisible (FALSE);
        uiW.checkBox_DeleteAfter -> setVisible (FALSE);
        uiW.pushButton_changeRestore -> setVisible (FALSE);
    }
    if (wizard_type == "restoreBackup")
    {
        uiW.pushButton_logo -> setIcon (QIcon(":/luckyPrefix/manage.png"));
        //uiW.pushButton_logo -> setText (tr("change"));
        uiW.groupBox_title -> setTitle(tr("Restore backup","this is the title of a wizard"));
        uiW.label_time -> setText(tr("Date & time","simple label of the wizard gui") +
                    ": <font color=magenta><b>" + timeReadable + "</b></font><br>" + 
                    tr("Backup path","...is the backup directory path") + ": <font color=blue><b>" + dest + "</b></font>");
                    
        uiW.label_paths	-> setText(tr("Restore path","...is the restore directory path") + ": <font color=blue><b>" + source +"</b></font>");
        deleteAfterChanged();
    }
}

// calcCommandArgs()=====================================================================================================
// function to calculate command arguments for RESTORE
void manageWizard::calcCommandArgs()
{
    commandArguments.clear();
    commandArguments = AppendArguments(Operation[currentOperation]);
    commandArguments.removeLast();	// remove the last 2 arguments (hopefuly source & destination)
    commandArguments.removeLast();

    // Scan the list and remove all arguments that are not needed
    // keep all other arguments intact
    count =0;

    while (count < commandArguments.size())
    {
        if 	(	(commandArguments[count].contains("--exclude"))	||
                (commandArguments[count].contains("--include"))	||
                (commandArguments[count] == "--prune-empty-dirs") ||
                (commandArguments[count] == "-m") 		||
                (commandArguments[count] == "--update")		||
                (commandArguments[count] == "-u")		||
                (commandArguments[count] == "--delay-updates")	||
                (commandArguments[count].contains("--delete"))	||
                (commandArguments[count].contains("--backup"))	||
                (commandArguments[count].contains("--filter"))	||
                (commandArguments[count].contains("--log"))	||
                (commandArguments[count] == "--del")
            )
                commandArguments.removeAt(count);		//remove the argument if one of the above is true
        else
            count++;
    }
    
    if (DryRun)
        commandArguments.append("--dry-run");	// add --dry-run if checkbox checked
        
    //exclude stuff that have been backed-up, after the snapshot was made
    //this means read the changes.logs files from every snapshot after the current one
    count = currentSnap+1;
    while (count < snapshotsNo)
    {
        commandArguments.append("--exclude-from=" + snapChangesDir + profileName + "-" + Operation[currentOperation] -> GetName() + "-" +
                    (Operation[currentOperation] -> GetSnapshotsListItem(count)) + ".changes.log");
        count++;
    }

    if (MainRun)
    {
        //exclude the luckybackup snapshots directory cause it is inside the destination
        commandArguments.append("--exclude=" + snapDefaultDir);
        
        // add --delete options if checkbox checked
        if (DeleteAfter)
        {
            commandArguments.append("--delete-after");
            commandArguments.append("--delete-excluded");
        }
        
        commandArguments.append(dest);	// set new dest as source Argument  - as it was calculated at manageWizard
    }
    else
    {
        QString tslash;
        if (WINrunning && Operation[currentOperation] -> GetRemote())
            tslash=XnixSLASH;
        else
            tslash=SLASH;
        
        commandArguments.append(dest + snapDefaultDir + time + tslash + sourceLast);
    }
        
    commandArguments.append(source);	// set new source as destination ...as it was calculated at manageWizard or changed by changeRestorePath
}



// runProcess()()=====================================================================================================
// Run the desired process
void manageWizard::runProcess()
{
    bool skipTHIS = FALSE;
    
    // specify command & arguments & append information message
    QString commandLocal =""; commandArguments.clear();   // the local command is used here !!
    QString InfoMessage = "<br><font color=magenta><b>";
    if (wizard_type == "restoreBackup")
    {
        commandLocal = rsyncCommandPath;

        calcCommandArgs();	//calculate command arguments and set commandArguments
        
        if (MainRun)
            InfoMessage.append(tr("Restoring data: main trunk","info message displayed during ...data restoration"));
        else
        {
            InfoMessage.append(tr("Restoring data: snapshot files","info message displayed during ...data restoration") + " - " + time);
            if (!snapSpecificDirExists)
                skipTHIS = TRUE;
        }
        if (DryRun)
            InfoMessage.append(" (" + tr("simulation") + ")");
    }
    else
    {
        InfoMessage.append(tr("Deleting data","info message displayed during ...data deletion"));
        QDir destFolder(dest);
        if (destFolder.exists())
        {
            commandLocal = "rm";
            commandArguments << "-rvf" << dest;
        }
        else
            skipTHIS = TRUE;
        
    }

    InfoMessage.append(" ...</b><br>=====================================</font><br>");
    
    if (skipTHIS)
        InfoMessage.append("<br><font color=blue>" + tr("No snapshot specific data exist. Skipping...","info message displayed during ...data restoration/deletion") +"</font><br>");
    
    uiW.actionView->append(InfoMessage);

    // These are for testing purposes~~~~~~~~~~~~~~~~~~~~
    //commandLocal = "sleep";
    //commandArguments.clear();commandArguments << "4";
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // Do not start specific snapshot data restoration if the relevant snapshots dir does not exist
    // or do not delete the snapshots folder if it does not exist
    if (skipTHIS)
        procFinished();
    else
    {
        commandProcess -> start (commandLocal,commandArguments);
        commandProcess -> waitForStarted();
        procRunning = TRUE;
    }
}
// end of managewizard.cpp ---------------------------------------------------------------------------

