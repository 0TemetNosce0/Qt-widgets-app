/* --------------------------luckybackupwindow.cpp -----------------------------------------------------------------------------
cpp file that does all stuff needed when a signal is transmitted (eg button pressed) from the main app window

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

developer       : luckyb 
last modified   : 10 Feb 2014
===============================================================================================================================
===============================================================================================================================
*/

#include <QtGui>

#include "global.cpp"

//inluded headers ---------------------------------------------------------------
#include "luckybackupwindow.h"

//inluded sources ---------------------------------------------------------------
#include "textDialog.cpp"
#include "winDialog.cpp"
#include "modifyDialog.cpp"
#include "helpBrowser.cpp"
#include "scheduleDialog.cpp"
#include "emailDialog.cpp"
#include "about.cpp"
#include "manage.cpp"
#include "functions.cpp"
#include "executenow.cpp"
#include "patternEditor.cpp"

helpBrowser *helpbrowser;

//class luckyBackupWindow constructor=============================================================================================
luckyBackupWindow::luckyBackupWindow(QMainWindow *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    InitializeVariables();

    //create directory ~/.luckyBackup including folders "logs", "profiles", "schedule", snaps if they do not exist for the current user
    QDir profiledir(profileDir), logdir(logDir), scheduledir(scheduleDir), snapdir(snapChangesDir), emptydir(snapEmptyDir);
    if (!profiledir.exists())
        profiledir.mkpath(profileDir);
    if (!logdir.exists())
        logdir.mkpath(logDir);
    if (!scheduledir.exists())
        scheduledir.mkpath(scheduleDir);
    if (!snapdir.exists())
        snapdir.mkpath(snapChangesDir);
    if (!emptydir.exists())
        emptydir.mkpath(snapEmptyDir);
    //check if the EMPTY dir is empty
    QStringList emptyList = emptydir.entryList(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot);
    if (emptyList.size() > 0)
    {
        QProcess *rmProcess;
        rmProcess  = new QProcess(this);
        QStringList rmArgs;
        rmArgs << "-rvf" << snapEmptyDir;
        rmProcess -> start ("rm",rmArgs);
        rmProcess -> waitForFinished();
        emptydir.mkpath(snapEmptyDir);
    }
    
    currentUser = myHome;
    if (currentUser == "/root")
    {
        currentUser = tr("super user","super user is the root user");
        this -> setWindowTitle(appName + " - " + tr("super user mode"));
    }
    else
    {
        currentUser.remove("/home/");
        this -> setWindowTitle(appName);
    }

    // load the user settings file. If it does not exist create it
    QFile settingsfile(settingsFile);
    if (settingsfile.exists())
        loadSettings();
    else
        saveSettings();

    createActions();	//create all actions needed
    createToolbar();	// create tool bar
    createMenus();		//create the top menu

    retranslateUi();

    //change gui to normal mode and resize it!!
    this -> resize(mainWindowWidth, mainWindowHeight);
    swapGUI("normal");

    // Connections ----------------------------------------------------------------------------------------------------------
    connect ( ui.pushButton_exit, SIGNAL( clicked() ), this, SLOT( exitApp() ) );		//pushbutton exit
    connect ( ui.actionQuit, SIGNAL(triggered()), this, SLOT(exitApp()));			//menu action quit

    connect ( ui.comboBox_profile, SIGNAL(currentIndexChanged (const int) ), this, SLOT(profileComboChanged()));

    connect ( ui.actionNew, SIGNAL(triggered()), this, SLOT(NewProfile()));			//menu action newProfile
    connect ( ui.actionRename, SIGNAL(triggered()), this, SLOT(renameCurrentProfile()));	//menu action renameProfile
    connect ( ui.actionSave, SIGNAL(triggered()), this, SLOT(savePressed()));		//menu action saveProfile
    connect ( ui.actionSchedule, SIGNAL( triggered() ), this, SLOT( schedule() ) );		//action schedule
    connect ( ui.actionEmail, SIGNAL( triggered() ), this, SLOT( email() ) );     //action email
    connect ( ui.actionRefresh, SIGNAL( triggered() ), this, SLOT( refreshList() ) );	//action refresh (task list)
    connect ( ui.actionDelete, SIGNAL( triggered() ), this, SLOT( deleteCurrentProfile() ) );	//action delete (currentProfile)
    connect ( ui.actionDefault, SIGNAL( triggered() ), this, SLOT( setDefaultProfile() ) );	//action default (set currentProfile as default)
    connect ( ui.actionImport, SIGNAL( triggered() ), this, SLOT( importProfile() ) );	//action import profile
    connect ( ui.actionExport, SIGNAL( triggered() ), this, SLOT( exportProfile() ) );	//action export profile
    connect ( ui.actionDuplicate_Profile, SIGNAL( triggered() ), this, SLOT( duplicateProfile() ) ); //action duplicate profile
    connect ( ui.actionDescription, SIGNAL(triggered()), this, SLOT(changeProfileDescription()));	//menu action changeProfileDescription
    
    connect ( ui.action_TaskAdd, SIGNAL( triggered() ), this, SLOT( add() ) ); 			//action add task
    connect ( ui.action_TaskModify, SIGNAL( triggered() ), this, SLOT( modify() ) ); 		//action modify task
    connect ( ui.action_TaskRemove, SIGNAL( triggered() ), this, SLOT( remove() ) ); 		//action remove task
    connect ( ui.action_TaskDuplicate, SIGNAL( triggered() ), this, SLOT( duplicateTask() ) ); 	//action create duplicate
    connect ( ui.action_TaskCreateRestore, SIGNAL( triggered() ), this, SLOT( AlsoCreateRestore() ) ); 	//action create restore
    connect ( ui.action_TaskManageBackup, SIGNAL( triggered() ), this, SLOT( manage() ) ); 		//action manage backup
    
    connect ( ui.pushButton_add, SIGNAL (clicked() ), this, SLOT(add()));			//pushbutton create (task)
    connect ( ui.pushButton_edit, SIGNAL (clicked() ), this, SLOT(modify()));		//pushbutton modify (task)
    connect ( ui.pushButton_remove, SIGNAL( clicked() ), this, SLOT( remove() ) );		//pushbutton remove (task)
    connect ( ui.pushButton_up, SIGNAL( clicked() ), this, SLOT( moveUp() ) );		//pushbutton up
    connect ( ui.pushButton_down, SIGNAL( clicked() ), this, SLOT( moveDown() ) );		//pushbutton down
    connect ( ui.pushButton_start, SIGNAL( clicked() ), this, SLOT( start() ) );		//pushbutton start
    //find a way to emit a signal when spacebar is used to change the state of an item.  itemChanged does not seem to work !!
    connect ( ui.listWidget_operations, SIGNAL( itemClicked ( QListWidgetItem*) ), this, SLOT( checkCurrentItem(QListWidgetItem *) ) );
    connect ( ui.listWidget_operations, SIGNAL( itemChanged ( QListWidgetItem*) ), this, SLOT( taskStateChanged() ) );

    connect (ui.pushButton_minimizeToTray, SIGNAL (clicked() ), this, SLOT(minimizeTray()));//pushbutton minimize to tray
    connect (ui.pushButton_previousError, SIGNAL (clicked() ), this, SLOT(previousErrorJump()));//pushbutton jump to prev error
    connect (ui.pushButton_nextError, SIGNAL (clicked() ), this, SLOT(nextErrorJump()));//pushbutton jump to next error
    
    connect (ui.pushButton_InfoCollapse, SIGNAL (clicked() ), this, SLOT(hideShowInfoWindow()));//pushbutton hide/show info window
    
    // Load the default profile as soon as the app starts or the one given as a command line argument
    if (!runImmediately)
        setCurrentProfile(defaultProfile);	// set the defaultProfile as current

    int create = createCurrentProfile();	// if it does not exist create it

    loadCurrentProfile();			// load the current (default or not ) profile - this is inside functions.cpp

// *********************TESTING purposes message boxs ****************************************************************************
/*QMessageBox::information(this, "LB","CurrentProfile=" + currentProfile + "\ntotal tasks: " + countStr.setNum(TotalOperations));
QString preRelease="8"; QString preDate="09 Feb 2012";
QString tempOSrunning="";if (OS2running) tempOSrunning="OS2";if (WINrunning) tempOSrunning="windows";if (!notXnixRunning) tempOSrunning="*nix";
QMessageBox::warning(this, "luckybackup",       "This is a testing version of <b>luckyBackup</b><br>"
                                                "NOT to be used as an official release and NOT to be trusted for actual backups<br><br>"
                                                "pre-release: <b>" + preRelease +"</b><br>version: <b>" + appVersionString + "</b><br>date: <b>"+preDate+
                                                 
                                                "</b><br>Operating system in use: <b>"+tempOSrunning +"</b><br><br>         Loukas :)");*/
// ********************* END of TESTING ******************************************************************************************

    checkCurrentItem(ui.listWidget_operations -> currentItem());	//refresh the selected (last) task as well as the menu items that depend on its type (sync/backup)

    createProfileCombo();	// update the profile combobox with all existing profiles and set index to currentProfile
    InfoData.append("<p align=\"center\"><font color=magenta><b>" + tr("Welcome to","full phrase: 'Welcome to luckyBackup'") +" "
    + appName);
    if (notXnixRunning)
        InfoData.append(" :-)</font></b></p>");
    else
        InfoData.append(", " + currentUser + " :-)</font></b></p>");
    
    if (create == 0)
        InfoData.append(loadData);
    else
        InfoData.append(createData);
    ui.textBrowser_info -> setText(InfoData);	//update the info window

    if (DryRun)		// if --dry-run was given as an argument, check the relevant box
        ui.checkBox_DryRun -> setChecked(TRUE);

    if (runImmediately)
        start();
    
    //variable that helps with translations
    QString currentLanguageIs = tr("English","Do not translate this. Enter here the language of the translation in native characters instead. This is how your translation will appear under the 'language' menu.");

}

