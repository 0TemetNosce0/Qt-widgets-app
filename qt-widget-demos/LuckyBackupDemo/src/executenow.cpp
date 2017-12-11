/* ---------------------------------- executenow.cpp ---------------------------------------------------------------------------
do everything that deals with commands (rsync & others) execution

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
last modified      : 10 Feb 2014
===============================================================================================================================
===============================================================================================================================
********************************** DO NOT FORGET TO CHANGE "commandline.cpp:rsyncIT()" ********************************************************
*/

QProcess *syncProcess;
QTime StartTime(0,0,0,0);	//find out elapsed time from these;

// executeNOW=================================================================================================
// executes rsync (& other commands )and displays progress.
void luckyBackupWindow::executeNOW ()
{
    //Variables initialization
    // do NOT intitialise specific task variables here. Use the executeBeforeTask() function instead
    
    NOWexecuting = TRUE;		//this is mainly used if the window close button (or alt+F4) is pressed
    ABORTpressed = FALSE;		//becomes true if abort button pressed
    //change gui to execute mode !!
    guiModeNormal = FALSE;

    (ui.rsyncOutput->document())->setMaximumBlockCount(50000);	// set the maximum block count for the output window to avoid freezing

    swapGUI("execution");
    ui.AbortButton -> setVisible (TRUE);
    ui.DoneButton -> setVisible (FALSE);
    ui.rsyncOutput -> setText("");

    outputString = "";
    outputError = "";
    calculating = FALSE;		//these 3 bools are used to diplay progress of rsync at the info window
    transferring = FALSE;
    deleting = FALSE;
    ExecuteBefore=FALSE;
    ExecuteBeforeExitedError = FALSE;
    ProcReportedError = FALSE;
    StopTaskExecution = FALSE;
    ExecuteAfter=FALSE;
    writeToLog=FALSE;
    errorsFound = 0;		//total error founds during profile execution
    filesTransfered = 0;    //total bytes transfered during profile execution
    bytesTransfered = 0;    //total bytes transfered during profile execution
    count = 0;
    currentAfter = 0;
    currentBefore = 0;
    errorCount = 0;			//errors found during task execution
    repeatOnFailTry = 0;
    repeatOnFailMax = 0;

    //initiate tray icon
    if (QSystemTrayIcon::isSystemTrayAvailable ())
    {
        createTrayIcon();	//create the tray icon
        LBtray -> show();	// show the tray icon
    }
    //display a popup baloon
    trayMessage = 	tr("execution of profile:","tray message - execution of profile: <PROFILENAME> in progress...") + " " + 
            profileName + " " + tr("in progress...","tray message - execution of profile: <PROFILENAME> in progress...");
    if (DryRun)
        trayMessage.append("\n(" + tr("simulation mode") + ")");
    if ( (QSystemTrayIcon::isSystemTrayAvailable ()) && (QSystemTrayIcon::supportsMessages ()) )
    {
        if (KDErunning)
        {
            QProcess *dialogProcess;    dialogProcess = new QProcess(this);
            QStringList dialogArgs;     dialogArgs << "--title" << appName << "--passivepopup" << trayMessage << "10";
            dialogProcess -> start ("kdialog",dialogArgs);
        }
        else
            LBtray -> showMessage (appName, trayMessage, QSystemTrayIcon::Information,3000);
    }
    //Initialize shhutdown button
    ui.pushButton_shutdown -> setChecked(FALSE);

    connect ( ui.AbortButton, SIGNAL( clicked() ), this, SLOT( abortPressed() ) );	//connect abort pushButton SLOT ----------------
    connect ( ui.DoneButton, SIGNAL( clicked() ), this, SLOT( donePressed() ) );	//connect done pushButton SLOT ----------------

/*    if (WINrunning)           // disable VSS until...
    {
      vssTimer= new QTimer(this);

        pipeVssFile =  new QFile(tempDirPath+SLASH+"qt_tempvss"+QString::number(qrand() % (999998) + 1));
        if (pipeVssFile->open(QIODevice::ReadWrite))
        {
            pipeVssFile->close();
//            if (pipeVssFile->open(QIODevice::ReadOnly | QIODevice::Text))
//              connect(pipeVssFile,SIGNAL(readyRead()),this,SLOT(appendRsyncVssOutput()));
        }
        pipeVssErrFile =  new QFile(tempDirPath+SLASH+"qt_tempvsserr"+QString::number(qrand() % (999998) + 1));
        if (pipeVssErrFile->open(QIODevice::ReadWrite)){
            pipeVssErrFile->close();
//            if (pipeVssErrFile->open(QIODevice::ReadOnly | QIODevice::Text))
//              connect(pipeVssErrFile,SIGNAL(readyRead()),this,SLOT(appendRsyncVssOutput()));
        }
        if (Operation[currentOperation]->GetOptionsVss())
        {
            connect (vssTimer,SIGNAL(timeout()),this,SLOT(appendRsyncVssOutput()));
            vssTimer->start(vssSleepTime);
        }
    }*/
      
    syncProcess = new QProcess(this);	//create a new qprocess (for rsync) & connect signals
    connect(syncProcess, SIGNAL(readyReadStandardError()), this, SLOT(appendRsyncOutput()));
    connect(syncProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(appendRsyncOutput()));
    connect(syncProcess, SIGNAL (finished(int, QProcess::ExitStatus)), this, SLOT(procFinished()));
    connect(syncProcess, SIGNAL (error(QProcess::ProcessError)), this, SLOT(procError()));

    if (silentMode)
        minimizeTray();
        
    //rsync command & arguments initiation
    command = rsyncCommandPath;
    rsyncArguments.clear();
    syncAB = TRUE;

    StartTime.start();	//start the timer to measure elapsed time

    currentOperation = 0;

    //increase currentOperation until first operation to be executed (execute tasks with a "by-pass WARNING option too)
    while ( (currentOperation < TotalOperations) && (!Operation[currentOperation] -> GetPerform()) )
            currentOperation++;

    executeBeforeTask();				//execute pre-task commands if any
}

