/* ------------------ global.h --------------------------------------------------------------------------------------
 header file for luckyBackup project

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

 developer          : lucky
 last modified      : 06 Feb 2014
===============================================================================================================================
===============================================================================================================================
*/


#ifndef GLOBAL_H
#define GLOBAL_H

QString myHome = QDir::homePath();                          // user's home directory
QString currentUser;                                        // will hold the current username (definition at luckybackupwindow.cpp)
QString const appName = "luckyBackup";                      // application name
double const appVersion = 0.48;                             // application version
QString appVersionString = "0.4.8";                         // application version
double const validProfileVersion = 0.21;                    // profile version before this a profile won't be loaded
double const validScheduleVersion = 0.34;                   // schedule version before this a schedule won't be loaded
double const validSettingsVersion = 0.3;                    // Settings file valid version
QString luckyBackupDir = myHome + "/."+appName+"/";         // app working directory
QString luckyBackupDefaultDir = myHome + "/."+appName+"/";  // same as above. WINDOWS use
QString settingsFile = luckyBackupDir + "settings.ini";     // settings file
QString profileDir = luckyBackupDir + "profiles/";          // profiles directory
QString defaultProfile = profileDir + "default.profile";    // default profile
QString standardDefaultProfile = profileDir + "default.profile"; // standard default profile
QString logDir = luckyBackupDir + "logs/";                  // logs directory
QString logfilename = logDir + "logfile.log";               // logfile filename - this will change according to the profile an task executed
QString cronlogString = "LastCronLog.log";                  // cron logfile full filename: "ProfileName-LastCronLog.log"
QString emailLogString = "-email.log";                      // logfile to send by email (all task logs merged) full filename: "ProfileName-email.log"
QString emailLastLogString = "-email-LastLog.log";          // email logfile full filename: "ProfileName-email-LastLog.log"
QString snapDefaultDir = ".luckybackup-snaphots/";          // This is the directory where snapshots are placed. It lies inside the destination
QString snapChangesDir = luckyBackupDir + "snaps/";         // Snapshots changes files are stored here. It lies inside ~
QString snapEmptyDir = snapChangesDir + "EMPTY/";           // empty directory used to delete older snapshots
QString snapchangesfilename = snapChangesDir + "changes.log"; // Snapshot changes filename. This will change according to the snapshot
QString snapChangesString = "[changed_data]%i[LB]%n";       // The log lines format of the "changes" file that stores changes made for every snapshot
QString scheduleDir = luckyBackupDir + "schedule/";         // schedule directory
QString schedulefilename = scheduleDir + "schedule.dat";    // cron data filename
QString cronfilename = scheduleDir + "luckyCron.txt";       // cron filename
QString relativeTransDir = "translations/";                 // translation directory when app executed but not installed
QString systemTransDir = "/usr/share/luckybackup/translations/";// system translation directory (when app is installed)
QDir transDir;                                              // the current translations directory
QTranslator appTranslator;                                  //QTranslator that holds the applications translation
QString locale = QLocale::system().name();                  //String that holds the current language locale
QString relativeLicense = "license/gpl.html";               // licence directory when app executed but not installed
QString systemLicense = "/usr/share/doc/luckybackup/license/gpl.html";    // system licence directory (when app is installed)
QString suseLicense = "/usr/share/doc/packages/luckybackup/license/gpl.html";    // system licence directory (when app is installed) - openSuse
QString debianLicense = "/usr/share/common-licenses/GPL-3"; // system licence directory (when app is installed) - debian
QString relativeManual = "manual/index.html";               // manual directory when app executed but not installed
QString systemManual = "/usr/share/doc/luckybackup/manual/index.html";    // system manual directory (when app is installed)
QString suseManual = "/usr/share/doc/packages/luckybackup/manual/index.html";    // system manual directory (when app is installed) - opensuse

QString countStr;                                           //this helps displaying integers as strings
QString message="";                                         //this is really handy to hold messages for dialogs
QString messageCLI="";                                      //this is really handy to hold messages for the Command-Line
int errorsFound;                                            //count errors when executing rync or pre/post command
int filesTransfered;                                        //count files transfered when executing rync
unsigned long long int bytesTransfered;                     //count bytes transfered when executing rync

