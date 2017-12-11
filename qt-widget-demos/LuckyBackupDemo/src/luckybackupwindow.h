/* ------------------ luckybackupwindow.h --------------------------------------------------------------------------------------
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


 project version	: Please see "main.cpp" for project version

 developer          : luckyb 
 last modified      : 07 Feb 2014
===============================================================================================================================
===============================================================================================================================
*/


#ifndef LUCKYBACKUPWINDOW_H
#define LUCKYBACKUPWINDOW_H

//include  header file that qmake produces from "*.ui" created with qt designer
#include "ui_luckybackupwindow.h"
#include <QSystemTrayIcon>

//==============================================================================================================
//Declaration of luckyBackupWindow class (this is the main window of the app)
class luckyBackupWindow : public QMainWindow
{
    Q_OBJECT
    
    public:
        luckyBackupWindow (QMainWindow *parent = 0);
        
        // general variables
        bool taskClicked;   //these 2 bool vars help to determine when a checkbox state is changed for SLOT taskStateChanged
        bool taskChanged;
        bool savedProfile;  // Becomes true if a profile is saved and false if it is modified

        bool GoBack;        // Becomes true if the user tries to load a profile, but regrets it !!
        QString InfoData;   //String holding the information window text
        QString createData; //String holding messages from createCurrentProfile
        QString loadData;   //String holding messages from loadCurrentProfile
        QString saveData;   //String holding messages from saveCurrentProfile

        int InfoInt;        // this helps to define which message will appear at the info window
        int count;          //simple count variable !!

    private slots:
        void profileComboChanged(); // SLOT to set the currentProfile when profileCombo index changes
        void savePressed();         // SLOT to execute when "save" pressed
        void deleteCurrentProfile();//SLOT: Delete the current profile
        void NewProfile();          //SLOT: Create a new empty profile
        void setDefaultProfile();   //SLOT: Set the current profile as default
        void renameCurrentProfile();//SLOT: rename the current profile
        void exportProfile();       //SLOT to export a profile
        void importProfile();       //SLOT to import a profile
        void duplicateProfile();    //SLOT to duplicate a profile
        void changeProfileDescription();//SLOT to change the profile description

        void exitApp();             //SLOT: check if a profile is saved and exit application

        void help();                //SLOT: open "help" popup when action selected
        void about();               //SLOT: open "about" popup when action selected
        void setToolbarAttrs();     //SLOT: sets the toolbar attributes
        void setWinPaths();         //SLOT: sets the rsync and ssh paths for windows

        void setLanguage(QAction *);//SLOT: Change the application language

        void checkCurrentItem(QListWidgetItem *);	//SLOT: Check the currently selected operation and set an icon
        void taskStateChanged();    //SLOT: Sets the profile state to unsaved if a task checkbox is changed
        void refreshList();         //SLOT: Refresh the operations list when refresh button pressed
        void start();               //SLOT: Open start operations dialog when Button clicked()
        void modify();              //SLOT: Modify an existing task. Will also save it if bool is TRUE
        void add();                 //SLOT: Add a new task
        void remove();              //SLOT: remove highlighted task
        void manage();              //SLOT: Manage existing backups of an existing task
        void AlsoCreateRestore();   //SLOT: Create another operation for RESTORE
        void duplicateTask();       //SLOT to duplicate a task
        void moveUp();              //SLOT: move  highlighted operation one position up
        void moveDown();            //SLOT: move  highlighted operation one position down
        void schedule();            //SLOT: Open schedule dialog when Button clicked()
        void email();               //SLOT: Open email dialog when Button clicked()
        
        void hideShowInfoWindow();	// SLOT to hide or show the info window

        //execute.cpp SLOTS
        void abortPressed();		//SLOT when button pressed( see also notYet)
        void donePressed();		//SLOT when done button pressed
        void appendRsyncOutput();	//Display o/p to textbrowser & update logfile
/*disable vss until...
        void appendRsyncVssOutput();
        void appendRsyncVssOutput(int size);*/
        void procFinished();		//SLOT executed when syncProcess is finshed (will start a new syncProcess if any left)
        void procError();        // SLOT for when a process reports an error (eg: failed to start)
        
        void LBtrayActivated(QSystemTrayIcon::ActivationReason reason);
        void minimizeTray();
        void restoreTray();

        void previousErrorJump();
        void nextErrorJump();

    private:
        Ui::luckyBackupWindow ui;
        
        QSystemTrayIcon *LBtray;	//this is luckybackup's tray icon
        QMenu *languageMenu;
        QMenu *settingsMenu;
        QMenu *toolbarsMenu;
        QActionGroup *languageGroup;
        QActionGroup *toolbarsGroup;
        QMenu *helpMenu;
        QAction *action;
        QAction *actionHelp;
        QAction *actionAbout;
        QToolBar *profileToolbar;
        QToolBar *profileComboToolbar;
        QToolBar *profileStartToolbar;
        QToolBar *shutdownToolbar;
        QToolBar *errorsToolbar;
        QAction *visibleProfileToolbar;
        QAction *visibleProfileComboToolbar;
        QAction *visibleProfileStartToolbar;
        QAction *actionLockToolbars;
        QAction *actionVisibleToolbarText;
        QAction *actionSetWinPaths;
        QStringList deletedTaskNames;
        bool saveOrNot;
        