// swapGUI=====================================================================================================
//swaps the gui mode from normal to execute
void luckyBackupWindow::swapGUI(QString GUImode)
{
    if (GUImode == "execution")	//change gui to execution mode
    {
        ui.pushButton_start	-> setVisible (FALSE);
        ui.listWidget_operations -> setVisible (FALSE);
        ui.textBrowser_info	-> setVisible (FALSE);
        ui.label_TaskList -> setText(tr("commands output","output window label"));
        ui.frame_operations -> setToolTip(tr("rsync and pre/post task commands output is displayed here","tooltip"));
        
        ui.pushButton_up    -> setVisible (FALSE);
        ui.pushButton_down  -> setVisible (FALSE);
        ui.label_include    -> setVisible (FALSE);
        ui.menuFile         -> setEnabled (FALSE);
        ui.menu_Task        -> setEnabled (FALSE);
        languageMenu        -> setEnabled (FALSE);
        settingsMenu        -> setEnabled (FALSE);
        helpMenu            -> setEnabled (FALSE);
        if (!runImmediately)
            IsVisibleProfileToolbar = profileToolbar -> isVisible();//hold the visibility state of this toolbar
        profileToolbar      -> setVisible (FALSE);
        profileComboToolbar -> setEnabled (FALSE);
        ui.comboBox_profile -> setEnabled (FALSE);
        ui.groupBox_task    -> setVisible (FALSE);
        ui.checkBox_DryRun  -> setEnabled (FALSE);
        ui.pushButton_exit  -> setVisible (FALSE);
        ui.label            -> setVisible (FALSE);

        ui.AbortButton              -> setVisible (TRUE);
        ui.DoneButton               -> setVisible (TRUE);
        ui.rsyncOutput              -> setVisible (TRUE);
        //ui.pushButton_InfoCollapse -> setChecked(!IsVisibleInfoWindow);
        shutdownToolbar-> setVisible (TRUE);
        if ( (KDErunning) || (currentUser == "super user") )
            shutdownToolbar-> setEnabled (TRUE);
        else
            shutdownToolbar-> setEnabled (FALSE);
        ui.nowDoing                 -> setVisible (IsVisibleInfoWindow);
        ui.OperationProgress        -> setVisible (TRUE);
        if (QSystemTrayIcon::isSystemTrayAvailable ())
            ui.pushButton_minimizeToTray	-> setVisible (TRUE);
        else
            ui.pushButton_minimizeToTray	-> setVisible (FALSE);
        errorsToolbar-> setVisible (TRUE);
        ui.pushButton_nextError	-> setVisible (TRUE);
        ui.pushButton_previousError	-> setVisible (TRUE);
        ui.pushButton_nextError	-> setEnabled (FALSE);
        ui.pushButton_previousError	-> setEnabled (FALSE);
        ui.checkBox_onlyShowErrors -> setVisible (TRUE);
    }
    else		//change gui to normal mode !!
    {
        ui.AbortButton              -> setVisible (FALSE);
        ui.DoneButton               -> setVisible (FALSE);
        ui.rsyncOutput              -> setVisible (FALSE);
        ui.nowDoing                 -> setVisible (FALSE);
        ui.OperationProgress        -> setVisible (FALSE);
        ui.pushButton_minimizeToTray-> setVisible (FALSE);
        ui.pushButton_nextError     -> setVisible (FALSE);
        ui.pushButton_previousError -> setVisible (FALSE);
        ui.checkBox_onlyShowErrors  -> setVisible (FALSE);
        
        ui.pushButton_start	-> setVisible (TRUE);
        ui.listWidget_operations -> setVisible (TRUE);
        ui.pushButton_InfoCollapse -> setChecked(!IsVisibleInfoWindow);
        ui.textBrowser_info	-> setVisible (IsVisibleInfoWindow);
        ui.label_TaskList -> setText(tr("Task list","task list label"));
        ui.frame_operations -> setToolTip(tr("List of all the available tasks","task list tooltip - line1")+"\n"+
                tr("Use the 'include checkboxes' to include or not a selected task","task list tooltip - line2"));
        
        ui.pushButton_up    -> setVisible (TRUE);
        ui.pushButton_down  -> setVisible (TRUE);
        ui.label_include    -> setVisible (TRUE);
        ui.menuFile         -> setEnabled (TRUE);
        ui.menu_Task        -> setEnabled (TRUE);
        languageMenu        -> setEnabled (TRUE);
        settingsMenu        -> setEnabled (TRUE);
        helpMenu            -> setEnabled (TRUE);
        profileToolbar      -> setVisible (IsVisibleProfileToolbar);
        profileComboToolbar -> setEnabled (TRUE);
        shutdownToolbar     -> setVisible (FALSE);
        errorsToolbar     -> setVisible (FALSE);
        ui.comboBox_profile -> setEnabled (TRUE);
        ui.groupBox_task    -> setVisible (TRUE);
        ui.checkBox_DryRun  -> setEnabled (TRUE);
        ui.pushButton_exit  -> setVisible (FALSE);	// set this to true to make the exit button visible at normal mode
        ui.label            -> setVisible (TRUE);
    }
}

// done button pressed=====================================================================================================
void luckyBackupWindow::donePressed()
{
    ui.rsyncOutput -> setText("");
    guiModeNormal = TRUE;
    swapGUI("normal");

    if (QSystemTrayIcon::isSystemTrayAvailable ())	// this prevents a segfault when system tray is NOT available
        LBtray -> hide();	// hide the tray icon
    
    refreshList(); //refresh the listWidget_operations
    
    InfoData = QDateTime::currentDateTime().toString(Qt::DefaultLocaleLongDate) + "<br>" +
        tr("Execution of profile","full phrase: 'Execution of profile <PROFILENAME> finished'") +
        " <b>" + profileName + "</b> " + tr("finished","full phrase: 'Execution of profile <PROFILENAME> finished'")+" !!<br>";
    if (DryRun)
        InfoData.append("(" + tr("simulation mode") +")");
    else
    {
        if (!savedProfile)
            InfoData.append(tr("Could not update last execution time of tasks") + "<br>" + profile.errorString());
        else
            InfoData.append(tr("Last execution time of tasks updated"));
    }
    ui.textBrowser_info -> setText(InfoData);
}
// abort button pressed=====================================================================================================
void luckyBackupWindow::abortPressed()
{
    //if (syncProcess->state() == QProcess::NotRunning)	//if syncProcess is not Running (done pressed)

    // the next condition is used because for some wierd reason the abort button is presses multiple times
    // if you launch LB, run a profile twice and abort both of them. The second run you abort, will emitt 2 abort clicked() signals !!!
    if (ABORTpressed)
        return;

    ui.rsyncOutput->append("<br><br><font color=red>" + tr("Aborting: Please wait for all processes to be killed") + "...</font>");
    ExecuteBefore = FALSE;
    ExecuteAfter = FALSE;
    ABORTpressed = TRUE;
    
    syncProcess -> kill();	//kill rsyncProcess
    syncProcess -> waitForFinished();

    setNowDoing ();		//update Nowdoing textBrowser

}

// createTrayIcon =============================================================================================================================
// create the tray icon
// This is only called when system tray is available
void luckyBackupWindow::createTrayIcon()
{
    //actions----------------------------------
    LBtrayMenu = new QMenu(this);
    actionAbort = new QAction(QIcon(":/luckyPrefix/abort.png"), tr("&Abort"), this);
    minimizeToTray = new QAction(QIcon(":/luckyPrefix/window_minimize.png"), tr("&Minimize to tray","tray menu action"), this);
    restoreFromTray = new QAction(QIcon(":/luckyPrefix/window_restore.png"), tr("&Restore","tray menu action"), this);
    
    connect( actionAbort, SIGNAL(triggered()), this, SLOT(abortPressed()));		//tray icon action ABORT
    connect( minimizeToTray, SIGNAL(triggered()), this, SLOT(minimizeTray()));			//tray icon action minimize to Tray
    connect( restoreFromTray, SIGNAL(triggered()), this, SLOT(restoreTray()));		//tray icon action restore from tray
    
    //context menu----------------------------
    LBtrayMenu	-> addAction(minimizeToTray);
    LBtrayMenu	-> addAction(minimizeToTray);
    LBtrayMenu	-> addSeparator();
    LBtrayMenu	-> addAction(actionAbort);

    //tray icon--------------------------------
    LBtray = new QSystemTrayIcon(QIcon(":/luckyPrefix/luckybackup_96.png"),this);
    LBtray -> setContextMenu(LBtrayMenu);
    if (isMinimizedToTray == TRUE)
    {
        minimizeToTray 	-> setVisible(FALSE);
        restoreFromTray	-> setVisible(TRUE);
    }
    else
    {
        minimizeToTray 	-> setVisible(TRUE);
        restoreFromTray	-> setVisible(FALSE);
    }
    
    //connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(LBtray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(LBtrayActivated(QSystemTrayIcon::ActivationReason)));
}