// Useful variables for operations ---------------------------------------------------------------------------------------------------
int const maxOperations = 100;                              //The maximum number or operations permitted
int TotalOperations=0;                                      //The number of available operations "operations list"- starts from 1
int currentOperation=-1;                                    //this holds the current row from the operations list- starts from 0
int removeCharLimit;                                        // No of characters to remove from lines inside snapshot .changes file
bool modifyOK=FALSE;                                        //bool variable that says create or modify opeartion went ok
bool modifyConnected=FALSE;                                 //if the operation under modification is connected to another op, this becomes TRUE
bool DryRun=FALSE;                                          //shows if dry-run is checked
bool ask=FALSE;                                       // becomes true if we want to ask the user if he/she wants to continue with the execution of operations or not
bool newTaskThisIs = TRUE;                                  // becomes true if "add task" is pressed and FALSE if "modify" task is pressed
bool NothingToDo=FALSE;                                     // Becomes true if there is nothing to do when start button pressed
bool NothingIncluded=FALSE;                                 // Becomes true if there is nothing checked ("include" checkboxes)
bool crontabUpdated=FALSE;                                  // Becomes true if the user's crontab is updated
QString currentProfile="";                                  // This holds the filename of the currently used profile
QString profileName="";                                     //just holds the profile name not the full path+filename.profile
QString profileDescription="";                              //holds a description of the profile
QFile profile("");                                          //this is the profile QFile
QFile logfile("");                                          //this is the logfile QFile
QFile snapfile("");                                         //this is the snapshot changes QFile
QString CheckedData;                                        //String holding the current task message (OK - WARNING - CRITICAL) for info window display
QString CheckedDataCLI;                                     //String holding the current task message (OK - WARNING - CRITICAL) for CLI  display
operation *Operation[maxOperations];                        //The array that holds name, source, destination & arguments of "Opereations list"

bool console;                                               // these become true depending on the argument given at command line
bool NoQuestions;                                           // do not ask any questions at console mode
bool SkipCritical;                                          // skip critical tasks
bool silentMode;                                            // start at silent mode
bool runImmediately;                                        // execute a profile immediately after gui loads
bool validation;                                            // becomes true if "validation check" button is pressed
bool KDErunning = FALSE;                                    // becomes true if desktop running is KDE
bool GNOMErunning = FALSE;                                  // becomes true if desktop running is GNOME

// functions ------------------------------------------------------------------------------------------------------------------------
bool argumentsTest(int , char**);                           // checks the arguments given at command-line and returns true if everything is ok
bool loadCurrentProfile();                                  //loads an already created profile
void declareRsyncCommand();                                 // Declares the rsync & ssh commands (full path for windows)
bool check_list();                                          //check the operations list
bool check_dirs();                                          //check directories of declared profile data

void help();                                                // Displayes command-line usage
void checkSyncDirs(QString, QString);                       // function to check if the directories to be synced exist or are empty
void checkBackupDirs(QString, QString);                     // function to check if the source & dest dirs exist and are not empty
int  loadProfile(QString);                                  // loads an existing profile - text mode
int  loadProfileQV(QString);                                // loads an existing profile - data mode
bool saveProfile(QString);                                  // saves an existing profile
bool exportFullProfile(QString,QString);                    //function to export the .profile file + logs + snaps
int importFullProfile(QString,QString);                     //function to import the .profile file + logs + snaps (whatever is available)
bool checkTaskList();                                       // Checks if the Task list is ok to proceed
bool checkDeclaredDirs(bool);                               // Check if the declared data are ok by calling checkBackupDirs or checkSyncDirs
QStringList AppendArguments(operation*);                    // Set command's (normally rsync) arguments
bool writeToLog;                                            // if the log file is ok to write this becomes TRUE
QString logFileUpdate(QString, QString, int);               // Update the logfile with some string
bool checkMountPoint(QString);                              // Check if a path belongs to a mountpoint or is a mountpoint itself
void setTextMessages (QString,QString,bool,bool,QString,QString,QString);// function to set text feedback for the user
QString fixWinPathForRsync(QString,bool);                        // Fixes a windows path for rsync use
QString calculateLastPath(QString);                         // Calculates the last part of a path eg path=user@host:destination\path\here -> returns "here"