//===================================================================================================================================================
//------------ SLOTS --------------------------------------------------------------------------------------------------------------------------------
//===================================================================================================================================================

// exit =============================================================================================================================================
// Exits luckybackup. Warn if the profile used is not saved
void luckyBackupWindow::exitApp()
{
    if (NOWexecuting)		//if a profile execution is in progress just minimize to tray
    {
        if (QSystemTrayIcon::isSystemTrayAvailable ())
            minimizeTray();
        return;
    }
    if (isProfileSaved() == 0)	//if the current profile is not saved, ask the user if he/she wants to
        return;
    mainWindowWidth = this -> width();
    mainWindowHeight = this -> height();
    IsVisibleProfileComboToolbar = profileComboToolbar -> isVisible();
    IsVisibleProfileToolbar = profileToolbar -> isVisible();
    IsVisibleProfileStartToolbar = profileStartToolbar -> isVisible();
    saveSettings();
    exit(0);	//quit
}

//do the same if the main window close button (or alt+F4) is pressed
void luckyBackupWindow::closeEvent(QCloseEvent *event)
{
    exitApp();
    event->ignore();
}

// profileComboChanged ================================================================================================================================
// SLOT to be executed when the profileCombo index changes
void luckyBackupWindow::profileComboChanged()
{
    if (GoBack)		//if this function is called but shouldn't be executed.
    {
        GoBack = FALSE;
        return;
    }
    InfoData = "";

    if (isProfileSaved() == 0)	//if the current profile is not saved, ask the user if he/she wants to
        return;

    //set the current profile according to the combobox reading
    QString ComboReadFullPath = profileDir + (ui.comboBox_profile -> currentText()) + ".profile";
    setCurrentProfile(ComboReadFullPath);
    loadCurrentProfile();			// load the current profile
    InfoData.append(saveData + "<br>");
    InfoData.append(loadData);
    ui.textBrowser_info -> setText(InfoData);	//update the info window
    loadData=""; saveData=""; createData="";
}

// lockToolbars ================================================================================================================================
// SLOT to lock the toolbars in their position
void luckyBackupWindow::setToolbarAttrs()
{
    AreToolbarsLocked = actionLockToolbars->isChecked();

    profileComboToolbar -> setFloatable(!AreToolbarsLocked);
    profileComboToolbar -> setMovable(!AreToolbarsLocked);
    profileStartToolbar -> setFloatable(!AreToolbarsLocked);
    profileStartToolbar -> setMovable(!AreToolbarsLocked);
    profileToolbar -> setFloatable(!AreToolbarsLocked);
    profileToolbar -> setMovable(!AreToolbarsLocked);

    shutdownToolbar -> setVisible (FALSE);
    shutdownToolbar -> setFloatable(!AreToolbarsLocked);
    shutdownToolbar -> setMovable(!AreToolbarsLocked);
    
    errorsToolbar -> setVisible (FALSE);
    errorsToolbar -> setFloatable(!AreToolbarsLocked);
    errorsToolbar -> setMovable(!AreToolbarsLocked);

    IsVisibleToolbarText = actionVisibleToolbarText -> isChecked();
    if (IsVisibleToolbarText)
        profileToolbar -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    else
        profileToolbar -> setToolButtonStyle(Qt::ToolButtonIconOnly);
}

// setWinPaths ================================================================================================================================
// SLOT to set rsync and ssh paths for windows
void luckyBackupWindow::setWinPaths()
{
    winDialog windialog (this);
    windialog.exec();
}

// savePressed ===============================================================================================================================
// function to execute when save pressed
void luckyBackupWindow::savePressed()
{
    InfoData = "";
    saveCurrentProfile();
    InfoData.append(saveData);
    ui.textBrowser_info -> setText(InfoData);	//update the info window
    saveData="";
}

// NewProfile =====================================================================================================================================
// Create an new, blank profile
void luckyBackupWindow::NewProfile()
{
    InfoData = "";
    if (isProfileSaved() == 0)	//if the current profile is not saved, ask the user if he/she wants to
        return;

    textDialog textdialog ("NewProfile", "", this);
    textdialog.exec();
    if (textdialog.getGoOn() == 0)
        return;
    if (textdialog.getGoOn() == 2)
    {
        InfoData = tr("Failed to create new profile","full phrase: 'Failed to create new profile <PROFILENAME>'")+" <b>" +
            profileName + "</b><br><font color=red>"
            + tr("The name you have entered contains only invalid characters") +"</font>";
        ui.textBrowser_info -> setText(InfoData);	//update the info window
        return;
    }
    
    QString newProfileName = textdialog.getUserInput();
    QString newProfile = profileDir + newProfileName + ".profile";

    //check if it exists and ask to replace
    QFile newprofile;
    newprofile.setFileName(newProfile);

    if (newprofile.exists())			//if the newprofile already exists ask to replace
    {
        message = tr("Profile","full phrase: 'Profile <PROFILENAME> already exists'")+" <b>" + newProfileName + "</b> " +
            tr("already exists","full phrase: 'Profile <PROFILENAME> already exists'") + "<br>" +
            tr("Would you like to replace it ?");

        textDialog textdialogQ ("QtQuestion", message, this);
        textdialogQ.exec();

        if (textdialogQ.getGoOn() > 0)		//if user answers yes
        {
            if (!newprofile.remove())	// delete the old profile or display a message if you can't
            {
                InfoData = "<font color=red><b>" + tr("ERROR") + "</font></b><br>" +
                    tr("Failed to replace profile","full phrase: 'Failed to replace profile <PROFILENAME>'")+
                    " <b>" + newProfileName + "</b><br><font color=red>"
                    + profile.errorString() +"</font>";
                ui.textBrowser_info -> setText(InfoData);	//update the info window
                return;
            }
        }
        else
            return;
    }

    setCurrentProfile(newProfile);
    createCurrentProfile();	// try to create it (also calls createProfileCombo)
    loadCurrentProfile();	// load the current profile
    InfoData.append(createData);
    ui.textBrowser_info -> setText(InfoData);	//update the info window
    loadData=""; saveData=""; createData="";
}

