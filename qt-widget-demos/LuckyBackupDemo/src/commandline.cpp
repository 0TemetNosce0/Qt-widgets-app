/*-------------------------commandline.cpp------------------------------------------
 runs luckybackup in command line mode

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
     along with luckyBackup.  If not,see <http://www.gnu.org/licenses/>.
 developer      : luckyb 
 last modified  : 06 Feb 2014
===============================================================================================================================
===============================================================================================================================
*/

#include "luckybackupwindow.cpp"
#include "commandline.h"

// class commandline Constructor=================================================================================================
commandline::commandline()
{
    writeToLog=FALSE;
    errorsFound = 0;	// Total number of errors from all tasks (in CLI, only 1 error per task is allowed !!)
    filesTransfered = 0;    //total bytes transfered during profile execution
    bytesTransfered = 0;    //total bytes transfered during profile execution
    errorCount = 0;		// Number of errors from one task (max value is 1)
}

// class commandline Destructor=================================================================================================
commandline::~commandline()
{
}

// result===================================================================================================================
// calls functions intro, loadProfile, check_list, check_dirs, rsyncIT, thats_all and returns an integer to main()
int commandline::result()
{
    intro();
    
    rsyncIT();
    thats_all();

    if (errorsFound > 0)
        return 6;		// error at rsync or pre/post command execution

    return 0;
}

// intro===================================================================================================================
// displays an intro message
void commandline::intro()
{
    cout << "\n============================================================================================\n";
    cout << "		luckybackup version ";
    cout << appVersion;
    cout << " - command line mode \n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    cout << "This application will (hopefully) sync and backup everything you need in no time\n";
    cout << "(Well, it might take a little longer if run for the first time ;-)\n\n";
    cout << "\n";
    if (!NoQuestions)	//if questions are required
    {
        cout <<  "Make sure that:\n";
        cout <<  "You have already declared and mounted all the directories that need to be synced/backed-up\n";
        cout <<  "Please take a moment to examine all messages from checks done until now\n\n";
        cout <<  "Also have in mind that, to avoid errors, it is best to run this app as su\n\n";
        cout <<  "Hit 'enter' to continue otherwise press 'ctrl+c' to exit NOW\n";
        cin.get();
    }
    cout << "\n\n";
}



