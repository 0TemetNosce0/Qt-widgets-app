/* ---------------------------------- global.cpp ---------------------------------------------------------------------------
file containing all variables & functions used globaly

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
last modified      : 12 Jan 2014
===============================================================================================================================
===============================================================================================================================
*/

#include "operationClass.h"
#include <iostream>
#include "global.h"
using namespace std;

// argumentsTest===================================================================================================================
// tests the arguments given when LB executed at command-line
bool argumentsTest(int ArgsNo, char **arg)
{
    console = FALSE;
    NoQuestions = FALSE;
    SkipCritical = FALSE;
    DryRun = FALSE;
    silentMode = FALSE;
    runImmediately = FALSE;
    
    if (ArgsNo == 1)		// if just luckybackup is given without argumets just run the gui
        return TRUE;

    int NoOfArgs = ArgsNo-1;	//the number of arguments given minus the command luckybackup
    string stdArgs[7] = { "-c",	"--no-questions",	"--skip-critical",	"--dry-run",	"--silent"};
    bool argCheck = FALSE;	// if a specific argument is ok this becomes true

    int count = 1;
    while (count < NoOfArgs)
    {
        if (arg[count] == stdArgs[0])
            { console = TRUE; argCheck = TRUE; }
        if (arg[count] == stdArgs[1])
            { NoQuestions = TRUE; console = TRUE; argCheck = TRUE; }
        if (arg[count] == stdArgs[2])
            { SkipCritical = TRUE; argCheck = TRUE; }
        if (arg[count] == stdArgs[3])
            { DryRun = TRUE; argCheck = TRUE; }
        if (arg[count] == stdArgs[4])
            { silentMode = TRUE; argCheck = TRUE; }
        if ((arg[count] == stdArgs[5]) || (arg[count] == stdArgs[6]))
        {
            // what was I thinking ???
        }
        if (!argCheck)			// if the argument is unknown
            { help(); return FALSE;	}	
        argCheck = FALSE;
        count++;
    }
    
    const char *profileNameChar = arg[NoOfArgs];	//const char* used cause argument in terminal is in utf-8 and this helps to convert it to QString
    QString profileNameArg = arg[NoOfArgs];
    if ( (profileNameArg == "--help") || (profileNameArg == "-h") )
        { help(); return FALSE;}
    if ( (profileNameArg == "--version") || (profileNameArg == "-v") )
    {
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "     You are using luckyBackup version: " << appVersionString.toStdString() <<"\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        return FALSE;
    }
    
    //currentProfile = profileNameArg;	// currentProfile holds the full path+filename of the current profile
    currentProfile = QString::fromUtf8(profileNameChar);	// currentProfile holds the full path+filename of the current profile
    
    if ( notXnixRunning )
    {
        profileDir.replace("/",SLASH);
        profileNameArg.replace("/",SLASH);
        currentProfile.replace("/",SLASH);
    }
    if (!profileNameArg.endsWith(".profile",Qt::CaseSensitive))
        currentProfile.append(".profile");
    if ( (!profileNameArg.startsWith(SLASH)) && (!notXnixRunning) )
        currentProfile.prepend(profileDir);
    if ( (notXnixRunning) && (!profileNameArg.contains(":"+SLASH)) )
        currentProfile.prepend(profileDir);
    
    //current profile QFile
    profile.setFileName(currentProfile);
    
    //current profile's name (QString) - this just holds the profile name. No path & no extension
    profileName = currentProfile;
    profileName = profileName.right(profileName.size() - profileName.lastIndexOf(SLASH) - 1);
    profileName.chop(8);
    
    runImmediately = TRUE;
    return TRUE;	// all arguments ok
}

// declareRsyncCommand===================================================================================================================
// declares the rsync and ssh commands (full path for windows)
void declareRsyncCommand()
{
    if (notXnixRunning)
    {
        if (WINrunning)
        {
            rsyncCommandPath    = rsyncDefaultWinCommand;                                     // This is the default rsync path that windows use
            sshCommandPath      = sshDefaultWinCommand;                                       // This is the default ssh path that windows use
        }
        
        if (OS2running)
        {
            rsyncCommandPath    = rsyncDefaultCommand;                                     // This is the default rsync path that OS2 use
            sshCommandPath      = sshDefaultCommand;                                       // This is the default ssh path that OS2 use
        }
    }
    else        // normal *nix
    {
        rsyncCommandPath    = rsyncDefaultCommand;                                     // This is the default rsync command that *nix use
        sshCommandPath      = sshDefaultCommand;                                       // This is the default ssh command that *nix use
        
    }
}

// loadCurrentProfile===================================================================================================================
// loads an existing profile - non-gui call
bool loadCurrentProfile()
{
    QString currentProfileUTF8 = QString(currentProfile.toUtf8());
    
    cout << "\n============================================================================================\n";
    cout << "		Loading profile " << currentProfileUTF8.toStdString() << "\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    
    QString source, dest;

    //read the file and fill all arrays
    int loadOK = loadProfile(currentProfileUTF8);	// try to load the currentProfile
    if (loadOK == 1)		// if it cannot open
    {
        cout << "	** Unable to open profile : " << currentProfileUTF8.toStdString() << " **\n";
        cout << "	" << profile.errorString().toStdString();
        cout << "\n\n";
        return FALSE;					//do nothing more
    }

    if (loadOK == 2)			// if it is not a valid profile
    {
        cout << "	** The profile you are trying to open is not a valid luckyBackup v."
        << countStr.setNum(appVersion).toStdString() << " profile **\n\n";
        return FALSE;	//do nothing more
    }

    // if all went ok (profile loaded) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    //append the profile description (CLI)
    //if (profileDescription != "")
    //	cout << "\n\n Profile description: \n" << (QString(profileDescription.toUtf8())).toStdString() <<"\n\n";
    
    currentOperation = 0;
    while (currentOperation < TotalOperations)
    {
        source = Operation[currentOperation]->GetSource();
        dest = Operation[currentOperation]->GetDestination();
        
        if ( (Operation[currentOperation] -> GetRemote()) && (Operation[currentOperation] -> GetRemoteSource()) )
        {
            if (Operation[currentOperation] -> GetRemoteModule())
                source.prepend(":");
            source.prepend((Operation[currentOperation] -> GetRemoteHost())+":");
            if (Operation[currentOperation] -> GetRemoteUser()!="")
                source.prepend((Operation[currentOperation] -> GetRemoteUser())+"@");
        }
    
        if ( (Operation[currentOperation] -> GetRemote()) && (Operation[currentOperation] -> GetRemoteDestination()) )
        {
            if (Operation[currentOperation] -> GetRemoteModule())
                dest.prepend(":");
            dest.prepend((Operation[currentOperation] -> GetRemoteHost())+":");
            if (Operation[currentOperation] -> GetRemoteUser()!="")
                dest.prepend((Operation[currentOperation] -> GetRemoteUser())+"@");
        }
        cout << "\n* task name		: " << QString((Operation[currentOperation]->GetName()).toUtf8()).toStdString();
        cout << "\n* source			: " << QString(source.toUtf8()).toStdString();
        cout << "\n* destination			: " << QString(dest.toUtf8()).toStdString();

        if (Operation[currentOperation]->GetIncluded())
            cout << "\n* This task is included\n";
        else
            cout << "\n* This task is NOT included\n";	

        currentOperation++;
    }
    cout << "\n\n			** Profile loaded successfuly ... **\n\n";
    return TRUE;
}

// check_list===================================================================================================================
// checks the loaded operations list for errors (eg nothing is included)
// calls global function checkTaskList()
bool check_list()
{
    cout << "\n============================================================================================\n";
    cout << "				Task list check \n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";



    cout << "\n* Checking if the task list is empty...					done";
    cout << "\n* Checking if 2 connected tasks have been selected for execution...	done";
    cout << "\n* Checking if no task is included...					done";
    cout << "\n* Checking if 2 or more identical destination directories are declared\n  & 'Backup dir contents' is checked...					done\n";

    checkTaskList();

    if (ask)
    {
        cout << messageCLI.toStdString();;
        return FALSE;
    }
    else
    {
        cout << "\n\n			** Task list looks ok... **\n";
        return TRUE;
    }
    return TRUE;
}