// minimizeTray =============================================================================================================================
// minimizes the gui to the tray
void luckyBackupWindow::minimizeTray()
{
    if (QSystemTrayIcon::isSystemTrayAvailable ())
    {
        minimizeToTray 	-> setVisible(FALSE);
        restoreFromTray	-> setVisible(TRUE);
    }
    isMinimizedToTray = TRUE;
    this -> hide();
}
// restoreTray =============================================================================================================================
// restores the gui from the tray
void luckyBackupWindow::restoreTray()
{
    if (QSystemTrayIcon::isSystemTrayAvailable ())
    {
        minimizeToTray 	-> setVisible(TRUE);
        restoreFromTray	-> setVisible(FALSE);
    }
    isMinimizedToTray = FALSE;
    this -> showNormal();
}
// LBtrayActivated============================================================================================================
// LB tray icon activated SLOT
void luckyBackupWindow::LBtrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Context:
            break;
        case QSystemTrayIcon::Trigger:
            if (isMinimizedToTray == TRUE)
                restoreTray();
            else
                minimizeTray();
            break;
        default:
            ;
    }
    
    if (isMinimizedToTray == TRUE)
    {
        minimizeToTray 	-> setVisible(FALSE);
        restoreFromTray	-> setVisible(TRUE);
    }
    else
    {
        minimizeToTray 	-> setVisible(TRUE);
        restoreFromTray	-> setVisible(FALSE);
    }
}
//executes pre-task commands ===============================================================================================
void luckyBackupWindow::executeBeforeTask()
{
    if (ABORTpressed)		//better safe than sorry ;)
        return;
    
    repeatOnFailMax = Operation[currentOperation] -> GetRepeatOnFail();    // This holds the number of re-runs to try if the task fails for a reason
    
    // logfile & older snapshots actions if real run is performed
    if ( (!DryRun) && (currentBefore == 0) && (repeatOnFailTry == 0) )
    {
        int maxSnaps = Operation[currentOperation] -> GetKeepSnapshots();	// this is the number of snapshots to keep
        if (maxSnaps < 1)
            maxSnaps = 1;
        int currentSnaps = Operation[currentOperation] -> GetSnapshotsListSize();	// this is the current number of snapshots
        if (currentSnaps < 1)
            currentSnaps = 1;
        
        // first remove the older logfiles and snapshots if max keep snapshots is reached
        
        bool RemoteDestUsed = (Operation[currentOperation] -> GetRemoteDestination()) && (Operation[currentOperation] -> GetRemote());
        
        // SNAPSHOTS REMOVAL - This is outside the (currentSnaps >= maxSnaps) condition, because it will eventually cause the snapshots directory to get created so that the profile will be backed up without problems later on
        // First calculate the folder where snapshots go (tempDestination)
        QStringList tempArguments = Operation[currentOperation] -> GetArgs();
        QString tempSource = tempArguments[tempArguments.size()-2];
        QString tempDestination     = tempArguments[tempArguments.size()-1];
        QString tempDestinationOrig = tempArguments[tempArguments.size()-1];
        QString tempDestinationOrig2;
        QString sourceLast = tempSource;
        if (!tempSource.endsWith(SLASH))    // this means task is of type "backup dir by name"
        {
            sourceLast = calculateLastPath(sourceLast); // This is the lowest dir of the source
            
            tempSource.append(SLASH);
            if (WINrunning && RemoteDestUsed)
                tempDestination.append(sourceLast + XnixSLASH);
            else
                tempDestination.append(sourceLast + SLASH);
        }
        tempDestinationOrig2=tempDestination;
        if (RemoteDestUsed && WINrunning)
            tempDestination.append (snapDefaultDir.replace(SLASH,XnixSLASH));
        else
            tempDestination.append (snapDefaultDir);
        
        QStringList remoteArgs; remoteArgs.clear();
        //all remote arguments exactly as used at normal backup
        if (RemoteDestUsed)
        {
            remoteArgs.append("--protect-args");
            //if ( Operation[currentOperation] -> GetRemotePassword() != "")
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
        }
        
            
        if (currentSnaps >= maxSnaps)
        {
            outputInsert = "\n<font color=magenta>" +
                tr("Removing old snapshots and logfiles of task","info message displayed during ...data removal\nFull phrase: Removing old snapshots and logfiles of task: <TASKNAME>") +
                ": <b>" + Operation[currentOperation] -> GetName() +
                "</b></font><br>=====================================<br>";
            ui.rsyncOutput->append(outputInsert);
            
            // **************Remove actual backup data ***************************************************

            // increase the remove limit to include the source.size() if "backup dir by name" is used
            if (Operation[currentOperation] -> GetTypeDirName())
                removeCharLimit = 4 + sourceLast.size()+1;
            else
                removeCharLimit = 4;
            
            //we will delete the snapshots directory by using an rsync command with an empty source:
            QProcess *rmProcess;
            rmProcess  = new QProcess(this);
            QStringList rmArgs;
            rmArgs << "--progress" << "-r" << "--delete-after";
            int snapToKeep = currentSnaps-maxSnaps + 1;
            while ( snapToKeep < currentSnaps )
            {
                if (WINrunning && RemoteDestUsed)
                    rmArgs.append("--filter=protect " + Operation[currentOperation] -> GetSnapshotsListItem(snapToKeep) + XnixSLASH);
                else
                    rmArgs.append("--filter=protect " + Operation[currentOperation] -> GetSnapshotsListItem(snapToKeep) + SLASH);
                snapToKeep++;
            }
            // protect the backup profile dir too
            if (WINrunning && RemoteDestUsed)
                rmArgs.append("--filter=protect " + profileName + ".profile" + XnixSLASH);
            else
                rmArgs.append("--filter=protect " + profileName + ".profile" + SLASH);
            
            //also add all remote arguments exactly as used at normal backup
            if (RemoteDestUsed)
                //rmArgs.append(remoteArgs);  // use operator << instead of append to maintain compatiiblity with debian 5
                rmArgs << remoteArgs;
            
            rmArgs.append(snapEmptyDir);
            rmArgs.append(tempDestination);
            
            if (WINrunning)
            {

                //bool createWinRsyncCommand(tempDirPath,QFile command1,QFile command2,bool vss,QString rsyncArgs,QString source,QString dest);
                QString command2=createWinRsyncCommand(tempDirPath,false,rmArgs);
                ui.rsyncOutput->append("\n"+command2);
                if (command2=="")
                    cout << "\nfailed to create bat file in rmProccess";
                else
                    rmProcess -> start (command2);
            }
            else
                rmProcess -> start (command,rmArgs);
            rmProcess -> waitForFinished();
            
            if ((rmProcess -> exitCode()) == 0)
                ui.rsyncOutput->append("\n" + tr("Removed all older snapshots data"));// +" " + tempDestination + Operation[currentOperation] -> GetSnapshotsListItem(0) + SLASH);
            else
                ui.rsyncOutput->append("\n" + tr("failed to remove all older snapshots data"));// +" " + tempDestination + Operation[currentOperation] -> GetSnapshotsListItem(0) + SLASH);
            
            //******************************************************
        
            count = 0;
            while ( count < (currentSnaps -maxSnaps + 1 ) )
            {
                //remove the changes file ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                snapchangesfilename = snapChangesDir + profileName + "-" + Operation[currentOperation] -> GetName() + "-" +
                            (Operation[currentOperation] -> GetSnapshotsListItem(0)) + ".changes.log";
                snapfile.setFileName(snapchangesfilename);
                if (snapfile.exists())
                {
                    if (snapfile.remove())	// this is the old snapshot changes file
                        ui.rsyncOutput->append("\n" + tr("Removing") +" " + snapchangesfilename);
                    else 
                        ui.rsyncOutput->append("\n" + tr("failed to remove") +" " + snapchangesfilename);
                }
                
                //remove the oldest logfile ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                logfilename = logDir + profileName + "-" + Operation[currentOperation] -> GetName() + "-" +
                            (Operation[currentOperation] -> GetSnapshotsListItem(0)) + ".log";
                logfile.setFileName(logfilename); // this is the old logfile
                if (logfile.exists())
                {
                    if (logfile.remove())
                        ui.rsyncOutput->append("\n" + tr("Removing") +" " + logfilename);
                    else
                        ui.rsyncOutput->append("\n" + tr("failed to remove") +" " + logfilename);
                }

                //remove the oldest snapshot (0) from the list
                Operation[currentOperation] -> RemoveSnapshotsListItem (0);
                count++;
            }
        }
        else        // this is just to create the .snapDefaultDir if it does not to exist so as to copy profile data later...
        {
            //we will create the snapshots default directory by using an rsync command with an empty source without --delete option
            QProcess *mkdirProcess;
            mkdirProcess  = new QProcess(this);
            QStringList mkdirArgs;      mkdirArgs.clear();
            //no needed any more
            //if ( (WINrunning) && (RemoteDestUsed) )
            //    mkdirArgs << "--mkdir";
            //else
            mkdirArgs << "--progress" << "-r";
            
            //add all remote arguments exactly as used at normal backup
            if (RemoteDestUsed)
                //mkdirArgs.append(remoteArgs);   // use operator << instead of append to maintain compatiiblity with debian 5
                mkdirArgs << remoteArgs;
            
            mkdirArgs.append(snapEmptyDir);
            
            //rsync throws error if directory is not yet created, ..so create it first
            
            // Add the destination folder
            mkdirArgs.append(tempDestinationOrig);  // this is actually an empty argument
            if (WINrunning)
            {
                //bool createWinRsyncCommand(tempDirPath,QFile command1,QFile command2,bool vss,QString rsyncArgs,QString source,QString dest);
                QString command2=createWinRsyncCommand(tempDirPath,false,mkdirArgs);
                ui.rsyncOutput->append("\n"+command2);
                if (command2=="")
                    cout << "\nfailed to create bat file in mkdirProccess";
                else
                    mkdirProcess -> start (command2);
            }
            else
                mkdirProcess -> start (command,mkdirArgs);
            
            mkdirProcess -> waitForFinished();
            if ((mkdirProcess -> exitCode()) == 0)
                ui.rsyncOutput->append("\n!!");
            else
                ui.rsyncOutput->append("\n!");
            mkdirArgs.removeLast(); //remove the tempDestinationOrig argument
            
            // Add the destination folder [ + sourceLast +SLASH ]
            mkdirArgs.append(tempDestinationOrig2);  // this is actually an empty argument
            if (WINrunning)
            {
                //bool createWinRsyncCommand(tempDirPath,QFile command1,QFile command2,bool vss,QString rsyncArgs,QString source,QString dest);
                    QString command2=createWinRsyncCommand(tempDirPath,false,mkdirArgs);
                    ui.rsyncOutput->append("\n"+command2);
                if (command2=="")
                    cout << "\nfailed to create bat file in mkdirProccess";
                else
                    mkdirProcess -> start (command2);
            }
            else
                mkdirProcess -> start (command,mkdirArgs);

            mkdirProcess -> waitForFinished();
            if ((mkdirProcess -> exitCode()) == 0)
                ui.rsyncOutput->append("\n!!");
            else
                ui.rsyncOutput->append("\n!");
            
            // Add the destination folder [ + sourceLast +SLASH ] + snapDefaultDir
            mkdirArgs.removeLast(); //remove the tempDestinationOrig2 argument
            mkdirArgs.append(tempDestination);
            if (WINrunning)
            {
                //bool createWinRsyncCommand(tempDirPath,QFile command1,QFile command2,bool vss,QString rsyncArgs,QString source,QString dest);
                    QString command2=createWinRsyncCommand(tempDirPath,false,mkdirArgs);
                    ui.rsyncOutput->append("\n"+command2);
                if (command2=="")
                    cout << "\nfailed to create bat file in mkdirProccess";
                else
                    mkdirProcess -> start (command2);
            }
            else
                mkdirProcess -> start (command,mkdirArgs);
            
            mkdirProcess -> waitForFinished();
            if ((mkdirProcess -> exitCode()) == 0)
                ui.rsyncOutput->append("\n!!");
            else
                ui.rsyncOutput->append("\n!");
        }

        //set the current date and time as the operation's last execution date-time
        Operation[currentOperation] -> SetLastExecutionTime (QDateTime::currentDateTime());
        
        // add a new snapshot with the last execution date-time
        Operation[currentOperation] ->
                    AddSnapshotsListItem ((Operation[currentOperation] -> GetLastExecutionTime()).toString("yyyyMMddhhmmss"));
        currentSnaps = Operation[currentOperation] -> GetSnapshotsListSize();	// update the current number of snapshots
        
        // set a new changes file. This has a tag of the previous snapshot will include changes made to this snapshot
        snapchangesfilename = snapChangesDir + profileName + "-" + Operation[currentOperation] -> GetName() + "-" +
                    (Operation[currentOperation] -> GetSnapshotsListItem(currentSnaps - 1)) + ".changes.log";
        snapfile.setFileName(snapchangesfilename);
        
        // set a new logfile
        logfilename = logDir + profileName + "-" + Operation[currentOperation] -> GetName() + "-" +
            ( Operation[currentOperation] -> GetSnapshotsListItem(currentSnaps - 1) ) + ".log";
        logfile.setFileName(logfilename); // this is the logfile
        if (logfile.open(QIODevice::WriteOnly | QIODevice::Text))	//create a new log file
            writeToLog = TRUE;				//& if it's ok set this to TRUE
        else
            writeToLog = FALSE;
    }

    errorCount = 0;		// task starts, so set this to 0 no matter dry or real run

    // execute commands before task -----------------------------------------------------------------------------------------------------
    // if there are no (more) pre-task commands to be executed || 
                        // the previous pre-task command exited with an error(all repeatOnFail runs) and the stop checkbox is checked
    if ( (Operation[currentOperation] -> GetExecuteBeforeListSize() == currentBefore) || (StopTaskExecution) )
    {
        currentBefore = 0;
        ExecuteBefore=FALSE;
        repeatOnFailTry = 0;

        executeRsync();
    }
    else
    {
        ExecuteBefore=TRUE;
        ExecuteBeforeExitedError = FALSE;
        StopTaskExecution = FALSE;
        ProcReportedError = FALSE;      // This might change as soon as syncprocess will start ()
        outputInsert = logFileUpdate("pre-starting","",currentBefore);

        ui.rsyncOutput->append(outputInsert);

        syncProcess -> start (Operation[currentOperation] -> GetExecuteBeforeListItem(currentBefore));
        syncProcess -> waitForStarted(5000);
        
        // The reason for the below jump is that when a process reports an error it does not emit finished() signals neither std output/errors
        if (ProcReportedError)
            procFinished();
    }
}