// rsyncIT===================================================================================================================
// Performs the execution of operations
void commandline::rsyncIT()
{
    cout << "\n============================================================================================\n";
    cout << "				Executing tasks";
    if (DryRun)
        cout << "  (simulation mode)";
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

    //some useful variables-----------------------------------------------------------------------
    QProcess *syncProcess;	syncProcess = new QProcess;	//create a new qprocess (for rsync)
    QString command = rsyncCommandPath;	//command to be executed. Normally this is "rsync"
    QString command2="";                // windows use
    QStringList rsyncArguments;	// This stringList holds all arguments for the rsync command
    QString dirA;			//holds the first dir to be synced
    QString dirB;			//holds the second dir to be synced
    QString logText="";		//This text will be appended to the logfile
    
    currentOperation = 0;
    
    while (currentOperation < TotalOperations)
    {
        if (WINrunning)
        {
            setAppDir(Operation[currentOperation] -> GetLuckyBackupDir());
            /* disable vss until...
            pipeVssFile =  new QFile(Operation[currentOperation] -> GetTempPath()+SLASH+"qt_tempvss"+QString::number(qrand() % (999998) + 1));
            if (pipeVssFile->open(QIODevice::ReadWrite)){
                pipeVssFile->close();
            }
            pipeVssErrFile =  new QFile(Operation[currentOperation] -> GetTempPath()+SLASH+"qt_tempvsserr"+QString::number(qrand() % (999998) + 1));
            if (pipeVssErrFile->open(QIODevice::ReadWrite)){
                pipeVssErrFile->close();
            }*/
        }
          
        //if --skip-critical is given as argument and the task is CRITICAL
        if ( (Operation[currentOperation] -> GetCRITICAL()) && (SkipCritical) )	
            Operation[currentOperation] -> SetPerform(FALSE);	//don't perform this operation

        if ( (Operation[currentOperation] -> GetPerform()) || (Operation[currentOperation] -> GetByPassWARNING()) )
        {
            bool RemoteDestUsed = (Operation[currentOperation] -> GetRemoteDestination()) && (Operation[currentOperation] -> GetRemote());
            
            // SNAPSHOTS REMOVAL - This is outside the (currentSnaps >= maxSnaps) condition, because it will eventually cause the snapshots directory to get created so that the profile will be backed up without problems later on
            // First calculate the folder where snapshots go
            QStringList tempArguments = Operation[currentOperation] -> GetArgs();
            QString tempSource = tempArguments[tempArguments.size()-2];
            QString tempDestination     = tempArguments[tempArguments.size()-1];
            QString tempDestinationOrig = tempArguments[tempArguments.size()-1]; //windows use
            QString tempDestinationOrig2;
            QString sourceLast = tempSource;
            
            // win stuff ~~~~~
            QString tslash;
            if (WINrunning)
                tslash=XnixSLASH;
            else
                tslash=SLASH;

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
                if ( (Operation[currentOperation]-> GetRemoteModule()) && (Operation[currentOperation] -> GetRemotePassword() != "") )
                    remoteArgs.append("--password-file=" + ( Operation[currentOperation] -> GetRemotePassword()) );
                if ( Operation[currentOperation] -> GetRemoteSSH())
                {
                    QString sshOptions=(Operation[currentOperation] -> GetRemoteSSHOptions()).replace("\"","\\\"")+" -o \"StrictHostKeyChecking no\"  -o \"PasswordAuthentication no\" ";
                    if (WINrunning)
                    {
                        if (
                            Operation[currentOperation] -> GetRemoteSSHPassword() != "")
                            if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                              remoteArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+" -i \"" +  Operation[currentOperation] -> GetRemoteSSHPassword() + "\" -p " +
                                            countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                            else
                              remoteArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+" -i \"" +  Operation[currentOperation] -> GetRemoteSSHPassword() + "\"");
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
                    
            //update the last execution time + logfile actions ~~~~~~~~~~~~~~~~~~~~~
            if (!DryRun)
            {
                int maxSnaps = Operation[currentOperation] -> GetKeepSnapshots(); // this is the number of snapshots to keep
                if (maxSnaps < 1)
                    maxSnaps = 1;
                int currentSnaps = Operation[currentOperation] -> GetSnapshotsListSize(); // this is the current number of snapshots
                if (currentSnaps < 1)
                    currentSnaps = 1;

                // Juan's patch ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // this is just to create the .snapDefaultDir if it does not to exist so as to copy profile data later...

                    //we will create the snapshots default directory by using an rsync command with an empty source without --delete option
                    QProcess *mkdirProcess;     mkdirProcess  = new QProcess;
                    QStringList mkdirArgs;      mkdirArgs.clear();

                    //if (WINrunning && RemoteDestUsed)
                    //  mkdirArgs << "--mkdir";
                    //else
                      mkdirArgs << "--progress" << "-r";
                    //add all remote arguments exactly as used at normal backup
                    if (RemoteDestUsed)
                        mkdirArgs << remoteArgs;

                    // Add the destination folder
                    mkdirArgs.append(snapEmptyDir);
                    mkdirArgs.append(tempDestinationOrig);
                    if (WINrunning)
                    {
                        //bool createWinRsyncCommand(tempDirPath,QFile command1,QFile command2,bool vss,QString rsyncArgs,QString source,QString dest);
                        command2=createWinRsyncCommand(Operation[currentOperation] -> GetTempPath(),false,mkdirArgs,false);
                        if (command2=="")
                            cout << "\nfailed to create bat file in mkdirProccess";
                        else
                            mkdirProcess -> start (command2);
                    }
                    else
                      mkdirProcess -> start (command,mkdirArgs);
                    mkdirProcess -> waitForFinished();

                    if ((mkdirProcess -> exitCode()) == 0)
                        cout << "\n!";
                    else
                        cout << "\n!mkdir error!";
                    
                    // Add the destination folder [ + sourceLast +SLASH ]
                    mkdirArgs.removeLast();
                    mkdirArgs.append(tempDestinationOrig2);
                    if (WINrunning)
                    {
                        //bool createWinRsyncCommand(tempDirPath,QFile command1,QFile command2,bool vss,QString rsyncArgs,QString source,QString dest);
                        command2=createWinRsyncCommand(Operation[currentOperation] -> GetTempPath(),false,mkdirArgs,false);
                        if (command2=="")
                            cout << "\nfailed to create bat file in mkdirProccess";
                        else
                            mkdirProcess -> start (command2);
                    }
                    else
                      mkdirProcess -> start (command,mkdirArgs);
                    mkdirProcess -> waitForFinished();

                    if ((mkdirProcess -> exitCode()) == 0)
                        cout << "\n!";
                    else
                        cout << "\n!mkdir error!";

                    // Add the destination folder [ + sourceLast +SLASH ] + snapDefaultDir
                    mkdirArgs.removeLast();
                    mkdirArgs.append(tempDestination);
//                    QTemporaryFile command1(QDir::tempPath()+"\\qt_tempXXXXXX.bat");
//                    QTemporaryFile command2(QDir::tempPath()+"\\qt_tempXXXXXX.bat");
                    if (WINrunning)
                    {
                        //bool createWinRsyncCommand(tempDirPath,QFile command1,QFile command2,bool vss,QString rsyncArgs,QString source,QString dest);
                        command2=createWinRsyncCommand(Operation[currentOperation] -> GetTempPath(),false,mkdirArgs,false);
                        if (command2=="")
                            cout << "\nfailed to create bat file in rmProccess";
                        else
                            mkdirProcess -> start (command2);
                    }
                    else
                       mkdirProcess -> start (command,mkdirArgs);
                    mkdirProcess -> waitForFinished();

                    if ((mkdirProcess -> exitCode()) == 0)
                        cout << "\n!";
                    else
                        cout << "\n!mkdir error!";
                // Juan's patch END~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        
                // first remove the older logfiles and snapshots if max keep snapshots is reached
                if (currentSnaps >= maxSnaps)
                {
                    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                    cout << " Removing old snapshots and logfiles of task: " <<
                        QString((Operation[currentOperation] -> GetName()).toUtf8()).toStdString() << "\n";
                
                    // ************** actually REMOVE DATA of all older snapshots ***************************
                    // ******************************************************************************
                    
                    
                    // increase the remove limit to include the source.size() if "backup dir by name" is used
                    if (Operation[currentOperation] -> GetTypeDirName())
                        removeCharLimit = 4 + sourceLast.size()+1;
                    else
                        removeCharLimit = 4;
                    
                    QProcess *rmProcess;	rmProcess  = new QProcess;
                    QStringList rmArgs;
                    rmArgs << "--progress" << "-r" << "--delete-after";
                    int snapToKeep = currentSnaps-maxSnaps + 1;
                    while ( snapToKeep < currentSnaps )
                    {                            
                        if (WINrunning)
                            rmArgs.append("--filter=protect " + Operation[currentOperation] -> GetSnapshotsListItem(snapToKeep) + XnixSLASH);
                        else
                            rmArgs.append("--filter=protect " + Operation[currentOperation] -> GetSnapshotsListItem(snapToKeep) + SLASH);
                        snapToKeep++;
                    }
                    // protect the backup profile dir too
                    if (WINrunning)
                        rmArgs.append("--filter=protect " + profileName + ".profile" + XnixSLASH);
                    else
                        rmArgs.append("--filter=protect " + profileName + ".profile" + SLASH);
                    
                    //also add all remote arguments exactly as used at normal backup
                    if (RemoteDestUsed)
                        rmArgs << remoteArgs;
                    
                    rmArgs.append(snapEmptyDir);
                    rmArgs.append(tempDestination);
                    if (WINrunning)
                    {
                        //bool createWinRsyncCommand(tempDirPath,QFile command1,QFile command2,bool vss,QString rsyncArgs,QString source,QString dest);
                        command2=createWinRsyncCommand(Operation[currentOperation] -> GetTempPath(),false,rmArgs,false);
                        if (command2=="")
                            cout << "\nfailed to create bat file in rmProccess";
                        else
                        {
                            rmProcess -> start (command2);
                            rmProcess -> waitForFinished();
                        }
                    }
                    else
                    {
                        rmProcess -> start (command,rmArgs);
                        rmProcess -> waitForFinished();
                    }
                    
                    if ((rmProcess -> exitCode()) == 0)
                        cout << "\nRemoved  all older snapshots data";// << QString((tempDestination + Operation[currentOperation] -> GetSnapshotsListItem(0) + SLASH).toUtf8()).toStdString();
                    else
                        cout << "\nfailed to remove all older snapshots data";// << QString((tempDestination + Operation[currentOperation] -> GetSnapshotsListItem(0) + SLASH).toUtf8()).toStdString() << "\n";
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    count = 0;
                    while ( count < (currentSnaps -maxSnaps + 1 ) )
                    {
                        //remove the changes file
                        snapchangesfilename = snapChangesDir + QString(profileName.toUtf8()) + "-" + 
                                QString((Operation[currentOperation] -> GetName()).toUtf8()) + "-" +
                                (Operation[currentOperation] -> GetSnapshotsListItem(0)) + ".changes.log";
                        snapfile.setFileName(snapchangesfilename);
                        if (snapfile.exists())
                        {
                            if (snapfile.remove())	// this is the old snapshot changes file
                                cout << "\nRemoving " << QString(snapchangesfilename.toUtf8()).toStdString();
                            else 
                                cout << "\nfailed to remove " << QString(snapchangesfilename.toUtf8()).toStdString() << "\n";
                        }
                
                        //remove the oldest logfile
                        logfilename = logDir + QString(profileName.toUtf8()) + "-" + 
                                QString((Operation[currentOperation] -> GetName()).toUtf8()) + "-" +
                                Operation[currentOperation] -> GetSnapshotsListItem(0) + ".log";
                        logfile.setFileName(logfilename); // this is the old logfile
                        if (logfile.exists())
                        {
                            if (logfile.remove())
                                cout << "\nRemoving " << QString(logfilename.toUtf8()).toStdString();
                            else
                                cout << "\nfailed to remove " << QString(logfilename.toUtf8()).toStdString() << "\n";
                        }
                        
                        //remove the oldest snapshot (0) from the list
                        Operation[currentOperation] -> RemoveSnapshotsListItem (0);
                        count++;
                    }
                }
                // the following is transfered in the very beginning of the actions for !DryRun,
                /*else        // this is just to create the .snapDefaultDir if it does not to exist so as to copy profile data later...
                {
                    //we will create the snapshots default directory by using an rsync command with an empty source without --delete option
                    QProcess *mkdirProcess;     mkdirProcess  = new QProcess;
                    QStringList mkdirArgs;      mkdirArgs.clear();
                    if ( (WINrunning) && (RemoteDestUsed) )
                        mkdirArgs << "--mkdir";
                    else
                        mkdirArgs << "--progress" << "-r";
                    
                    //add all remote arguments exactly as used at normal backup
                    if (RemoteDestUsed)
                        mkdirArgs << remoteArgs;
                    
                    mkdirArgs.append(snapEmptyDir);
                    mkdirArgs.append(tempDestination);
                    mkdirProcess -> start (command,mkdirArgs);
                    mkdirProcess -> waitForFinished();
                    
                    if ((mkdirProcess -> exitCode()) == 0)
                        cout << "\n!!";
                    else
                        cout << "\n!";
                    
                }*/

                //set the current date and time as the operation's last execution date-time
                Operation[currentOperation] -> SetLastExecutionTime (QDateTime::currentDateTime());
        
                // add a new snapshot with the last execution date-time
                Operation[currentOperation] ->
                            AddSnapshotsListItem ((Operation[currentOperation] ->
                                    GetLastExecutionTime()).toString("yyyyMMddhhmmss"));
                currentSnaps = Operation[currentOperation] -> GetSnapshotsListSize();	// update the current number of snapshots

                // set a new changes file. This has a tag of the previous snapshot will include changes made to this snapshot
                snapchangesfilename = snapChangesDir + QString(profileName.toUtf8()) + "-" + 
                    QString((Operation[currentOperation] -> GetName()).toUtf8()) + "-" +
                    (Operation[currentOperation] -> GetSnapshotsListItem(currentSnaps - 1)) + ".changes.log";
                snapfile.setFileName(snapchangesfilename);
        
                // set a new logfile
                logfilename = logDir + QString(profileName.toUtf8()) + "-" +
                    QString((Operation[currentOperation] -> GetName()).toUtf8()) + "-" +
                    ( Operation[currentOperation] -> GetSnapshotsListItem(currentSnaps - 1) ) + ".log";
                
                logfile.setFileName(logfilename); // this is the current logfile
                if (logfile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))	//create a new log file
                {
                    writeToLog = TRUE;	//& if it's ok
                    syncProcess -> setStandardOutputFile(logfilename, QIODevice::Append );
                    syncProcess -> setStandardErrorFile(logfilename, QIODevice::Append );
                }
                else
                {
                    cout << "\nError writting to log:" << QString(logfilename.toUtf8()).toStdString();
                    writeToLog = FALSE;
                }
                
                // reset the error counter
                errorCount = 0;		// Number of errors from one task (max value is 1)
            }
            
            // The following part will be run as many times as the RepeatOnFail argument
            // It includes execute before, task & execute after actions
            int repeatTaskOnFailMax = Operation[currentOperation] -> GetRepeatOnFail();    // This holds the number of re-runs to try if the task fails for a reason
            int RunTry = 0; // This run is No... RunTry
            bool runNOW = TRUE;
            
            //pre-task commands execution ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~        
            count = 0;
            bool StopTaskExecution = FALSE;
            
            while ( (Operation[currentOperation] -> GetExecuteBeforeListSize() > count) && (!StopTaskExecution) )
            {
                cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                cout << " Now executing pre-task command:  "
                    << QString((Operation[currentOperation] -> GetExecuteBeforeListItem(count)).toUtf8()).toStdString() << "\n";
                
                logFileUpdate("pre-starting","",count);	//update the logfile

                RunTry = 0;     // This run of the command is No...
                runNOW = TRUE;  // run it this time
                
                while ( (RunTry < repeatTaskOnFailMax+1) && (runNOW) )
                {
                    runNOW = FALSE;  // do NOT run this another time if it goes ok
                    
                    if (RunTry > 0)
                    {
                        cout << "\n Repeating execution of pre-task command due to failure -  run " << RunTry+1 << " of " << repeatTaskOnFailMax+1 << "\n\n";
                        logFileUpdate("repeat-on-fail","",count); //update the logfile
                    }
                    
                    //syncProcess -> execute (Operation[currentOperation] -> GetExecuteBeforeListItem(count));
                    syncProcess -> start (Operation[currentOperation] -> GetExecuteBeforeListItem(count));
                    
                    //wait for the process to start and finish
                    if (syncProcess -> waitForStarted (-1))	// the "-1" arguments are used to avoid timing out
                    {
                        cout << "\nThe process started successfully\n";
                        syncProcess -> waitForFinished (-1);
                    }
                    else
                    {
                        cout << "\nThe process failed to start\n";
                        errorCount++;
                        if (RunTry < repeatTaskOnFailMax+1)
                            runNOW = TRUE;  // run it another time because of error
                            
                        if ( (Operation[currentOperation] -> GetExecuteBeforeListItemState(count) == TRUE) && (RunTry == repeatTaskOnFailMax) )
                        {
                            StopTaskExecution = TRUE;
                            break;
                        }
                    }
                    
                    cout << "\nexit code	: " << syncProcess -> exitCode();
                    cout << "\nexit status	: " << syncProcess -> exitStatus() << "\n";
                    if (syncProcess -> exitCode() != 0)
                    {
                        errorCount++;
                        if (RunTry < repeatTaskOnFailMax+1)
                            runNOW = TRUE;  // run it another time because of error
                        if ( (Operation[currentOperation] -> GetExecuteBeforeListItemState(count) == TRUE) && (RunTry == repeatTaskOnFailMax) )
                        {
                            StopTaskExecution = TRUE;
                            break;
                        }
                    }
                    RunTry++;
                }       // Main repeat-On-Fail loop -> The specific command will be repeated according to user setting
                logFileUpdate("pre-finished", "", count);
                count++;
            }   // Execute before commands loop

            //task execution
            if (StopTaskExecution)
            {
                logFileUpdate("pre-task-exited-with-error", "", 0);
                
                cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                cout << " Pre-task command exited with an error. Skipping task execution...";
                cout << "\n--------------------------------------------------------------------------------------------\n";
            }
            else
            {
                cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                cout << " Now executing :  " << QString((Operation[currentOperation] -> GetName()).toUtf8()).toStdString();
                cout << "\n--------------------------------------------------------------------------------------------\n";
                
                if (Operation[currentOperation] -> GetTypeSync())
                    logFileUpdate("rsync-starting-syncAB", "", 0);
                else
                    logFileUpdate("rsync-starting-backup", "", 0);

                // Create the destination if it does not exist
                bool DestCreateFail = FALSE;	 // This will become TRUE if destination does not exist and cannot be created
                
                rsyncArguments = AppendArguments(Operation[currentOperation]);	//set rsync arguments
                
                dirB = rsyncArguments[rsyncArguments.size()-1];
                QDir destCreate (dirB.toUtf8());
                if ( (!destCreate.exists()) && (!Operation[currentOperation] -> GetTypeSync()) && (!RemoteDestUsed) ) // local use ONLY
                {
                    if (destCreate.mkpath(dirB.toUtf8()))
                    {
                        logFileUpdate("rsync-standard", "<br>Successfuly created destination directory", 0);
                        cout << "\n\n Successfuly created destination directory\n";
                    }
                    else
                    {
                        logFileUpdate("rsync-error", "<br>Failed to create destination directory", 0);
                        cout << "\n\n Failed to create destination directory\n";
                        DestCreateFail = TRUE;
                        errorCount++;
                    }
                }
                    
                    if (!DestCreateFail)
                    {
                        //convert rsyncArguments to utf-8 for console compatibility
                        count=0;
                        
                    
                        while (count < rsyncArguments.size())
                        {
                            rsyncArguments[count] = QString(rsyncArguments[count].toUtf8());
                            count++;
                        }
                        
                        // add the --dry-run to arguments if applicable
                        if (DryRun)
                            rsyncArguments.insert(rsyncArguments.size()-2,"--dry-run");
                        //if (writeToLog )
                        //	rsyncArguments.insert(rsyncArguments.size()-2,"--log-file="+logfilename);

                        //syncProcess -> execute (command,rsyncArguments);	// execute rsync command with rsyncArguments for backup or sync A->B
                            
                        // start the repeat on fail loop for the rsync command (backup or sync1)
                        RunTry = 0;     // This run of the command is No...
                        runNOW = TRUE;  // run it this time
                        while ( (RunTry < repeatTaskOnFailMax+1) && (runNOW) )
                        {
                            runNOW = FALSE;  // do NOT run this another time if it goes ok
                            if (RunTry > 0)
                            {
                                cout << "\n Repeating execution of rsync command due to failure -  run " << RunTry+1 << " of " << repeatTaskOnFailMax+1 << "\n\n";
                                logFileUpdate("repeat-on-fail","",count); //update the logfile
                            }
                    
                            if (WINrunning)
                            {
                                //bool createWinRsyncCommand(tempDirPath,QFile command1,QFile command2,bool vss,QString rsyncArgs,QString source,QString dest);
                                command2=createWinRsyncCommand(Operation[currentOperation] -> GetTempPath(),Operation[currentOperation]->GetOptionsVss(),rsyncArguments,false);
                                if (command2=="")
                                    cout << "\nfailed to create bat file in syncProccess";
                                else
                                    syncProcess -> start (command2);
                            }
                            else
                                syncProcess -> start (command,rsyncArguments);
                            
                            //wait for the process to start and finish
                            if (syncProcess -> waitForStarted (-1))	// the "-1" arguments are used to avoid timing out
                            {
                                cout << "\nThe process started successfully\n";
                                syncProcess -> waitForFinished (-1);
                            }
                            else
                            {
                                cout << "\nThe process failed to start\n";
                                errorCount++;
                            }
                            
                            cout << "\nrsync exit code		: " << syncProcess -> exitCode();
                            cout << "\nrsync exit status	: " << syncProcess -> exitStatus() << "\n";
                            if (syncProcess -> exitCode() != 0)
                                errorCount++;
                            
                            /* If there is an error repeat the rsync command. Errors:
                                5 - Error starting client-server protocol
                                12 - Error in rsync protocol data stream
                                23 - Partial transfer due to error -> I took this out
                                30 - Timeout in data send/receive 
                                35 - Timeout waiting for daemon connection
                                255 - unexplained error */
                            if (    (syncProcess -> exitCode()==30) || (syncProcess -> exitCode()==35) || (syncProcess -> exitCode()==255) ||
                                    (syncProcess -> exitCode()==12) || (syncProcess -> exitCode()==5) )
                                runNOW = TRUE;
                            
                            RunTry++;
                        }                   // The repeat-on-fail loop
                        if (Operation[currentOperation] -> GetTypeSync())
                            logFileUpdate("rsync-finished-sync1", "", 0);
                        else
                        {
                            // strip unused lines from the snapshot changes file
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
                            }
                            if (snapfile.open(QIODevice::WriteOnly))
                            {
                                QTextStream out(&snapfile);
                                out << filesAdded;
                                snapfile.close();
                            }
                            
                            QString exportProfileDir = "";  QString sourceLast = Operation[currentOperation] -> GetSource();
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

                            // Backup profile + logs + snaps to destination
                            // If this is a backup task && not a dryrun
                            if ( (!Operation[currentOperation] -> GetTypeSync()) && (!DryRun) && (!rsyncArguments.isEmpty()) )
                            {
                                // Create the export path if it does not exist
                                QDir exportPathCreate (exportProfileDir);
                                if ( (!exportPathCreate.exists()) && (!RemoteDestUsed) ) // local use ONLY
                                    exportPathCreate.mkpath(exportProfileDir);
                                
                                if (exportFullProfile(exportProfileDir,"ExportOnlyTask"))
                                {
                                    cout << "\n Backing-up profile, logfiles and snapshot data -> Ok\n";
                                    logFileUpdate("backup-profile", " -> Ok", 0);
                                }
                                else
                                {
                                    cout << "\n Backing-up profile, logfiles and snapshot data -> FAILED\n";
                                    logFileUpdate("backup-profile", " -> Fail", 0);
                                }
                            }
                            
                            logFileUpdate("rsync-finished", "", 0);
                        }
                            
                        
                        if (Operation[currentOperation] -> GetTypeSync())	//execute rsync for syncing B -> A
                        {
                            logFileUpdate("rsync-starting-syncBA", "", 0);
                            cout << "\n\n Now executing 2nd part of sync task...\n";
                            
                            dirA = rsyncArguments[rsyncArguments.size()-2];	//swap last 2 arguments (dir names)
                            dirB = rsyncArguments[rsyncArguments.size()-1];
                            rsyncArguments.removeLast();	rsyncArguments.removeLast();
                            rsyncArguments.append(dirB);
                            rsyncArguments.append(dirA);

                            // start the repeat on fail loop for the rsync command (sync2)
                            RunTry = 0;     // This run of the command is No...
                            runNOW = TRUE;  // run it this time
                            while ( (RunTry < repeatTaskOnFailMax+1) && (runNOW) )
                            {
                                runNOW = FALSE;  // do NOT run this another time if it goes ok
                                if (RunTry > 0)
                                {
                                    cout << "\n Repeating execution of rsync command due to failure -  run " << RunTry+1 << " of " << repeatTaskOnFailMax+1 << "\n\n";
                                    logFileUpdate("repeat-on-fail","",count); //update the logfile
                                }
                            
                                //syncProcess -> execute (command,rsyncArguments);	// execute rsync command with rsyncArguments B->A
                                if (WINrunning)
                                {
                                    //bool createWinRsyncCommand(tempDirPath,QFile command1,QFile command2,bool vss,QString rsyncArgs,QString source,QString dest);
                                        command2=createWinRsyncCommand(Operation[currentOperation] -> GetTempPath(),Operation[currentOperation]->GetOptionsVss(),rsyncArguments,false);
                                    if (command2=="")
                                        cout << "\nfailed to create bat file in rmProccess";
                                    else
                                        syncProcess -> start (command2);
                                }
                                else
                                    syncProcess -> start (command,rsyncArguments);	
                                if (syncProcess -> waitForStarted (-1))	// the "-1" arguments are used to avoid timing out
                                {
                                    cout << "\nThe process started successfully\n";
                                    syncProcess -> waitForFinished (-1);
                                }
                                else
                                {
                                    cout << "\nThe process failed to start\n";
                                    errorCount++;
                                }
                            
                                cout << "\nrsync exit code		: " << syncProcess -> exitCode();
                                cout << "\nrsync exit status	: " << syncProcess -> exitStatus() << "\n";
                                if (syncProcess -> exitCode() != 0)
                                    errorCount++;
                                
                                // If there is an error repeat the rsync command. Errors
                                if (    (syncProcess -> exitCode()==30) || (syncProcess -> exitCode()==35) || (syncProcess -> exitCode()==255) ||
                                        (syncProcess -> exitCode()==12) || (syncProcess -> exitCode()==5) || (syncProcess -> exitCode()==23) )
                                    runNOW = TRUE;
                                
                                RunTry++;
                            }                   // The repeat-on-fail loop
                            logFileUpdate("rsync-finished", "", 0);
                        
                        }

                        //post-task commands execution
                        count = 0;
                        while ( (Operation[currentOperation] -> GetExecuteAfterListSize() > count) && (!StopTaskExecution) )
                        {
                            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                            cout << " Now executing post-task command:  "
                                << QString(Operation[currentOperation] -> GetExecuteAfterListItem(count).toUtf8()).toStdString() << "\n";
                                
                            //update the logfile
                            logFileUpdate("post-starting", "", count);
                            
                            RunTry = 0;     // This run of the command is No...
                            runNOW = TRUE;  // run it this time
                            while ( (RunTry < repeatTaskOnFailMax+1) && (runNOW) )
                            {
                                runNOW = FALSE;  // do NOT run this another time if it goes ok
                                if (RunTry > 0)
                                {
                                    cout << "\n Repeating execution of post-rsync command due to failure -  run " << RunTry+1 << " of " << repeatTaskOnFailMax+1 << "\n\n";
                                    logFileUpdate("repeat-on-fail","",count); //update the logfile
                                }
                    
                                //syncProcess -> execute (Operation[currentOperation] -> GetExecuteAfterListItem(count));

                                syncProcess -> start (Operation[currentOperation] -> GetExecuteAfterListItem(count));
                                if (syncProcess -> waitForStarted (-1))	// the "-1" arguments are used to avoid timing out
                                {
                                    cout << "\nThe process started successfully\n";
                                    syncProcess -> waitForFinished (-1);
                                }
                                else
                                {
                                    cout << "\nThe process failed to start\n";
                                    errorCount++;
                                    
                                    if (RunTry < repeatTaskOnFailMax+1)
                                        runNOW = TRUE;  // run it another time because of error
                                        
                                    if ( (Operation[currentOperation] -> GetExecuteAfterListItemState(count) == TRUE) && (RunTry == repeatTaskOnFailMax) )
                                    {
                                        StopTaskExecution = TRUE;
                                        break;
                                    }
                                }
                            
                                cout << "\nexit code	: " << syncProcess -> exitCode();
                                cout << "\nexit status	: " << syncProcess -> exitStatus() << "\n";
                                if (syncProcess -> exitCode() != 0)
                                {
                                    errorCount++;
                                    
                                    if (RunTry < repeatTaskOnFailMax+1)
                                        runNOW = TRUE;  // run it another time because of error
                                        
                                    if ( (Operation[currentOperation] -> GetExecuteAfterListItemState(count) == TRUE) && (RunTry == repeatTaskOnFailMax) )
                                    {
                                        StopTaskExecution = TRUE;
                                        break;
                                    }
                                }
                                
                                RunTry++;
                            }                   // The repeat-on-fail loop
                            
                            logFileUpdate("post-finished", "", count);
                            
                            count++;
                        }
                        
                        if (StopTaskExecution)
                        {
                            logFileUpdate("pre-task-exited-with-error", "", 0);
                            
                            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                            cout << " Post-task command exited with an error. Skipping executing the rest of commands...";
                            cout << "\n--------------------------------------------------------------------------------------------\n";
                        }
                        
                    }
                }               // Task & execute after task loop
                
                
            
            // close the logfile
            if (writeToLog){
                QTextStream out(&logfile);
                out << "<pre>";
                logfile.close();
            }
            
            // Update the last execution errors and .changes file if real run
            if (!DryRun)
                Operation[currentOperation] -> SetLastExecutionErrors (errorCount);	// update the last execution errors
                
            errorsFound = errorsFound + errorCount;
            errorCount = 0;
        }
        currentOperation++;
    }
}


