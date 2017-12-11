/* ---------------------------------- manage.cpp ---------------------------------------------------------------------------
 Class to display the manage backups dialog

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
 last modified      : 11 Sep 2013
===============================================================================================================================
===============================================================================================================================
*/
#include "manage.h"

#include "logDialog.cpp"
#include "manageWizard.cpp"
#include "calcDiffThread.cpp"
#include "RsyncDirModel.cpp"

// class manageDialog Constructor=================================================================================================
// Displays the manage backups of a task dialog
manageDialog::manageDialog (QDialog *parent) : QDialog (parent)
{
    // initialize variables
    CurrentSnapshotString = "";
    CurrentSnapshotDirectory = "";
    CurrentSnapshotNo = 0;
    
    //first set string variables source, dest
    QStringList arguments = Operation[currentOperation] -> GetArgs();
    source = arguments[arguments.size()-2];
    dest = arguments[arguments.size()-1];
    sourceLast = "";

    //fix source and dest
    if (!source.endsWith(SLASH))	// this means task is of type "backup dir by name"
    {
        sourceLast = calculateLastPath(source); // This is the lowest dir of the source
        
        source.append(SLASH);
        
        if (WINrunning && Operation[currentOperation] -> GetRemote())
        {
            sourceLast.append(XnixSLASH);
            dest.append(sourceLast);
            if (dest.endsWith(XnixSLASH+XnixSLASH))
                dest.chop(1);
          }
        else
        {
            sourceLast.append(SLASH);
            dest.append(sourceLast);
            if (dest.endsWith(SLASH+SLASH))
                dest.chop(1);
          }
    }

    uiG.setupUi(this);
    
    calcdiffthread = new CalcDiffThread(this);
    abortCalcThread = FALSE;
    connect( calcdiffthread, SIGNAL(updateViewer(const QString, const bool)), this, SLOT(refreshDifWindow(const QString &, const bool &)) );
    connect( calcdiffthread, SIGNAL(terminated()), this, SLOT(calcDiffEnd()));
    connect( calcdiffthread, SIGNAL(finished()), this, SLOT(calcDiffEnd()));

    //connect pushButton SLOTs ----------------
    connect ( uiG.pushButton_cancel, SIGNAL( clicked() ), this, SLOT( cancel() ) );
    connect ( uiG.pushButton_viewLog, SIGNAL( clicked() ), this, SLOT( logView() ) );
    connect ( uiG.pushButton_restore, SIGNAL( clicked() ), this, SLOT( restoreBackup() ) );
    connect ( uiG.pushButton_delete, SIGNAL( clicked() ), this, SLOT( deleteBackup() ) );
    connect ( uiG.checkBox_viewSource, SIGNAL( clicked() ), this, SLOT( hideSourceStuff() ) );
    connect ( uiG.listWidget_dates, SIGNAL( itemSelectionChanged() ), this, SLOT( SnapshotsListSelected() ) );
    connect ( uiG.pushButton_calculate_diffs, SIGNAL ( clicked() ), this, SLOT ( calculateDifferences() ) );
    

    //____________________Initial gui changes (these will remain the same for as long as the gui is visible)_______________
    
    // set the text to labels profile & task
    uiG.label_profile -> setText (tr("profile")+ ": <font color = blue><b>" +profileName + "</b></font>");
    uiG.label_task -> setText (tr("task") + ": <font color = blue><b>" + Operation[currentOperation] -> GetName() + "</b></font>");
    
    //resize the treeview headers
    uiG.treeView_browser -> header() -> resizeSection(0,230);
    uiG.treeView_source -> header() -> resizeSection(0,230);
    uiG.treeView_browser -> header() -> resizeSection(1,80);
    uiG.treeView_source -> header() -> resizeSection(1,80);
    uiG.treeView_browser -> header() -> resizeSection(2,60);
    uiG.treeView_source -> header() -> resizeSection(2,60);
    uiG.treeView_browser -> header() -> resizeSection(3,100);
    uiG.treeView_source -> header() -> resizeSection(3,100);

    // Set the lineEdits source & dest with real paths
    uiG.lineEdit_destination -> setText(dest);
    uiG.lineEdit_source	-> setText(source);
    
    (uiG.textBrowser_snapshot->document())->setMaximumBlockCount(50000);	// set maximum blocks to avoid freeze
    
    updateSnapshots();	// update the snapshots listWidget
    SnapshotsListSelected(); //set currentSnapshotString & No. Will also call fixGui()
}
// SLOTS-------------------------------------------------------------------------------------
// --------------------------------cancel pressed------------------------------------------------
void manageDialog::cancel()
{
    close();
}