//executes post-task commands ===============================================================================================
void luckyBackupWindow::executeAfterTask()
{
    if (ABORTpressed)		//better safe than sorry :)
        return;
    
    // execute commands after task -----------------------------------------------------------------------------------------------------
    //if there are no (more) post-task commands to be executed or we are here because a pre/post-task command exited with an error or destination could not be created
    if ( (Operation[currentOperation] -> GetExecuteAfterListSize() == currentAfter)|| (DestCreateFail) || (StopTaskExecution) )
    {
        if (!DryRun)
        {
            logfile.close();	//close the logfile first (will create a new one for the next task)
            Operation[currentOperation] -> SetLastExecutionErrors (errorCount);	// update the last execution errors
        }

        currentAfter = 0;
        ExecuteAfter=FALSE;

        errorCount = 0;		// reset the current task error count

        currentOperation++;
        //increase currentOperation until next operation to be executed or end of operations
        while ( (currentOperation < TotalOperations) && (!Operation[currentOperation] -> GetPerform()) )
            currentOperation++;
        if (currentOperation < TotalOperations)
        {
            ExecuteBeforeExitedError = FALSE;
            StopTaskExecution = FALSE;
            executeBeforeTask();
        }
        else
            setNowDoing();
    }
    else
    {
        ExecuteAfter=TRUE;
        ProcReportedError = FALSE;  // This might change as soon as syncprocess will start ()
        outputInsert = logFileUpdate("post-starting", "", currentAfter);
        ui.rsyncOutput->append(outputInsert);

        syncProcess -> start (Operation[currentOperation] -> GetExecuteAfterListItem(currentAfter));
        syncProcess -> waitForStarted(5000);
        
        // The reason for the below jump is that when a process reports an error it does not emit finished() signals neither std output/errors
        if (ProcReportedError)
            procFinished();
    }
}

//executes rsync  ===============================================================================================
void luckyBackupWindow::executeRsync()
{
    if (ABORTpressed)		//better safe than sorry :)
        return;
    
    if (StopTaskExecution)	// if a pre-task command exited with an error do not do anything
    {
        procFinished();
        return;
    }

    sync = Operation[currentOperation] -> GetTypeSync();		//set sync variable according to checkstate of radiobutton operation type
    rsyncArguments = AppendArguments(Operation[currentOperation]);	//set rsync arguments
    
    bool RemoteDestUsed = (Operation[currentOperation] -> GetRemoteDestination()) && (Operation[currentOperation] -> GetRemote()); // Is remote dest used ?

    if (DryRun)
        rsyncArguments.insert(rsyncArguments.size()-2,"--dry-run");

    dirA = rsyncArguments[rsyncArguments.size()-2];
    dirB = rsyncArguments[rsyncArguments.size()-1];
    
    if (sync)	//execute rsync for syncing 2 dirs
    {
        if (syncAB)	//execute rsync A -> B
            syncAB = FALSE;

        else		//execute rsync B -> A
        {
            rsyncArguments.removeLast();
            rsyncArguments.removeLast();
            rsyncArguments.append(dirB);	// set SyncDirA & SyncDirB as Arguments
            rsyncArguments.append(dirA);
            syncAB = TRUE;
        }
    }

    //display a couple of lines to inticate start of task
    if ((sync) && (!syncAB))
        outputInsert = logFileUpdate("rsync-starting-syncAB", "", 0);

    if ((sync) && (syncAB))
        outputInsert = logFileUpdate("rsync-starting-syncBA", "", 0);

    DestCreateFail = FALSE;	 // This will become TRUE if destination does not exist and cannot be created
    
    if (!sync)
    {
        outputInsert = logFileUpdate("rsync-starting-backup", "", 0);
        
        // Create the destination if it does not exist
        QDir destCreate (dirB);
        if ( (!destCreate.exists()) && (!RemoteDestUsed) ) // local use ONLY
        {
            if (destCreate.mkpath(dirB))
                outputInsert.append(logFileUpdate("rsync-standard", "<br>" + tr("Successfuly created destination directory"), 0));
            else
            {
                outputInsert.append(logFileUpdate("rsync-error", "<br>" +tr("Failed to create destination directory"), 0));
                ui.rsyncOutput->append(outputInsert);
                DestCreateFail = TRUE;
                errorsFound++;
                errorCount++;
                procFinished();	// Do not proceed any further
                return;
            }
        }
    }

    ui.rsyncOutput->append(outputInsert);
    //set the progressbar to 0
    ui.OperationProgress -> setRange(0,100);
    ui.OperationProgress -> setValue (0);
    
    ProcReportedError = FALSE;      // This might change as soon as syncprocess will start ()

    if (WINrunning)
    {
        //bool createWinRsyncCommand(tempDirPath,QFile command1,QFile command2,bool vss,QString rsyncArgs,QString source,QString dest);
        QString command2=createWinRsyncCommand(tempDirPath,Operation[currentOperation]->GetOptionsVss(),rsyncArguments);
        ui.rsyncOutput->append("\n"+command2);
        if (command2=="")
            cout << "\nfailed to create bat file for vss";
        else
            syncProcess -> start (command2);
    }
    else
        syncProcess -> start (command,rsyncArguments);	// execute rsync command with rsyncArguments
    
    // The reason for the below jump is that when a process reports an error it does not emit finished() signals neither std output/errors
    if (ProcReportedError)
        procFinished();
}