// renameCurrentProfile =============================================================================================================================
// rename the current profile
void luckyBackupWindow::renameCurrentProfile()
{
    InfoData="";

    textDialog textdialog ("RenameProfile", profileName, this);
    textdialog.exec();
    if (textdialog.getGoOn() == 0)
        return;

    if (textdialog.getGoOn() == 2)
    {
        InfoData = tr("Failed to rename profile","full phrase: 'Failed to rename profile <PROFILENAME>'")+
            " <b>" + profileName + "</b><br><font color=red>"
            + "The name you have entered contains only invalid characters" +"</font>";
        ui.textBrowser_info -> setText(InfoData);	//update the info window
        return;
    }

    if (textdialog.getGoOn() == 3)		//if the new profile name is the same with the old one do nothing
    {
        InfoData.append(tr("profile","full phrase: 'profile <PROFILENAME> renamed successfully to <NEWPROFILENAME>'")
            + " <b>" + profileName + "</b><br>...<font color=green>"
            + tr("renamed successfully to","full phrase: 'profile <PROFILENAME> renamed successfully to <NEWPROFILENAME>'") +
            "</font> <b>" + profileName +"</b>");
        ui.textBrowser_info -> setText(InfoData);	//update the info window
        return;
    }

    QString newProfileName = textdialog.getUserInput();
    QString newProfile = profileDir + newProfileName + ".profile";

    //check if it exists and ask to replace
    QFile newprofile;
    newprofile.setFileName(newProfile);

    if (newprofile.exists())			//if the newprofile already exists ask to replace
    {
        message = tr("Profile","full phrase: 'Profile <PROFILENAME> already exists'")+" <b>" + newProfileName + "</b> " +
            tr("already exists","full phrase: 'Profile <PROFILENAME> already exists'") + "<br>" +
            tr("Would you like to replace it ?");

        textDialog textdialogQ ("QtQuestion", message, this);
        textdialogQ.exec();

        if (textdialogQ.getGoOn() > 0)		//if user answers yes
        {
            if (!newprofile.remove())	// delete the old profile or display a message if you can't
            {
                InfoData = "<font color=red><b>" + tr("ERROR") + "</font></b><br>" +
                    tr("Failed to replace profile",
                    "full phrase: 'Failed to replace profile <PROFILENAME>'")+" <b>" + newProfileName + "</b><br><font color=red>"
                    + newprofile.errorString() +"</font>";
                ui.textBrowser_info -> setText(InfoData);	//update the info window
                return;
            }
        }
        else
            return;
    }

    if (!profile.rename(newProfile))	//try to rename the current profile
    {
        InfoData = "<font color=red><b>" + tr("ERROR") + "</font></b><br>" +
            tr("Failed to rename profile",
            "full phrase: 'Failed to rename profile <PROFILENAME>'")+" <b>" + profileName + "</b><br><font color=red>"
            + profile.errorString() +"</font>";
        ui.textBrowser_info -> setText(InfoData);	//update the info window
        return;
    }
    if (currentProfile == defaultProfile)
    {
        InfoData.append(tr("default profile","full phrase: 'default profile <PROFILENAME> renamed successfully to <NEWPROFILENAME>'."));
        defaultProfile = newProfile;
        saveSettings();
    }
    else
        InfoData.append(tr("profile", "full phrase: 'profile <PROFILENAME> renamed successfully to <NEWPROFILENAME>'"));
    
    InfoData.append(" <b>" + profileName + "</b><br>...<font color=green>"	+ tr("renamed successfully to",
        "full phrase: '(default) profile <PROFILENAME> renamed successfully to <NEWPROFILENAME>'") + "</font> <b>" + newProfileName +"</b>");
    
    // update all relevant snap .changes as well as log files
    if (arrangeLogSnap(1,"rename",newProfileName))
        InfoData.append("<br><br>" + tr("All relevant files (logs etc) have also been updated"));
    else
        InfoData.append("<br><br>" + tr("Failed to update all relevant files (logs etc)"));
    
    setCurrentProfile(newProfile);
    createProfileCombo();	// update the profile combobox with all existing profiles and set index to currentProfile
    loadCurrentProfile();	// load the current profile
    ui.textBrowser_info -> setText(InfoData);	//update the info window
    loadData=""; saveData=""; createData="";

}
// deleteProfile ======================================================================================================================================
// deletes the current profile
void luckyBackupWindow::deleteCurrentProfile()
{
    InfoData="";
    if (currentProfile == defaultProfile)
        message = tr("Are you sure you want to delete the default profile",
            "full phrase: 'Are you sure you want to delete the default profile: <PROFILENAME> ? (a new blank one, with the same name, will be created)'")+
            ": <b>" + profileName + "</b> ?<br>(" +
            tr("a new blank one, with the same name, will be created",
            "full phrase: 'Are you sure you want to delete the default profile: <PROFILENAME> ? (a new blank one, with the same name, will be created)'") +")";
    else
        message = tr("Are you sure you want to delete profile",
        "full phrase: 'Are you sure you want to delete profile: <PROFILENAME> ?'")+": <b>" + profileName + "</b> ?";

    textDialog textdialogQ ("QtQuestion", message, this);
    textdialogQ.exec();

    if (textdialogQ.getGoOn() > 0)		//if user answers yes
    {
        savedProfile = TRUE;	//assume the profile is saved
        //try to delete the profile
        if (!profile.remove())
        {
            InfoData.append("<font color=red><b>" + tr("ERROR") + "</font></b><br>" +
                tr("Failed to delete profile",
                "full phrase: 'Failed to delete profile <PROFILENAME>'")+": <b>" + profileName + "</b><br><font color=red>"
                + profile.errorString() +"</font><br>");
            ui.textBrowser_info -> setText(InfoData);	//update the info window
            return;
        }

        InfoData.append(tr("Profile","full phrase: 'Profile <PROFILENAME> deleted successfully'") +
                ": <b>" + profileName + "</b><br>...<font color=green>" +
                tr("deleted successfully","full phrase: 'Profile <PROFILENAME> deleted successfully'") + " !!</font><br>");

        // delete all relevant snap .changes as well as log files
        if (arrangeLogSnap(1,"delete",profileName))
            InfoData.append("<br>" + tr("All relevant files (logs etc) have also been deleted") + "<br>");
        else
            InfoData.append("<br>" + tr("Failed to delete all relevant files (logs etc)") + "<br>");
    
        // Load the default profile
        setCurrentProfile(defaultProfile);	// set the defaultProfile as current
        int create = createCurrentProfile();	// if it does not exist create it
        loadCurrentProfile();			// load the current (default) profile
        createProfileCombo();	// update the profile combobox with all existing profiles and set index to currentProfile

        if (create == 0)
            InfoData.append(loadData);
        else
            InfoData.append(createData);
        ui.textBrowser_info -> setText(InfoData);	//update the info window
        loadData=""; saveData=""; createData="";
    }
}


// setDefaultProfile ================================================================================================================================
// sets the current profile as default
void luckyBackupWindow::setDefaultProfile()
{
    InfoData = "";

    defaultProfile = currentProfile;
    saveSettings();
    InfoData.append(tr("Profile","full phrase: 'Profile <PROFILENAME> set as default'") + ": <b>" + profileName + "</b><br>...<font color=green>" + tr("set as default","full phrase: 'Profile <PROFILENAME> set as default'") + " !!</font><br>");
    ui.textBrowser_info -> setText(InfoData);	//update the info window
}