//do the same if the main window close button (or alt+F4) is pressed
void manageDialog::closeEvent(QCloseEvent *event)
{
    // do not close the window if a calc thread is still running
    if (calcdiffthread->isRunning())
        event->ignore();
}

// SLOT logView =====================================================================================================================
// Display the logfile
void manageDialog::logView()
{
    QUrl logURL;
    logURL.setScheme("file");
    logURL.setUrl("Does_not_exist");

    //extract the logfilename from the dates listwidget
    logfilename = CurrentSnapshotString;
    logfilename.prepend(logDir + profileName + "-" + Operation[currentOperation] -> GetName() + "-");
    logfilename.append(".log");	
    
    logfile.setFileName(logfilename); // this is the logfile of the item selected
    if (logfile.exists())	//if the logfile exists
        logURL.setUrl(logfilename);

    logDialog logdialog (logURL);
    logdialog.exec();
}

// SLOT restoreBackup =====================================================================================================================
// launch the restore wizard
void manageDialog::restoreBackup()
{
    manageWizard restoreWizard("restoreBackup", source, dest, CurrentSnapshotNo);	//pass the number of the current row
    restoreWizard.exec();
    
    fixGui();	// update the gui with new dirs data
}

// SLOT deleteBackup =====================================================================================================================
// Launch the delete backup wizard
void manageDialog::deleteBackup()
{
    
    // launch the delete backup wizard
    manageWizard deleteWizard("deleteBackup", source, dest, CurrentSnapshotNo);
    deleteWizard.exec();

    updateSnapshots();	// update the snapshots listwidget
    SnapshotsListSelected(); // set a new currentSnapshot and update the gui
}