QString emailCommand;
QString emailArguments;
bool    emailNever;
bool    emailError;
bool    emailSchedule;
bool    emailTLS;
QString emailFrom;
QString emailTo;
QString emailSubject;
QString emailSMTP;
QString emailBody;
QString emailDefaultSubject =   appName + " report";     // Holds the default subject
QString emailDefaultBody    =   "Profile:      %p"
                                "\nDate:         %d"
                                "\nTime:         %i"
                                "\nErrors found: %e";                   // Holds the default body text
QString emailDefaultCommand    =   "sendemail";     // Holds the default email command
QString emailDefaultArguments  =   "-f %f -t %t -u %s -m %b -a %l -s %v";     // Holds the default email arguments
QString emailDefaultWinCommand ="C:\\Program Files (x86)\\luckyBackup\\blat\\blat.exe";     // Holds the default email command - WINDOWS
QString emailDefaultWinArguments ="-f %f -to %t -s %s -server %v -attach %l -body %b";     // Holds the default email arguments - WINDOWS
QString sendEmailNow (bool);                                // Send an email after a profile run. bool is TRUE if called for testing purposes

QString rsyncDefaultCommand = "rsync";                      // Holds the default rsync command
QString sshDefaultCommand = "ssh";                          // Holds the default ssh command

// WINDOWS related variables. Also search variables above for "WINDOWS use"
QString rsyncDefaultWinCommand = "C:\\Program Files (x86)\\luckyBackup\\cygwin\\rsync.exe"; // Holds the default rsync command for windows
QString sshDefaultWinCommand = "C:\\Program Files (x86)\\luckyBackup\\cygwin\\ssh.exe";    // Holds the default ssh command for windows
QString appPath = QCoreApplication::applicationDirPath();           // This is used for windows app path. It's also causing a ...
                                                    //"QCoreApplication::applicationDirPath: Please instantiate the QApplication object first" WARNING message
//QString rsyncDefaultWinCommand = appPath+"/rsync.exe"; // Holds the default rsync command for windows
//QString sshDefaultWinCommand = appPath+"/ssh.exe";             // Holds the default ssh command for windows
QString mapdrive="w";
QString vshadowDir=             appPath;
QString vshadowDefaultDir=      appPath;
QString dosdevCommand=          appPath+"/dosdev.exe";
QString dosdevDefaultCommand=   appPath+"/dosdev.exe";
QString cygpathCommand=         appPath+"/cygpath.exe";
QString cygpathDefaultCommand=  appPath+"/cygpath.exe";
bool isTempDirPath=false;
QString tempDirPath=QDir::tempPath();
QString tempDefaultDirPath=QDir::tempPath();
void setAppDir(QString s);
/* disable vss until
int doVss=0;
int vssPos=0;
int vssErrPos=0;
QTimer *vssTimer;
int vssSleepTime=50;
int vssReadSize=400;
QFile *pipeVssFile;
QFile *pipeVssErrFile;*/
//QString createWinMkdirCommand(QString tempPath,bool vss,QStringList rsyncArgs,bool logGui);
QString createWinRsyncCommand(QString tempPath,bool vss,QStringList rsyncArgs,bool logGui);
// END of Windows related variables

QString rsyncCommandPath;       // holds the full path of the rsync command for WINDOWS or just "rsync" for *nix
QString sshCommandPath;         // holds the full path of the ssh command for WINDOWS or just "ssh" for *nix

QString XnixSLASH = "/";        // holds the default Xnix slash which is /

#ifdef Q_OS_OS2
bool OS2running = TRUE;
QString SLASH = "\\";
#else
bool OS2running = FALSE;
QString SLASH = "/";
#endif

#ifdef Q_OS_WIN32
bool WINrunning = TRUE;
#else
bool WINrunning = FALSE;
#endif

#if defined Q_OS_OS2 || defined Q_OS_WIN32
bool notXnixRunning=TRUE;
#else
bool notXnixRunning=FALSE;
#endif
#endif

// end of global.h--------------------------------------------------------------