// check_dirs===================================================================================================================
// checks all declared directories for errors by calling checkBackupDirs or checkSyncDirs
//This is called from the console
bool check_dirs()
{
    cout << "\n============================================================================================\n";
    cout << "				Directories check\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

    checkDeclaredDirs(FALSE);

    if (ask == FALSE)	//if all the dirs are ok prepend  this lines to the dialog message
    {
        CheckedDataCLI.prepend("\n		(Have in mind that checks are not performed for remote data)\n\n"
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        CheckedDataCLI.prepend("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "		All data declared apear to be ok - You are ready to go !!"
        "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    }
    else			//else prepend the following
    {
        CheckedDataCLI.prepend("			Errors have been found\n"
        "		Please have a good look at the following messages\n\n"
        "	WARNING means that the task is NOT going to be performed\n"
        "	CRITICAL means that the task is going to be performed normally\n\n"
        "	If a directory is empty or does not exist,\n"
        "	there is a possibility that you 've forgotten to mount a partition/drive\n	or have just mistyped a path !!\n"
        "\n	BEWARE if a destination is empty or non-existent\n"
        "	and it is not the first time you perform the specific task(s)\n\n"
        "	Also have in mind that checks are not performed for remote data\n"
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

        CheckedDataCLI.prepend("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "		Source & destination data check results"
        "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    }

    cout << CheckedDataCLI.toStdString();
    //cout << CheckedDataCLI.toUtf8().constData();
    
    cout <<"\n\n";
    if (NothingToDo) //if there is nothing to Do anyway then just display a message
    {
        cout << "\n\n		** ..nothing to do !! **\n\n";
        return FALSE;
    }
    return TRUE;
}

// help===================================================================================================================
// displays command line usage instructions
void help()
{
    cout << "\n============================================================================================\n";
    cout << "\n * usage :       luckybackup [options] [filename]";
    cout << "\n -------------------------------------------------------------------------------------------\n";
    cout << " [options] can be  :\n\n";
    cout << " --help            : displays this help message\n";
    cout << " --version         : displays the current version of the application\n\n";

    cout << " --skip-critical   : does not execute tasks that appear with a 'CRITICAL' warning message.\n";
    cout << " --dry-run         : executes luckybackup in dry-run (simulation) mode\n";
    cout << " --silent          : executes luckybackup in silent mode (just tray notification icon shown)\n";
    cout << "\n";
    cout << " -c                : console mode. Use this, if there is no graphical envrironment available\n";
    cout << " --no-questions: skips confirmation questions asked to user. Implies -c (console mode).\n\n";

    cout << " [filename] is the already created profile that is going to be executed\n";
    cout << " -------------------------------------------------------------------------------------------\n";
    cout << " * examples:\n";
    cout << " Execute luckybackup gui :\n";
    cout << " $ luckybackup\n\n";

    cout << " Execute luckybackup in silent mode for profile '~/.luckyBackup/profiles/BackupHome.profile' :\n";
    cout << " $ luckybackup --silent ~/.luckyBackup/profiles/BackupHome.profile\n\n";

    cout << " Execute luckybackup in console mode for profile '~/.luckyBackup/profiles/BackupHome.profile' :\n";
    cout << " $ luckybackup -c BackupHome.profile\n\n";

    cout << " Execute luckybackup in console mode for profile '~/.luckyBackup/profiles/BackupHome.profile' :\n";
    cout << " Do not ask any questions and skip all tasks that apear CRITICAL after the checks\n";
    cout << " $ luckybackup --skip-critical --no-questions ~/.luckyBackup/profiles/BackupHome.profile";
    cout << "\n -------------------------------------------------------------------------------------------\n";
    cout << " see also luckybackup man page:\n";
    cout << " $ man luckybackup";
    cout << "\n============================================================================================\n\n";
}
// loadProfile =====================================================================================================================================
// loads an existing profile
int loadProfile(QString profileToLoad)
{
    profile.setFileName(profileToLoad);

    if (!profile.open(QIODevice::ReadOnly))		//if the profile cannot be opened
    {
        profile.close();
        return 1;
    }

    QTextStream in(&profile);

    QString ProfileLine="";				//temp variable to import the profile line by line
    ProfileLine = in.readLine();
    
    // First check if the profile is a text or data stream
    // if data, call loadProfileQV
    if (ProfileLine !="***************************** WARNING *****************************")
    {
        profile.close();
        return loadProfileQV(profileToLoad);
    }

    QString tempAppName = "asxeto";
    profileDescription = "";
    double tempAppVersion=0;
    bool IntOk;
    
    // Init email variables in case profile does not contain them
    if(WINrunning)
    {       
        emailCommand = emailDefaultWinCommand;
        emailArguments = emailDefaultWinArguments;
    }
    else 
    {
        emailCommand = emailDefaultCommand;
        emailArguments = emailDefaultArguments;
    }
    emailBody = emailDefaultBody;
    emailSubject = emailDefaultSubject;
    emailNever = TRUE;
    emailError = FALSE;
    emailSchedule = FALSE;
    emailTLS = FALSE;
    emailFrom = "";
    emailTo = "";
    emailSMTP = "";
    
    // Read all lines until the first task line or end of file if invalid
    while ( !(ProfileLine.startsWith("[Task]")) && (!in.atEnd()) )
    {
        ProfileLine = in.readLine();
        
        //input the application name & version--------------------------
        if (ProfileLine.startsWith("appName="))             tempAppName = ProfileLine.remove("appName=");
        if (ProfileLine.startsWith("appVersion="))          tempAppVersion = (ProfileLine.remove("appVersion=")).toDouble(&IntOk);

        //input the size of the tasks list
        if (ProfileLine.startsWith("TotalTasks="))          TotalOperations = (ProfileLine.remove("TotalTasks=")).toInt(&IntOk,10);
        
        //input the profile description
        if (ProfileLine.startsWith("ProfileDescription="))  profileDescription.append("\n" + ProfileLine.remove("ProfileDescription="));
        
        //input email stuff
        if (ProfileLine.startsWith("[email]"))              emailBody = "";// the profile contains email info, so init this var to start appending
        if (ProfileLine.startsWith("emailCommand="))        emailCommand = ProfileLine.remove("emailCommand=");
        if (ProfileLine.startsWith("emailArguments="))      emailArguments = ProfileLine.remove("emailArguments=");
        if (ProfileLine.startsWith("emailSubject="))        emailSubject = ProfileLine.remove("emailSubject=");
        if (ProfileLine.startsWith("emailNever="))          emailNever = (ProfileLine.remove("emailNever=")).toInt(&IntOk,10);
        if (ProfileLine.startsWith("emailError="))          emailError = (ProfileLine.remove("emailError=")).toInt(&IntOk,10);
        if (ProfileLine.startsWith("emailSchedule="))       emailSchedule = (ProfileLine.remove("emailSchedule=")).toInt(&IntOk,10);
        if (ProfileLine.startsWith("emailTLS="))            emailTLS = (ProfileLine.remove("emailTLS=")).toInt(&IntOk,10);
        if (ProfileLine.startsWith("emailFrom="))           emailFrom = ProfileLine.remove("emailFrom=");
        if (ProfileLine.startsWith("emailTo="))             emailTo = ProfileLine.remove("emailTo=");
        if (ProfileLine.startsWith("emailSMTP="))           emailSMTP = ProfileLine.remove("emailSMTP=");
        if (ProfileLine.startsWith("emailBody="))           emailBody.append("\n" + ProfileLine.remove("emailBody="));
    
    }
    profileDescription.remove(0,1); //remove the first "\n" from the profileDescription as well as the email body
    if (emailBody.startsWith("\n"))
        emailBody.remove(0,1); 
    
    if ( (tempAppName != appName) || (tempAppVersion < validProfileVersion) )//check if the file is a valid luckybackup profile
    {
        profile.close();
        return 2;		//profile is not valid
    }

    // import task details one bye one
    currentOperation = 0;
    while (currentOperation < TotalOperations)
    {
        operation *tempOp = new operation;
        bool doNotReadNextLine = FALSE;

        ProfileLine = in.readLine();	// inport the next line
        while ( (!ProfileLine.startsWith("[Task_end]")) && (!in.atEnd()) )
        {
            doNotReadNextLine = FALSE;
            if (ProfileLine.startsWith("Name="))					tempOp	-> SetName(ProfileLine.remove("Name="));
            if (ProfileLine.startsWith("TaskDescription="))			tempOp	-> SetDescription(tempOp->GetDescription() + "\n" + ProfileLine.remove("TaskDescription="));
            if (ProfileLine.startsWith("Args="))					tempOp	-> AppendArg(ProfileLine.remove("Args="));

            if (ProfileLine.startsWith("ConnectRestore="))			tempOp	-> SetConnectRestore(ProfileLine.remove("ConnectRestore="));

            if (ProfileLine.startsWith("LastExecutionTime="))		tempOp	-> SetLastExecutionTime(QDateTime::fromString(ProfileLine.remove("LastExecutionTime="),
"yyyyMMddhhmmss"));
            if (ProfileLine.startsWith("LastExecutionErrors="))		tempOp	-> SetLastExecutionErrors((ProfileLine.remove("LastExecutionErrors=")).toInt(&IntOk,10));
            if (ProfileLine.startsWith("KeepSnapshots="))			tempOp	-> SetKeepSnapshots((ProfileLine.remove("KeepSnapshots=")).toInt(&IntOk,10)); //see also "update the max.." few lines below
            if (ProfileLine.startsWith("SnapshotsListItem="))		tempOp	-> AddSnapshotsListItem(ProfileLine.remove("SnapshotsListItem="));
            
            if (ProfileLine.startsWith("TypeDirContents="))			tempOp	-> SetTypeDirContents(ProfileLine.remove("TypeDirContents=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("TypeDirName="))             tempOp	-> SetTypeDirName(ProfileLine.remove("TypeDirName=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("TypeSync="))				tempOp	-> SetTypeSync(ProfileLine.remove("TypeSync=").toInt(&IntOk,10));
    
            if (ProfileLine.startsWith("Source="))                  tempOp	-> SetSource(ProfileLine.remove("Source="));
            if (ProfileLine.startsWith("Destination="))				tempOp	-> SetDestination(ProfileLine.remove("Destination="));

            if (ProfileLine.startsWith("ExcludeTemp="))             tempOp	-> SetExcludeTemp(ProfileLine.remove("ExcludeTemp=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("ExcludeFromFile="))			tempOp	-> SetExcludeFromFile(ProfileLine.remove("ExcludeFromFile=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("ExcludeFile="))				tempOp	-> SetExcludeFile(ProfileLine.remove("ExcludeFile="));
            if (ProfileLine.startsWith("ExcludeCache="))			tempOp	-> SetExcludeCache(ProfileLine.remove("ExcludeCache=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("ExcludeBackup="))			tempOp	-> SetExcludeBackup(ProfileLine.remove("ExcludeBackup=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("ExcludeMount="))			tempOp	-> SetExcludeMount(ProfileLine.remove("ExcludeMount=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("ExcludeLostFound="))		tempOp	-> SetExcludeLostFound(ProfileLine.remove("ExcludeLostFound=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("ExcludeSystem="))			tempOp	-> SetExcludeSystem(ProfileLine.remove("ExcludeSystem=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("ExcludeTrash="))			tempOp	-> SetExcludeTrash(ProfileLine.remove("ExcludeTrash=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("ExcludeGVFS="))             tempOp  -> SetExcludeGVFS(ProfileLine.remove("ExcludeGVFS=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("ExcludeListItem="))			tempOp	-> AddExcludeListItem(ProfileLine.remove("ExcludeListItem="));
            tempOp	-> SetExclude();
        
            if (ProfileLine.startsWith("IncludeListItem="))			tempOp	-> AddIncludeListItem(ProfileLine.remove("IncludeListItem="));
            if (ProfileLine.startsWith("IncludeModeNormal="))		tempOp	-> SetIncludeModeNormal(ProfileLine.remove("IncludeModeNormal=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("IncludeFromFile="))			tempOp	-> SetIncludeFromFile(ProfileLine.remove("IncludeFromFile=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("IncludeFile="))				tempOp	-> SetIncludeFile(ProfileLine.remove("IncludeFile="));
            tempOp	-> SetInclude();

            if (ProfileLine.startsWith("Remote="))				    tempOp	-> SetRemote(ProfileLine.remove("Remote=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("RemoteModule="))			tempOp	-> SetRemoteModule(ProfileLine.remove("RemoteModule=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("RemoteDestination="))		tempOp	-> SetRemoteDestination(ProfileLine.remove("RemoteDestination=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("RemoteSource="))			tempOp	-> SetRemoteSource(ProfileLine.remove("RemoteSource=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("RemoteSSH="))			    tempOp	-> SetRemoteSSH(ProfileLine.remove("RemoteSSH=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("RemoteHost="))			    tempOp	-> SetRemoteHost(ProfileLine.remove("RemoteHost="));
            if (ProfileLine.startsWith("RemoteUser="))			    tempOp	-> SetRemoteUser(ProfileLine.remove("RemoteUser="));
            if (ProfileLine.startsWith("RemotePassword="))		    tempOp	-> SetRemotePassword(ProfileLine.remove("RemotePassword="));
            if (ProfileLine.startsWith("RemoteSSHPassword="))		tempOp	-> SetRemoteSSHPassword(ProfileLine.remove("RemoteSSHPassword="));
            if (ProfileLine.startsWith("RemoteSSHPasswordStr="))    tempOp  -> SetRemoteSSHPasswordStr(ProfileLine.remove("RemoteSSHPasswordStr="));
            if (ProfileLine.startsWith("RemoteSSHOptions="))        tempOp  -> SetRemoteSSHOptions(ProfileLine.remove("RemoteSSHOptions="));
            if (ProfileLine.startsWith("RemoteSSHPort="))			tempOp	-> SetRemoteSSHPort((ProfileLine.remove("RemoteSSHPort=")).toInt(&IntOk,10));

            if (ProfileLine.startsWith("OptionsUpdate="))			tempOp	-> SetOptionsUpdate(ProfileLine.remove("OptionsUpdate=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsDelete="))			tempOp	-> SetOptionsDelete(ProfileLine.remove("OptionsDelete=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsRecurse="))			tempOp	-> SetOptionsRecurse(ProfileLine.remove("OptionsRecurse=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsOwnership="))		tempOp	-> SetOptionsOwnership(ProfileLine.remove("OptionsOwnership=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsSymlinks="))		    tempOp	-> SetOptionsSymlinks(ProfileLine.remove("OptionsSymlinks=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsPermissions=")) 		tempOp	-> SetOptionsPermissions(ProfileLine.remove("OptionsPermissions=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsDevices="))			tempOp	-> SetOptionsDevices(ProfileLine.remove("OptionsDevices=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsCVS="))			    tempOp	-> SetOptionsCVS(ProfileLine.remove("OptionsCVS=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsHardLinks="))		tempOp	-> SetOptionsHardLinks(ProfileLine.remove("OptionsHardLinks=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsFATntfs="))			tempOp	-> SetOptionsFATntfs(ProfileLine.remove("OptionsFATntfs=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsSuper="))            tempOp  -> SetOptionsSuper(ProfileLine.remove("OptionsSuper=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsNumericIDs="))       tempOp  -> SetOptionsNumericIDs(ProfileLine.remove("OptionsNumericIDs=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsListItem="))			tempOp	-> AddOptionsListItem(ProfileLine.remove("OptionsListItem="));
            
            if (ProfileLine.startsWith("OptionsRestorent="))        tempOp  -> SetOptionsRestorent(ProfileLine.remove("OptionsRestorent=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("OptionsVss="))              tempOp  -> SetOptionsVss(ProfileLine.remove("OptionsVss=").toInt(&IntOk,10));
            
            if (ProfileLine.startsWith("TempPath="))                tempOp  -> SetTempPath(ProfileLine.remove("TempPath="));
            if (ProfileLine.startsWith("LuckyBackupDir="))          tempOp  -> SetLuckyBackupDir(ProfileLine.remove("LuckyBackupDir="));
            if (ProfileLine.startsWith("VshadowDir="))              tempOp  -> SetVshadowDir(ProfileLine.remove("VshadowDir="));
            if (ProfileLine.startsWith("RsyncCommand="))            tempOp  -> SetRsyncCommand(ProfileLine.remove("RsyncCommand="));
            if (ProfileLine.startsWith("SshCommand="))              tempOp  -> SetSshCommand(ProfileLine.remove("SshCommand="));
            if (ProfileLine.startsWith("DosdevCommand="))           tempOp  -> SetDosdevCommand(ProfileLine.remove("DosdevCommand="));
            if (ProfileLine.startsWith("CygpathCommand="))          tempOp  -> SetCygpathCommand(ProfileLine.remove("CygpathCommand="));
            
            if (ProfileLine.startsWith("ExecuteBeforeListItem="))
            {
                tempOp	-> AddExecuteBeforeListItem(ProfileLine.remove("ExecuteBeforeListItem="));
                ProfileLine = in.readLine();    // inport the next line to check if it states the checked state !!
                if (ProfileLine.startsWith("ExecuteBeforeListItemState="))
                    tempOp  -> AddExecuteBeforeListItemState(ProfileLine.remove("ExecuteBeforeListItemState=").toInt(&IntOk,10));
                else    // if there wasn't such a line -> older version of profile
                {
                    tempOp  -> AddExecuteBeforeListItemState(TRUE);
                    doNotReadNextLine = TRUE;
                }
            }
            
            if (ProfileLine.startsWith("ExecuteAfterListItem="))
            {
                tempOp	-> AddExecuteAfterListItem(ProfileLine.remove("ExecuteAfterListItem="));
                ProfileLine = in.readLine();    // inport the next line to check if it states the checked state !!
                if (ProfileLine.startsWith("ExecuteAfterListItemState="))
                    tempOp  -> AddExecuteAfterListItemState(ProfileLine.remove("ExecuteAfterListItemState=").toInt(&IntOk,10));
                else    // if there wasn't such a line -> older version of profile
                {
                    tempOp  -> AddExecuteAfterListItemState(TRUE);
                    doNotReadNextLine = TRUE;
                }
            }
            
            if (ProfileLine.startsWith("ByPassWarning="))           tempOp	-> SetByPassWARNING(ProfileLine.remove("ByPassWarning=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("CloneWarning="))            tempOp	-> SetCloneWARNING(ProfileLine.remove("CloneWarning=").toInt(&IntOk,10));
            if (ProfileLine.startsWith("RepeatOnFail="))            tempOp  -> SetRepeatOnFail((ProfileLine.remove("RepeatOnFail=")).toInt(&IntOk,10));
            //import include checkbox state
            if (ProfileLine.startsWith("IncludeState="))            tempOp	-> SetIncluded((ProfileLine.remove("IncludeState=")).toInt(&IntOk,10));
            
            if (!doNotReadNextLine)
                ProfileLine = in.readLine();	// import the next line if it's not already imported
            if (ProfileLine.startsWith("[Task_end]"))	// all properties have been loaded
            {
                // first fix some icompatibilities with older versions that did not save the following properties:
                // 1. update the max "keep snapshots" number if it is < 1 (or not defined !!) or if the task is a sync task
                if ((tempOp -> GetTypeSync()) || (tempOp -> GetKeepSnapshots() < 1) )
                    tempOp -> SetKeepSnapshots(1);
                // 2. Add a snapshot if last executiontime exists but snapshot list is empty
                QString LastTime = ( tempOp -> GetLastExecutionTime() ).toString("yyyyMMddhhmmss");
                if ( !(LastTime == "") && (tempOp -> SnapshotsListIsEmpty()) )
                    tempOp -> AddSnapshotsListItem (LastTime);
                //3. Remove the first "\n" from the task description
                tempOp	-> SetDescription(tempOp->GetDescription().remove(0,1));                
                Operation[currentOperation] = tempOp;	// update the currentOperation
            }
        }
        currentOperation++;
    }

    profile.close();
    
    // If the email fields are set from a version < 0.48
    if (tempAppVersion < 0.48)
    {
        emailArguments = emailCommand;
        emailCommand = emailCommand.left(emailCommand.indexOf(" "));
        emailArguments.remove(emailCommand + " ");
        
        saveProfile(profileToLoad);     //save the profile with all new info
    }
    
    return 0;
}


// loadProfileQV - qvariant =============================================================================================================================
// loads an existing profile using qvariant then saves this profile as simple text
// This is kept for compatibility purposes for older versions that use the qvariant and not simple text
int loadProfileQV(QString profileToLoad)
{
    int count;
    profile.setFileName(profileToLoad);

    if (!profile.open(QIODevice::ReadOnly))		//if the profile cannot be opened
    {
        profile.close();
        return 1;
    }

    QDataStream in(&profile);
    in.setVersion(QDataStream::Qt_4_3);

    QVariant v;					//we will import everything as QVariant using this temp variable
    QString vString;				//temp variable to import "labels" of real data
    QString tempAppName = "asxeto";
    profileDescription = "";
    double tempAppVersion=0;
    in>>v;	if (v.toString()=="appName")
        in >> v;	tempAppName = v.toString();	//input the application name & version--------------------------
    in>>v;	if (v.toString()=="appVersion")
        in >> v;	tempAppVersion = v.toDouble();

    if ( (tempAppName != appName) || (tempAppVersion < validProfileVersion) )//check if the file is a valid luckybackup profile
    {
        profile.close();
        return 2;		//profile is not valid
    }

    in>>v;	if (v.toString()=="TotalOperations")
        in >> v;	TotalOperations = v.toInt();	//input the size of the operations list

    currentOperation = 0;	vString="";
    while (currentOperation < TotalOperations)
    {
        operation *tempOp = new operation;

        in>>v;	vString = v.toString();	in >> v;	//input a label in vString and real data in v
        while (vString != "operation end")
        {
            if (vString == "ProfileDescription")	profileDescription = v.toString();//input the profile description
                
            //cout << "\ntask: " <<currentOperation << "\nvString: " << vString.toStdString() << "\n";
            if (vString == "Name")			tempOp	-> SetName(v.toString());
            if (vString == "TaskDescription")	tempOp	-> SetDescription(v.toString());
            if (vString == "Args")			tempOp	-> SetArgs(v.toStringList());

            if (vString == "ConnectRestore")	tempOp	-> SetConnectRestore(v.toString());

            if (vString == "LastExecutionTime")	tempOp	-> SetLastExecutionTime(v.toDateTime());
            if (vString == "LastExecutionErrors")	tempOp	-> SetLastExecutionErrors(v.toInt());
            if (vString == "KeepSnapshots")		tempOp	-> SetKeepSnapshots(v.toInt()); //see also "update the max.." few lines below
            if (vString == "SnapshotsListSize")
            {
                int snapshotsListSize = v.toInt();
                count = 0;
                while ( count < snapshotsListSize)
                {
                    in >> v;		// load the string SnapshotsListItem1,2....XX
                    in >> v; 		tempOp	-> AddSnapshotsListItem(v.toString());
                    count++;
                }
            }

            if (vString == "TypeDirContents")	tempOp	-> SetTypeDirContents(v.toBool());
            if (vString == "TypeDirName")		tempOp	-> SetTypeDirName(v.toBool());
            if (vString == "TypeSync")		tempOp	-> SetTypeSync(v.toBool());
    
            if (vString == "Source")		tempOp	-> SetSource(v.toString());
            if (vString == "Destination")		tempOp	-> SetDestination(v.toString());

            if (vString == "ExcludeTemp")		tempOp	-> SetExcludeTemp(v.toBool());
            if (vString == "ExcludeFromFile")	tempOp	-> SetExcludeFromFile(v.toBool());
            if (vString == "ExcludeFile")		tempOp	-> SetExcludeFile(v.toString());
            if (vString == "ExcludeCache")		tempOp	-> SetExcludeCache(v.toBool());
            if (vString == "ExcludeBackup")		tempOp	-> SetExcludeBackup(v.toBool());
            if (vString == "ExcludeMount")		tempOp	-> SetExcludeMount(v.toBool());
            if (vString == "ExcludeLostFound")	tempOp	-> SetExcludeLostFound(v.toBool());
            if (vString == "ExcludeSystem")		tempOp	-> SetExcludeSystem(v.toBool());
            if (vString == "ExcludeTrash")		tempOp	-> SetExcludeTrash(v.toBool());
            if (vString == "ExcludeListSize")
            {
                int excludeListSize = v.toInt();
                count = 0;
                while ( count < excludeListSize)
                {
                    in >> v; 		tempOp	-> AddExcludeListItem(v.toString());
                    count++;
                }
            }
            tempOp	-> SetExclude();

            if (vString == "IncludeListSize")
            {
                int IncludeListSize = v.toInt();
                count = 0;
                while ( count < IncludeListSize)
                {
                    in >> v; 		tempOp	-> AddIncludeListItem(v.toString());
                    count++;
                }
            }
            if (vString == "IncludeModeNormal")	tempOp	-> SetIncludeModeNormal(v.toBool());
            if (vString == "IncludeFromFile")	tempOp	-> SetIncludeFromFile(v.toBool());
            if (vString == "IncludeFile")		tempOp	-> SetIncludeFile(v.toString());
            tempOp	-> SetInclude();

            if (vString == "Remote")			tempOp	-> SetRemote(v.toBool());
            if (vString == "RemoteModule")		tempOp	-> SetRemoteModule(v.toBool());
            if (vString == "RemoteDestination")	tempOp	-> SetRemoteDestination(v.toBool());
            if (vString == "RemoteSource")		tempOp	-> SetRemoteSource(v.toBool());
            if (vString == "RemoteSSH")			tempOp	-> SetRemoteSSH(v.toBool());
            if (vString == "RemoteHost")		tempOp	-> SetRemoteHost(v.toString());
            if (vString == "RemoteUser")		tempOp	-> SetRemoteUser(v.toString());
            if (vString == "RemotePassword")	tempOp	-> SetRemotePassword(v.toString());
            if (vString == "RemoteSSHPassword")	tempOp	-> SetRemoteSSHPassword(v.toString());
            if (vString == "RemoteSSHPasswordStr")  tempOp  -> SetRemoteSSHPasswordStr(v.toString());
            if (vString == "RemoteSSHOptions")  tempOp  -> SetRemoteSSHOptions(v.toString());
            if (vString == "RemoteSSHPort")		tempOp	-> SetRemoteSSHPort(v.toInt());

            if (vString == "OptionsUpdate")		tempOp  -> SetOptionsUpdate(v.toBool());
            if (vString == "OptionsDelete")		tempOp  -> SetOptionsDelete(v.toBool());
            if (vString == "OptionsRecurse")	tempOp  -> SetOptionsRecurse(v.toBool());
            if (vString == "OptionsOwnership")	tempOp  -> SetOptionsOwnership(v.toBool());
            if (vString == "OptionsSymlinks")	tempOp  -> SetOptionsSymlinks(v.toBool());
            if (vString == "OptionsPermissions") tempOp -> SetOptionsPermissions(v.toBool());
            if (vString == "OptionsDevices")	tempOp  -> SetOptionsDevices(v.toBool());
            if (vString == "OptionsCVS")		tempOp  -> SetOptionsCVS(v.toBool());
            if (vString == "OptionsHardLinks")	tempOp  -> SetOptionsHardLinks(v.toBool());
            if (vString == "OptionsFATntfs")	tempOp  -> SetOptionsFATntfs(v.toBool());
            if (vString == "OptionsRestorent")  tempOp  -> SetOptionsRestorent(v.toBool());
            if (vString == "OptionsVss")        tempOp  -> SetOptionsVss(v.toBool());

            if (vString == "OptionsListSize")
            {
                int OptionsListSize = v.toInt();
                count = 0;
                while ( count < OptionsListSize)
                {
                    in >> v;			tempOp	-> AddOptionsListItem(v.toString());
                    count++;
                }
            }
            if (vString == "ExecuteBeforeListSize")
            {
                int ExecuteBeforeListSize = v.toInt();
                count = 0;
                while ( count < ExecuteBeforeListSize)
                {
                    in >> v;			tempOp	-> AddExecuteBeforeListItem(v.toString());
                    count++;
                }
            }
            if (vString == "ExecuteAfterListSize")
            {
                int ExecuteAfterListSize = v.toInt();
                count = 0;
                while ( count < ExecuteAfterListSize)
                {
                    in >> v;			tempOp	-> AddExecuteAfterListItem(v.toString());
                    count++;
                }
            }
            if (vString == "ByPassWarning")		tempOp	-> SetByPassWARNING(v.toBool());
            if (vString == "CloneWarning")		tempOp	-> SetCloneWARNING(v.toBool());
            //import include checkbox state
            if (vString == "IncludeState")		tempOp	-> SetIncluded(v.toBool());
            in>>v;	vString = v.toString();
            if (vString!="operation end")
                in >> v;
            else			// all properties have been loaded
            {
                // first fix some icompatibilities with older versions that did not save the following properties:
                // 1. update the max "keep snapshots" number if it is < 1 (or not defined !!) or if the task is a sync task
                if ((tempOp -> GetTypeSync()) || (tempOp -> GetKeepSnapshots() < 1) )
                    tempOp -> SetKeepSnapshots(1);
                // 2. Add a snapshot if last executiontime exists but snapshot list is empty
                QString LastTime = ( tempOp -> GetLastExecutionTime() ).toString("yyyyMMddhhmmss");
                if ( !(LastTime == "") && (tempOp -> SnapshotsListIsEmpty()) )
                    tempOp -> AddSnapshotsListItem (LastTime);

                Operation[currentOperation] = tempOp;	// update the currentOperation
            }
        }
        currentOperation++;
    }
    profile.close();
    
    //backup the original qvariant profile before replacing it with a plain text one
    //create directory ~/.luckyBackup including folders "logs", "profiles", "schedule", snaps if they do not exist for the current user
    QDir profilebackupdir(profileDir + "backups/");
    if (!profilebackupdir.exists())
        profilebackupdir.mkpath(profileDir + "backups/");
    profile.copy(profileDir + "backups/" + profileName + ".profile" );
    
    saveProfile(profileToLoad);		//save the profile to text format
    return 0;
}

// saveProfile =====================================================================================================================================
// saves an existing profile
bool saveProfile(QString profileToSave)
{
    int count;

    profile.setFileName(profileToSave);
    
    if (!profile.open(QIODevice::WriteOnly))	// if the profile cannot be saved (or fails to create)
    {
        profile.close();
        return FALSE;
    }

    //write arrays to profile file
    QTextStream out(&profile);

    out << "***************************** WARNING *****************************\n";
    out << "Do NOT edit this file directly, unless you REALLY know what you are doing !!\n\n\n";
    
    out << "[profile_global]\n";
    out << "appName="                       << appName << "\n";             //output the application name 
    out << "appVersion="                    << appVersion << "\n";          //output the application version 
    out << "TotalTasks="                    << TotalOperations << "\n";     //output the size of the opeartions list
    
    if (profileDescription!="")
    {
        QStringList DescriptionLines = profileDescription.split("\n"); 
        for (count=0; count<DescriptionLines.size();++count)
            out << "ProfileDescription=" 		<< DescriptionLines.at(count) << "\n";  //output the profile description
    }
    
    out << "\n[email]\n";
    
    out << "emailCommand="  << emailCommand     << "\n"; //output the full email command with arguments
    out << "emailArguments="<< emailArguments   << "\n"; //output the full email arguments
    out << "emailSubject="  << emailSubject     << "\n"; //output the email subject
    out << "emailNever="    << emailNever       << "\n"; //output the email never condition
    out << "emailError="    << emailError       << "\n"; //output the email error condition
    out << "emailSchedule=" << emailSchedule    << "\n"; //output the email schedule condition
    out << "emailTLS="      << emailTLS         << "\n"; //output the TLS option condition
    out << "emailFrom="     << emailFrom        << "\n"; //output the email from
    out << "emailTo="       << emailTo          << "\n"; //output the email To
    out << "emailSMTP="     << emailSMTP        << "\n"; //output the email smtp server
    if (emailBody!="")
    {
        QStringList emailBodyLines = emailBody.split("\n"); 
        for (count=0; count<emailBodyLines.size();++count)
            out << "emailBody="        << emailBodyLines.at(count) << "\n";  //output the email body line by line
    }
    
    out << "\n";
    currentOperation = 0;

    while ( currentOperation < TotalOperations )
    {
        out << "[Task] - "                  << currentOperation << "\n";
        out << "Name="                      << Operation[currentOperation] -> GetName() << "\n";

        out << "TypeDirContents="           << Operation[currentOperation] -> GetTypeDirContents() << "\n";
        out << "TypeDirName="               << Operation[currentOperation] -> GetTypeDirName() << "\n";
        out << "TypeSync="                  << Operation[currentOperation] -> GetTypeSync() << "\n";
        
        out << "Source="                    << Operation[currentOperation] -> GetSource() << "\n";
        out << "Destination="               << Operation[currentOperation] -> GetDestination() << "\n";

        out << "LastExecutionTime="         << Operation[currentOperation] -> GetLastExecutionTime().toString("yyyyMMddhhmmss") << "\n";
        out << "LastExecutionErrors="       << Operation[currentOperation] -> GetLastExecutionErrors() << "\n";
        
        if (Operation[currentOperation] -> GetDescription() != "")
        {
            QStringList DescriptionLines = Operation[currentOperation] -> GetDescription().split("\n");
            for (count=0; count<DescriptionLines.size();++count)
                out << "TaskDescription="   << DescriptionLines.at(count) << "\n";	//output the task description
        }

        QStringList TaskArgs = Operation[currentOperation] -> GetArgs();
        for (count = 0; count < TaskArgs.size(); ++count)
            out << "Args=" << TaskArgs.at(count) << "\n";

        out << "ConnectRestore="            << Operation[currentOperation] -> GetConnectRestore() << "\n";

        out << "KeepSnapshots="             << Operation[currentOperation] -> GetKeepSnapshots() << "\n";
        count = 0;
        while ( count < (Operation[currentOperation] -> GetSnapshotsListSize()) )
        {
            out << "SnapshotsListItem="     << Operation[currentOperation] -> GetSnapshotsListItem(count) << "\n";
            count++;
        }

        out << "Exclude="                   << Operation[currentOperation] -> GetExclude() << "\n";
        out << "ExcludeFromFile="           << Operation[currentOperation] -> GetExcludeFromFile() << "\n";
        out << "ExcludeFile="               << Operation[currentOperation] -> GetExcludeFile() << "\n";
        out << "ExcludeTemp="               << Operation[currentOperation] -> GetExcludeTemp() << "\n";
        out << "ExcludeCache="              << Operation[currentOperation] -> GetExcludeCache() << "\n";
        out << "ExcludeBackup="             << Operation[currentOperation] -> GetExcludeBackup() << "\n";
        out << "ExcludeMount="              << Operation[currentOperation] -> GetExcludeMount() << "\n";
        out << "ExcludeLostFound="          << Operation[currentOperation] -> GetExcludeLostFound() << "\n";
        out << "ExcludeSystem="             << Operation[currentOperation] -> GetExcludeSystem() << "\n";
        out << "ExcludeTrash="              << Operation[currentOperation] -> GetExcludeTrash() << "\n";
        out << "ExcludeGVFS="               << Operation[currentOperation] -> GetExcludeGVFS() << "\n";
        count = 0;
        while ( count < (Operation[currentOperation] -> GetExcludeListSize()) )
        {
            out << "ExcludeListItem="       << Operation[currentOperation] -> GetExcludeListItem(count) << "\n";
            count++;
        }

        out << "Include="                   << Operation[currentOperation] -> GetInclude() << "\n";
        out << "IncludeFromFile="           << Operation[currentOperation] -> GetIncludeFromFile() << "\n";
        out << "IncludeModeNormal="         << Operation[currentOperation] -> GetIncludeModeNormal() << "\n";
        out << "IncludeFile="               << Operation[currentOperation] -> GetIncludeFile() << "\n";
        count = 0;
        while ( count < (Operation[currentOperation] -> GetIncludeListSize()) )
        {
            out << "IncludeListItem="       << Operation[currentOperation] -> GetIncludeListItem(count) << "\n";
            count++;
        }

        out << "Remote="                    << Operation[currentOperation] -> GetRemote() << "\n";
        out << "RemoteModule="              << Operation[currentOperation] -> GetRemoteModule() << "\n";
        out << "RemoteDestination="         << Operation[currentOperation] -> GetRemoteDestination() << "\n";
        out << "RemoteSource="              << Operation[currentOperation] -> GetRemoteSource() << "\n";
        out << "RemoteSSH="                 << Operation[currentOperation] -> GetRemoteSSH() << "\n";
        out << "RemoteHost="                << Operation[currentOperation] -> GetRemoteHost() << "\n";
        out << "RemoteUser="                << Operation[currentOperation] -> GetRemoteUser() << "\n";
        out << "RemotePassword="            << Operation[currentOperation] -> GetRemotePassword() << "\n";
        out << "RemoteSSHPassword="         << Operation[currentOperation] -> GetRemoteSSHPassword() << "\n";
        out << "RemoteSSHPasswordStr="      << Operation[currentOperation] -> GetRemoteSSHPasswordStr() << "\n";
        out << "RemoteSSHOptions="          << Operation[currentOperation] -> GetRemoteSSHOptions() << "\n";            
        out << "RemoteSSHPort="             << Operation[currentOperation] -> GetRemoteSSHPort() << "\n";

        out << "OptionsUpdate="             << Operation[currentOperation] -> GetOptionsUpdate() << "\n";
        out << "OptionsDelete="             << Operation[currentOperation] -> GetOptionsDelete() << "\n";
        out << "OptionsRecurse="            << Operation[currentOperation] -> GetOptionsRecurse() << "\n";
        out << "OptionsOwnership="          << Operation[currentOperation] -> GetOptionsOwnership() << "\n";
        out << "OptionsSymlinks="           << Operation[currentOperation] -> GetOptionsSymlinks() << "\n";
        out << "OptionsPermissions="        << Operation[currentOperation] -> GetOptionsPermissions() << "\n";
        out << "OptionsDevices="            << Operation[currentOperation] -> GetOptionsDevices() << "\n";
        out << "OptionsCVS="                << Operation[currentOperation] -> GetOptionsCVS() << "\n";
        out << "OptionsHardLinks="          << Operation[currentOperation] -> GetOptionsHardLinks() << "\n";
        out << "OptionsFATntfs="            << Operation[currentOperation] -> GetOptionsFATntfs() << "\n";
        out << "OptionsSuper="              << Operation[currentOperation] -> GetOptionsSuper() << "\n";
        out << "OptionsNumericIDs="         << Operation[currentOperation] -> GetOptionsNumericIDs() << "\n";

        out << "OptionsRestorent="          << Operation[currentOperation] -> GetOptionsRestorent() << "\n";
        out << "OptionsVss="                << Operation[currentOperation] -> GetOptionsVss() << "\n";
        
        out << "LuckyBackupDir="            << Operation[currentOperation] -> GetLuckyBackupDir() << "\n";
        out << "VshadowDir="                << Operation[currentOperation] -> GetVshadowDir() << "\n";
        out << "RsyncCommand="              << Operation[currentOperation] -> GetRsyncCommand() << "\n";
        out << "SshCommand="                << Operation[currentOperation] -> GetSshCommand() << "\n";
        out << "DosdevCommand="             << Operation[currentOperation] -> GetDosdevCommand() << "\n";
        out << "CygpathCommand="            << Operation[currentOperation] -> GetCygpathCommand() << "\n";
        out << "TempPath="                  << Operation[currentOperation] -> GetTempPath() << "\n";
        
        count = 0;
        while ( count < (Operation[currentOperation] -> GetOptionsListSize()) )
        {
            out << "OptionsListItem="       << Operation[currentOperation] -> GetOptionsListItem(count) << "\n";
            count++;
        }
        count = 0;
        while ( count < (Operation[currentOperation] -> GetExecuteBeforeListSize()) )
        {
            out << "ExecuteBeforeListItem=" << Operation[currentOperation] -> GetExecuteBeforeListItem(count) << "\n";
            out << "ExecuteBeforeListItemState=" << Operation[currentOperation] -> GetExecuteBeforeListItemState(count) << "\n";
            count++;
        }
        count = 0;
        while ( count < (Operation[currentOperation] -> GetExecuteAfterListSize()) )
        {
            out << "ExecuteAfterListItem="  << Operation[currentOperation] -> GetExecuteAfterListItem(count) << "\n";
            out << "ExecuteAfterListItemState=" << Operation[currentOperation] -> GetExecuteAfterListItemState(count) << "\n";
            count++;
        }
        out << "ByPassWarning="             << Operation[currentOperation] -> GetByPassWARNING() << "\n";
        out << "CloneWarning="              << Operation[currentOperation] -> GetCloneWARNING() << "\n";
        out << "RepeatOnFail="              << Operation[currentOperation] -> GetRepeatOnFail() << "\n";
        //export include state
        out << "IncludeState="              << Operation[currentOperation] -> GetIncluded() << "\n";

        out << "[Task_end] - "              << currentOperation <<  "\n\n";
        currentOperation++;
    }
    out << "\n[profile end]" << "\n";

    profile.close();
    return TRUE;
}


// exportFullProfile ====================================================================================================================================
//function to export the .profile file + logs + snaps to a location
bool exportFullProfile(QString ExportPath, QString exportType)
{
    //we will export everything by using an rsync command
    QProcess *exportProcess;    exportProcess  = new QProcess;      QStringList exportArgs;
    exportArgs  << "-t" << "-r" << "--delete-after" << "--delete-excluded";      // standard rsync args
    
    if (exportType == "ExportOnlyTask")           // Only include the .profile file and logs and snaps for a specific task
        exportArgs << "--include=" + profileName + ".profile" << "--include=/*/" + profileName + "-" + Operation[currentOperation] -> GetName() +"-*";
    else                                    // Include the .profile file and all logs & snaps related to that
        exportArgs << "--include=/*/" + profileName +"*";
         
    exportArgs << "--include=*/" << "--exclude=*" << "--prune-empty-dirs";  // "only include" rsync args
           
    //also add all remote arguments exactly as used at normal backup
    if (exportType == "ExportOnlyTask")
    {
        if ((Operation[currentOperation] -> GetRemoteDestination()) && (Operation[currentOperation] -> GetRemote()))
        {
            exportArgs << "--protect-args";
            //if ( Operation[currentOperation] -> GetRemotePassword() != "")
            if ( (Operation[currentOperation]-> GetRemoteModule()) && (Operation[currentOperation] -> GetRemotePassword() != "") )
                exportArgs.append("--password-file=" + ( Operation[currentOperation] -> GetRemotePassword()) );
            if ( Operation[currentOperation] -> GetRemoteSSH())
            {
                QString sshOptions=(Operation[currentOperation] -> GetRemoteSSHOptions()).replace("\"","\\\"")+" -o \"StrictHostKeyChecking no\"  -o \"PasswordAuthentication no\" ";
                if (WINrunning)
                {
                    if ( Operation[currentOperation] -> GetRemoteSSHPassword() != "")
                        if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                            exportArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+" -i \"" +  Operation[currentOperation] -> GetRemoteSSHPassword() +"\" -p " +
                                        countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                        else
                            exportArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+" -i \"" +  Operation[currentOperation] -> GetRemoteSSHPassword()+"\"");
                    else
                        if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                            exportArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+" -p " + countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                        else
                            exportArgs.append("-e \""+Operation[currentOperation] -> GetSshCommand()+"\" "+sshOptions+"");
                }
                else
                {
                    if ( Operation[currentOperation] -> GetRemoteSSHPassword() != "")
                        if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                            exportArgs.append("-e "+sshCommandPath+" -i " +  Operation[currentOperation] -> GetRemoteSSHPassword() +" -p " +
                                        countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                        else
                            exportArgs.append("-e "+sshCommandPath+" -i " +  Operation[currentOperation] -> GetRemoteSSHPassword());
                    else
                        if ( Operation[currentOperation] -> GetRemoteSSHPort() != 0)
                            exportArgs.append("-e "+sshCommandPath+" -p " + countStr.setNum( Operation[currentOperation] -> GetRemoteSSHPort()) );
                        else
                            exportArgs.append("-e "+sshCommandPath);
                }
            }
        }
    }
    
    exportArgs.append(luckyBackupDir);      // The source is ~/.luckyBackup/
    
    //cycnet debemos comprobar que es windows y el destino es remoto
    if (WINrunning && (Operation[currentOperation] -> GetRemoteDestination()) && (Operation[currentOperation] -> GetRemote()))
        ExportPath.replace(SLASH,XnixSLASH);
    
    exportArgs.append(ExportPath);          // The destination is given by the user
    
    //cycnet code. Windows use
    if (WINrunning)
    {
        //bool createWinRsyncCommand(tempDirPath,QFile command1,QFile command2,bool vss,QString rsyncArgs,QString source,QString dest);
        QString command2=createWinRsyncCommand(Operation[currentOperation] -> GetTempPath(),false,exportArgs,false);
        if (command2=="")
            cout << "\nfailed to create bat file in rmProccess";
        else
            exportProcess -> start (command2);
    }
    else
      exportProcess -> start (rsyncCommandPath,exportArgs);
    
    exportProcess -> waitForFinished();

    if (!(exportProcess -> exitCode() == 0))
        return FALSE;

    return TRUE;
}

// importFullProfile ====================================================================================================================================
//function to import the .profile file + logs + snaps from a location to ~/.luckyBackup with the profilename given
int importFullProfile(QString ImportPath,QString newProfileName)
{
    int returnThis = 0;
    QString PathProfileName = ImportPath;
    PathProfileName = PathProfileName.right(PathProfileName.size() - PathProfileName.lastIndexOf(SLASH) - 1);
    if (PathProfileName.endsWith(".profile"))
        PathProfileName.chop(8);
    
    // copy everything from the importFullProfile to ~/.luckyBackupDir
    QDir dirToCopy;     QStringList dirToCopyContents;  QFile fileToCopy;   QList<QString>::iterator count;
    
    // import all .profile files from ImportPath/profiles
    dirToCopy.setPath(ImportPath + SLASH + "profiles");
    dirToCopyContents = dirToCopy.entryList(QStringList("*.profile"),QDir::Files, QDir::NoSort);
    
    if (dirToCopyContents.size() == 0)
        return 1;
    for (count = dirToCopyContents.begin(); count != dirToCopyContents.end(); ++count)
    {
        QString oldFileNamePart = *count;
        oldFileNamePart = oldFileNamePart.right(oldFileNamePart.size() - oldFileNamePart.lastIndexOf(SLASH) - 1);
        oldFileNamePart.chop(8);
        oldFileNamePart.remove(0,PathProfileName.size());
        
        fileToCopy.setFileName(ImportPath + SLASH + "profiles" +SLASH +*count);
        if ((!fileToCopy.copy(profileDir + newProfileName + oldFileNamePart + ".profile")) && (returnThis < 1))
            return 1;
    }

    // import all .log files from ImportPath/logs
    dirToCopy.setPath(ImportPath + SLASH + "logs");
    dirToCopyContents = dirToCopy.entryList(QStringList("*.log"),QDir::Files, QDir::NoSort);

    for (count = dirToCopyContents.begin(); count != dirToCopyContents.end(); ++count)
    {
        QString oldFileNamePart = *count;
        oldFileNamePart = oldFileNamePart.right(oldFileNamePart.size() - oldFileNamePart.lastIndexOf(SLASH) - 1);
        oldFileNamePart.chop(4);
        oldFileNamePart.remove(0,PathProfileName.size());
        
        // TESTING
        //QMessageBox::information(0, "LB","source= " +ImportPath + SLASH + "logs" +SLASH + *count + "<br><br>dest: " + logDir + newProfileName + oldFileNamePart + ".log<br><br>oldFileNamePar= "+oldFileNamePart);
        
        fileToCopy.setFileName(ImportPath + SLASH + "logs" +SLASH +*count);
        if ((!fileToCopy.copy(logDir + newProfileName + oldFileNamePart + ".log")) && (returnThis < 10))
            returnThis=returnThis+10;
    }
    
    // import all changes.log files from ImportPath/snaps
    dirToCopy.setPath(ImportPath + SLASH + "snaps");
    dirToCopyContents = dirToCopy.entryList(QStringList("*.changes.log"),QDir::Files, QDir::NoSort);

    for (count = dirToCopyContents.begin(); count != dirToCopyContents.end(); ++count)
    {
        QString oldFileNamePart = *count;
        oldFileNamePart = oldFileNamePart.right(oldFileNamePart.size() - oldFileNamePart.lastIndexOf(SLASH) - 1);
        oldFileNamePart.chop(12);
        oldFileNamePart.remove(0,PathProfileName.size());
        
        fileToCopy.setFileName(ImportPath + SLASH + "snaps" +SLASH +*count);
        if ((!fileToCopy.copy(snapChangesDir + newProfileName + oldFileNamePart + ".changes.log")) && (returnThis < 20))
            returnThis=returnThis+20;
    }
    
    return returnThis;
}

// checkTaskList =====================================================================================================================================
// Checks if the Task list is ok to proceed
bool checkTaskList()
{
    int count;
    QString tempConnect="";
    message="";
    messageCLI="";
    ask = FALSE;
    NothingIncluded=TRUE;

    if (TotalOperations==0)						//check if the operations list is empty ------------------------------
    {
        message.append("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~<br><b>" +
                QObject::tr("The task list is empty")+" !!</b><br>..."+
            QObject::tr("nothing to start"));
        messageCLI.append("\nThe task list is empty !!\n"
            "nothing to start !!\n\n");
        ask = TRUE;
        return FALSE;
    }

    //first check if 2 connected operations have been selected for execution--------------------------------------------------------------
    //set NothingInluded to FALSE if 1 or more operation is included
    bool askTemp = FALSE;	QString dirNames="";	QString dirNamesCLI="";	currentOperation=0;
    while  (currentOperation < TotalOperations)
    {
        if (Operation[currentOperation] -> GetIncluded())	//if the operations is "included"
        {
            NothingIncluded = FALSE;

            tempConnect = Operation[currentOperation] -> GetConnectRestore();
            if (tempConnect != "")							//if it is connected to another operation
            {
                count = currentOperation+1;
                while (count < TotalOperations)
                {
                    if  ( (Operation[count]->GetName() == tempConnect)	//if 2 connected operations are both included
                    && (Operation[count] -> GetIncluded()) )
                    {
                        dirNames.append("* " + Operation[currentOperation]->GetName() + "<br>* " + tempConnect + "<br>");
                        dirNamesCLI.append(Operation[currentOperation]->GetName() + "\n" + tempConnect + "\n\n");
                        askTemp = TRUE; ask=TRUE;
                        break;
                    }
                    count++;
                }
            }
        }
        currentOperation++;
    }
    if (askTemp)
    {
        message.append("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~<br>" +
                QObject::tr("You have included both of the following connected tasks:")+"<b><br>" + dirNames + 
                "</b>" + QObject::tr("this is not allowed for obvious reasons")+" !!<br>"+
                QObject::tr("Please <b>uncheck appropriate include boxes</b> before proceeding")+"... <br>");
        messageCLI.append("\nYou have included both of the following connected tasks:\n" + QString(dirNamesCLI.toUtf8()) + 
                "this is not allowed for obvious reasons !!\n"
                "Please uncheck appropriate include boxes before proceeding...\n\n");
    }

    if ( (NothingIncluded) && (TotalOperations!=0) )		//if no checkboxes are selected show this message ---------------------
    {
        message.append("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~<br><b>"+
            QObject::tr("You have not included any tasks")+" !!</b><br>"
            "..." + QObject::tr("nothing to start"));
        messageCLI.append("\nYou have not included any tasks !!\n\n"
            "nothing to start !!\n\n");
        ask = TRUE;
        return FALSE;
    }

    //check if 2 or more identical destination directories are decleared & "Backup dir contents" is checked -------------------------------
    currentOperation=0;	askTemp = FALSE;	dirNames="";	dirNamesCLI="";
    QString dest1="", dest2="";
    //the following loop compares an included operation (currentoperation) with all the other included
    //to check if they share the same destination
    while  (currentOperation < TotalOperations)
    {
        dest1 = Operation[currentOperation] -> GetDestination();
        if (dest1.endsWith(SLASH)) dest1.chop(1);
        if (WINrunning && dest1.endsWith(XnixSLASH)) dest1.chop(1);

        if (Operation[currentOperation] -> GetIncluded())
        {
            count = 0;
            while (count < TotalOperations)
            {
                if (count == currentOperation) count++;
                else
                {
                    dest2 = Operation[count] -> GetDestination();
                    if (dest2.endsWith(SLASH)) dest2.chop(1);
                    if (WINrunning && dest2.endsWith(XnixSLASH))  dest2.chop(1);
                
                //if this operation's destination is identical to another one's which is included and is of type 'Backup dir contents'
                    if ( (Operation[count] -> GetIncluded()) 
                    && ( dest1 == dest2 )
                    && ( ((Operation[count] -> GetTypeDirContents()) && (!Operation[count] -> GetInclude())) ||
                    ((Operation[currentOperation] -> GetTypeDirContents()) && (!Operation[currentOperation] -> GetInclude()))) )
                    {
                        dirNames.append("* " + Operation[currentOperation]->GetName() + "<br>");
                        dirNamesCLI.append(Operation[currentOperation]->GetName() + "\n");
                        askTemp = TRUE; ask=TRUE;
                        break;
                    }
                    count++;
                }
            }
        }
        currentOperation++;
    }
    if (askTemp)
    {
        message.append("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~<br>" +
                QObject::tr("The following included tasks <b>share the same destination directory</b> (all together or at groups) and at least one of them will backup the contents of a directory")+" :<br><b>"
                + dirNames +
                "</b>" + QObject::tr("this will lead to one task canceling the other")+" !!<br>"+
                QObject::tr("Please uncheck appropriate include boxes or change all task types to other than '<b>Backup dir contents</b>' "
                " or use 'Backup dir contents' together with the '<b>Only include</b>' option, before proceeding")+"...");

        messageCLI.append("\nThe following included tasks share the same destination directory (all together or at groups) and at least one of them will backup the contents of a directory :\n"
                + QString(dirNamesCLI.toUtf8()) +
                "\nthis will lead to one task canceling the other !!\n"
                "Please uncheck appropriate include boxes or change all task types to other than 'Backup dir contents'\n "
                "or use 'Backup dir contents' together with the 'Only include' option, before proceeding...\n\n");
    }

    return TRUE;
}

// checkDeclaredDirs =================================================================================================================================
//Check if the declared data are ok by calling checkBackupDirs or checkSyncDirs
//If guiExec is TRUE this is called from the gui, otherwise from console
bool checkDeclaredDirs(bool guiExec)
{
    ask=FALSE;
    NothingToDo = TRUE;

    QString source, dest;

    currentOperation = 0;
    CheckedData = "";
    CheckedDataCLI = "";
    while (currentOperation < TotalOperations)
    {
        Operation[currentOperation] -> SetOK(FALSE);
        Operation[currentOperation] -> SetWARNING(FALSE);
        Operation[currentOperation] -> SetCRITICAL(FALSE);
        Operation[currentOperation] -> SetSourcePerms(FALSE);
        Operation[currentOperation] -> SetDestPerms(FALSE);
        Operation[currentOperation] -> SetDestMounted(FALSE);
        Operation[currentOperation] -> SetSourceMounted(FALSE);

        if (Operation[currentOperation] -> GetIncluded())	//if the operations is "included"
        {
            //first set  variables source & dest as well as itsPerform which will finaly decide if the task will be preformed
            source = Operation[currentOperation] -> GetSource();
            dest = Operation[currentOperation] -> GetDestination();

            if (!guiExec)	//this is used for compatibility issues with console
            {
                source=QString(source.toUtf8());
                dest=QString(dest.toUtf8());
            }

            Operation[currentOperation] -> SetIncluded(TRUE);
            Operation[currentOperation] -> SetPerform(TRUE);	//this will change at the next commands

            if ( (Operation[currentOperation] -> GetTypeDirContents()) || (Operation[currentOperation] -> GetTypeDirName()) )	
                checkBackupDirs(source,dest);			//if the operation is of type "backup dir ...'
            if (Operation[currentOperation] -> GetTypeSync())	//if the operation is of type "sync dirs'
                checkSyncDirs(source,dest);
        }
        else
        {
            Operation[currentOperation] -> SetIncluded(FALSE);
            Operation[currentOperation] -> SetPerform(FALSE);	
        }
        currentOperation++;
    }
    return TRUE;
}

//===================================================================================================================================================
//Check if the directories to be synced are empty or don't exist
void checkSyncDirs(QString source, QString dest)
{
    Operation[currentOperation] -> SetOK(FALSE);
    Operation[currentOperation] -> SetWARNING(FALSE);
    Operation[currentOperation] -> SetCRITICAL(FALSE);
    Operation[currentOperation] -> SetSourcePerms(FALSE);
    Operation[currentOperation] -> SetDestPerms(FALSE);
    Operation[currentOperation] -> SetDestMounted(FALSE);
    Operation[currentOperation] -> SetSourceMounted(FALSE);

    bool remoteSource = FALSE;
    bool remoteDest = FALSE;

    if ( (Operation[currentOperation] -> GetRemote()) && (Operation[currentOperation] -> GetRemoteSource()) )
    {
        if (Operation[currentOperation] -> GetRemoteModule())
            source.prepend(":");
        source.prepend((Operation[currentOperation] -> GetRemoteHost())+":");
        if (Operation[currentOperation] -> GetRemoteUser()!="")
            source.prepend((Operation[currentOperation] -> GetRemoteUser())+"@");
        remoteSource = TRUE;
    }

    if ( (Operation[currentOperation] -> GetRemote()) && (Operation[currentOperation] -> GetRemoteDestination()) )
    {
        if (Operation[currentOperation] -> GetRemoteModule())
            dest.prepend(":");
        dest.prepend((Operation[currentOperation] -> GetRemoteHost())+":");
        if (Operation[currentOperation] -> GetRemoteUser()!="")
            dest.prepend((Operation[currentOperation] -> GetRemoteUser())+"@");
        remoteDest = TRUE;
    }

    QFileInfo dirAFile(source);
    QFileInfo dirBFile(dest);
    QString currentOpNameCLI = QString((Operation[currentOperation] -> GetName())).toUtf8();
    
    //QString taskDescriptionCLI = QString((Operation[currentOperation] -> GetDescription())).toUtf8();
    QString taskDescription = Operation[currentOperation] -> GetDescription();
    taskDescription.replace("\n","<br>");

    //If user does not have sufficient permissions for the dirA or dirB, skip it
    if ( (dirAFile.exists()) && ((!dirAFile.isReadable()) || (!dirAFile.isExecutable())) && (!remoteSource) )
    {
        setTextMessages(source,dest,remoteSource,remoteDest, "warning","sync","source-perms");

        if (!Operation[currentOperation] -> GetByPassWARNING())
            Operation[currentOperation] -> SetPerform(FALSE);	//don't perform this operation if the "bypass WARNING" OPTION is disabled
        else
            NothingToDo = FALSE;
        Operation[currentOperation] -> SetSourcePerms(TRUE);
        ask=TRUE;	//ask the user if he/she wants to continue
        return;
    }

    if ( (dirBFile.exists()) && ((!dirBFile.isReadable()) || (!dirBFile.isExecutable())) && (!remoteDest) )
    {
        setTextMessages(source,dest,remoteSource,remoteDest,"warning","sync","dest-perms");

        ask=TRUE;	//ask the user if he/she wants to continue
        if (!Operation[currentOperation] -> GetByPassWARNING())
            Operation[currentOperation] -> SetPerform(FALSE);	//don't perform this operation if the "bypass WARNING" OPTION is disabled
        else
            NothingToDo = FALSE;
        Operation[currentOperation] -> SetDestPerms(TRUE);
        return;
    }

    QDir dirA (source);
    QDir dirB (dest);
    
    // WARNING The following 2 commands cause a "std::bad_alloc" crash when cloudfuse is used
    QStringList dirAList = dirA.entryList(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot);
    QStringList dirBList = dirB.entryList(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot);
    bool dirAIsEmpty, dirBIsEmpty;
    if (dirAList.size() == 0)
        dirAIsEmpty = TRUE;
    else
        dirAIsEmpty = FALSE;
    if (dirBList.size() == 0)
        dirBIsEmpty = TRUE;
    else
        dirBIsEmpty = FALSE;

    // Check if sync dirs A & B are under /media or /mnt and belong to a mountpoint ~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Operation[currentOperation] -> SetDestMounted(checkMountPoint(dest));
    Operation[currentOperation] -> SetSourceMounted(checkMountPoint(source));
    
    //Do directories exist and are not emty ??(skip remote)								->	[ Ok ]
    if ( ( ((dirA.exists())  && !(dirAIsEmpty)) || (remoteSource) )
    && (((dirB.exists()) && !(dirBIsEmpty)) ||(remoteDest) ) )
    {
        setTextMessages(source,dest,remoteSource,remoteDest,"okay","sync","okay");

        NothingToDo = FALSE;
        Operation[currentOperation] -> SetOK(TRUE);
    }
    
    //is one or both sync dirs non-existent ??									    ->	[ WARNING ]
    else if ( !(dirA.exists()) || !(dirB.exists()) )
    {
        setTextMessages(source,dest,remoteSource,remoteDest,"warning","sync","sync-not-exist");

        if (!Operation[currentOperation] -> GetByPassWARNING())
            Operation[currentOperation] -> SetPerform(FALSE);	//don't perform this operation if the "bypass WARNING" OPTION is disabled
        else
            NothingToDo = FALSE;
        Operation[currentOperation] -> SetWARNING(TRUE);
        ask=TRUE;
    }

    //Is one or both of the directories empty ??
    else
    {
        // if it is NOT mounted under /media or /mnt                                            ->  [ WARNING ]
        if ( (!Operation[currentOperation] -> GetDestMounted()) || (!Operation[currentOperation] -> GetSourceMounted()) )
        {
            setTextMessages(source,dest,remoteSource,remoteDest,"warning","sync","sync-not-mounted");
            
            if (!Operation[currentOperation] -> GetByPassWARNING())
                Operation[currentOperation] -> SetPerform(FALSE);   //don't perform this operation if the "bypass WARNING" OPTION is disabled
            else
                NothingToDo = FALSE;
            Operation[currentOperation] -> SetWARNING(TRUE);
            
        }
        else                //                                                      ->  [ CRITICAL ]
        {
            setTextMessages(source,dest,remoteSource,remoteDest,"critical","sync","sync-empty");

            Operation[currentOperation] -> SetCRITICAL(TRUE);
            if (SkipCritical)						// if a --skip-critical is given as argument
                Operation[currentOperation] -> SetPerform(FALSE);	//don't perform this operation
            else
                NothingToDo = FALSE;
        }
        ask=TRUE;   //ask the user if he/she wants to continue
    }

}

//===================================================================================================================================================
//Check if the source and destination backup directories are empty or don't exist
void checkBackupDirs(QString source, QString dest)
{
    Operation[currentOperation] -> SetOK(FALSE);
    Operation[currentOperation] -> SetWARNING(FALSE);
    Operation[currentOperation] -> SetCRITICAL(FALSE);
    Operation[currentOperation] -> SetSourcePerms(FALSE);
    Operation[currentOperation] -> SetDestPerms(FALSE);
    Operation[currentOperation] -> SetDestMounted(FALSE);
    Operation[currentOperation] -> SetSourceMounted(FALSE);

    bool remoteSource = FALSE;
    bool remoteDest = FALSE;

    //first check if a remote source or dest is used so that to skip checks
    if ( (Operation[currentOperation] -> GetRemote()) && (Operation[currentOperation] -> GetRemoteSource()) )
    {
        if (Operation[currentOperation] -> GetRemoteModule())
            source.prepend(":");
        source.prepend((Operation[currentOperation] -> GetRemoteHost())+":");
        if (Operation[currentOperation] -> GetRemoteUser()!="")
            source.prepend((Operation[currentOperation] -> GetRemoteUser())+"@");
        remoteSource = TRUE;
    }
    if ( (Operation[currentOperation] -> GetRemote()) && (Operation[currentOperation] -> GetRemoteDestination()) )
    {
        if (Operation[currentOperation] -> GetRemoteModule())
            dest.prepend(":");
        dest.prepend((Operation[currentOperation] -> GetRemoteHost())+":");
        if (Operation[currentOperation] -> GetRemoteUser()!="")
            dest.prepend((Operation[currentOperation] -> GetRemoteUser())+"@");
        remoteDest = TRUE;
    }

    //If user does not have sufficient permissions for the source or dest, skip it
    QFileInfo destFile(dest);
    QFileInfo sourceFile(source);

    if ( (sourceFile.exists()) && ((!sourceFile.isReadable()) || (!sourceFile.isExecutable())) && (!remoteSource) )
    {
        setTextMessages(source,dest,remoteSource,remoteDest,"warning","backup","source-perms");

        if (!Operation[currentOperation] -> GetByPassWARNING())
            Operation[currentOperation] -> SetPerform(FALSE);	//don't perform this operation if the "bypass WARNING" OPTION is disabled
        else
            NothingToDo = FALSE;

        ask=TRUE;	//ask the user if he/she wants to continue
        Operation[currentOperation] -> SetSourcePerms(TRUE);
        return;
    }

    if ( (destFile.exists()) && ((!destFile.isReadable()) || (!destFile.isExecutable())) && (!remoteDest) )
    {
        setTextMessages(source,dest,remoteSource,remoteDest,"warning","backup","dest-perms");

        if (!Operation[currentOperation] -> GetByPassWARNING())
            Operation[currentOperation] -> SetPerform(FALSE);	//don't perform this operation if the "bypass WARNING" OPTION is disabled
        else
            NothingToDo = FALSE;
        ask=TRUE;	//ask the user if he/she wants to continue
        Operation[currentOperation] -> SetDestPerms(TRUE);
        return;
    }
    
    QDir sourceDir (source);
    QDir destDir (dest);

    // WARNING The following 2 commands cause a "std::bad_alloc" crash when cloudfuse is used
    QStringList sourceList = sourceDir.entryList(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot);
    QStringList destList = destDir.entryList(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot);

    bool SourceIsEmpty, DestIsEmpty;
    if (sourceList.size() == 0)
        SourceIsEmpty = TRUE;
    else
        SourceIsEmpty = FALSE;
    if (destList.size() == 0)
        DestIsEmpty = TRUE;
    else
        DestIsEmpty = FALSE;
    
    // Check if source & dest are under /media or /mnt and belong to a mountpoint ~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Operation[currentOperation] -> SetDestMounted(checkMountPoint(dest));
    Operation[currentOperation] -> SetSourceMounted(checkMountPoint(source));

    //Does the source directory exist and it is not empty OR we're using remote source?? 
    if  ( ((sourceDir.exists())  && !(SourceIsEmpty)) || (remoteSource) )
    {
        //Does the destination directory exist and it is not empty ?? 								->	[ Ok ]
        if ( ((destDir.exists())  && !(DestIsEmpty)) || (remoteDest) )
        {
            setTextMessages(source,dest,remoteSource,remoteDest,"okay","backup","okay");
            
            Operation[currentOperation] -> SetOK(TRUE);
            NothingToDo = FALSE;
        }
        else //The destination directory does not exist or it is empty
        {
            // A partition is NOT mounted under /media or /mnt                                     ->  [WARNING ]
            if (!Operation[currentOperation] -> GetDestMounted())
            {
                setTextMessages(source,dest,remoteSource,remoteDest,"warning","backup","dest-not-mounted");
                if (!Operation[currentOperation] -> GetByPassWARNING())
                    Operation[currentOperation] -> SetPerform(FALSE);   //don't perform this operation if the "bypass WARNING" OPTION is disabled
                else
                    NothingToDo = FALSE;
                Operation[currentOperation] -> SetWARNING(TRUE);
                ask=TRUE;   //ask the user if he/she wants to continue
            }
            else    // partition is mounted                                                     ->  [ CRITICAL ]
            {
                setTextMessages(source,dest,remoteSource,remoteDest,"critical","backup","dest-not-exist");

                ask=TRUE;	//ask the user if he/she wants to continue

                Operation[currentOperation] -> SetCRITICAL(TRUE);
                
                if (SkipCritical)						// if a --skip-critical is given as argument
                    Operation[currentOperation] -> SetPerform(FALSE);	//don't perform this operation
                else
                    NothingToDo = FALSE;
            }
        }
    }
    else //The source directory does not exist or it is empty								->	[WARNING ]
    {
        setTextMessages(source,dest,remoteSource,remoteDest,"warning","backup","source-not-exist");

        if (!Operation[currentOperation] -> GetByPassWARNING())
            Operation[currentOperation] -> SetPerform(FALSE);	//don't perform this operation if the "bypass WARNING" OPTION is disabled
        else
            NothingToDo = FALSE;
        Operation[currentOperation] -> SetWARNING(TRUE);
        ask=TRUE;	//ask the user if he/she wants to continue
    }

}

// /AppendArguments =======================================================================================================
//function to append "arguments" object at a given operation according to the fields of the modify window
QStringList AppendArguments(operation *operationToAppend)
{
    QStringList arguments; int count;
    int operationToAppendCurrentSnaps = operationToAppend -> GetSnapshotsListSize();	// this is the current number of snapshots
    int operationToAppendMaxSnaps = operationToAppend -> GetKeepSnapshots();		// this is the max number of snapshots to keep
    
    arguments << "-h" << "--progress" << "--stats";	//These are the standard arguments used by rsync

    //add rsync arguments	--------------------------------------------------------------------------------------------------
    if (operationToAppend -> GetOptionsRecurse())           arguments.append("-r");
    if (operationToAppend -> GetOptionsFATntfs())
    {
        arguments.append("-t");
        arguments.append("--modify-window=1");
    }
    else
    {
        if (operationToAppend -> GetOptionsOwnership())     arguments.append("-tgo");
        if ((!WINrunning) && (operationToAppend -> GetOptionsPermissions()))
                                                            arguments.append("-p");
        if ((WINrunning) && (operationToAppend -> GetOptionsPermissions()))       // Windows ONLY: Do not use -p but --backup-nt-streams and --source-filter-tmp=
        {
            arguments.append("--source-filter-tmp="+operationToAppend->GetTempPath());
            arguments.append("--backup-nt-streams");
        }
    }
    if (WINrunning)
    {
        /* disable vss until...
        if (operationToAppend -> GetOptionsVss())           arguments.append("--vss");                  // this option is only visbile at windows */
        if (operationToAppend -> GetOptionsRestorent())     arguments.append("--restore-nt-streams");   // this option is only visbile at windows 
    }
    if (operationToAppend -> GetOptionsSymlinks())          arguments.append("-l");
    if (operationToAppend -> GetOptionsDevices())           arguments.append("-D");
    if (operationToAppend -> GetOptionsCVS())               arguments.append("-C");
    if (operationToAppend -> GetOptionsHardLinks())         arguments.append("-H");
    if (operationToAppend -> GetOptionsSuper())             arguments.append("--super");
    if (operationToAppend -> GetOptionsNumericIDs())        arguments.append("--numeric-ids");
    if (operationToAppend -> GetOptionsUpdate())            arguments.append("--update");
    if (operationToAppend -> GetOptionsDelete())            arguments.append("--delete-after");
    count =0;
    while ( count < (operationToAppend -> GetOptionsListSize()) )
    {
        arguments.append(operationToAppend -> GetOptionsListItem(count));
        count++;
    }
    
    bool disableExclude=FALSE;
    //add included items------------------------------------------------------------------------------
    if (operationToAppend -> GetInclude())
    {
        // from file
        if ( (operationToAppend -> GetIncludeFromFile()) && !(operationToAppend -> GetIncludeFile()=="") )
            arguments.append("--include-from=" + (operationToAppend -> GetIncludeFile()) );
        // from "only include" tab
        count =0;
        while ( count < (operationToAppend -> GetIncludeListSize()) )
        {
            arguments.append("--include=" + (operationToAppend -> GetIncludeListItem(count)) );
            count++;
        }
        // if "Only Include" mode is used add the following
        if (!operationToAppend -> GetIncludeModeNormal())
        {
            arguments.append("--include=*/");
            arguments.append("--exclude=*");
            arguments.append("--prune-empty-dirs");
            disableExclude=TRUE;
        }
    }
    
    //add excluded items (unless "only include" is used and the include list is not empty)--------------------------------------------------------------
    if ( (operationToAppend -> GetExclude()) && (!disableExclude) )
    {
        if (operationToAppend -> GetOptionsDelete())	arguments.append("--delete-excluded");
        if ( (operationToAppend -> GetExcludeFromFile()) && !(operationToAppend -> GetExcludeFile()=="") )
            arguments.append("--exclude-from=" + (operationToAppend -> GetExcludeFile()) );
        if (operationToAppend -> GetExcludeTemp())	arguments.append("--exclude=**/*tmp*/");
        if (operationToAppend -> GetExcludeCache()){	arguments.append("--exclude=**/*cache*/");
                                arguments.append("--exclude=**/*Cache*/");}
        if (operationToAppend -> GetExcludeBackup())	arguments.append("--exclude=**~");
        if (operationToAppend -> GetExcludeMount()){	arguments.append("--exclude=/mnt/*/**");
                                arguments.append("--exclude=/media/*/**");}
        if (operationToAppend -> GetExcludeLostFound())	arguments.append("--exclude=**/lost+found*/");
        if (operationToAppend -> GetExcludeSystem()){	arguments.append("--exclude=/var/run/**");
                                arguments.append("--exclude=/run/**");
                                arguments.append("--exclude=/proc/**");
                                arguments.append("--exclude=/dev/**");
                                arguments.append("--exclude=/sys/**");}
        if (operationToAppend -> GetExcludeTrash()){	arguments.append("--exclude=**/*Trash*/");
                                arguments.append("--exclude=**/*trash*/");}
        if (operationToAppend -> GetExcludeGVFS()) {    arguments.append("--exclude=**/.gvfs/");}
    
        //also read the custom exclude list
        count =0;
        while ( count < (operationToAppend -> GetExcludeListSize()) )
        {
            arguments.append("--exclude=" + (operationToAppend -> GetExcludeListItem(count)) );
            count++;
        }
    }

    //set temp strings sourceString & destString accordingly if groupbox "remote" is checked--------------------------------------------
    //also add -e ssh if "ssh" is checked & --password-file=FILE
    // WARNING: if you change something here, also change it in executenow.cpp when removing older snapshopt data
    QString sourceString, destString, remoteHost = "";	//temp strings
    if (operationToAppend -> GetRemote())
    {
        //append --protect-args because trouble is caused with spaces
        arguments.append("--protect-args");
        
        if (operationToAppend -> GetRemoteUser() != "")	//append remote user@ if applicable to temp string
            remoteHost.append(operationToAppend -> GetRemoteUser() + "@");

        if (operationToAppend -> GetRemoteModule())	//append remote host: (or :: if it's a module) to temp string
        {
            remoteHost.append(operationToAppend -> GetRemoteHost() + "::");
            //add --password-file=FILE if password file lineEdit is not empty
            if (operationToAppend -> GetRemotePassword() != "")
                arguments.append("--password-file=" + (operationToAppend -> GetRemotePassword()) );
        }
        else
            remoteHost.append(operationToAppend -> GetRemoteHost() + ":");

        if (operationToAppend -> GetRemoteDestination())	//set temp source & destination strings
        {
            remoteHost.append(operationToAppend -> GetDestination());
            destString = remoteHost;
            
            sourceString 	= operationToAppend -> GetSource();
            if (WINrunning)   // Bruce patch condition for winpaths~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            {
                // Commented after Juan's patch
                //destString = fixWinPathForRsync(destString, TRUE);         //fix destination (which is remote)
                //sourceString =  fixWinPathForRsync(sourceString, FALSE);    //fix source (which is local)
            }
        }
        else 
        {
            remoteHost.append(operationToAppend -> GetSource());
            sourceString = remoteHost;
            
            destString 	= operationToAppend -> GetDestination();
            if (WINrunning)   // Bruce patch condition for winpaths~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            {
                // Commented after Juan's patch
                //sourceString =  fixWinPathForRsync(sourceString, TRUE);     //fix source (which is remote)
                //destString = fixWinPathForRsync(destString, FALSE);        //fix destination (which is local)
            }
        }

        //add argument for ssh if the checkbox is checked & ssh keyfile
        if (operationToAppend -> GetRemoteSSH())
        {
            QString sshOptions=(Operation[currentOperation] -> GetRemoteSSHOptions()).replace("\"","\\\"")+" -o \"StrictHostKeyChecking no\"  -o \"PasswordAuthentication no\" ";
            if (WINrunning)
            {
                if (operationToAppend -> GetRemoteSSHPassword() != "")
                    if ( operationToAppend -> GetRemoteSSHPort() != 0 )
                        arguments.append("-e \""+operationToAppend -> GetSshCommand()+"\" "+sshOptions+" -i \"" +  operationToAppend -> GetRemoteSSHPassword() + "\" -p " + countStr.setNum( operationToAppend -> GetRemoteSSHPort()) );
                    else
                        arguments.append("-e \""+operationToAppend -> GetSshCommand()+"\" "+sshOptions+" -i \"" +  operationToAppend -> GetRemoteSSHPassword() + "\"");
                else
                    if ( operationToAppend -> GetRemoteSSHPort() != 0 )
                        arguments.append("-e \""+operationToAppend -> GetSshCommand()+"\" "+sshOptions+" -p " + countStr.setNum( operationToAppend -> GetRemoteSSHPort()) );
                    else
                        arguments.append("-e \""+operationToAppend -> GetSshCommand()+"\" "+sshOptions+"");
            }
            else
            {
                if (operationToAppend -> GetRemoteSSHPassword() != "")
                {
                    //arguments.append("-e \"ssh -i " + uiM.lineEdit_sshPassword -> text() + "\"");
                
                    // NOTE:  character ' is not used in linux due to QT comptibility issues. It works just fine without it. It is added at the "validate" dialog though for real CLI command pasting purposes!!  NOTE
                
                    if (operationToAppend -> GetRemoteSSHPort() != 0)
                        arguments.append("-e "+sshCommandPath+" -i " + operationToAppend -> GetRemoteSSHPassword() + " -p " + countStr.setNum(operationToAppend -> GetRemoteSSHPort()) );
                    else
                        arguments.append("-e "+sshCommandPath+" -i " + operationToAppend -> GetRemoteSSHPassword());
                }
                else
                {
                    if (operationToAppend -> GetRemoteSSHPort() != 0)
                        arguments.append("-e "+sshCommandPath+" -p " + countStr.setNum(operationToAppend -> GetRemoteSSHPort()) );
                    else
                        arguments.append("-e "+sshCommandPath);
                }
            }
        }
    }
    else		//Operate locally----------------------------------------------------------------------------------------
    {
        sourceString    = operationToAppend -> GetSource();
        destString      = operationToAppend -> GetDestination();
        
        // Bruce patch condition for winpaths~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // convert path to cygwin paths, change any \ to / :)
        if (WINrunning)
        {
            // Commented after Juan's patch
            //sourceString =  fixWinPathForRsync(sourceString, FALSE);    //fix local source
            //destString =    fixWinPathForRsync(destString, FALSE);      //fix local destination
        }
        // Bruce patch end ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
    }
    //add snapshot arguments - do not perform this if the function is called when "validate" button pressed
    //perform this if more than 1 snapshot is already made
    if  ( (operationToAppendCurrentSnaps > 1) && (!validation) )
    {
        //fix source and dest for snapshots directory
        QString snapSource=sourceString;	QString snapDest=destString;	//temp variables
                
        //if ( (snapDest.contains(":")) && (!notXnixRunning))// this is normal for a remote directory (not for OS/2 or win: eg c:\)
        if ( ((snapDest.contains(":")) && (!notXnixRunning)) || (snapDest.contains(":") && WINrunning && operationToAppend -> GetRemote()) )// this is normal for a remote directory
        {
                snapDest = snapDest.right(snapDest.size()-snapDest.lastIndexOf(":")-1);	//this is the remote dest dir without the remote pc
                snapDest = "";
        }

        if (!snapSource.endsWith(SLASH))   // this means task is of type "backup dir by name"
        {
            QString sourceLast = snapSource;
            sourceLast = calculateLastPath(sourceLast); // This is the lowest dir of the source
            
            if (WINrunning && operationToAppend -> GetRemote())
                sourceLast.append(XnixSLASH);
            else
                sourceLast.append(SLASH);

            snapDest.append(sourceLast);
        }
        
        QString prevSnapDateTime = operationToAppend -> GetSnapshotsListItem(operationToAppendCurrentSnaps-2);
        
        QString prevSnapDir = snapDest + snapDefaultDir + prevSnapDateTime + SLASH; // This is where the deleted files (== previous snapshot) will go
        if (WINrunning)     // windows
            prevSnapDir.replace(SLASH,XnixSLASH);
        else if (notXnixRunning)    //OS2
            prevSnapDir.replace("/",SLASH);

        // add arguments to backup files to be be deleted inside the snapshot direcotry
        arguments.append("--backup");
        arguments.append("--backup-dir=" + prevSnapDir);
    }
    
    // protect the snapshots directories from being deleted. Do nothing for older snapshots dirs
    // This is outside the condition because the snapDefaultDir also contains the backup of the profile + logs + snaps
    if (!validation)
    {
        if (WINrunning)
            arguments.append("--filter=protect " + snapDefaultDir.replace(SLASH,XnixSLASH));
        else        // linux & OS2
            arguments.append("--filter=protect " + snapDefaultDir);
    }
    
    // keep snapshot changes files only for backup task types, not sync
    if ( (!validation) && (operationToAppendMaxSnaps > 1) )
    {
        //Define a file to log new files transfered so that to exclude these when restoring previous snapshots
        arguments.append("--log-file=" + snapchangesfilename);
        arguments.append("--log-file-format=" + snapChangesString);
    }
    
    //set source & destination according to sourceString & destString ---------------------------------------------------------
    arguments.append(sourceString);
    arguments.append(destString);

    return arguments;
}

// calculateLastPath =====================================================================================================================================
// Calculates the last part of a path eg path=user@host:destination/path/here/ -> returns "here"
QString calculateLastPath(QString origPath)
{
    QString returnPATH = origPath;
    
    if ( returnPATH.contains(":") )   // this is a remote directory eg user@host:directory/path
        returnPATH = returnPATH.right(returnPATH.size()-returnPATH.lastIndexOf(":")-1); //this is the remote returnPATH dir without the remote pc ([user@]host:)
            
    if (returnPATH.endsWith(SLASH))
        returnPATH.chop(1);
    
    if (returnPATH.contains(SLASH)) // this is normal for a directory unless it is remote
        returnPATH = returnPATH.right(returnPATH.size()-returnPATH.lastIndexOf(SLASH)-1);   //this is the lowest dir of returnPATH
                    
    return returnPATH;
}
// fixWinPathForRsync =====================================================================================================================================
// Fixes a windows path for rsync use
QString fixWinPathForRsync(QString fixTHIS, bool remotePATH)
{
    QString returnPATH = fixTHIS;
    QChar drive = fixTHIS[0];
    drive = drive.toLower();        // This is the windows drive letter eg C ..as in C:\ :P
    
    if (remotePATH)
    {
        returnPATH = returnPATH.replace("\\","/");
        if (returnPATH.endsWith("//"))
            returnPATH.chop(1);
    }
    else
    {
        if (fixTHIS.startsWith("\\\\"))    // this is probably a remote share
            returnPATH = returnPATH.replace("\\","/");
        else
            returnPATH = returnPATH.replace(0,3,"/cygdrive/"+QString(drive)+"/").replace("\\","/");
    }
    
    return returnPATH;
}

// logFileUpdate =====================================================================================================================================
// Updates the current logfile with some string
QString logFileUpdate(QString appendTYPE, QString appendTHIS, int currentPrePost)
{
    QTextStream out(&logfile);
    QString dirA = Operation[currentOperation] -> GetSource();
    QString dirB = Operation[currentOperation] -> GetDestination();
    
    if (appendTYPE == "pre-starting")
        appendTHIS = "\n<font color=magenta>" +
            QObject::tr("pre-task execution of command","Full phrase: pre-task execution of command: <COMMAND> starting")+
            "	: <b>" + Operation[currentOperation] -> GetExecuteBeforeListItem(currentPrePost) +
            "</b>, "+ QObject::tr("starting","Full phrase: pre-task execution of command: <COMMAND> starting")+"</font>\n";

    if (appendTYPE == "repeat-on-fail")
        appendTHIS = "\n<font color=cyan>&nbsp;&nbsp;&nbsp;&nbsp;-----| " +
            QObject::tr("Command re-run due to failure","This means that a specific command is run for once more because it failed the first time")+
                    " |-----</font>\n";
            
    if (appendTYPE == "post-starting")
        appendTHIS = "\n<font color=magenta>" +
            QObject::tr("post-task execution of command","Full phrase: post-task execution of command: <COMMAND> starting")+
            "	: <b>" + Operation[currentOperation] -> GetExecuteAfterListItem(currentPrePost) +
            "</b>, "+QObject::tr("starting","Full phrase: post-task execution of command: <COMMAND> starting")+"</font>\n";
    
    if (appendTYPE == "rsync-starting-backup")
        appendTHIS = "\n=====================================<br><font color=magenta>" +
                QObject::tr("execution of task","Full phrase: execution of task: <TASKNAME> starting")+
                "	: <b>" + Operation[currentOperation] -> GetName() +
                "</b>, "+QObject::tr("starting","Full phrase: execution of task: <TASKNAME> starting")+"</font><br>"+
                QObject::tr("Source","Full phrase: source: <SOURCE_NAME")+"	: <b><font color=blue>" + dirA +
                "</font></b><br>"+QObject::tr("Destination","Full phrase: Destination: <DEST_NAME")+
                "	: <b><font color=blue>" + dirB + "</font></b>\n";

    if (appendTYPE == "rsync-starting-syncAB")
        appendTHIS = "\n=====================================<br><font color=magenta>" +
                QObject::tr("execution of 1st part of task","Full phrase: execution of 1st part of task: <TASKNAME> starting")+
                "	: <b>" + Operation[currentOperation] -> GetName() +
                "</b>, "+QObject::tr("starting","Full phrase: execution of 1st part of task: <TASKNAME> starting")+"</font><br>"+
                QObject::tr("Syncing","Full phrase: Syncing <DIR-A> to <DIR-B>")+"	: <b><font color=blue>" + dirA +
                "</font></b><br>"+QObject::tr("to","Full phrase: Syncing <DIR-A> to <DIR-B>")+
                "	: <b><font color=blue>" + dirB + "</font></b>\n";
        
    if (appendTYPE == "rsync-starting-syncBA")
        appendTHIS = "\n=====================================<br><font color=magenta>" +
                QObject::tr("execution of 2nd part of task","Full phrase: execution of 2nd part of task: <TASKNAME> starting")+
                "	: <b>" + Operation[currentOperation] -> GetName() +
                "</b>, "+QObject::tr("starting","Full phrase: execution of 2nd part of task: <TASKNAME> starting")+"</font><br>"+
                QObject::tr("Syncing","Full phrase: Syncing <DIR-B> to <DIR-A>")+"	: <b><font color=blue>" + dirB +
                "</font></b><br>"+QObject::tr("to","Full phrase: Syncing <DIR-B> to <DIR-A>")+"	: <b><font color=blue>" + dirA + "</font></b>\n";

    if (appendTYPE == "pre-finished")
        appendTHIS = "\n<font color=magenta>" +
            QObject::tr("pre-task execution of command","Full phrase: pre-task execution of COMMAND: <COMMANDNAME> finished")+
            "	: <b>" + Operation[currentOperation] -> GetExecuteBeforeListItem(currentPrePost) +
            "</b>, "+QObject::tr("finished","Full phrase: pre-task execution of COMMAND: <COMMANDNAME> finished")+"</font>\n";
    
    if (appendTYPE == "post-finished")
        appendTHIS = "\n<font color=magenta>" +
            QObject::tr("post-task execution of command","Full phrase: post-task execution of COMMAND: <COMMANDNAME> finished")+
            "	: <b>" + Operation[currentOperation] -> GetExecuteAfterListItem(currentPrePost) +
            "</b>, "+QObject::tr("finished","Full phrase: post-task execution of COMMAND: <COMMANDNAME> finished")+"</font><br>";

    if (appendTYPE == "rsync-finished-sync1")
        appendTHIS = "\n<font color=magenta>" +
                QObject::tr("execution of 1st part of task","Full phrase: execution of 1st part of task: <TASKNAME> finished")+
                "	: <b>" + Operation[currentOperation] -> GetName() +
                "</b>, "+QObject::tr("finished","Full phrase: execution of 1st part of task: <TASKNAME> finished") +
                "</font><br>=====================================<br>";

    if (appendTYPE == "rsync-finished")
        appendTHIS = "\n<font color=magenta>" +
                QObject::tr("execution of task","Full phrase: execution of task: <TASKNAME> finished")+
                "	: <b>" + Operation[currentOperation] -> GetName() +
                "</b>, "+QObject::tr("finished","Full phrase: execution of task: <TASKNAME> finished") +
                "</font>\n=====================================<br>";
                
    if (appendTYPE == "pre-task-exited-with-error")
        appendTHIS = "\n<font color=magenta>" +
                QObject::tr("execution of task","Full phrase: execution of task: <TASKNAME> finished because of pre/post task command execution error")+
                "	: <b>" + Operation[currentOperation] -> GetName() +
                "</b>, "+QObject::tr("finished because of pre/post task command execution error",
                            "Full phrase: execution of task: <TASKNAME> finished because of pre/post task command execution error") +
                "</font>\n=====================================<br>";
                
    if (appendTYPE == "process-reported-error")
        appendTHIS = "<a name=\"error" + countStr.setNum(errorsFound) + "\"></a><font color=red>" + QObject::tr("The process reported an error") + ": \"" +
                        appendTHIS + "\"</font>\n";

    if (appendTYPE == "rsync-standard")
        appendTHIS = appendTHIS + "\n";

    if (appendTYPE == "rsync-error")
        appendTHIS = "<a name=\"error" + countStr.setNum(errorsFound) + "\"></a><font color=red>" + appendTHIS + "</font>\n";
    
    if (appendTYPE == "backup-profile")
        appendTHIS = "\n<font color=cyan>&nbsp;&nbsp;&nbsp;&nbsp;-----| " +
            QObject::tr("Backing-up profile, logfiles and snapshot data") + appendTHIS + " |-----</font><br>";

    if (writeToLog)
    {
        if (console)	//this is used for console compatibility with utf-8
            appendTHIS = QString(appendTHIS.toUtf8());
        out << appendTHIS;
    }

    return appendTHIS;
}

// checkMountPoint =====================================================================================================================================
// Checks if the given path belongs to a mountpoint structure under /media or /mnt
// Will also return TRUE for every path that does not start with /media or /mnt
bool checkMountPoint(QString dirPath)
{
    bool returnTHISplease = TRUE;
    
    if ( (dirPath.startsWith ("/media", Qt::CaseSensitive )) || (dirPath.startsWith ("/mnt", Qt::CaseSensitive )) )
    {
        if (!dirPath.endsWith(SLASH))
            dirPath.append(SLASH);
        int ROOTcounts = dirPath.count(SLASH) - 2;
        
        QString mountpoint = dirPath;
        
        int count = 0;
        while (count < ROOTcounts)  // scan all directory depth one by one except /media or /mnt
        {
            QProcess *mountProcess;                         mountProcess = new QProcess;
            QStringList mArgs;                              mArgs << mountpoint;
            mountProcess -> start ("mountpoint",mArgs);     mountProcess -> waitForFinished();
            
            // The following means that the given path belongs to a directory structure under /media or /mnt that is a mountpoint
            if (mountProcess -> exitCode() == 0)
            {
                returnTHISplease = TRUE;
                count = ROOTcounts;         // Exit this loop and return true if mount point found
            }
            else
                returnTHISplease = FALSE;
            
            mountpoint = mountpoint.left(mountpoint.lastIndexOf(SLASH,mountpoint.size()-2)+1);    // Cut the right part of the path
            
            count++;
        }
    }
    
    return returnTHISplease;
}

// sendEmailNow =====================================================================================================================================
// Send an email after a profile run. bool is TRUE if called for testing purposes
QString sendEmailNow (bool testEmail)
{
    QString returnString = "";      // This is the string that will be finally returned
    
    // Form command to execute (first argument of emailCommand ) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //QString emailCommandExec = emailCommand.left(emailCommand.indexOf(" "));
    QString emailCommandExec = emailCommand;
    //if (WINrunning)
    //    emailCommandExec = luckyBackupDir+SLASH+emailCommandExec;
    
    // Calculate arguments and command used from variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //QString emailArgs = emailCommand;   emailArgs.remove(emailCommandExec);
    QStringList emailArgsExec = emailArguments.split(" ",QString::SkipEmptyParts);
    
    // Body & Subject might contain other args inside them. So,replace first ~~~~~~~~~~~
    emailArgsExec.replaceInStrings("%s",emailSubject);          // %s subject
    emailArgsExec.replaceInStrings("%b",emailBody);             // %b body
    
    // %l or %c logfile filename - Only do this is there exists a %l or %c arguments because many file actions are involved
    bool stopEmail = FALSE;
    if ( (emailArgsExec.contains("%l")) || (emailArgsExec.contains("%c")) )
    {
        QString argLog = logDir + profileName + emailLogString;
        QFile sendlogfile(argLog);
        
        if (!sendlogfile.open(QIODevice::WriteOnly))    // if the log file to send cannot be opened for writing
            stopEmail = TRUE;
        else
        {
            QTextStream out(&sendlogfile);
            
            if (testEmail)                                      // if this is a test email
                out << "This logfile is used for TESTING purposes only !!";
            else                    // if this is a real email - merge all task logs to a single file
            {
                currentOperation = 0;
                while (currentOperation < TotalOperations)  // scan all tasks one by one
                {
                    if ( (Operation[currentOperation] -> GetPerform()) || (Operation[currentOperation] -> GetByPassWARNING()) ) // if the task did run
                    {
                        out     << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << Operation[currentOperation] -> GetName().toUtf8() 
                                << " - START ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
                        
                        logfilename = logDir + QString(profileName.toUtf8()) + "-" + 
                                    QString((Operation[currentOperation] -> GetName()).toUtf8()) + "-" +
                                    Operation[currentOperation] -> GetSnapshotsListItem(Operation[currentOperation]->GetSnapshotsListSize()-1) 
                                    + ".log";
                        logfile.setFileName(logfilename);   // this is the last logfile
                        if (logfile.exists())
                        {
                            if (logfile.open(QIODevice::ReadOnly))     //if the profile cannot be opened
                            {
                                QTextStream in(&logfile);
                                out << in.readAll();
                                logfile.close();
                            }
                            else
                                out << "\n" << QObject::tr("Could not open the logfile") << "\n";
                        }
                        else
                            out << "\n" << QObject::tr("The logfile does not exist") << "\n";
                        out << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "+ Operation[currentOperation] -> GetName().toUtf8() + " - END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
                    }
                    currentOperation++;
                }
                
            }
            sendlogfile.close();
        }
        
        if (emailArgsExec.contains("%c") && !WINrunning)  // if the argument %c is included, also compress the file. This is valid for non windows systems
        {
            // Execute the tar command
            QString compressCommand="tar", compressExtension=".tar.gz";
            QStringList compressArgs;
            compressArgs << "-C" << logDir << "-cvzf" << argLog + compressExtension << profileName + emailLogString;
            //compressArgs << "-cvzf" << argLog + compressExtension << argLog + emailLogString; // this adds the full path of the logfile inside the tar.gz
            QProcess *compressProcess;                         compressProcess = new QProcess;
            compressProcess -> setProcessChannelMode(QProcess::MergedChannels);
            
            if (WINrunning)
            {
                compressProcess -> setWorkingDirectory(luckyBackupDir);
                QDir::setCurrent(luckyBackupDir);
            }
            
            compressProcess -> start (compressCommand,compressArgs);
            compressProcess -> waitForFinished(10000);
            emailArgsExec.replaceInStrings("%c",argLog+compressExtension);
        }
        
        if (WINrunning)
            emailArgsExec.replaceInStrings("%l",argLog.replace(XnixSLASH,SLASH));
        else
            emailArgsExec.replaceInStrings("%l",argLog);
    }
    
    // %d  Current Date
    QString argDate = QDate::currentDate().toString(Qt::DefaultLocaleLongDate);
    emailArgsExec.replaceInStrings("%d",argDate);
    
    // %i  Current Time
    QString argTime = QTime::currentTime().toString("hh:mm:ss");
    emailArgsExec.replaceInStrings("%i",argTime);
    
    // %p  Profile Name
    emailArgsExec.replaceInStrings("%p",profileName);
    
    // %e  No. of errors
    QString argErrors = countStr.setNum(errorsFound);
    emailArgsExec.replaceInStrings("%e",argErrors);
    
    // %f From address
    emailArgsExec.replaceInStrings("%f",emailFrom);
    
    // %t To address
    emailArgsExec.replaceInStrings("%t",emailTo);
    
    // %v smtp server
    emailArgsExec.replaceInStrings("%v",emailSMTP);
    // End of arguments calculations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // Execute the email command
    QProcess *emailProcess;                         emailProcess = new QProcess;
    emailProcess -> setProcessChannelMode(QProcess::MergedChannels);
    if(WINrunning)
    {   
        QDir::setCurrent(luckyBackupDir);
        emailProcess -> setWorkingDirectory(luckyBackupDir);
    }  
    emailProcess -> start (emailCommandExec,emailArgsExec);
    emailProcess -> waitForFinished(10000);
    
    // Build the return string ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    QString errorOccured = emailProcess -> errorString();
    if (errorOccured == "Unknown error")
        errorOccured = "";
    if (errorOccured == "No such file or directory")
        returnString.append(QObject::tr("The specified command is probably not installed") + "\n");
    if (stopEmail)
        returnString.append(QObject::tr("The logfile could not be created") + "\n");
    
    returnString.append(  "\n"+QObject::tr("command:   ") + emailCommandExec+
                            //"\n"+QObject::tr("arguments: ") + emailArgsExec.join(" ") +
                            //"\n"+QObject::tr("arguments: ") + emailArgs +
                            "\n"+QObject::tr("exit code: ") + countStr.setNum(emailProcess -> exitCode()) +
                            "\n"+QObject::tr("output:    ") + errorOccured + "\n" + emailProcess -> readAll() );
    
    if (!testEmail)     //  email last log
    {
        QFile emailLog(logDir + profileName + emailLastLogString);
        if (emailLog.open(QIODevice::WriteOnly))    // Create the test log file to send
        {
            QTextStream out(&emailLog);
            out << returnString;
        }
        emailLog.close();
    }
    
    return returnString;

}

// setTextMessages =======================================================================================================
// function to set text feedback for the user
// This will be displayed at the gui info window or at CLI
void setTextMessages (QString source,QString dest,bool remoteSource,bool remoteDest,QString status, QString type, QString reason)
{
    // useful variables
    QString currentOpNameCLI = QString((Operation[currentOperation] -> GetName())).toUtf8();
    int lastErrors = Operation[currentOperation] -> GetLastExecutionErrors();
    QString lastTimeReadable = (Operation[currentOperation] -> GetLastExecutionTime()).toString(Qt::DefaultLocaleLongDate);
    QString lastTime = (Operation[currentOperation] -> GetLastExecutionTime()).toString();
    //QString taskDescriptionCLI = QString((Operation[currentOperation] -> GetDescription())).toUtf8();
    QString taskDescription = Operation[currentOperation] -> GetDescription();
    taskDescription.replace("\n","<br>");
    
    if (status == "okay")
        CheckedDataCLI.append("[Ok]         ->  ");
    if (status == "warning")
        CheckedDataCLI.append("[WARNING]    ->  ");
    if (status == "critical")
        CheckedDataCLI.append("[CRITICAL]   ->  ");
    CheckedDataCLI.append(currentOpNameCLI);
    
    // Last execution time & errors
    CheckedData.append(QObject::tr("Last execution time") + ": <b>");
    CheckedDataCLI.append("\nLast execution time    : ");
    if (lastTime == "")
    {
        CheckedData.append(QObject::tr("not available") + "</b><br>");
        CheckedDataCLI.append("not available");
    }
    else
    {
        CheckedData.append(lastTimeReadable +"</b>");
        CheckedDataCLI.append(lastTimeReadable);
        if (lastErrors > -1)    // if there is error information available
        {
            if (lastErrors == 0)
            {
                CheckedData.append(" (" + QObject::tr("no errors") + ")");
                CheckedDataCLI.append(" (no errors)");
            }
            else
            {
                CheckedData.append(" (" + QObject::tr("errors found") + ")");
                CheckedDataCLI.append(" (errors found)");
            }
        }
        CheckedData.append("<br>");
    }
    
    // task status          ->          [ok] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (status == "okay")
    {
        CheckedData.append(QObject::tr("status") + ": <font color=green><b>" + QObject::tr("OK") + "</font></b><br>");
        if (type == "sync")
        {
            CheckedData.append(QObject::tr("Sync directory")+" A: <b>");
            CheckedDataCLI.append("\nSync directory A       : ");
        }
        if (type == "backup")
        {
            CheckedData.append(QObject::tr("Source directory")+": <b>");
            CheckedDataCLI.append("\nSource directory       : ");
        }
        
        CheckedData.append(source+"</b>");
        CheckedDataCLI.append(source);
        
        if (remoteSource)
        {
            CheckedData.append("<br><font color=magenta>("+QObject::tr("Using remote, check is skipped")+"...)</font>");
            CheckedDataCLI.append(" (Using remote, check is skipped...)");
        }
        if (type == "sync")
        {
            CheckedData.append("<br>" + QObject::tr("Sync directory")+" B: <b>");
            CheckedDataCLI.append("\nSync directory B       : ");
        }
        if (type == "backup")
        {
            CheckedData.append("<br>" + QObject::tr("Destination directory")+": <b>");
            CheckedDataCLI.append("\nDestination directory  : ");
        }
        
        CheckedData.append(dest+"</b>");
        CheckedDataCLI.append(dest);
        
        if (remoteDest)
        {
            CheckedData.append("<br><font color=magenta>("+QObject::tr("Using remote, check is skipped")+"...)</font>");
            CheckedDataCLI.append(" (Using remote, check is skipped...)");
        }
        else       // display destination disk free space
        if (!WINrunning)
        {
            QProcess *diskSpace;
            diskSpace  = new QProcess(0);
            QStringList diskSpaceArgs;
            diskSpaceArgs << "-h" << dest;
            diskSpace -> start ("df",diskSpaceArgs);
            diskSpace -> waitForFinished();
            QString diskSpaceString = diskSpace->readAllStandardOutput();
            if (diskSpaceString.contains("Avail"))
            {
                QStringList diskLines = diskSpaceString.split( "\n", QString::SkipEmptyParts );
                QStringList diskFields = diskLines[1].split(" ", QString::SkipEmptyParts );
                CheckedData.append(" (" + diskFields[3] +" " + QObject::tr("free", "as in free disk space")  + ")");
            }
        }
    }
    
    // task status          ->          [WARNING] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (status == "warning")
    {
        CheckedData.append(QObject::tr("status") + ": <font color=red><b>"+QObject::tr("WARNING")+"</font></b><br>");
        if (reason == "source-perms")
        {
            if (type == "sync")
            {
                CheckedData.append(QObject::tr("I do not have the permission to read/enter sync directory A")+":<b><br>");
                CheckedDataCLI.append("\nI do not have the permission to read/enter sync directory A :\n");
            }
            if (type == "backup")
            {
                CheckedData.append(QObject::tr("I do not have the permission to read/enter the source directory")+":<b><br>");
                CheckedDataCLI.append("\nI do not have the permission to read/enter the source directory :\n");
            }
            CheckedData.append(source + "</b><br>");
            CheckedDataCLI.append(source);
        }
        
        if (reason == "dest-perms")
        {
            if (type == "sync")
            {
                CheckedData.append(QObject::tr("I do not have the permission to read/enter sync directory B")+":<b><br>");
                CheckedDataCLI.append("\nI do not have the permission to read/enter sync directory B :\n");
            }
            if (type == "backup")
            {
                CheckedData.append(QObject::tr("I do not have the permission to read/enter the destination directory")+":<b><br>");
                CheckedDataCLI.append("\nI do not have the permission to read/enter the destination directory :\n");
            }
            CheckedData.append(dest + "</b><br>");
            CheckedDataCLI.append(dest);
        }
        
        if ((reason == "sync-not-exist") || (reason == "sync-not-mounted"))
        {
            CheckedData.append(QObject::tr("Directory")+" <b>");
            CheckedData.append(source);
            CheckedData.append("</b><br>"+QObject::tr("and/or")+" <b>");
            CheckedData.append(dest);
            if (reason == "sync-not-exist")
                CheckedData.append("</b><br><font color=red><b>"+QObject::tr("does not exist")+"</b></font>.<br>");
            if (reason == "sync-not-mounted")
                CheckedData.append("</b><br><font color=red><b>"+QObject::tr("is not mounted")+"</b></font>.<br>");
            
            CheckedDataCLI.append("\nDirectory ");
            CheckedDataCLI.append(source);
            CheckedDataCLI.append("\nand/or ");
            CheckedDataCLI.append(dest);
            if (reason == "sync-not-exist")
                CheckedDataCLI.append("\ndoes not exist.\n");
            if (reason == "sync-not-mounted")
                CheckedDataCLI.append("\nis not mounted.\n");
        }
        if (reason == "source-not-exist")
        {
            CheckedData.append(QObject::tr("Source directory")+": <b>");
            CheckedData.append(source);
            CheckedData.append("<br><font color=red> "+QObject::tr("is empty or does not exist")+"</font>.</b><br>");
            
            CheckedDataCLI.append("\nSource directory   : ");
            CheckedDataCLI.append(source);
            CheckedDataCLI.append(" is empty or does not exist.\n"
                    "Destination directory  : ");
            CheckedDataCLI.append(dest);
            if (remoteDest)
                CheckedDataCLI.append(" (Using remote, check is skipped...)");
        }
        
        if (reason == "dest-not-mounted")
        {
            CheckedData.append(QObject::tr("Destination directory")+": <b>");
            CheckedData.append(dest);
            CheckedData.append("<br><font color=red> "+QObject::tr("is not mounted")+"</font>.</b><br>");
            
            CheckedDataCLI.append("\nSource directory   : ");
            CheckedDataCLI.append(source);
            if (remoteSource)
                CheckedDataCLI.append(" (Using remote, check is skipped...)");
            CheckedDataCLI.append("\nDestination directory  : ");
            CheckedDataCLI.append(dest);
            CheckedDataCLI.append(" is not mounted.\n");
        }

        
        if (Operation[currentOperation] -> GetByPassWARNING())
        {
            CheckedData.append(QObject::tr("I will <font color=red><b>NOT SKIP</b></font> this task because you have enabled the \"by-pass WARNING\" option"));
            CheckedDataCLI.append("\nThis task will NOT be skipped because you have enabled the \"by-pass WARNING\" option\n");
        }
        else
        {
            CheckedData.append(QObject::tr("This task will be <font color=red><b>skipped</b></font>"));
            CheckedDataCLI.append("\nThis task will be SKIPPED\n");
        }
    }
    
    // task status          ->          [CRITICAL] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (status == "critical")
    {
        CheckedData.append(QObject::tr("status") + ": <font color=orange><b>"+QObject::tr("CRITICAL")+"</font></b><br>");
        if (type == "sync")
        {
            CheckedData.append(QObject::tr("Directory")+" <b>");
            CheckedData.append(source);
            CheckedData.append("</b><br>"+QObject::tr("and/or")+" <b>");
            CheckedData.append(dest);
            CheckedData.append("</b><br><font color=orange><b>"+QObject::tr("is empty")+"</b></font>.<br>"+
            QObject::tr("I will <font color=orange><b>not skip</b></font> this task. Synchronizing is going to be performed anyway"));
            
            CheckedDataCLI.append("\nDirectory ");
            CheckedDataCLI.append(source);
            CheckedDataCLI.append("\nand/or ");
            CheckedDataCLI.append(dest);
            CheckedDataCLI.append("\nis empty.\n"
            "I will NOT skip this task (unless '--skip-critical' is given as argument).\n"
            "Synchronizing is going to be performed anyway !!\n");
        }
        if (type == "backup")
        {
            CheckedDataCLI.append("\nSource directory   : ");
            CheckedDataCLI.append(source);
            if (remoteSource)
                CheckedDataCLI.append(" (Using remote, check is skipped...)");
            CheckedDataCLI.append("\nDestination directory  : ");
            CheckedDataCLI.append(dest);
            CheckedDataCLI.append(" is empty or does not exist.\n"
            "This task will NOT be skipped (unless '--skip-critical' is given as argument)\n"
            "The Destination Directory will be created if it doesn't exist and filled with new backup data.\n");
            
            CheckedData.append(QObject::tr("Destination directory")+": <b>");
            CheckedData.append(dest);
            CheckedData.append("<br><font color=orange> "+QObject::tr("is empty or does not exist")+"</font>.</b><br>"+
            QObject::tr("This task will <font color=orange><b>not be skipped")+"</b></font> <br>"+
            QObject::tr("The Destination Directory will be created if it doesn't exist and filled with new backup data")+".");
        }
    }
    
    CheckedDataCLI.append("\n_____________________________________________________________________________________________\n");
    
    // Task description
    if (taskDescription != "")
        CheckedData.append("<br><br><b>"+QObject::tr("Task description") + ":</b><br>" + taskDescription);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Various windows stuff from this point to the end of the file...
QString getMapdrive(){
    QString mapdrive="w";
    QStringList units;
    units << "w"<<"v"<<"u"<<"t"<<"s"<<"r"<<"q"<<"p"<<"z"<<"y"<<"x"<<"o"<<"n"<<"m"<<"l"<<"k"<<"j"<<"i";
    for (int i = 0; i < units.size(); ++i){
        mapdrive=units.at(i);
        if (! QDir(units.at(i)+":"+SLASH).exists())
          break;
      }
    return mapdrive;
}
/*luckyb commended this function out
//Create execute command in windows ==================================================
//Modify source and dest with cygpath and analyze vss
QString createWinMkdirCommand(QString tempPath,bool vss,QStringList rsyncArgs,bool logGui=true){
      rsyncArgs << "";
      
      //return createWinRsyncCommand(tempPath,vss,rsyncArgs,logGui);
      QString logstring="";
      //QFile command1(tempPath+"\\l1qt_temp"+QString::number(qrand() % (999998) + 1) +".bat");
      QFile command2(tempPath+"l2qt_temp"+QString::number(qrand() % (999998) + 1) +".bat");
      //QTemporaryFile setvar(tempPath+"\\qt_tempXXXXXX.bat");
      QString dest=rsyncArgs.takeLast();
      QString source=rsyncArgs.takeLast();
      bool srcremote=false;
      bool dstremote=false;
      rsyncArgs.replaceInStrings("\"","\\\"");
      QString args="\""+rsyncArgs.join("\" \"")+"\"";
      args.replace("\"--vss\"","");
      if (source.contains('@')||source.startsWith("\\\\")){
          args.replace("\"--backup-nt-streams\"","");
          vss=false;
          srcremote=true;
          //source=source.replace("\\","/");
        }
      if (dest.contains('@')||dest.startsWith("\\\\")){
          args.replace("\"--restore-nt-streams\"","");
          args.append(" \"--chmod=u=rwX\" ");
          dstremote=true;
          //dest=dest.replace("\\","/");
        }
      //source=fixWinPathForRsync(source,srcremote);
      //dest=fixWinPathForRsync(dest,dstremote);
      mapdrive=getMapdrive();
      QTextStream outCommand2(&command2);
      outCommand2 << "\n@ECHO OFF";
      outCommand2 << "\nSET tdebug=y";
      outCommand2 << "\nSET tdeleteshadows=y";
      outCommand2 << "\nSET el=0";
          if (!srcremote) outCommand2 << "\n\""+Operation[currentOperation] -> GetCygpathCommand()+"\" \""+source+"\"> "+tempPath+"\\_cygpath.tmp";
          else outCommand2 << "\nECHO "+source+"> "+tempPath+"\\_cygpath.tmp";
          outCommand2 << "\nSET /p source=< "+tempPath+"\\_cygpath.tmp";
          if (!dstremote) outCommand2 << "\n\""+Operation[currentOperation] -> GetCygpathCommand()+"\" \""+dest+"/\"> "+tempPath+"\\_cygpath.tmp";
          else outCommand2 << "\nECHO "+dest+"> "+tempPath+"\\_cygpath.tmp";
          outCommand2 << "\nSET /p dest=< "+tempPath+"\\_cygpath.tmp";
          outCommand2 << "\n \""+Operation[currentOperation] -> GetRsyncCommand()+"\" "+args+" \"%source%\" \"%dest%\" ";
          outCommand2 << "\n  SET el=%ERRORLEVEL%";
          outCommand2 << "\ndel "+tempPath+"/_cygpath.tmp 2>nul";

      outCommand2 << "\n:ennd";
      outCommand2 << "\nIF %el% neq 0 exit /b %el%";
      //outCommand2 << "\ndel \""+command1.fileName().replace("/","\\")+"\"";
      //outCommand2 << "\nstart \"rsync.bat\" /min cmd /C del \"%0\" >nul 2>&1";
      outCommand2 << "\nECHO BACKUP OK";
      QString ret=command2.fileName();
      command2.close();
      
   
}*/

QString createWinRsyncCommand(QString tempPath,bool vss,QStringList rsyncArgs,bool logGui=true){
//  QFile settingsfile(settingsFile);
//  if (!settingsfile.open(QIODevice::WriteOnly))   // if the settings file cannot be saved (or fails to create)
//  {
//      settingsfile.close();
//      return FALSE;
//  }

    //luckyb line to avoid compile WARNING
    vss = logGui;
    if (vss)
        vss=TRUE;
    // end of luckyb lines
    
//  showOnlyErrors = ui.checkBox_onlyShowErrors -> isChecked();
    QString logstring="";
    QFile command1(tempPath+SLASH+"l1qt_temp"+QString::number(qrand() % (999998) + 1) +".bat");
    QFile command2(tempPath+SLASH+"l2qt_temp"+QString::number(qrand() % (999998) + 1) +".bat");
    QTemporaryFile setvar(tempPath+SLASH+"qt_tempXXXXXX.bat");
    QString dest=rsyncArgs.takeLast();
    QString source=rsyncArgs.takeLast();
    //bool srcremote=false; // luckyb commend to avoid compile WARNING
    //bool dstremote=false;
    rsyncArgs.replaceInStrings("\"","\\\"");//double escape chars to include in bat
    QString args="\""+rsyncArgs.join("\" \"")+"\"";
/* disable vss until...
    args.replace("\"--vss\"",""); */
    if (source.contains('@')||source.startsWith(SLASH+SLASH)){
        args.replace("\"--backup-nt-streams\"","");
        vss=false;
        //srcremote=true;   // luckyb lines to avoid compile WARNING
        if (source.startsWith("\\\\"))
            source="\\\\"+source;
        //source=source.replace("\\","/");
      }
    if (dest.contains('@')||dest.startsWith(SLASH+SLASH)){
        args.replace("\"--restore-nt-streams\"","");
        args.append(" \"--chmod=u=rwX\" ");
        // dstremote=true;  // luckyb lines to avoid compile WARNING
        //dest=dest.replace("\\","/");
        if (dest.startsWith("\\\\"))
            dest="\\\\"+dest;
      }
    //source=fixWinPathForRsync(source,srcremote);
    //dest=fixWinPathForRsync(dest,dstremote);
    mapdrive=getMapdrive();
    /* disable vss until...
    if (vss)
    {
        doVss=1;
        logstring=" >> \""+pipeVssFile->fileName()+"\" 2>> \""+pipeVssErrFile->fileName()+"\"";
    

        if (!setvar.open()) // if the settings file cannot be saved (or fails to create)
        {
            setvar.close();
            return "";
        }
        setvar.close(); 
        
        //QTemporaryFile logfile;
        //if (!logfile.open())    // if the settings file cannot be saved (or fails to create)
        //{
        //   logfile.close();
        //    return "";
        //}
        logfile.close();
        
        //write arrays to file
        if (!command1.open(QIODevice::WriteOnly | QIODevice::Text)) // if the settings file cannot be saved (or fails to create)
        {
            command1.close();
            return "";
        }

        QTextStream outCommand1(&command1);
        outCommand1 << "\n@ECHO OFF";
        outCommand1 << "\nECHO DOING RSYNC >> \""+pipeVssFile->fileName()+"\" ";
        //outCommand1 << "\nECHO \"\" > \""+pipeVssErrFile->fileName()+"\"";
        outCommand1 << "\nSETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION ";

        outCommand1 << "\nCALL "+setvar.fileName();

        outCommand1 << "\n\""+Operation[currentOperation] -> GetDosdevCommand()+"\" "+mapdrive+": %SHADOW_DEVICE_1%  >> \""+pipeVssFile->fileName()+"\" 2>> \""+pipeVssErrFile->fileName()+"\"";
        outCommand1 << "\n SET SOURCE="+source;
        if (vss) outCommand1 << "\n SET SOURCE="+mapdrive+"%SOURCE:~1%";
        if (!source.contains('@')) outCommand1 << "\n\""+Operation[currentOperation] -> GetCygpathCommand()+"\" \"%SOURCE%\"> "+tempPath+SLASH+"_cygpath.tmp";
        else outCommand1 << "\nECHO "+source+"> "+tempPath+SLASH+"_cygpath.tmp";
        outCommand1 << "\nSET /p source=< "+tempPath+SLASH+"_cygpath.tmp";
        if (!dest.contains('@')) outCommand1 << "\n\""+Operation[currentOperation] -> GetCygpathCommand()+"\" \""+dest+"/\"> "+tempPath+SLASH+"_cygpath.tmp";
        else outCommand1 << "\nECHO "+dest+"> "+tempPath+SLASH+"_cygpath.tmp";
        outCommand1 << "\nSET /p dest=< "+tempPath+SLASH+"_cygpath.tmp";
        outCommand1 << "\nSET HOME="+luckyBackupDir;
        outCommand1 << "\nSET CYGWIN=nodosfilewarning";
        outCommand1 << "\n\""+Operation[currentOperation] -> GetRsyncCommand()+"\" "+args+" \"!source!\" \"!dest!\"  >> \""+pipeVssFile->fileName()+"\" 2>> \""+pipeVssErrFile->fileName()+"\"";
        outCommand1 << "\nSET ACTERR=!ERRORLEVEL! ";

        outCommand1 << "\nECHO Backing up completed: !ACTERR!. !DATE! !TIME!  >> \""+pipeVssFile->fileName()+"\"";

        outCommand1 << "\nECHO delete shadow device drive mapping >> \""+pipeVssFile->fileName()+"\" 2>> \""+pipeVssErrFile->fileName()+"\"";
        outCommand1 << "\n\""+Operation[currentOperation] -> GetDosdevCommand()+"\" -r -d "+mapdrive+": 2>NUL ";
        //outCommand1 << "\nrem del "+setvar.fileName()+" ";
        //outCommand1 << "\nrem del %0 ";
        outCommand1 << "\nIF %ACTERR% GTR 0 ( ";
        outCommand1 << "\nECHO ERROR on backup.  %DATE% %TIME% >> \""+pipeVssErrFile->fileName()+"\"";
        outCommand1 << "\nexit 1 ";
        outCommand1 << "\n) ";
        command1.close();
    }*/


    if (!command2.open(QIODevice::WriteOnly | QIODevice::Text)) // if the settings file cannot be saved (or fails to create)
    {
        command2.close();
        return "";
    }
    QTextStream outCommand2(&command2);
    outCommand2 << "\n@ECHO OFF";
    outCommand2 << "\nSET tdebug=y";
    outCommand2 << "\nSET tdeleteshadows=y";
    outCommand2 << "\nSET el=0";
    //remove vss and
    /* disable vss until...
    if (vss)
    {
        outCommand2 << "\nFOR /F \"tokens=2* delims=[]\" %%A IN ('VER') DO FOR /F \"tokens=2,3 delims=. \" %%B IN (\"%%A\") DO SET WINVER=%%B.%%C";
        outCommand2 << "\nSET WINBIT=x86&&IF \"%PROCESSOR_ARCHITECTURE%\" == \"AMD64\" (SET WINBIT=x64) ELSE IF \"%PROCESSOR_ARCHITEW6432%\" == \"AMD64\" SET WINBIT=x64";
        outCommand2 << "\nIF %WINVER% LSS 5.1 (";
        outCommand2 << "\n        ECHO Sorry, %this% cannot run under this version of Windows %WINVER%-%WINBIT%  " + logstring;
        outCommand2 << "\n        SET el=12";
        outCommand2 << "\n        GOTO :ennd";
        outCommand2 << "\n)";
        outCommand2 << "\nSET VSHADOWVER=%WINVER%";
        outCommand2 << "\nIF %WINVER%==5.1 SET VSHADOWVER=xp&&SET WINBIT=x86";
        outCommand2 << "\nIF %WINVER%==5.2 SET VSHADOWVER=2003&&SET WINBIT=x86";
        outCommand2 << "\nIF %WINVER%==6.0 SET VSHADOWVER=2008";
        outCommand2 << "\nIF %WINVER%==6.1 SET VSHADOWVER=2008-r2";
        outCommand2 << "\nCD "+tempPath+"";
        outCommand2 << "\n      IF NOT \"%tdeleteshadows%\"==\"y\" (";
        outCommand2 << "\n              IF \"%tdebug%\"==\"y\" ECHO Skipping deletion of any existing shadow copies  " + logstring;
        outCommand2 << "\n      ) ELSE (";
        outCommand2 << "\n              IF \"%tdebug%\"==\"y\" ECHO About to delete any existing shadow copies  " + logstring;
        outCommand2 << "\n              ECHO y|\""+Operation[currentOperation] -> GetVshadowDir()+SLASH+"vshadow-%VSHADOWVER%-%WINBIT%.exe\" -da>nul";
        outCommand2 << "\n              IF ERRORLEVEL 1 (";
        outCommand2 << "\n                      IF \"%tdebug%\"==\"y\" ECHO Error occurred: testing for administrator permissions  " + logstring;
        outCommand2 << "\n                      IF EXIST \"%windir%\\system32\\test\" RMDIR \"%windir%\\system32\\__test\" 2>nul";
        outCommand2 << "\n                      VERIFY>NUL";
        outCommand2 << "\n                      MKDIR \"%windir%\\system32\\test\" 2>nul";
        outCommand2 << "\n                      IF ERRORLEVEL 1 (";
        outCommand2 << "\n                              REM not running as administrator, this is cause of failure" + logstring;
        outCommand2 << "\n                              IF \"%tdebug%\"==\"y\" ECHO No administrator permissions   " + logstring;
        outCommand2 << "\n                              SET /A el=11";
        outCommand2 << "\n                      ) ELSE (";
        outCommand2 << "\n                              ECHO running as administrator, there is a problem with vshadow" + logstring;
        outCommand2 << "\n                              RMDIR \"%windir%\\system32\\__test";
        outCommand2 << "\n                              SET /A el=7";
        outCommand2 << "\n                      )";
        outCommand2 << "\n                      GOTO :endd";
        outCommand2 << "\n              )";
        outCommand2 << "\n              IF \"%tdebug%\"==\"y\" ECHO Deleted any existing shadow copies   " + logstring;
        outCommand2 << "\n      )";
        outCommand2 << "\n       \""+Operation[currentOperation] -> GetVshadowDir()+SLASH+"vshadow-%VSHADOWVER%-%WINBIT%.exe\" -script=\""+setvar.fileName()+"\" -exec=\""+command1.fileName()+"\" "+source.left(1)+": ";
        outCommand2 << "\n      SET el=%ERRORLEVEL%";
        outCommand2 << "\n      del "+tempPath+"/_cygpath.tmp 2>nul";
        //outCommand2 << "\ncall \""+setvar.fileName()+"\"";
        //outCommand2 << "\n  \""+dosdevCommand+"\" "+mapdrive+": %SHADOW_DEVICE_1%  ";
        //outCommand2 << "\n       \""+vshadowDir+SLASH+"vshadow-%VSHADOWVER%-%WINBIT%.exe\" -ds=%SHADOW_ID_1%";
        if (!logGui){
          outCommand2 << "\nTYPE \""+pipeVssFile->fileName()+"\" ";
          outCommand2 << "\nTYPE \""+pipeVssErrFile->fileName()+"\" 1>&2";
          }
    }
    
    else {*/
        if (!source.contains('@')) outCommand2 << "\n\""+Operation[currentOperation] -> GetCygpathCommand()+"\" \""+source+"\"> "+tempPath+SLASH+"_cygpath.tmp";
        else outCommand2 << "\nECHO "+source+"> "+tempPath+SLASH+"_cygpath.tmp";
        outCommand2 << "\nSET /p source=< "+tempPath+SLASH+"_cygpath.tmp";
        if (!dest.contains('@')) outCommand2 << "\n\""+Operation[currentOperation] -> GetCygpathCommand()+"\" \""+dest+"/\"> "+tempPath+SLASH+"_cygpath.tmp";
        else outCommand2 << "\nECHO "+dest+"> "+tempPath+SLASH+"_cygpath.tmp";
        outCommand2 << "\nSET /p dest=< "+tempPath+SLASH+"_cygpath.tmp";
        outCommand2 << "\nSET HOME="+luckyBackupDir;
        outCommand2 << "\nSET CYGWIN=nodosfilewarning";
        outCommand2 << "\n \""+Operation[currentOperation] -> GetRsyncCommand()+"\" "+args+" \"%source%\" \"%dest%\" ";
        outCommand2 << "\n  SET el=%ERRORLEVEL%";
        outCommand2 << "\ndel "+tempPath+"/_cygpath.tmp 2>nul";
    /* disable vss until...  
    } */
    outCommand2 << "\n:ennd";
    outCommand2 << "\nIF %el% neq 0 exit /b %el%";
    //outCommand2 << "\ndel \""+command1.fileName().replace("/",SLASH+"")+"\"";
    //outCommand2 << "\nstart \"rsync.bat\" /min cmd /C del \"%0\" >nul 2>&1";
    outCommand2 << "\nECHO BACKUP OK";
    QString ret=command2.fileName();
    command2.close();
    return ret;
}
void setAppDir(QString s){
  luckyBackupDir = s;
  settingsFile = luckyBackupDir + "settings.ini";     // settings file
  profileDir = luckyBackupDir + "profiles/";          // profiles directory
  defaultProfile = profileDir + "default.profile";    // default profile
  standardDefaultProfile = profileDir + "default.profile"; // standard default profile
  logDir = luckyBackupDir + "logs/";                  // logs directory
  logfilename = logDir + "logfile.log";               // logfile filename - this will change according to the profile an task executed
  snapChangesDir = luckyBackupDir + "snaps/";         // Snapshots changes files are stored here. It lies inside ~
  snapEmptyDir = snapChangesDir + "EMPTY/";           // empty directory used to delete older snapshots
  snapchangesfilename = snapChangesDir + "changes.log"; // Snapshot changes filename. This will change according to the snapshot
  snapChangesString = "[changed_data]%i[LB]%n";       // The log lines format of the "changes" file that stores changes made for every snapshot
  scheduleDir = luckyBackupDir + "schedule/";         // schedule directory
  schedulefilename = scheduleDir + "schedule.dat";    // cron data filename
  cronfilename = scheduleDir + "luckyCron.txt";       // cron filename
}
// end of global.cpp ---------------------------------------------------------------------------