// fixGui  =====================================================================================================================
// makes some changes to the gui according to various stuff to make it prettier !!
// also update treebrowsers with new snapshot data
void manageDialog::fixGui()
{
    // these will become false if dest or source treebrowsers are to be hidden
    bool destVisible = TRUE;
    sourceVisible = TRUE;

    //Thesw will become false if relevant pushButtons have to be disabled
    viewLogVisible = TRUE;
    deleteVisible = TRUE;
    restoreVisible = TRUE;
    
    syncTYPE = FALSE;	// This will become true if it is a sync task
    
    // Destination - Do all things needed to display the current snapshot only.
    QDir CurrentSnapshotDir(CurrentSnapshotDirectory);
    
    // set the model of the treebrowsers (source & destination) sort by name & refresh to use new source & dest
    //destination
    QDirModel *d_model = new QDirModel;
    
    //d_model -> setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
    //d_model -> setSorting(QDir::Name | QDir::DirsFirst | QDir::IgnoreCase | QDir::LocaleAware);

    //uiG.treeView_browser -> setModel(d_model);
    //uiG.treeView_browser -> sortByColumn (0, Qt::AscendingOrder);
    //if (CurrentSnapshotDir.exists())
    //	uiG.treeView_browser -> setRootIndex(d_model->index(CurrentSnapshotDirectory));
    //else
        
        //uiG.treeView_browser -> setRootIndex(d_model->index(dest));
    
    //source
    QDirModel *s_model = new QDirModel;
    
    //s_model -> setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
    //s_model -> setSorting(QDir::Name | QDir::DirsFirst | QDir::IgnoreCase | QDir::LocaleAware);
    //uiG.treeView_source	-> setModel(s_model);
    //uiG.treeView_source 	-> sortByColumn (0, Qt::AscendingOrder);
    //uiG.treeView_source	-> setRootIndex(s_model->index(source));
    
    RsyncDirModel *rsyncmodel=new RsyncDirModel;
    
    // if a snapshot is not selected 
    if (CurrentSnapshotString == "")
    {
        viewLogVisible = FALSE;
        deleteVisible = FALSE;
        restoreVisible = FALSE;

        if (!Operation[currentOperation] -> GetTypeSync())
        {
            destVisible = FALSE;
            uiG.label_destError -> setText("<font color=magenta>" + tr("Please select a snapshot from the list",
                                        "Information message") + "</font>");
        }
    }
    
    // if "not available" is selected
    if (CurrentSnapshotString == "not available")
        viewLogVisible = FALSE;	//disable the "view log" button

    // _______________________________ source & destination directories checks ____________________________________________
    // ___________________________________________________________________________________________________________________
    // check if source & destination exist or have read/enter permissions or are remote ----------------------------------
    QFileInfo destFile(dest);
    QFileInfo sourceFile(source);
    bool sourceRemote = (Operation[currentOperation] -> GetRemote()) && (Operation[currentOperation] -> GetRemoteSource());
    bool destRemote = (Operation[currentOperation] -> GetRemote()) && (Operation[currentOperation] -> GetRemoteDestination());
    
    if (sourceRemote)		// If remote is used for source
    {
        //sourceVisible = FALSE;
        //uiG.label_sourceError -> setText("<font color=magenta>" + tr("Display of remote places is not supported",
        //                                "Information message") + "</font>");
        
        // ~~~~~~~~~~~~~~~~ Juan's patch for source~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        QStringList remoteArgs;
        remoteArgs.append("--protect-args");
        if ( Operation[currentOperation]-> GetRemoteModule() && Operation[currentOperation] -> GetRemotePassword() != "")
            remoteArgs.append("--password-file=" + ( Operation[currentOperation] -> GetRemotePassword()) );
        
        if ( Operation[currentOperation] -> GetRemoteSSH())
        {
            QString sshOptions=(Operation[currentOperation] -> GetRemoteSSHOptions()).replace("\"","\\\"")+" -o \"StrictHostKeyChecking no\"  -o \"PasswordAuthentication no\" ";
            if (WINrunning)
            {
                if ( Operation[currentOperation] -> GetRemoteSSHPassword() != "")
                    if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                        remoteArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+" -i \"" +  Operation[currentOperation] -> GetRemoteSSHPassword() +"\" -p " +
                                    countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                    else
                        remoteArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+" -i \"" +  Operation[currentOperation] -> GetRemoteSSHPassword()+"\"");
                else
                    if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                        remoteArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+" -p " + countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                    else
                        remoteArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+"");
            }
            else
            {
                if ( Operation[currentOperation] -> GetRemoteSSHPassword() != "")
                    if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                        remoteArgs.append("-e "+sshCommandPath+" -i " +  Operation[currentOperation] -> GetRemoteSSHPassword() +" -p " +
                                    countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                    else
                        remoteArgs.append("-e "+sshCommandPath+" -i " +  Operation[currentOperation] -> GetRemoteSSHPassword());
                else
                    if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                        remoteArgs.append("-e "+sshCommandPath+" -p " + countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                    else
                        remoteArgs.append("-e "+sshCommandPath);
            }
        }
        
        rsyncmodel          -> setUrl(QUrl(source),rsyncCommandPath,remoteArgs);
        uiG.treeView_source -> setModel(rsyncmodel);
        uiG.treeView_source -> sortByColumn (0, Qt::AscendingOrder);
        
    }
    else
    {
        s_model -> setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
        s_model -> setSorting(QDir::Name | QDir::DirsFirst | QDir::IgnoreCase | QDir::LocaleAware);
        uiG.treeView_source    -> setModel(s_model);
        uiG.treeView_source    -> sortByColumn (0, Qt::AscendingOrder);
        uiG.treeView_source    -> setRootIndex(s_model->index(source));
    }
    if (destRemote)			// If remote is used for destination
    {
        //        destVisible = FALSE;
                
        // ********************** WARNING - Change this when you figure out a way to display/delete remote places *************************************
        //        uiG.label_destError -> setText("<font color=magenta>" + tr("Display of remote places is not supported",
        //                                        "Information message") + "</font>");
        deleteVisible = FALSE;		//disable the delete button
        
        // ~~~~~~~~~~~~~~~~ Juan's patch for dest~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        QStringList remoteArgs;
        remoteArgs.append("--protect-args");
        if ( Operation[currentOperation]-> GetRemoteModule() && Operation[currentOperation] -> GetRemotePassword() != "")
            remoteArgs.append("--password-file=" + ( Operation[currentOperation] -> GetRemotePassword()) );
        
        if ( Operation[currentOperation] -> GetRemoteSSH())
        {
            QString sshOptions=(Operation[currentOperation] -> GetRemoteSSHOptions()).replace("\"","\\\"")+" -o \"StrictHostKeyChecking no\"  -o \"PasswordAuthentication no\" ";
            if (WINrunning)
            {
                if ( Operation[currentOperation] -> GetRemoteSSHPassword() != "")
                    if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                        remoteArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+" -i \"" +  Operation[currentOperation] -> GetRemoteSSHPassword() +"\" -p " +
                                    countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                    else
                        remoteArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+" -i \"" +  Operation[currentOperation] -> GetRemoteSSHPassword()+"\"");
                else
                    if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                        remoteArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+" -p " + countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                    else
                        remoteArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+"");
            }
            else
            {
                if ( Operation[currentOperation] -> GetRemoteSSHPassword() != "")
                    if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                        remoteArgs.append("-e "+sshCommandPath+" -i " +  Operation[currentOperation] -> GetRemoteSSHPassword() +" -p " +
                                    countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                    else
                        remoteArgs.append("-e "+sshCommandPath+" -i " +  Operation[currentOperation] -> GetRemoteSSHPassword());
                else
                    if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                        remoteArgs.append("-e "+sshCommandPath+" -p " + countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                    else
                        remoteArgs.append("-e "+sshCommandPath);
            }
        }
        
        rsyncmodel->setUrl(QUrl(dest),rsyncCommandPath,remoteArgs);
        uiG.treeView_browser   -> setModel(rsyncmodel);
        uiG.treeView_browser   -> sortByColumn (0, Qt::AscendingOrder);
    }
    else        // Local destination
    {
        //if (CurrentSnapshotDir.exists())
        // uiG.treeView_browser -> setRootIndex(d_model->index(CurrentSnapshotDirectory));
        //else
        
        d_model -> setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
        d_model -> setSorting(QDir::Name | QDir::DirsFirst | QDir::IgnoreCase | QDir::LocaleAware);

        uiG.treeView_browser -> setModel(d_model);
        uiG.treeView_browser -> sortByColumn (0, Qt::AscendingOrder);
        uiG.treeView_browser -> setRootIndex(d_model->index(dest));
      }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Juan's patch END~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // If source does not exist (and is not remote)
    if ((!sourceFile.exists()) && (!sourceRemote))
    {
        sourceVisible = FALSE;
        uiG.label_sourceError -> setText("<font color=red>" + tr("This directory does not exist") + "</font>");
    }
    // If destination does not exist
    if ((!destFile.exists()) && !(destRemote))
    {
        destVisible = FALSE;
        uiG.label_destError -> setText("<font color=red>" + tr("This directory does not exist",
                                        "Information message") + "</font>");
        if (CurrentSnapshotString == "not available")
            deleteVisible = FALSE;	//disable the delete button
        restoreVisible = FALSE;	//disable the restore button
    }
    // If source does not have read/enter permissions
    if (((!sourceFile.isReadable()) || (!sourceFile.isExecutable())) && (!sourceRemote) && (sourceFile.exists()))
    {
        sourceVisible = FALSE;
        uiG.label_sourceError -> setText("<font color=red>" + tr("I do not have sufficient permissions to read this directory",
                                        "Information message") + "</font>");
        restoreVisible = FALSE;	//disable the restore button
    }
    // If destination does not have read/enter permissions
    if (((!destFile.isReadable()) || (!destFile.isExecutable())) && (!destRemote) && (destFile.exists()))
    {
        destVisible = FALSE;
        uiG.label_destError -> setText("<font color=red>" + tr("I do not have sufficient permissions to read this directory",
                                        "Information message") + "</font>");
        deleteVisible = FALSE;		//disable the delete button
        restoreVisible = FALSE;	//disable the restore button
    }

    // _______________________________ source & destination directories checks END____________________________________________
    // ___________________________________________________________________________________________________________________
    
    //if this is a "sync" task
    if (Operation[currentOperation] -> GetTypeSync())
    {
        syncTYPE = TRUE;
        uiG.label_destination -> setText (tr("sync dir A","full phrase: sync dir a: <DIRECTORY_A>")+ ": ");
        uiG.label_source -> setText (tr("sync dir B","full phrase: sync dir a: <DIRECTORY_b>")+ ": ");
        uiG.pushButton_viewLog -> setToolTip(tr("View the logfile of the selected sync task","'view log' pushbutton tooltip"));
        deleteVisible = FALSE;
        restoreVisible = FALSE;
        uiG.checkBox_viewSource -> setVisible(FALSE);
    }

    // hide or show the treebrowsers - textbrowser
    uiG.textBrowser_snapshot -> setVisible (FALSE);
    uiG.treeView_browser -> setVisible (destVisible);
    uiG.label_destError -> setVisible (!destVisible);
    hideSourceStuff();
    
    //enable/disable the pushbuttons
    uiG.pushButton_viewLog -> setEnabled(viewLogVisible);
    uiG.pushButton_calculate_diffs -> setEnabled(destVisible);

    // Enable the delete button only for the first snapshot in list
    if (CurrentSnapshotNo > 0)
        deleteVisible = FALSE;
    
    uiG.pushButton_delete -> setEnabled(deleteVisible);
    uiG.pushButton_restore -> setEnabled(restoreVisible);
}