//when rsyncProcess emits finished signal execute another RsyncProcess if any left====================================================================
void luckyBackupWindow::procFinished()
{
    if (ABORTpressed) //this is to prevent segmentation fault when abort button pressed
        return;

    /* Disable VSS until
    if (doVss==1) //reads all log file in vss before finished
    {
        doVss=2;
        return;
    }*/
      
    bool RemoteDestUsed = (Operation[currentOperation] -> GetRemoteDestination()) && (Operation[currentOperation] -> GetRemote()); // Is remote dest used ?
    if (ExecuteBefore)		// if the pre-task execution command (process) finished
    {
        outputInsert = logFileUpdate("pre-finished", "", currentBefore);
        ui.rsyncOutput->append(outputInsert);
        
        // set this for a successful run of a command. They might change if there was an error
        ExecuteBeforeExitedError = FALSE;
        StopTaskExecution = FALSE;
            
        // if the pre-task command exited with an error
        if ((syncProcess -> exitCode() != 0) || (ProcReportedError))
        {
            ExecuteBeforeExitedError = TRUE;
            
            if (repeatOnFailTry == repeatOnFailMax) // if the last run of the command just ended
            {
                if (Operation[currentOperation] -> GetExecuteBeforeListItemState(currentBefore) == TRUE)
                    StopTaskExecution = TRUE;
                repeatOnFailTry = 0;    // reset the runs counter for a specific command
                currentBefore++;    //go to the next pre-task execution command
            }
            else
            {
                outputInsert = logFileUpdate("repeat-on-fail", "", currentBefore);
                ui.rsyncOutput->append(outputInsert);
                repeatOnFailTry++;  // re-run this command, do not proceed to the next one
            }
        }
        else        // if the process was successful, go to the next one
        {
            currentBefore++;    //go to the next pre-task execution command
            repeatOnFailTry = 0;    // it should already be 0, but ...you never know
        }

        executeBeforeTask();    //and executeBeforeTask again

        return;
    }

    if (ExecuteAfter)		// if the post-task execution command (process) finished
    {
        outputInsert = logFileUpdate("post-finished", "", currentAfter);
        ui.rsyncOutput->append(outputInsert);
        
        // set this for a successful run of a command. They might change if there was an error
        StopTaskExecution = FALSE;
        
        // if the post-task command exited with an error
        if ((syncProcess -> exitCode() != 0) || (ProcReportedError))
        {    
            if (repeatOnFailTry == repeatOnFailMax) // if the last run of the command just ended
            {
                if (Operation[currentOperation] -> GetExecuteAfterListItemState(currentAfter) == TRUE)
                    StopTaskExecution = TRUE;
                repeatOnFailTry = 0;     //rest the counter for a specific command
                currentAfter++;    //go to the next pre-task execution command
            }
            else
            {
                outputInsert = logFileUpdate("repeat-on-fail", "", currentAfter);
                ui.rsyncOutput->append(outputInsert);
                repeatOnFailTry++;  // re-run this command, do not proceed to the next one
            }
        }
        else        // if the process was successful, go to the next one
            currentAfter++;    //go to the next post-task execution command

        executeAfterTask();		//and executeAfterTask again
        return;
    }

    //display a couple of lines to indicate end of task
    if (StopTaskExecution)
        outputInsert = logFileUpdate("pre-task-exited-with-error", "", 0);
    else
    {
        if (!DryRun)
        {
            // strip unused lines from the snapshot changes file ~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
            QString filesAdded = "", snapLine = "";
            if (snapfile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                ui.rsyncOutput->append(".");
                QTextStream in(&snapfile);
                while (!in.atEnd())
                {
                    snapLine = in.readLine();
                    if (snapLine.contains("+++++++", Qt::CaseInsensitive))
                    {
                        snapLine = snapLine.right(snapLine.size()-snapLine.lastIndexOf("[LB]")-removeCharLimit) + "\n";
                        filesAdded.append(snapLine);
                    }
                }
                snapfile.close();
                filesAdded.remove("[LB]", Qt::CaseSensitive);        // just to make sure cause sometimes there are [LB]'s left
            }
            if (snapfile.open(QIODevice::WriteOnly))
            {
                ui.rsyncOutput->append(".");
                QTextStream out(&snapfile);
                out << filesAdded;
                snapfile.close();
            }
        }
            
        if ((!sync) || ((sync) && (syncAB)) )
        {
            // Backup profile + logs + snaps to destination ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
            QString exportProfileDir = "";  QString sourceLast=Operation[currentOperation] -> GetSource();
            //calculate the last folder of source
            if (!sourceLast.endsWith(SLASH))    // this means task is of type "backup dir by name"
                sourceLast = calculateLastPath(sourceLast); // This is the lowest dir of the source
            else
                sourceLast = "";
            
            if (!rsyncArguments.isEmpty())      //rsyncArguments is calculated at executeRsync()
            {
                if (WINrunning && RemoteDestUsed)
                    exportProfileDir = rsyncArguments.last() + sourceLast + XnixSLASH + snapDefaultDir + profileName + ".profile" + XnixSLASH;
                else
                    exportProfileDir = rsyncArguments.last() + sourceLast + SLASH + snapDefaultDir + profileName + ".profile" + SLASH;
            }
            
            //QMessageBox::information(this, "LB",exportProfileDir);    //TESTING
            
            outputInsert = "";
            
            // If this is a backup task && not a dryrun, backup profile data to destination
            if ( (!sync) && (!DryRun) && (!rsyncArguments.isEmpty()) )
            {
                // Create the export path if it does not exist
                // local use
                QDir exportPathCreate (exportProfileDir);
                if ( (!exportPathCreate.exists()) && (!RemoteDestUsed) )
                    exportPathCreate.mkpath(exportProfileDir);
                    
                if (exportFullProfile(exportProfileDir,"ExportOnlyTask"))
                    outputInsert = logFileUpdate("backup-profile", " -> Ok", currentAfter);
                else
                    outputInsert = logFileUpdate("backup-profile", " -> Fail", currentAfter);
                
            }
            
            outputInsert.append(logFileUpdate("rsync-finished", "", 0));
        }
        else
            outputInsert = logFileUpdate("rsync-finished-sync1", "", 0);
    }
    
    ui.rsyncOutput->append(outputInsert);
    
    /* If there is an error repeat the rsync command. Errors:
                                5 - Error starting client-server protocol
                                12 - Error in rsync protocol data stream
                                23 - Partial transfer due to error -> I took this out
                                30 - Timeout in data send/receive 
                                35 - Timeout waiting for daemon connection
                                255 - unexplained error */
    if ((repeatOnFailTry < repeatOnFailMax) &&
          ( (syncProcess -> exitCode()==30) || (syncProcess -> exitCode()==35) || (syncProcess -> exitCode()==255) ||
            (syncProcess -> exitCode()==12) || (syncProcess -> exitCode()==5) || (ProcReportedError) ))
    {
        outputInsert = logFileUpdate("repeat-on-fail", "", 0);
        ui.rsyncOutput->append(outputInsert);
        repeatOnFailTry++;
        executeRsync();
        return;
    }
    else
        repeatOnFailTry = 0;    // reset the runs counter

    if ( (sync) && (!syncAB) )	//sync A->B is finished. Do the opposite now before proceeding to next included operation or post-task commands
        executeRsync();
    else
        executeAfterTask();	//execute post-task commands (if any)
}