        //The following functions are inside functions.cpp~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void setCurrentProfile(QString);//function to check if a profile is valid and load it by calling loadProfile
        bool loadCurrentProfile();      //function to  load an existing profile
        bool saveCurrentProfile();      //function to save a profile 
        int createCurrentProfile();     //function to create a profile
        int isProfileSaved();           //function to check if the current profile is saved and proceed or not
        void checkDeclared();           //function to check all declared data of included operations
        bool checkOperationList();      // function to first check the operations list for errors (eg nothing is included)
        void retranslateUi();           //function to retranslate the ui when user changes the gui language
        void createMenus();             // create the menu "language" with all available languages & menu "help"
        void createToolbar();           // create the toolbar
        void createActions();           // create all actions
        void createProfileCombo();      // fill the profile combo box with existing profile names
        bool saveSettings();            //saves various luckybackup settings such as the default profile
        bool loadSettings();            //loads various luckybackup settings such as the default profile - text mode
        bool loadSettingsQV();          //loads various luckybackup settings such as the default profile - data mode
        void InitializeVariables();     //initializes all variables
        bool arrangeLogSnap(bool,QString,QString);//Rename-delete-copy logs & snaps when a profile/task is renamed, deleted,duplicated

        QString defaultLanguage;        // holds the app's default language
        QString TransDir;               // holds the actual translation directory path
        QUrl helpURL;                   // holds the actual manual path as a QUrl
        QString manualChapter;          // holds the specific chapter of the manual. changes depending on which window is open
        QUrl licenseURL;                // holds the actual license path as a QUrl
        int mainWindowWidth;            // holds the main window width in pixels
        int mainWindowHeight;           // holds the main window height in pixels
        bool AreToolbarsLocked;         // holds the lock state of the toolbars
        bool IsVisibleProfileComboToolbar;  // holds the visible state of the profile combo toolbar
        bool IsVisibleProfileToolbar;   // holds the visible state of the profile actions toolbar
        bool IsVisibleProfileStartToolbar; // holds the visible state of the profile start toolbar
        bool IsVisibleToolbarText;      // holds the visible state of the toolbar text
        bool IsVisibleInfoWindow;       // holds the visible state of the info window
        bool showOnlyErrors;            //This becomes true if the user selects to only display errors at the commands output window

        //inside execute.cpp-----------------------------------------------------
        void executeNOW();      //start the execution of commands (rsync & others)
        void setNowDoing();     //Display sth in the Now Doing textBrowser
        void executeRsync();    //execute qprocess "rsync" with Arguments
        void swapGUI(QString);  //swaps the gui mode from normal to execute
        int errorCount;         //used for next/previous error button
        bool firstScroll;       //used for next/previous error button
        bool NOWexecuting;      //becomes true if a profile execution is running
        bool guiModeNormal;     //becomes true when the gui is in normnal mode
        bool ABORTpressed;      //becomes true if the abort button is pressed
        void finishUp();        // finish up some stuff when all tasks finish either normally or aborted
        void shutDownSystem();  // shutdown the system if the relevant button is pressed
        QString convertBytes(QString,bool);  // Converts a string of the form of 10GB to bytes and vice versa
        
        //Progress bar variables
        int progress_total;	//Maximum value of progress
        int progress_done;	//Current value of progress

        //variables used for rsync command
        QString command;		//command to be executed. Normally this is "rsync"
        QStringList rsyncArguments;	// This stringList holds all arguments for the rsync command
        QString outputString;		//all the output of rsync is going to fit in here
        QString outputError;		//all the error output of rsync is going to fit in here
        QString outputInsert;		//this is used to enter application output between outputString/Error
        QString nowDoingText;		//this is the text printed in the NowDoing textBrowser

        bool sync;			//becomes true if syncing is to be executed
        bool syncAB;			//becomes true if syncing from dirA to dirB is to be executed
        QString dirA;			//holds the first dir to be synced
        QString dirB;			//holds the second dir to be synced
        
        bool calculating;		//these 3 bools are used to diplay progress of rsync at the info window
        bool transferring;
        bool deleting;
        
        bool ExecuteBefore;		//becomes true if a before command is to be executed, not rsync !!
        bool ExecuteAfter;		//becomes true if a after command is to be executed, not rsync !!
        bool ExecuteBeforeExitedError;	// becomes true if a before command exits with an error
        bool StopTaskExecution; // becomes true if we want to stop task execution
        bool ProcReportedError;      //becomes true if any process reports an error (eg failed to start)
        bool DestCreateFail;		// This will become TRUE if destination does not exist and cannot be created
        int repeatOnFailMax;   // This is equal to the number of times a command will run when it fails
        int repeatOnFailTry;        // This is the current run of a command
        int currentBefore;		//count variable for commands to be executed before task
        int currentAfter;		//count variable for commands to be executed before task
        void executeBeforeTask();	//function to start execution of pre-task commands
        void executeAfterTask();	//function to start execution of post-task commands

        //tray icon stuff
        QString trayMessage;		// tray baloon message text
        QAction *actionAbort;
        QAction *minimizeToTray;
        QAction *restoreFromTray;
        QMenu *LBtrayMenu;
        void createTrayIcon();		// create the tray icon + relevant actions
        bool isMinimizedToTray;		// becomes true if the gui is minimized to tray

    protected:
        void closeEvent(QCloseEvent *event);
};

#endif

// end of luckybackupwindow.h--------------------------------------------------------------