// hideSourceStuff  =====================================================================================================================
// hides/shows the source treebrowser & label
void manageDialog::hideSourceStuff()
{
    // Check the state of the "hide source" checkbox
    bool boxState = uiG.checkBox_viewSource -> isChecked();
    
    if (boxState)
    {
        uiG.label_source -> setVisible(FALSE);
        uiG.lineEdit_source -> setVisible(FALSE);
        uiG.label_sourceError -> setVisible (FALSE);
        uiG.treeView_source -> setVisible (FALSE);
    }
    else
    {
        uiG.label_source -> setVisible(TRUE);
        uiG.lineEdit_source -> setVisible(TRUE);
        uiG.treeView_source -> setVisible (sourceVisible);
        uiG.label_sourceError -> setVisible (!sourceVisible);
    }
}

// SnapshotsListSelected  =====================================================================================================================
// disables pushbuttons when nothing is selected at snapshots listwidget
// Also sets QString CurrentSnapshotString at current snapshot, format YYYY
void manageDialog::SnapshotsListSelected()
{
    CurrentSnapshotNo = uiG.listWidget_dates -> currentRow();
    // if a snapshot is not selected 
    if (CurrentSnapshotNo < 0)
    {
        CurrentSnapshotString = "";
        CurrentSnapshotDirectory = "";
    }
    else
    {
        CurrentSnapshotString = Operation[currentOperation] -> GetSnapshotsListItem (CurrentSnapshotNo);
        
        if (WINrunning && Operation[currentOperation] -> GetRemote())
            CurrentSnapshotDirectory = dest + snapDefaultDir.replace(SLASH,XnixSLASH) + CurrentSnapshotString + XnixSLASH + sourceLast;
        else
            CurrentSnapshotDirectory = dest + snapDefaultDir + CurrentSnapshotString + SLASH + sourceLast;
        
        if (CurrentSnapshotString == "")	// if there is no execution time of the current snapshot
            CurrentSnapshotString = "not available";
    }

    fixGui();	// update the gui
}