// A process reported an error (eg failed to start or crashed etc)
void luckyBackupWindow::procError()
{
    ProcReportedError = TRUE;
    QProcess::ProcessError commandError = syncProcess -> error();
    QString errorText = tr("Unknown error");
    switch (commandError)
    {
        case QProcess::FailedToStart: errorText = tr("Failed to start","this refers to a process");
        break;
        case QProcess::Crashed      : errorText = tr("Crashed","this refers to a process");
        break;
        case QProcess::Timedout     : errorText = tr("Timed out","this refers to a process");
        break;
        case QProcess::WriteError   : errorText = tr("Write error","this refers to a process");
        break;
        case QProcess::ReadError    : errorText = tr("Read error","this refers to a process");
        break;
        case QProcess::UnknownError : errorText = tr("Unknown error","this refers to a process");
        break;
    }
    
    errorsFound++;
    errorCount++;
    ui.rsyncOutput->append(logFileUpdate("process-reported-error", errorText, 0));
    setNowDoing();    
}
//update dialog with new data (text - progressbar) - also update logfile =======================================================================
void luckyBackupWindow::appendRsyncOutput()
{
    if (ABORTpressed)		//better safe than sorry :)
        return;
    
    setNowDoing ();		//update Nowdoing textBrowser
    
    //update textBrowser ------------------------------------------------------------------------------------------------------
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    outputString = codec->toUnicode(syncProcess -> readAllStandardOutput());
    outputError = codec->toUnicode(syncProcess -> readAllStandardError());

    //if (!showOnlyErrors)
    if (!ui.checkBox_onlyShowErrors -> isChecked())
        ui.rsyncOutput->append(outputString);
    
    
    logFileUpdate("rsync-standard", outputString, 0);
    
    if (outputError !="")
    {
        errorsFound++;
        errorCount++;
        ui.rsyncOutput->append(logFileUpdate("rsync-error", outputError, 0));
    }
    
    //update progressbar--------------------------------------------------------------------------------------------------------
    bool ok;
    if ( (outputString.contains("to-check")) || (outputString.contains("to-chk")) )	//we will calculate how many files have been proccessed so far
    {
        //DoneToTotal_Ref & DoneToTotal_String hold a e.g. "17/84"
        QStringRef DoneToTotal_Ref;
        if (outputString.contains("to-check"))  // if rsync uses "to-check="
            DoneToTotal_Ref = outputString.midRef(outputString.indexOf("check=")+6,outputString.indexOf(")")-outputString.indexOf("check=")-6);
        else                                    // if rsync uses "to-chk="
            DoneToTotal_Ref = outputString.midRef(outputString.indexOf("o-chk=")+6,outputString.indexOf(")")-outputString.indexOf("o-chk=")-6);
        QString DoneToTotal_String = DoneToTotal_Ref.toString();

        //Total no files
        QStringRef ref_temp = DoneToTotal_String.rightRef(DoneToTotal_String.size() - DoneToTotal_String.indexOf(SLASH) -1);
        QString string_temp = ref_temp.toString();
        progress_total = string_temp.toInt(&ok,10);
        ui.OperationProgress -> setRange(0,progress_total);	//set the range of the progressbar to the no of files to consider

        //No of files processed so far
        ref_temp = DoneToTotal_String.leftRef(DoneToTotal_String.indexOf(SLASH));
        string_temp = ref_temp.toString();
        progress_done = string_temp.toInt(&ok,10);
        progress_done = progress_total - progress_done;
        ui.OperationProgress -> setValue (progress_done);	//set the current progressbar value 
    }
    if (outputString.contains("speedup is"))	//the process has finished, so if we're back fill it to 100%
    {
        ui.OperationProgress -> setRange(0,100);
        ui.OperationProgress -> setValue (100);
    }
    if (outputString.contains("building file list"))
    {
        calculating = TRUE;
        transferring = FALSE;
        deleting = FALSE;
    }
    if (outputString.contains("files to consider"))
    {
        calculating = FALSE;
        transferring = TRUE;
        deleting = FALSE;
    }
    if (outputString.contains("deleting"))
    {
        calculating = FALSE;
        transferring = FALSE;
        deleting = TRUE;
    }
    
    // Extraxt some data from the "stats" lines at the end of rsync
    if ( (outputString.contains("Number of files transferred")) || (outputString.contains("Total bytes sent:")) || (outputString.contains("Number of regular files")) )
    {
        // split the outputString to lines
        QString FilesTransferedString="",BytesTransferedString="";
        QStringList lines = outputString.split( "\n", QString::SkipEmptyParts );
        foreach( QString line, lines )
        {
            if (line.contains("Number of files transferred:"))
                FilesTransferedString = line.remove("Number of files transferred: ");          // old rsync report;
            if (line.contains("Number of regular files transferred:"))
                FilesTransferedString = line.remove("Number of regular files transferred: ");  // newer rsync report
            if (line.contains("Total transferred file size:"))
                BytesTransferedString = line.remove("Total transferred file size: ");           // newer rsync report
            if (line.contains("Total bytes sent:"))
                BytesTransferedString = line.remove("Total bytes sent: ");             // old rsync report
        }

        filesTransfered = filesTransfered + FilesTransferedString.toInt(&ok, 10);

        BytesTransferedString = convertBytes(BytesTransferedString,FALSE);       
        bytesTransfered = bytesTransfered + BytesTransferedString.toULongLong(&ok, 10);
    }
}