// duplicateProfile ================================================================================================================================
// duplicates the current profile
void luckyBackupWindow::duplicateProfile()
{
    InfoData="";

    textDialog textdialog ("RenameProfile", profileName, this);
    textdialog.exec();
    if (textdialog.getGoOn() == 0)
        return;

    if (textdialog.getGoOn() == 2)
    {
        InfoData = tr("Failed to duplicate profile","full phrase: 'Failed to duplicate profile <PROFILENAME>'")+
            " <b>" + profileName + "</b><br><font color=red>"
            + "The name you have entered contains only invalid characters" +"</font>";
        ui.textBrowser_info -> setText(InfoData);	//update the info window
        return;
    }

    QString duplicateProfileName = textdialog.getUserInput();
    QString duplicateProfile = profileDir + duplicateProfileName + ".profile";

    //check if it exists and ask to replace
    QFile duplicateprofile;
    duplicateprofile.setFileName(duplicateProfile);

    if (duplicateprofile.exists())			//if the duplicateprofile already exists ask to replace
    {
        message = tr("Profile","full phrase: 'Profile <PROFILENAME> already exists'")+" <b>" + duplicateProfileName + "</b> " +
            tr("already exists","full phrase: 'Profile <PROFILENAME> already exists'") + "<br>" +
            tr("Would you like to replace it ?");
        textDialog textdialogQ ("QtQuestion", message, this);
        textdialogQ.exec();

        if (textdialogQ.getGoOn() > 0)		//if user answers yes
        {
            if (!duplicateprofile.remove())	// delete the old profile or display a message if you can't
            {
                InfoData = "<font color=red><b>" + tr("ERROR") + "</font></b><br>" +
                    tr("Failed to replace profile",
                    "full phrase: 'Failed to replace profile <PROFILENAME>'")+" <b>" + duplicateProfileName + "</b><br><font color=red>"
                    + duplicateprofile.errorString() +"</font>";
                ui.textBrowser_info -> setText(InfoData);	//update the info window
                return;
            }
        }
        else
            return;
    }

    if (!saveProfile(duplicateProfile))	//try to save the new (duplicate) profile
    {
        InfoData = "<font color=red><b>" + tr("ERROR") + "</font></b><br>" +
            tr("Failed to duplicate profile","full phrase: 'Failed to duplicate profile <PROFILENAME> as <FILENAME>'")+
            " <b>" + profileName + "</b><br>"
            +tr("as","full phrase: 'Failed to duplicate profile <PROFILENAME> as <FILENAME>'")+
            " <b>" + duplicateProfileName +"</b><br><font color=red>"
            + profile.errorString() +"</font>";
        ui.textBrowser_info -> setText(InfoData);	//update the info window
        setCurrentProfile(currentProfile);		//reset all currentProfile variables
        return;
    }

    InfoData.append(tr("Profile","full phrase: 'Profile <PROFILENAME> duplicated successfully as <FILENAME>'") + ": <b>" +
        profileName + "</b><br>...<font color=green>"
        + tr("duplicated successfully as","full phrase: 'Profile <PROFILENAME> duplicated successfully as <FILENAME>'") +
        "</font> <b>" + duplicateProfileName +"</b>");
    
    // duplicate all relevant snap .changes as well as log files
    if (arrangeLogSnap(1,"duplicate",duplicateProfileName))
        InfoData.append("<br><br>" + tr("All relevant files (logs etc) have also been duplicated"));
    else
        InfoData.append("<br><br>" + tr("Failed to duplicate all relevant files (logs etc)"));
        
    setCurrentProfile(currentProfile);		//reset all currentProfile variables
    createProfileCombo();	// update the profile combobox with all existing profiles and set index to currentProfile
    ui.textBrowser_info -> setText(InfoData);	//update the info window
    loadData=""; saveData=""; createData="";
}

// changeProfileDescription ================================================================================================================================
// Changes the profile description
void luckyBackupWindow::changeProfileDescription()
{
    InfoData="";
    
    textDialog textdialog ("ProfileDescription", profileDescription, this);
    textdialog.exec();
    
    if (textdialog.getGoOn() == 0)
        return;

    profileDescription = textdialog.getUserInput();
    
    QString profileDescriptionDisplay = profileDescription;
    profileDescriptionDisplay.replace("\n","<br>");
    

    InfoData.append(tr("The description of profile","full phrase: 'The description of profile <PROFILENAME> set to: <DESCRIPTION>'") + " <b>" + profileName + "</b> " + tr("set to","full phrase: 'The description of profile <PROFILENAME> set to: <DESCRIPTION>'") + 
    ":<br>" + profileDescriptionDisplay);
    
    ui.textBrowser_info -> setText(InfoData);	//update the info window
    savedProfile = FALSE;			//change profile status to "unsaved"
    ui.actionSave -> setEnabled(TRUE);
}

// duplicateTask ================================================================================================================================
// duplicates the current task (creates a new task - same as selected - and opens modify dialog)
void luckyBackupWindow::duplicateTask()
{
    modifyOK = FALSE;
    modifyConnected = FALSE;
    newTaskThisIs = TRUE;
    
    currentOperation = ui.listWidget_operations -> currentRow();		//current task list row number
    if (currentOperation < 0)						//if nothing is selected do nothing
    {
        InfoData = tr("Please select a task to duplicate first") + " !!";	
        ui.textBrowser_info -> setText(InfoData);
        return;
    }
    int oldCurrentOperation = currentOperation;
    
    TotalOperations = ui.listWidget_operations -> count();		//Get the Operations list size
    if ( (TotalOperations) >= (maxOperations-1) )			//if the maxOperations limit-1 is reached 
    {
        textDialog textdialogW ("QtWarning", 
                    tr("You have reached the maximum limit of supported tasks")+" <br><br>" +
                    tr("You have to remove a task if you wish to add another !!"), this);
        textdialogW.exec();
        return;
    }
    
    currentOperation = TotalOperations;
    
    //Create a new array item identical to the one just created
    operation *tempOp = new operation;
    *tempOp = *Operation[oldCurrentOperation];
    Operation[currentOperation] = tempOp;	

    // Reset the last execution time/errors & clear its snapshots list
    QDateTime newTime;	// empty time variable
    Operation[currentOperation] -> SetLastExecutionTime (newTime);
    Operation[currentOperation] -> SetLastExecutionErrors (-1);
    Operation[currentOperation] -> ClearSnapshotsList();
    
    //Change the task name and remove any RESTORE connections
    Operation[currentOperation] -> SetName ((Operation[currentOperation] -> GetName()) + " DUPLICATE");
    Operation[currentOperation] -> SetConnectRestore("");

    //add a new item in the operations list
    ui.listWidget_operations -> addItem( Operation[currentOperation] -> GetName() );
    ui.listWidget_operations -> setCurrentRow(currentOperation);
    ui.listWidget_operations -> currentItem() -> setCheckState(Qt::Unchecked);
    TotalOperations = ui.listWidget_operations -> count();		//set the TotalOperations to what it is now

    saveOrNot=FALSE;
    modify();	//open the modify dialog for the new task, FALSE == do not save the result
    saveOrNot = TRUE;

    if (modifyOK)
    {
        savedProfile = FALSE;			//change profile status to "unsaved"
        ui.actionSave -> setEnabled(TRUE);
    }
    else
    {
        //remove already created DUPLICATE TASK from operations list
        ui.listWidget_operations -> takeItem(currentOperation);		//take out the selected item from the list
        TotalOperations = ui.listWidget_operations -> count();		//TotalOperations takes the new value (old - 1)
    }
}