// calculateDifferences() ========================================================================================
// calculate differences between source and snapshot
// Calls readDirEntries()
void manageDialog::calculateDifferences()
{
	// if the thread is running (meaning: STOP is pressed)
	if (calcdiffthread -> isRunning())
	{
		uiG.textBrowser_snapshot -> setText (tr("Please wait until the thread is terminated"));
		uiG.pushButton_calculate_diffs -> setEnabled(FALSE);
		calcdiffthread -> setAbort(TRUE);
		abortCalcThread = TRUE;
		return;
	}
	
	// change the gui a bit
	if (syncTYPE)
	{
		uiG.label_source -> setVisible(FALSE);
		uiG.lineEdit_source -> setVisible(FALSE);
		uiG.treeView_source -> setVisible (FALSE);
	}
	uiG.treeView_browser -> setVisible (FALSE);
	uiG.textBrowser_snapshot -> setVisible (TRUE);
	
	if (!snapCalculated.at(CurrentSnapshotNo))	// if the differences have not been calculated yet
	{
		//disable some gui stuff during calculations
		uiG.pushButton_delete -> setEnabled(FALSE);
		uiG.pushButton_restore -> setEnabled(FALSE);
		uiG.pushButton_viewLog -> setEnabled(FALSE);
		uiG.pushButton_cancel -> setEnabled(FALSE);
		uiG.pushButton_calculate_diffs -> setText(tr("STOP"));
		uiG.pushButton_calculate_diffs -> setToolTip(tr("Stop calculations NOW"));
		
		
		calcdiffthread -> passParams(dest, dest, CurrentSnapshotDirectory, CurrentSnapshotString, sourceLast, source, CurrentSnapshotNo, currentSnaps, syncTYPE);
		calcdiffthread -> start();
	}
	else
		uiG.textBrowser_snapshot -> setText (calculatedDifferences.at(CurrentSnapshotNo));
}