/*  disable vss until...
void luckyBackupWindow::appendRsyncVssOutput()
{
    appendRsyncVssOutput(vssReadSize);
}

//Read size lines, if size=-1 read all file
void luckyBackupWindow::appendRsyncVssOutput(int size)
{
    if (ABORTpressed)       //better safe than sorry :)
        return;
    if (doVss==0)
    return;
    setNowDoing ();     //update Nowdoing textBrowser



    QString s,se;
    if (pipeVssFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int i=size;
        QTextStream stream(pipeVssFile);
        stream.setCodec("UTF-8");
        stream.seek(vssPos);
        outputString="";
        s=stream.readLine();
        while(!s.isNull()&&i!=0){
            outputString=outputString+s+"\n";
            s=stream.readLine();
            //if (!showOnlyErrors)
            i--;
        };
        vssPos=stream.pos();
        pipeVssFile->close();
        if (outputString !="")
        {
            if (!ui.checkBox_onlyShowErrors -> isChecked())
                ui.rsyncOutput->append(outputString);
            logFileUpdate("rsync-standard", outputString, 0);
            //update progressbar--------------------------------------------------------------------------------------------------------
            bool ok;
            if (outputString.contains("to-check"))  //we will calculate how many files have been proccessed so far
            {
                //DoneToTotal_Ref & DoneToTotal_String hold a e.g. "17/84"
                QStringRef DoneToTotal_Ref = outputString.midRef(outputString.indexOf("check=")+6,outputString.indexOf(")")-outputString.indexOf("check=")-6);
                QString DoneToTotal_String = DoneToTotal_Ref.toString();

                //Total no files
                QStringRef ref_temp = DoneToTotal_String.rightRef(DoneToTotal_String.size() - DoneToTotal_String.indexOf(SLASH) -1);
                QString string_temp = ref_temp.toString();
                progress_total = string_temp.toInt(&ok,10);
                ui.OperationProgress -> setRange(0,progress_total); //set the range of the progressbar to the no of files to consider

                //No of files processed so far
                ref_temp = DoneToTotal_String.leftRef(DoneToTotal_String.indexOf(SLASH));
                string_temp = ref_temp.toString();
                progress_done = string_temp.toInt(&ok,10);
                progress_done = progress_total - progress_done;
                ui.OperationProgress -> setValue (progress_done);   //set the current progressbar value
            }
            if (outputString.contains("speedup is"))    //the process has finished, so if we're back fill it to 100%
            {
                ui.OperationProgress -> setRange(0,100);
                ui.OperationProgress -> setValue (100);
            }
            if (outputString.contains("building file list"))
            {
                calculating = TRUE;
                transferring = FALSE;
                deleting = FALSE;
            }
            if (outputString.contains("files to consider"))
            {
                calculating = FALSE;
                transferring = TRUE;
                deleting = FALSE;
            }
            if (outputString.contains("deleting"))
            {
                calculating = FALSE;
                transferring = FALSE;
                deleting = TRUE;
            }
        }
    }
    if (pipeVssErrFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
            int i=size;
        QTextStream stream(pipeVssErrFile);
        stream.setCodec("UTF-8");
        stream.seek(vssErrPos);
        outputError="";
        se=stream.readLine();
        while(!se.isNull()&&i!=0){
            outputError=outputError+se+"\n";
            se=stream.readLine();
            i--;
        }

        vssErrPos=stream.pos();
        pipeVssErrFile->close();
        if (outputError !="")
        {
            errorsFound++;
            errorCount++;
            ui.rsyncOutput->append(logFileUpdate("rsync-error", outputError, 0));
        }
    }
    if (doVss == 2 && se.isNull() && s.isNull())
    {
        vssTimer->stop();
        doVss = 0;
        pipeVssFile->remove();
        pipeVssErrFile->remove();
        procFinished();

    }
}
*/
//updates Now Doing textBrowser ===============================================================================================================
void luckyBackupWindow::setNowDoing()
{
    //calculate elapsed time since all operations start
    QTime DifTime(0,0,0,0);
    int elapsedMsec = StartTime.elapsed();
    DifTime = DifTime.addMSecs(elapsedMsec);
    
    if ( (currentOperation < TotalOperations) && (!ABORTpressed) )
    {
        if (ExecuteBefore)
            nowDoingText = 	"<p align=\"center\">"+tr("Elapsed time")+" : <b><font color=red>" + DifTime.toString("hh:mm:ss") +
                    "</font></b><br>"+tr("pre-task execution of command")+"	: <b>" +
                    Operation[currentOperation] -> GetExecuteBeforeListItem(currentBefore) + "</b>";

        if (ExecuteAfter)
            nowDoingText = 	"<p align=\"center\">"+tr("Elapsed time")+" : <b><font color=red>" + DifTime.toString("hh:mm:ss") +
                    "</font></b><br>"+tr("post-task execution of command")+"	: <b>" +
                    Operation[currentOperation] -> GetExecuteAfterListItem(currentAfter) + "</b>";

        if ( (sync) && (!ExecuteAfter) && (!ExecuteBefore) )	//if a sync operation is executed
        {
            nowDoingText = 	"<p align=\"center\">"+tr("Elapsed time")+" : <b><font color=red>" + DifTime.toString("hh:mm:ss") +
                    "</font></b><br>"+tr("Now performing task")+"	: <b>" + Operation[currentOperation] -> GetName() +
                    "</b>";

            if (DryRun)
                nowDoingText.append(" <b><font color=magenta>(" + tr("simulation mode") + ")</font>");

            nowDoingText.append("</p>");
            nowDoingText.append(tr("Directory")+" A	: <b><font color=blue>" + dirA +
                    "</font></b><br>"+tr("Directory")+" B	: <b><font color=blue>" + dirB + "</font></b><br>");
            
            if (calculating)
                nowDoingText.append(tr("calculating","info message displayed during ...calculations")+": " + outputString);
            if (transferring)
                nowDoingText.append(tr("transferring files","info message displayed during ...file transfers")+": " + outputString);
            if (deleting)
                nowDoingText.append(tr("deleting files","info message displayed during ...file deletions")+": " + outputString);
        }

        if ( (!sync) && (!ExecuteAfter) && (!ExecuteBefore) ) //if a backup operation is executed
        {
            nowDoingText = 	"<p align=\"center\">"+tr("Elapsed time")+" : <b><font color=red>" + DifTime.toString("hh:mm:ss") +
                    "</font></b><br>"+tr("Now performing task")+"	: <b>" + Operation[currentOperation] -> GetName() +
                    "</b>";

            if (DryRun)
                nowDoingText.append(" <b><font color=magenta>(" + tr("simulation mode") + ")</font>");

            nowDoingText.append("</p>");
            nowDoingText.append(tr("Source")+"	: <b><font color=blue>" + dirA +
                    "</font></b><br>"+tr("Destination")+"	: <b><font color=blue>" + dirB + "</font></b><br>");

            if (calculating)
                nowDoingText.append(tr("calculating")+": " + outputString);
            if (transferring)
                nowDoingText.append(tr("transferring files")+": " + outputString);
            if (deleting)
                nowDoingText.append(tr("deleting files")+": " + outputString);
        }
    }
    
    if ( (currentOperation == TotalOperations) && (!ABORTpressed))	//if all operations finished normally - not aborted
    {
        NOWexecuting = FALSE;		//this is mainly used if the window close button (or alt+F4) is pressed

        if (filesTransfered == 0)
            bytesTransfered = 0;
        
        nowDoingText = 	"<p align=\"center\">"+tr("Elapsed time")+" : <b><font color=red>" + DifTime.toString("hh:mm:ss") +
                "</font></b><br>" +
                tr("Total files transfered") + " : <b>" + countStr.setNum(filesTransfered) + "</b> (" + convertBytes(QString::number(bytesTransfered),TRUE) +")<br>"
                "========================================="
                "<b><br><font color=blue>"+tr("All tasks completed")+" </font></b>";
        trayMessage =	tr("All tasks completed");
        if (DryRun)
        {
            nowDoingText.append(" <b><font color=magenta>(" + tr("simulation mode") + ")</b></font>");
            trayMessage.append(" (" + tr("simulation mode") + ")");
        }
        if (errorsFound == 0)
        {
            nowDoingText.append("<br><font color=green>" + tr("No errors found") + "</font><br>");
            trayMessage.append("\n" + tr("No errors found"));
        }
        else
        {
            nowDoingText.append("<br><font color=green>" + tr("errors found") + ": " + countStr.setNum(errorsFound) +"</font><br>");
            trayMessage.append("\n" + tr("errors found"));

            // initialize jump to next error button 
            firstScroll=TRUE;
            errorCount = 0;
            ui.pushButton_nextError	-> setEnabled (TRUE);
        }
        if (!DryRun)
            nowDoingText.append(tr("logfile(s) have been created under directory: ")+ logDir +"<br>");
        nowDoingText.append("=========================================</p>");
        ui.AbortButton -> setVisible (FALSE);
        ui.DoneButton -> setVisible (TRUE);
        ui.pushButton_minimizeToTray	-> setVisible (FALSE);
        
        //update tray baloon
        if ( (QSystemTrayIcon::isSystemTrayAvailable ()) && (QSystemTrayIcon::supportsMessages ()) )
        {
            if (KDErunning)
            {
                QProcess *dialogProcess;    dialogProcess = new QProcess(this);
                QStringList dialogArgs;
                dialogArgs << "--title" << appName + " - " + tr("execution of profile:") + " " + profileName + " " + tr("finished") << "--passivepopup" << trayMessage << "10";
                dialogProcess -> start ("kdialog",dialogArgs);
            }
            else
                LBtray -> showMessage (appName + " - " + tr("execution of profile:") + " " + profileName + " " + tr("finished") , trayMessage, 
                                                    QSystemTrayIcon::Information,3000);
            actionAbort	-> setVisible(FALSE);
        }

        finishUp();
        
        // bring the system down if the relevant button is pressed
        if (ui.pushButton_shutdown -> isChecked())
            shutDownSystem();
        
        if ( (silentMode) && (isMinimizedToTray == TRUE) )		// if --silent is given as argument and the gui is not shown exit the app
        {
            //delay the app exit for 3 seconds
            QTime StartSleep(0,0,0,0);
            StartSleep.start();
            int elapsedSleepMsec = 0;

            while (elapsedSleepMsec < 3000)
                elapsedSleepMsec = StartSleep.elapsed();
            
            exit(0);	//quit
        }
    }
    
    if (ABORTpressed)	//if operations were terminated by user
    {
        NOWexecuting = FALSE;		//this is mainly used if the window close button (or alt+F4) is pressed
        nowDoingText = 	"<p align=\"center\">"+tr("Elapsed time")+" : <b><font color=red>" + DifTime.toString("hh:mm:ss") +
                "</font></b><br>========================================="
                "<br><b><font color=blue>"+tr("Execution of tasks were terminated violently by user")+"</font></b><br>";
        trayMessage = 	tr("Execution of tasks were terminated violently by user");
        
        if (!DryRun)
            nowDoingText.append(tr("logfile(s) have been created under directory: ")+ logDir +"<br>");
        nowDoingText.append("=========================================</p>");
        ui.AbortButton -> setVisible (FALSE);
        ui.DoneButton -> setVisible (TRUE);
        ui.pushButton_minimizeToTray	-> setVisible (FALSE);
        ui.rsyncOutput->append("<br><font color=red><b>" + tr("ABORTED") + " !!</b></font>");
        
        //update tray baloon
        if ( (QSystemTrayIcon::isSystemTrayAvailable ()) && (QSystemTrayIcon::supportsMessages ()) )
        {
            if (KDErunning)
            {
                QProcess *dialogProcess;    dialogProcess = new QProcess(this);
                QStringList dialogArgs;
                dialogArgs << "--title" << appName + " - " + tr("execution of profile:") + " " + profileName + " " + tr("finished") << "--passivepopup" << trayMessage << "10";
                dialogProcess -> start ("kdialog",dialogArgs);
            }
            else
                LBtray -> showMessage (appName + " - " + tr("execution of profile:") + " " + profileName + " " + tr("finished") , trayMessage, 
                                                            QSystemTrayIcon::Information,3000);
            actionAbort	-> setVisible(FALSE);
        }

        if  (errorsFound > 0)// initialize jump to next error button 
        {
            firstScroll=TRUE;
            ui.pushButton_nextError	-> setEnabled (TRUE);
        }

        finishUp();
        if (!DryRun)
        {
            // strip unused lines from the snapshot changes file ~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
            QString filesAdded = "", snapLine = "";
            if (snapfile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&snapfile);
                while (!in.atEnd())
                {
                    snapLine = in.readLine();
                    if (snapLine.contains("+++++++", Qt::CaseInsensitive))
                    {
                        snapLine = snapLine.right(snapLine.size()-snapLine.lastIndexOf("[LB]")-removeCharLimit) + "\n";
                        filesAdded.append(snapLine);
                    }
                }
                snapfile.close();
                filesAdded.remove("[LB]", Qt::CaseSensitive);    // just to make sure cause sometimes there are [LB]'s left
            }
            if (snapfile.open(QIODevice::WriteOnly))
            {
                QTextStream out(&snapfile);
                out << filesAdded;
                snapfile.close();
            }
        }
        
        if ( (silentMode) && (isMinimizedToTray == TRUE) )		// if --silent is given as argument and the gui is not shown, exit the app
            exit(0);	//quit
    }
    ui.nowDoing -> setText (nowDoingText);
}