// AlsoCreateRestore ================================================================================================================================
//create another operation for RESTORE
void luckyBackupWindow::AlsoCreateRestore()
{
    newTaskThisIs = TRUE;
    int oldCurrentOperation = ui.listWidget_operations -> currentRow();	//current task list row number;

    if (oldCurrentOperation  < 0)						//if nothing is selected do nothing
    {
        InfoData = tr("Please select a task first") + " !!";	
        ui.textBrowser_info -> setText(InfoData);
        return;
    }
    
    TotalOperations = ui.listWidget_operations -> count();			//Get the Operations list size
    if ( (TotalOperations) >= (maxOperations-1) )			//if the maxOperations limit-1 is reached 
    {
        textDialog textdialogW ("QtWarning", 
                    tr("You have reached the maximum limit of supported tasks")+" <br><br>" +
                    tr("You have to remove a task if you wish to add another !!"), this);
        textdialogW.exec();
        return;
    }
    
    currentOperation = TotalOperations;
    
    //Create a new array item identical to the one just created
    operation *tempOp = new operation;
    *tempOp = *Operation[oldCurrentOperation];
    Operation[currentOperation] = tempOp;	
    
    // Reset the last execution time/errors & clear its snapshots list
    QDateTime newTime;	// empty time variable
    Operation[currentOperation] -> SetLastExecutionTime (newTime);
    Operation[currentOperation] -> SetLastExecutionErrors (-1);
    Operation[currentOperation] -> ClearSnapshotsList();

    //Change its name, source, destination, update checkbox, Remote Host radiobuttons
    Operation[currentOperation] -> SetName ("RESTORE - " + (Operation[currentOperation] -> GetName()));
    Operation[currentOperation] -> SetOptionsUpdate(FALSE);
    Operation[currentOperation] -> SetRemoteDestination(Operation[oldCurrentOperation]-> GetRemoteSource());
    Operation[currentOperation] -> SetRemoteSource(Operation[oldCurrentOperation]-> GetRemoteDestination());
    QString sourceDir	= Operation[oldCurrentOperation] -> GetDestination();
    QString destDir		= Operation[oldCurrentOperation] -> GetSource();

    if (Operation[currentOperation] -> GetTypeDirName())
    {
        if (WINrunning && Operation[currentOperation] -> GetRemote())
        {
            sourceDir.append(destDir.right(destDir.size() - destDir.lastIndexOf(XnixSLASH) - 1));
            destDir.chop(destDir.size() - destDir.lastIndexOf(XnixSLASH) - 1);
        }
        else
        {
            sourceDir.append(destDir.right(destDir.size() - destDir.lastIndexOf(SLASH) - 1));
            destDir.chop(destDir.size() - destDir.lastIndexOf(SLASH) - 1);
        }
    }

    Operation[currentOperation] -> SetSource (sourceDir);
    Operation[currentOperation] -> SetDestination (destDir);

    //add a new item in the operations list
    ui.listWidget_operations -> addItem( Operation[currentOperation] -> GetName() );
    ui.listWidget_operations -> setCurrentRow(currentOperation);
    ui.listWidget_operations -> currentItem() -> setCheckState(Qt::Unchecked);
    TotalOperations = ui.listWidget_operations -> count();		//set the TotalOperations to what it is now

    textDialog textdialogW ("QtWarning", 
        tr("You have asked for a RESTORE task to be created","'create restore' message line 1/4")+"<br><br>"+
        tr("Please have a good look at the following task properties dialog","'create restore' message line 2/4")+" <br>"+
        tr("and change anything you wish before proceeding","'create restore' message line 3/4")+" <br><br>"+
        tr("Especially check 'Task name', 'source', 'destination' & 'skip newer destination files' checkbox (advanced)","'create restore' message line 4/4")+"<br>",
                this);
    textdialogW.exec();

    modifyConnected = TRUE;
    saveOrNot = FALSE;
    modify();	//open the modify dialog for the new operation to make sure everything is ok, FALSE == do not save the result
    saveOrNot = TRUE;

    if (modifyOK)		//connect the operation with its RESTORE duplicate
    {
        Operation[currentOperation] -> SetConnectRestore(Operation[oldCurrentOperation] -> GetName());	
        Operation[oldCurrentOperation] -> SetConnectRestore(Operation[currentOperation] -> GetName());
        savedProfile = FALSE;			//change profile status to "unsaved"
        ui.actionSave -> setEnabled(TRUE);
    }
    else
    {
        //remove already created RESTORE operation from operations list
        ui.listWidget_operations -> takeItem(currentOperation);		//take out the selected item from the list
        TotalOperations = ui.listWidget_operations -> count();		//TotalOperations takes the new value (old - 1)
    }
}

// exportProfile ================================================================================================================================
// exports the current profile to another location
void luckyBackupWindow::exportProfile()
{
    InfoData = "";

    // Display a save dialog for a directory to export the profile to
    QString exportProfileName = QFileDialog::getExistingDirectory(this,
            appName + " - " + tr("Select export directory","this is a dialog title for selecting a directory to export a profile to"), SLASH,
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks) + SLASH + profileName;
    
    if ( exportProfileName == "")   //if cancel is pressed at the file dialog, do nothing
        return;

    // put the ".profile" extension if its not there
    if  (!exportProfileName.endsWith(".profile", Qt::CaseInsensitive))
        exportProfileName.append(".profile" + SLASH);
    
    
    if (!exportFullProfile(exportProfileName,"ExportFullProfile"))    //try to save/export the new profile
    {
        InfoData = "<font color=red><b>" + tr("ERROR") + "</font></b><br>" +
            tr("Failed to export profile","full phrase: 'Failed to export profile <PROFILENAME> to <DIRNAME>'")+
            " <b>" + profileName + "</b><br>"
            +tr("to","full phrase: 'Failed to export profile <PROFILENAME> to <DIRNAME>'")+
            " <b>" + exportProfileName +"</b>";
        ui.textBrowser_info -> setText(InfoData);   //update the info window
        setCurrentProfile(currentProfile);      //reset all currentProfile variables
        return;
    }

    InfoData.append(tr("Profile","full phrase: 'Profile <PROFILENAME> exported successfully to <DIRNAME>'") + ": <b>" +
        profileName + "</b><br>...<font color=green>"
        + tr("exported successfully to","full phrase: 'Profile <PROFILENAME> exported successfully to <DIRNAME>'") +
        "</font> <b>" + exportProfileName +"</b>");

    ui.textBrowser_info -> setText(InfoData);   //update the info window
    setCurrentProfile(currentProfile);      //reset all currentProfile variables
    createProfileCombo();   // update the profile combobox (in case profile was exported at ~/.luckyBackup/profiles) and set index to currentProfile
}