// thats_all===================================================================================================================
// Displays an "all done" message
void commandline::thats_all()
{
    cout << "============================================================================================\n";
    cout << "			" << QDateTime::currentDateTime().toString(Qt::SystemLocaleLongDate).toStdString() << "\n";
    cout <<  "			Syncing and backing up is finished";
    if (DryRun)
        cout << "  (simulation mode)";
    if (errorsFound == 0)
        cout << "\n			No errors found";
    else
        cout << "\n			errors found: " << countStr.setNum(errorsFound).toStdString();
    if (writeToLog)
        cout << "\n 	logfile(s) have been created under directory: " << logDir.toStdString();
    cout <<  "\n\n			hope everything went ok ;-)\n";
    cout << "============================================================================================\n";
    
    saveProfile(QString(currentProfile.toUtf8()));	// updates the execution time
    
    // send an email
    if ( (!emailNever) && (!DryRun) )
    {
        bool send = TRUE;
        if ( ((emailError) && (errorsFound == 0))   // do not send if the condition "error" is checked and there are no errors
                ||
            ((emailSchedule) && (!NoQuestions)) )  // do not send if the condition "scheduled" is checked
                                                                // & --no-questions is NOT given as argument
            send = FALSE;
        
        // ***** gui mode and "schedule" is covered in executenow.cpp ******
        
        if (send)
        {
            cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "trying to send an email\n";
            cout << "       . . .\n\n";
            cout << sendEmailNow(FALSE).toStdString();
        }
    }
}


// end of commandline.cpp---------------------------------------------------------
 