// function finishUp=====================================================================================================
// finish up some stuff when all tasks finish either normally or aborted
void luckyBackupWindow::finishUp()
{
    if (!DryRun)
    {
        //save the profile to update last execution times & no of errors
        if (!saveProfile(currentProfile))
        {
            savedProfile = FALSE;
            ui.actionSave -> setEnabled(TRUE);
        }
        else
        {
            savedProfile = TRUE;			//change profile status to "saved"
            ui.actionSave -> setEnabled(FALSE);
        }
            
        logfile.close();			// close the logfile
        
        // send an email
        if ( (!ABORTpressed) && (!emailNever) )
        {
            bool send = TRUE;
            if ( ((emailError) && (errorsFound == 0))   // do not send if the condition "error" is checked and there are no errors
                    ||
                ((emailSchedule) && (!silentMode)) )  // do not send if the condition "scheduled" is checked and profile is not run in silent mode
                
                send = FALSE;
            
            // ***** console mode and "schedule" is covered in commandline.cpp ******
            
            if (send)
            {
                ui.rsyncOutput->append("<font color=green>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~</font>");
                ui.rsyncOutput->append(tr(  "trying to send an email"));
                ui.rsyncOutput->append(     "       . . .");
                ui.rsyncOutput->append(sendEmailNow(FALSE));
            }
        }
    }
    
    shutdownToolbar-> setEnabled (FALSE);

    // TESTING-TESTING-TESTING-TESTING-TESTING-TESTING
    //QMessageBox::information(this, "LB","QtextDocument title= **" + ui.rsyncOutput->documentTitle() +"**");
}

// function shutDownSystem=====================================================================================================
// shutdown the system if the relevant button is pressed, when all tasks are finished
void luckyBackupWindow::shutDownSystem()
{
    QProcess *shutdownProcess;
    shutdownProcess = new QProcess(this);
    QString shutdownCommand="";    QStringList shutdownArgs;    shutdownArgs.clear();
    
    if (KDErunning)
    {
        shutdownCommand = "/usr/bin/qdbus";
        shutdownArgs << "org.kde.ksmserver" << "/KSMServer" << "org.kde.KSMServerInterface.logout" << "1" << "2" << "2";
    }
    else if (currentUser == "super user")
    {
        shutdownCommand = "/sbin/shutdown";
        shutdownArgs << "-h" << "1";
        if ( (QSystemTrayIcon::isSystemTrayAvailable ()) && (QSystemTrayIcon::supportsMessages ()) )
            LBtray -> showMessage (appName + " - " + tr("WARNING"), tr("The system will shutdown in 1 minute"), QSystemTrayIcon::Information,3000);
    }
    
    shutdownProcess -> start (shutdownCommand,shutdownArgs);
    
    //delay the app exit for 3 seconds
    QTime StartSleep(0,0,0,0);
    StartSleep.start();
    int elapsedSleepMsec = 0;
    while (elapsedSleepMsec < 3000)
        elapsedSleepMsec = StartSleep.elapsed();
    exit(0);    //quit
}

// previous error button pressed=====================================================================================================
void luckyBackupWindow::previousErrorJump()
{
    errorCount--;		//decrease the current error by one

    if (errorCount == 0 )		// if the current error is the first within the logfile disable the previous button
        ui.pushButton_previousError -> setEnabled(FALSE);
    
    if (errorCount < errorsFound-1)	//if the current error is less than the last one within the logfile enable the next button
        ui.pushButton_nextError -> setEnabled(TRUE);
    
    ui.rsyncOutput -> scrollToAnchor("error" + countStr.setNum(errorCount+1));
}

// next error button pressed=====================================================================================================
void luckyBackupWindow::nextErrorJump()
{
    if (!firstScroll)
        errorCount++;	// increase the current error by one
    firstScroll = FALSE;
    
    if (errorCount == errorsFound-1)		// If the current error is the last within the logfile disable the next button
        ui.pushButton_nextError -> setEnabled(FALSE);
    
    if (errorCount > 0)				// if the current error is greater than the first one within the logfile enable the previous button
        ui.pushButton_previousError -> setEnabled(TRUE);
    
    ui.rsyncOutput -> scrollToAnchor("error" + countStr.setNum(errorCount+1));
}

// convertBytes (QString,bool)
// Converts a string of the form 67M to bytes and vice versa (eg 1024 -> 1KB)
// if bool=FALSE then conversion string->bytes. If bool=TRUE then conversion bytes->string
// =====================================================================================================
QString luckyBackupWindow::convertBytes (QString byteLine,bool toWhat)
{
    QString returnThis = "";
    bool ok;
   
    if (toWhat)           // convert bytes to string
    {
        QString multi = " bytes";
        double bytesFLOAT = byteLine.toDouble(&ok);
       
        if (bytesFLOAT >=  1024)
        {
            bytesFLOAT = bytesFLOAT / 1024;
            multi = "KB";
        }
        if (bytesFLOAT >= 1024)
        {
            bytesFLOAT = bytesFLOAT / 1024;
            multi = "MB";
        }
        if (bytesFLOAT >= 1024)
        {
            bytesFLOAT = bytesFLOAT / 1024;
            multi = "GB";
        }
        if (bytesFLOAT >= 1024)
        {
            bytesFLOAT = bytesFLOAT / 1024;
            multi = "TB";
        }
        returnThis = (QString::number(bytesFLOAT));
        if ( (returnThis.contains(".")) && ((returnThis.lastIndexOf(".") + 3) < returnThis.size()) )
            returnThis.chop(returnThis.size() - returnThis.lastIndexOf(".") - 3);   // leave only 3 decimal points
        returnThis = returnThis + multi;
    }
    else            // convert string to bytes
    {
        unsigned long int multiply = 1;
        
        if (byteLine.endsWith("K"))
            multiply = 1024;
        if (byteLine.endsWith("M"))
            multiply = pow(1024.0,2);
        if (byteLine.endsWith("G"))
            multiply = pow(1024.0,3);
        if (byteLine.endsWith("T"))
            multiply = pow(1024.0,4);

        if (    (byteLine.endsWith("K")) || (byteLine.endsWith("M")) ||
                (byteLine.endsWith("G")) || (byteLine.endsWith("T")) )
            byteLine.chop(1);
        
        unsigned long long int returnThisNo = byteLine.toDouble(&ok) * multiply;
        returnThis = QString::number( returnThisNo);
    }

    return returnThis;

}
// end of executenow.cpp ---------------------------------------------------------------------------