// importProfile ================================================================================================================================
// imports a profile (+logs +snaps) to the profile directory
void luckyBackupWindow::importProfile()
{
    InfoData = "";
    
    // This holds the full path of the profile to get imported directory (eg /media/exported/default.profile)
    QString importProfilePath =  QFileDialog::getExistingDirectory(this,
            appName + " - " + tr("Import Profile","this is a dialog title"), SLASH,
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if ( importProfilePath == "")	//if cancel is pressed at the file dialog, do nothing
        return;
    
    // check if the directory selected by the user contains valid profile data
    QDir importprofile;
    importprofile.setPath(importProfilePath);
    QStringList dirsToFilter; dirsToFilter << "profiles" << "logs" <<"snaps";
    QStringList importPprofileContents = importprofile.entryList(dirsToFilter,QDir::AllDirs,QDir::NoSort);
    if (!importPprofileContents.contains("profiles"))                  // check if there exists a "profile" dir
    {
        InfoData = tr("Failed to import profile","full phrase: 'Failed to import profile <PROFILENAME>'")+
                " <b>" + importProfilePath + "</b><br><font color=red>"
                + tr("The directory you have selected does not contain valid profile data") +"</font>";
        ui.textBrowser_info -> setText(InfoData);   //update the info window
        return;
    }
    
    // Check if the profile to import already exists
    QString newProfileName = importProfilePath;     //  newProfileName holds the final name of the profile that is going to get imported (eg "default2")
    newProfileName = newProfileName.right(newProfileName.size() - newProfileName.lastIndexOf(SLASH) - 1);
    if (newProfileName.endsWith(".profile"))
        newProfileName.chop(8);
    QString importProfileName = newProfileName;     //This holds the name of the profile to import (eg "default")

    //newProfile holds the final full path of the .profile file (eg ~/.luckyBackup/profiles/default2.profile)
    QString newProfile = profileDir + newProfileName + ".profile";  
    QFile newprofile;
    newprofile.setFileName(newProfile);

    while (newprofile.exists())			//if the newprofile already exists ask to rename or cancel
    {
        textDialog textdialog ("ImportProfile", newProfileName,this);
        textdialog.exec();
        newProfileName = textdialog.getUserInput();

        if (textdialog.getGoOn() == 0)
            return;
        if (textdialog.getGoOn() == 2)
        {
            InfoData = tr("Failed to import profile","full phrase: 'Failed to import profile <PROFILENAME>'")+
                " <b>" + importProfileName + "</b><br><font color=red>"
                + tr("The name you have entered contains only invalid characters") +"</font>";
            ui.textBrowser_info -> setText(InfoData);	//update the info window
            return;
        }
        newProfile = profileDir + newProfileName + ".profile";
        newprofile.setFileName(newProfile);
    }

    int ExitCodeImportProfile = importFullProfile(importProfilePath,newProfileName);
    //QMessageBox::information(this, "LB","Exit code=" + countStr.setNum(ExitCodeImportProfile));  // TESTING
    // if ExitCodeImportProfile != 1
    if ( (ExitCodeImportProfile == 0) || (ExitCodeImportProfile == 30) || (ExitCodeImportProfile == 20) || (ExitCodeImportProfile == 10) )
    {
        createProfileCombo();
        InfoData.append(tr("Profile",
            "full phrase: 'Profile <PROFILENAME> imported successfully as <NEWPROFILENAME> and added at the profile list'") +
            ": <b>" + importProfileName + "</b><br>...<font color=green>"
            + tr("imported successfully",
            "full phrase: 'Profile <PROFILENAME> imported successfully as <NEWPROFILENAME> and added at the profile list'") +
            "</font> " + tr("as","full phrase: 'Profile <PROFILENAME> imported successfully as <NEWPROFILENAME> and added at the profile list'")
            + " <b>" + newProfileName + "</b><br><font color=green>"
            + tr("and added at the profile list",
            "full phrase: 'Profile <PROFILENAME> imported successfully as <NEWPROFILENAME> and added at the profile list'") + "</font>");
        if (ExitCodeImportProfile == 30)
            InfoData.append("<br><font color=red>" + tr("Errors occured during snapshots and logfiles transfer") +"</font>");
        if (ExitCodeImportProfile == 20) 
            InfoData.append("<br><font color=red>" + tr("Errors occured during snapshots transfer") +"</font>");
        if (ExitCodeImportProfile == 10)
            InfoData.append("<br><font color=red>" + tr("Errors occured during logfiles transfer") +"</font>");
    }
    else    // ExitCodeImportProfile == 1
        InfoData = tr("Failed to import profile","full phrase: 'Failed to import profile <PROFILENAME>'")+" <b>" + importProfileName + 
                    "</b><br><font color=red>" +tr("Errors occured during the profile file transfer") +"</font>";
    ui.textBrowser_info -> setText(InfoData);	//update the info window
}

// setLanguage =====================================================================================================================================
// changes the language of the application
void luckyBackupWindow::setLanguage(QAction *action)
{
    QString currentLocale = action -> data().toString();
    transDir.setPath(relativeTransDir);
    QStringList transContQm = transDir.entryList ( QStringList("luckybackup*.qm"), QDir::Files, QDir::NoSort); // list of .qm files inside transdir
    if ( (transDir.exists()) && (!transContQm.isEmpty()) )
        appTranslator.load(QString("luckybackup_") + currentLocale, relativeTransDir);
    else 
        appTranslator.load(QString("luckybackup_") + currentLocale, systemTransDir);
    defaultLanguage = currentLocale;
    retranslateUi();
}

// hideShowInfoWindow ===============================================================================================================================
// Shows / hides the information window
void luckyBackupWindow::hideShowInfoWindow()
{
    IsVisibleInfoWindow = !(ui.pushButton_InfoCollapse -> isChecked());
    if (IsVisibleInfoWindow)
    {
        ui.pushButton_InfoCollapse -> setToolTip(tr("Hide information window","hide/show information window button tooltip"));
        ui.pushButton_InfoCollapse -> setIcon(QIcon(":/luckyPrefix/collapse.png"));
        if (guiModeNormal)
            ui.textBrowser_info -> setVisible (TRUE);
        else
            ui.nowDoing	-> setVisible (TRUE);
    }
    else
    {
        ui.pushButton_InfoCollapse -> setToolTip(tr("Show information window","hide/show information window button tooltip"));
        ui.pushButton_InfoCollapse -> setIcon(QIcon(":/luckyPrefix/collapseUP.png"));
        if (guiModeNormal)
            ui.textBrowser_info -> setVisible (FALSE);
        else
            ui.nowDoing	-> setVisible (FALSE);
    }
}

// help =============================================================================================================================================
// Shows the "help" information window
// This is a modeless dialog so that users can interact with it together with the main app
void luckyBackupWindow::help()
{
    if (helpURL.toString() == "Does_not_exist")
    {
        InfoData = "<font color=red><b>" + tr("ERROR") + "</font></b><br>" +
            tr("Could not locate the file","full phrase: 'Could not locate the file <FILENAME>'")+": <b>" + relativeManual +"</b><br>	:-(";
        ui.textBrowser_info -> setText(InfoData);	//update the info window
        return;
    }

    if (!helpbrowser)
        helpbrowser = new helpBrowser (helpURL);

    if (helpbrowser->isHidden())
        helpbrowser -> show();
        
    helpbrowser -> scrollToChapter(manualChapter);  // The manualChapter variable will scroll to the relevant chapter
    
    helpbrowser -> raise();
    helpbrowser -> activateWindow();
}

// about ============================================================================================================================================
// Shows the "about" information window
void luckyBackupWindow::about()
{
    aboutDialog aboutdialog(licenseURL);
    aboutdialog.exec();
}

//  add =============================================================================================================================================
// Creates a new operation by calling the modifyDialog
void luckyBackupWindow::add()
{
    modifyOK = FALSE;
    modifyConnected = FALSE;
    newTaskThisIs = TRUE;
    TotalOperations = ui.listWidget_operations -> count();				//Get the Operations list size
    currentOperation = TotalOperations;

    if ( (TotalOperations) >= (maxOperations-1) )					//if the maxOperations limit-1 is reached 
    {
        textDialog textdialogW ("QtWarning", 
                    tr("You have reached the maximum limit of supported tasks")+" <br><br>" +
                    tr("You have to remove a task if you wish to add another !!"), this);
        textdialogW.exec();
        return;
    }

    //open the modify dialog and create "Operation array" item at position currentOperation
    modifyDialog modifydialog(currentOperation); 
    modifydialog.exec();

    if (modifyOK)		//if all went ok - add new operation
    {
        //add a new item in the operations list
        ui.listWidget_operations -> addItem( Operation[currentOperation] -> GetName() );
        ui.listWidget_operations -> setCurrentRow(currentOperation);
        ui.listWidget_operations -> currentItem() -> setCheckState(Qt::Unchecked);
        checkCurrentItem(ui.listWidget_operations -> currentItem());
        TotalOperations = ui.listWidget_operations -> count();		//set the TotalOperations to what it is now
        savedProfile = FALSE;			//change profile status to "unsaved"
        ui.actionSave -> setEnabled(TRUE);
    }
}

//  modify ==========================================================================================================================================
// Modifies an existing operation by calling the modifyDialog
// Will also save the profile according to saveOrNot
void luckyBackupWindow::modify()
{
    modifyOK = FALSE;
    newTaskThisIs = FALSE;
    currentOperation = ui.listWidget_operations -> currentRow();		//current operations list row number
    if (currentOperation < 0)						//if nothing is selected do nothing
    {
        InfoData = tr("Please select a task to modify first") + " !!";	
        ui.textBrowser_info -> setText(InfoData);
        return;
    }

    QString tempConnect = Operation[currentOperation] -> GetConnectRestore();
    if ( (tempConnect != "") && (!modifyConnected) )	//the operations is connected and is a not new RESTORE operation
        modifyConnected = TRUE;
    int connectPosition=0;
    if (tempConnect != "")	//if this op is already connected with another op, (pop up a message & )hold the connection's position
    {
        count=0;
        while (count<TotalOperations)
        {					//get the connected operation position at connectPosition
            if  (Operation[count]->GetName()==tempConnect) connectPosition=count;
            count++;
        }
    }
    
    QString oldTaskName = Operation[currentOperation] -> GetName();  // the original task name wil become handy in case it changes

    //open the modify dialog and modify "Operation array" item at position currentOperation
    modifyDialog modifydialog(currentOperation); 
    modifydialog.exec();

    if (modifyOK)		//if all went ok - modify existing operation
    {
        Qt::CheckState isIncluded = ui.listWidget_operations -> currentItem() -> checkState(); //get the include checkbox state
        QString newTaskName = Operation[currentOperation] -> GetName();  // the new task name
        ui.listWidget_operations -> takeItem(currentOperation);	//take out the selected item from the list
                                    //insert a new one at the same position with the new name
        ui.listWidget_operations -> insertItem(currentOperation, newTaskName);	
        ui.listWidget_operations -> setCurrentRow(currentOperation);		//highlight this row
        ui.listWidget_operations -> currentItem() -> setCheckState(isIncluded); //set the include checkbox as it was
        Operation[currentOperation] -> SetConnectRestore(tempConnect);		//set the connection to what it was
        if (tempConnect != "")
            Operation[connectPosition]->SetConnectRestore(newTaskName);
        checkCurrentItem(ui.listWidget_operations -> currentItem());
        
        // update all relevant snap .changes as well as log files if the task name changes
        if (newTaskName != oldTaskName)
            arrangeLogSnap(0,"rename",oldTaskName);
        
        if (saveOrNot)      // also save the current profile if saveOrNot is TRUE
            saveCurrentProfile();     
    }
}

// remove ===========================================================================================================================================
// Removes highlighted operation from available list
void luckyBackupWindow::remove()
{
    currentOperation = ui.listWidget_operations -> currentRow();			//current Included list row number
    if (currentOperation < 0)							//if nothing is selected do nothing
    {
        InfoData = tr("Please select a task to remove first") + " !!";	
        ui.textBrowser_info -> setText(InfoData);
        return;
    }

    QString tempConnect = Operation[currentOperation] -> GetConnectRestore();
    QString oldTaskName = Operation[currentOperation] -> GetName();  // the original task name wil become handy in case it changes

    textDialog textdialogQ ("QtQuestion", tr("Are you sure you want to remove the following task ??")+" <br>" +
                (ui.listWidget_operations -> currentItem()) -> text(), this);
    textdialogQ.exec();

    if (textdialogQ.getGoOn() > 0)		//if user answers yes
    {
        textDialog textdialogQ2 ("QtQuestion", tr("Would you like to also remove:")+" <br>" + tempConnect+"<br>??", this);
        if (tempConnect != "")	//if this op is already connected with another op ask to remove that too
            textdialogQ2.exec();
        
        //remove current operation
        ui.listWidget_operations -> takeItem(currentOperation);		//take out the selected item from the list
        TotalOperations = ui.listWidget_operations -> count();		//TotalOperations takes the new value (old - 1)
        while (currentOperation < TotalOperations)			//shift array "Operation" one position up starting at current row
        {
            Operation[currentOperation]=Operation[currentOperation+1]; //make the current array item the same with the next one
            currentOperation ++;
        }

        if (tempConnect != "")
        {
            currentOperation=0;
            while (currentOperation < TotalOperations)
            {	if (Operation[currentOperation]->GetName()==tempConnect)
                {
                    if (textdialogQ2.getGoOn() > 0)		//remove current (conected) operation
                    {
                        ui.listWidget_operations -> takeItem(currentOperation);	
                        TotalOperations = ui.listWidget_operations -> count();
                        while (currentOperation < TotalOperations)
                        {
                            Operation[currentOperation]=Operation[currentOperation+1];
                            currentOperation ++;
                        }
                    }
                    else				//just remove the connection
                        Operation[currentOperation]->SetConnectRestore("");
                    break;
                }
                currentOperation ++;
            }
        }
        savedProfile = FALSE;			//change profile status to "unsaved"
        ui.actionSave -> setEnabled(TRUE);
        
        // add the deleted yask name to this list to be used when profile is saved
        deletedTaskNames << oldTaskName;
    }
}

//  manage ==========================================================================================================================================
// Manage existing backups of an existing operation by calling the manageDialog
void luckyBackupWindow::manage()
{
    currentOperation = ui.listWidget_operations -> currentRow();			//current Included list row number
    if (currentOperation < 0)							//if nothing is selected do nothing
    {
        InfoData = tr("Please select a task to manage first") + " !!";	
        ui.textBrowser_info -> setText(InfoData);
        return;
    }
    
    manageDialog managedialog;
    managedialog.exec();
    
    checkCurrentItem(ui.listWidget_operations -> currentItem());	//refresh the selected task
    saveCurrentProfile();	// save the profile if any snapshots have been deleted
//	refreshList(); //refresh the listWidget_operations
}

// moveUp ===========================================================================================================================================
// Moves highlighted operation one position up in the available list
void luckyBackupWindow::moveUp()
{
    currentOperation = ui.listWidget_operations -> currentRow();		//current list row number
    TotalOperations = ui.listWidget_operations -> count();			//total number of list items
    if ( currentOperation < 0 )						//if nothing is selected
        return;

    if ( currentOperation > 0 )
    {
        operation *tempOp;	//temp operation to use for swaping
        tempOp = Operation[currentOperation];		//swap array items
        Operation[currentOperation] = Operation [currentOperation-1];
        Operation[currentOperation-1] = tempOp;

        QListWidgetItem * currentItem = ui.listWidget_operations -> takeItem(currentOperation);	//swap list items
        ui.listWidget_operations -> insertItem(currentOperation - 1, currentItem);
        ui.listWidget_operations -> setCurrentRow(currentOperation - 1);
        
        savedProfile = FALSE;			//change profile status to "unsaved"
        ui.actionSave -> setEnabled(TRUE);
    }
}

// moveDown =========================================================================================================================================
// Moves highlighted operation one position down in the available list
void luckyBackupWindow::moveDown()
{
    currentOperation = ui.listWidget_operations -> currentRow();		//current list row number
    TotalOperations = ui.listWidget_operations -> count();			//total number of list items
    if ( currentOperation < 0 )						//if nothing is selected
        return;

    if (currentOperation < (TotalOperations-1))
    {
        operation *tempOp;						//temp operation to use for swaping
        tempOp = Operation[currentOperation];				//swap array
        Operation[currentOperation] = Operation [currentOperation+1];
        Operation[currentOperation+1] = tempOp;

        QListWidgetItem * currentItem = ui.listWidget_operations -> takeItem(currentOperation);	//swap list items
        ui.listWidget_operations -> insertItem(currentOperation + 1, currentItem);
        ui.listWidget_operations -> setCurrentRow(currentOperation + 1);

        savedProfile = FALSE;			//change profile status to "unsaved"
        ui.actionSave -> setEnabled(TRUE);
    }
}


// start ============================================================================================================================================
//start the execution of operations
void luckyBackupWindow::start()
{
    TotalOperations = ui.listWidget_operations -> count();		//set TotalOperations to what it is now

    if (!checkOperationList())	//check the Operations list for "errors" (eg nothing is included or the list is empty)
        return;

    checkDeclared();		//Check if the declared data are ok by calling checkBackupDirs, checkSyncDirs accordingly

    if (NothingToDo == TRUE)	//if there is nothing to Do anyway then just display a message
    {
        InfoData = "<font color=red><b>" + tr("ERROR") + "</b></font><br>" +
                "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~<br><b>" +
                tr("You have only included tasks that are going to be skipped") + "</b><br>" +
                "..." + tr("nothing to do") +" !!";
        
        ui.textBrowser_info -> setText(InfoData);
        return;
    }

    DryRun = ui.checkBox_DryRun -> isChecked();	//set bool Dryrun according to checkbox

    executeNOW();
}

// schedule==========================================================================================================================================
// Displays a new dialog to make a cron job for included operations
void luckyBackupWindow::schedule()
{
    scheduleDialog scheduledialog; 
    scheduledialog.exec();

    if (crontabUpdated)
        InfoData = tr("current crontab <font color=green>updated successfully") + "</font>";
    ui.textBrowser_info -> setText(InfoData);
    
    crontabUpdated = FALSE;		//this is set true each time the crontab is update
}

// email==========================================================================================================================================
// Displays a new dialog to email report after a profile execution
void luckyBackupWindow::email()
{
    emailDialog emaildialog; 
    emaildialog.exec();

    if (emaildialog.getGoOn() == 0)     // everything went ok
    {
        InfoData = tr("Email preferences have been <font color=green>updated successfully") + "</font>";
        ui.textBrowser_info -> setText(InfoData);
        
        savedProfile = FALSE;           //change profile status to "unsaved"
        ui.actionSave -> setEnabled(TRUE);
    }
    
}

// taskStateChanged =================================================================================================================================
// Sets the profile state to unsaved if a task checkbox is changed
void luckyBackupWindow::taskStateChanged()
{
    //theory (due to connections at luckybackwindow constructor):
    //when an item is just clicked functions called: checkCurrentItem -> taskStateChanged
    //when a checkbox state changes functiond called: taskStateChanged -> checkCurrentItem -> taskStateChanged
    //when a checkbox state changes not by clicking but with SPACEBAR, only taskStateChanged is called !!

    if (!taskChanged)
    {
        if (taskClicked)
            taskClicked = FALSE;
        else
            taskChanged = TRUE;
        return;
    }

    if ( (taskChanged) && (taskClicked) )
    {
        savedProfile = FALSE;			//change profile status to "unsaved"
        ui.actionSave -> setEnabled(TRUE);
    }

    taskClicked = FALSE;
    taskChanged = FALSE;
}

// checkCurrentItem =================================================================================================================================
// Checks the currently selected operation (if checked) for validity
void luckyBackupWindow::checkCurrentItem(QListWidgetItem *thisIsTheCurrentItem)
{
    taskClicked = TRUE;	//this is used at taskStateChanged() to determine if a task state is changed

    InfoData="";
    CheckedData = "";
    
    // use this because when a checkbox state changes and another item is selected, it remains this way. The checked one does not become selected !!
    ui.listWidget_operations -> setCurrentItem(thisIsTheCurrentItem); 
    currentOperation = ui.listWidget_operations -> currentRow();
    
    if (currentOperation < 0)	// to avoid segfault when nothing selected
        return;
    
    //first set  variables source & dest
    QString source, dest;
    source = Operation[currentOperation] -> GetSource();
    dest = Operation[currentOperation] -> GetDestination();
    
    if (Operation[currentOperation] -> GetTypeSync())	//if the operation is of type "sync dirs'
    {
        ui.action_TaskCreateRestore -> setEnabled(FALSE);	//grey out the "create restore task" from menu
        ui.action_TaskManageBackup -> setText(tr("Manage Task","This is a top 'Task' menu action"));
        ui.action_TaskManageBackup -> setToolTip(tr("display information regarding highlighted task",
                            "This is a top 'Task' menu action tooltip"));
    }
    else
    {
        ui.action_TaskCreateRestore -> setEnabled(TRUE);
        ui.action_TaskManageBackup -> setText(tr("Manage &Backup","This is a top 'Task' menu action"));
        ui.action_TaskManageBackup -> setToolTip(tr("display - restore - delete existing backups of highlighted task",
                            "This is a top 'Task' menu action tooltip"));
    }

    if (ui.listWidget_operations -> currentItem() -> checkState() == Qt::Unchecked)	//if the operation is " NOT included" do not check it
    {
        ui.listWidget_operations -> currentItem() -> setIcon(QIcon(":/luckyPrefix/about.png"));
        CheckedData.append(tr("status") + ": <font color=blue><b>"+tr("NOT INCLUDED")+"</font></b><br>");
        CheckedData.append(tr("Checks are disabled. This task will be <b>skipped</b>"));
        ui.textBrowser_info -> setText(CheckedData);
        Operation[currentOperation] -> SetIncluded(FALSE);	// also set its include state to FALSE
        return;
    }

    Operation[currentOperation] -> SetIncluded(TRUE);	// also set its include state to TRUE

    if ( (Operation[currentOperation] -> GetTypeDirContents()) || (Operation[currentOperation] -> GetTypeDirName()) )
        checkBackupDirs(source,dest);			//if the operation is of type "backup dir ...'
    if (Operation[currentOperation] -> GetTypeSync())	//if the operation is of type "sync dirs'
        checkSyncDirs(source,dest);

    if (Operation[currentOperation] -> GetOK())
        ui.listWidget_operations -> currentItem() -> setIcon(QIcon(":/luckyPrefix/okay.png"));
    if (Operation[currentOperation] -> GetWARNING())
        ui.listWidget_operations -> currentItem() -> setIcon(QIcon(":/luckyPrefix/cancel.png"));
    if (Operation[currentOperation] -> GetCRITICAL())
        ui.listWidget_operations -> currentItem() -> setIcon(QIcon(":/luckyPrefix/warning.png"));
    if (Operation[currentOperation] -> GetSourcePerms())
        ui.listWidget_operations -> currentItem() -> setIcon(QIcon(":/luckyPrefix/cancel.png"));
    if (Operation[currentOperation] -> GetDestPerms())
        ui.listWidget_operations -> currentItem() -> setIcon(QIcon(":/luckyPrefix/cancel.png"));
    ui.textBrowser_info -> setText(CheckedData);
}

// refreshList ======================================================================================================================================
// refreshes the task list and the profile combobox when button refresh clicked
void luckyBackupWindow::refreshList()
{
    TotalOperations = ui.listWidget_operations -> count();	//Get the Operations list size
    checkDeclared();					// Check tasks & set icons
    createProfileCombo();	// update the profile combobox with all existing profiles and set index to currentProfile
    InfoData = tr("Task list of profile","full phrase: 'Task list of profile <PROFILENAME> and 'profile' drop-down list refreshed'") +
            " <b>" + profileName + "</b><br>" +
            tr("and 'profile' drop-down list","full phrase: 'Task list of profile <PROFILENAME> and 'profile' drop-down list refreshed'") +
            "<br>...<font color=blue>" + tr("refreshed",
            "full phrase: 'Task list of profile <PROFILENAME> and 'profile' drop-down list refreshed'") + " !!</font>";
    ui.textBrowser_info -> setText(InfoData);
}

//===================================================================================================================================================
//end of luckybackupwindow.cpp