// calcDiffEnd  =====================================================================================================================
// // diffs have been calculated - update viewer with new text
void manageDialog::calcDiffEnd()
{
	// Update the textBrowser_snapshot with differences data
	calculatedDifferences.replace(CurrentSnapshotNo, calcdiffthread -> returnResult() );
	uiG.textBrowser_snapshot -> setText (calculatedDifferences.at(CurrentSnapshotNo));

	if (abortCalcThread)
		uiG.textBrowser_snapshot -> append ("<p align=\"center\"><font color=red><b>" + tr("Calculations terminated by user") + "</b></font></p>");
	else
		snapCalculated.replace(CurrentSnapshotNo, TRUE );
	
	abortCalcThread = FALSE;
	calcdiffthread -> setAbort(FALSE);
	
	// re-enable gui stuff
	uiG.pushButton_delete -> setEnabled(deleteVisible);
	uiG.pushButton_restore -> setEnabled(restoreVisible);
	uiG.pushButton_viewLog -> setEnabled(viewLogVisible);
	uiG.pushButton_cancel -> setEnabled(TRUE);
	uiG.pushButton_calculate_diffs -> setEnabled(TRUE);
	uiG.pushButton_calculate_diffs -> setText(tr("Calculate differences"));
	uiG.pushButton_calculate_diffs -> setToolTip(tr("Calculate the differences between the source and the selected snapshot"));
}

// FUNCTIONS-------------------------------------------------------------------------------------

// refreshDifWindow =====================================================================================================
//Refresh the calc diff window with text
void manageDialog::refreshDifWindow(const QString &newText, const bool &appendText)
{
	if (appendText)
		uiG.textBrowser_snapshot -> append(newText);
	else
		uiG.textBrowser_snapshot -> setText(newText);
//	QCoreApplication::processEvents();
}

// updateSnapshots  =====================================================================================================================
// update the snapshots date & times listwidget
void manageDialog::updateSnapshots()
{
	//clear the listWidget
	uiG.listWidget_dates -> clear();
	calculatedDifferences.clear();		// this holds the calculated differences text for each snapshot
	snapCalculated.clear();
	
	//initialize snapshot variables
	currentSnaps = Operation[currentOperation] -> GetSnapshotsListSize();	// this is the current number of snapshots
	bool emptySnapList = Operation[currentOperation] -> SnapshotsListIsEmpty();	// Is the list empty ??
	
	// first check if there is a last execution time available but no snapshots are declared
	// and add a new snapshot with the last execution date-time
	time = ( Operation[currentOperation] -> GetLastExecutionTime() ).toString("yyyyMMddhhmmss");
	if ( !(time == "") && (emptySnapList) )
	{
		Operation[currentOperation] -> AddSnapshotsListItem (time);
		currentSnaps = Operation[currentOperation] -> GetSnapshotsListSize();	// this is the current number of snapshots
		emptySnapList = Operation[currentOperation] -> SnapshotsListIsEmpty();	// Is the list empty ??
	}
	
	//update the listwidget with times from snapshots
	count=0;
	while (count < currentSnaps)
	{
		QDateTime currentSnapTime = QDateTime::fromString(Operation[currentOperation]-> GetSnapshotsListItem(count),"yyyyMMddhhmmss");
		if ((Operation[currentOperation]-> GetSnapshotsListItem(count)) == "")	// if there is no snapshot time for a reason
			uiG.listWidget_dates -> addItem (tr("not available","refers to a date-time"));
		else
			uiG.listWidget_dates -> addItem (currentSnapTime.toString("yyyy/MM/dd - hh:mm:ss"));
		
		calculatedDifferences.append("");
		snapCalculated.append(FALSE);
		
		count++;
	}
	
	if (emptySnapList)
	{
		uiG.listWidget_dates -> addItem (tr("not available","refers to a date-time"));
		calculatedDifferences.append("");
		snapCalculated.append(FALSE);
	}

	// select the latest snapshot
	uiG.listWidget_dates	-> setCurrentRow(uiG.listWidget_dates -> count() - 1);
}


// end of manage.cpp ---------------------------------------------------------------------------

