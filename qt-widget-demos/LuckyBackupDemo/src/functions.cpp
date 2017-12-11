/* ---------------------------------- functions.cpp ---------------------------------------------------------------------------
file containing all functions for luckybackupwindow

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
last modified      : 11 Sep 2013
===============================================================================================================================
===============================================================================================================================
*/
#include <QToolBar>

// InitializeVariables =============================================================================================================================
// variables initialization
void luckyBackupWindow::InitializeVariables()
{    
    TotalOperations = 0;
    currentOperation=-1;
    NOWexecuting = FALSE;
    guiModeNormal = TRUE;
    modifyOK = FALSE;
    savedProfile = TRUE;
    taskClicked = FALSE;
    taskChanged = FALSE;
    GoBack = FALSE;
    InfoData = "";
    InfoInt = 0;
    defaultLanguage = "en";
    mainWindowWidth = 615;
    mainWindowHeight = 500;
    AreToolbarsLocked = TRUE;
    IsVisibleProfileComboToolbar = TRUE;
    IsVisibleProfileToolbar = TRUE;
    IsVisibleProfileStartToolbar = TRUE;
    IsVisibleToolbarText = FALSE;
    IsVisibleInfoWindow = TRUE;
    validation = FALSE;
    deletedTaskNames.clear();
    saveOrNot = TRUE;
    manualChapter = "";
    showOnlyErrors = FALSE;

    // Running desktop environment
    // kde
    char *isKDE = getenv("KDE_FULL_SESSION");
    if (QString(isKDE) != "")
        KDErunning = TRUE;
    else
        KDErunning = FALSE;
    // if LB is run using kdesu the environmental variable does not work
    // so we will check if kdesud is running as a process...
    // It is commented because the super use cannot use eg the tray notification anyway, so he/she will use the qt stuff
    /*if (currentUser == "super user")
    {
        QProcess *kdesuProcess;    kdesuProcess = new QProcess(this);
        QStringList kdesuArgs;     kdesuArgs << "-c" << "ps aux | grep kdesud";
        kdesuProcess -> start ("/bin/sh",kdesuArgs);
        kdesuProcess -> waitForFinished();
        if (kdesuProcess -> exitCode() == 0)        // there is a root process "kdesu_stub running
            KDErunning = TRUE;
    }*/

    // gnome
    char *isGnome = getenv("DESKTOP_SESSION");
    if ((QString(isGnome) == "gnome") || (QString(isGnome) == "GNOME"))
        GNOMErunning = TRUE;
    else
        GNOMErunning = TRUE;

    // translations --------------------------------
    TransDir = "";
    transDir.setPath(relativeTransDir);
    QStringList transContQm = transDir.entryList ( QStringList("luckybackup*.qm"), QDir::Files, QDir::NoSort); // list of .qm files inside transdir
    if ( (transDir.exists()) && (!transContQm.isEmpty()) )
        TransDir = transDir.absolutePath();
    else
    {
        transDir.setPath(systemTransDir);
        TransDir = transDir.absolutePath();
    }

    // manual actual path (QUrl helpURL) --------------------------------
    helpURL.setScheme("file");
    helpURL.setUrl("Does_not_exist");
    QFile manual;
    manual.setFileName(suseManual);
    if (manual.exists())	//if the manual is located in /usr/share/doc/packages/luckybackup (normal installation) - openSuse
        helpURL.setUrl(suseManual);
    manual.setFileName(systemManual);
    if (manual.exists())	//if the manual is located in /usr/share/doc/luckybackup (normal installation)
        helpURL.setUrl(systemManual);
    manual.setFileName(relativeManual);
    if (manual.exists())	//if the manual is located in relative path manual/ (app run from commandline)
        helpURL.setUrl(QApplication::applicationDirPath() + SLASH + relativeManual);

    // licence actual path (QUrllicenseURL) --------------------------------------------------------
    licenseURL.setScheme("file");
    licenseURL.setUrl("Does_not_exist");
    QFile license;
    license.setFileName(debianLicense);
    if (license.exists())	//if the licence file is located in the normal debian directory
        licenseURL.setUrl(debianLicense);
    license.setFileName(suseLicense);
    if (license.exists())	//if the licence file is located in the normal suse directory
        licenseURL.setUrl(suseLicense);
    license.setFileName(systemLicense);
    if (license.exists())	//if the licence file is located in the normal installation directory
        licenseURL.setUrl(systemLicense);
    license.setFileName(relativeLicense);
    if (license.exists())	//if the licence file is located in the same directory (compile directory)
        licenseURL.setUrl(relativeLicense);
    
    // fix OS/2 & win compatibility issues
    if (notXnixRunning)
    {
        licenseURL.setUrl("Does_not_exist");
        helpURL.setUrl("Does_not_exist");
        
        QString OS2manual = relativeManual;
        OS2manual.replace("/",SLASH);
        OS2manual = OS2manual.toLower();

        QString OS2license = relativeLicense;
        OS2license.replace("/",SLASH);
        OS2license= OS2license.toLower();
                                                    
        manual.setFileName(OS2manual);
        license.setFileName(OS2license);

        if (manual.exists())
        {
            helpURL.setUrl(OS2manual);
        }
        if (license.exists())
        {
            licenseURL.setUrl(OS2license);
        }

        myHome.replace("/",SLASH);
        luckyBackupDir.replace("/",SLASH);
        settingsFile.replace("/",SLASH);
        profileDir.replace("/",SLASH);
        defaultProfile.replace("/",SLASH);
        defaultProfile.replace("/",SLASH);
        standardDefaultProfile.replace("/",SLASH);
        logDir.replace("/",SLASH);
        logfilename.replace("/",SLASH);
        snapDefaultDir.replace("/",SLASH);
        snapChangesDir.replace("/",SLASH);
        snapEmptyDir.replace("/",SLASH);
        snapchangesfilename.replace("/",SLASH);
        scheduleDir.replace("/",SLASH);
        schedulefilename.replace("/",SLASH);
        cronfilename.replace("/",SLASH);
        relativeTransDir.replace("/",SLASH);
        systemTransDir.replace("/",SLASH);
    }
}


// retranslateUi ===================================================================================================================================
// retranslate the ui every time the user chooses a different language from the menu
void luckyBackupWindow::retranslateUi()
{
    ui.menuFile->setTitle(tr("&Profile","This is a top menu item"));
    ui.actionRefresh->setText(tr("&Refresh","This is a top 'Profile' menu action"));
    ui.actionDefault->setText(tr("De&fault","This is a top 'Profile' menu action"));
    ui.actionDefault->setToolTip(tr("Set as Default","This is a top 'Profile' menu action tooltip"));
    ui.actionDescription->setText(tr("&View/Edit Description","This is a top 'Profile' menu action"));
    ui.actionDescription->setToolTip(tr("View/Edit the profile description","This is a top 'Profile' menu action tooltip"));
    ui.actionRename->setText(tr("R&ename","This is a top 'Profile' menu action"));
    ui.actionDelete->setText(tr("&Delete","This is a top 'Profile' menu action"));
    ui.actionNew->setText(tr("&New","This is a top 'Profile' menu action"));
    ui.actionSave->setText(tr("&Save","This is a top 'Profile' menu action"));
    ui.actionExport->setText(tr("E&xport","This is a top 'Profile' menu action"));
    ui.actionImport->setText(tr("&Import","This is a top 'Profile' menu action"));
    ui.actionSchedule->setText(tr("S&chedule","This is a top 'Profile' menu action"));
    ui.actionEmail->setText(tr("E&mail","This is a top 'Profile' menu action"));
    ui.actionEmail->setToolTip(tr("Email report after profile execution","This is a top 'Profile' menu action tooltip"));
    ui.actionQuit->setText(tr("&Quit","This is a top 'Profile' menu action"));
    ui.actionDuplicate_Profile->setText(tr("D&uplicate","This is a top 'Profile' menu action"));
    
    ui.menu_Task->setTitle(tr("&Task","This is a top menu action"));
    ui.action_TaskAdd->setText(tr("&Add","This is a top 'Task' menu action"));
    ui.action_TaskRemove->setText(tr("&Remove","This is a top 'Task' menu action"));
    ui.action_TaskModify->setText(tr("&Modify","This is a top 'Task' menu action"));
    ui.action_TaskDuplicate->setText(tr("Create D&uplicate task","This is a top 'Task' menu action"));
    ui.action_TaskCreateRestore->setText(tr("Create R&estore task","This is a top 'Task' menu action"));
    ui.action_TaskManageBackup->setText(tr("Manage &Backup","This is a top 'Task' menu action"));
    ui.action_TaskManageBackup->setToolTip(tr("display - restore - delete existing backups of highlighted task",
                                                "This is a top 'Task' menu action tooltip"));

    settingsMenu->setTitle(tr("&Settings","This is a top menu item"));
    visibleProfileToolbar->setText(tr("Actions","This is a top menu action"));
    visibleProfileComboToolbar->setText(tr("Current Profile","This is a top menu action"));
    actionLockToolbars->setText(tr("Lock","This is a top menu action. Refers to toolbars"));
    actionVisibleToolbarText->setText(tr("Show text under icons","This is a top menu action"));
    languageMenu->setTitle(tr("&Language","This is a top menu item"));
    toolbarsMenu->setTitle(tr("&Toolbars","This is a top menu item"));
    
    if (WINrunning)
    {
        actionSetWinPaths->setText(tr("Set paths","This is a top menu action"));
        actionSetWinPaths->setToolTip(tr("Set paths for rsync and ssh commands","This is a top menu action tooltip"));
    }

    helpMenu->setTitle(tr("&Help","This is a top menu item"));
    actionHelp->setText(appName + " " + tr("&Handbook","full phrase: 'luckyBackup Handbook'"));
    actionAbout->setText(tr("&About","full phrase: 'about luckyBackup'") + " " + appName);

    ui.comboBox_profile->setToolTip(tr("current profile"));

    ui.label_TaskList->setText(tr("Task list","task list label"));
    ui.label_include->setText(tr("include","label of 'include' checkboxes"));
    ui.frame_operations->setToolTip(tr("List of all the available tasks","task list tooltip - line1")+"\n"+
                                      tr("Use the 'include checkboxes' to include or not a selected task","task list tooltip - line2"));
    ui.pushButton_up->setToolTip(tr("Move the highlighted task up, by one position","button tooltip"));
    ui.pushButton_down->setToolTip(tr("Move the highlighted task down, by one position","button tooltip"));
    ui.pushButton_nextError->setToolTip(tr("jump to next error","button tooltip"));
    ui.pushButton_previousError->setToolTip(tr("jump to previous error","button tooltip"));
    ui.checkBox_onlyShowErrors->setText(tr("quiet mode"));
    ui.checkBox_onlyShowErrors->setToolTip(tr("Only show errors and important messages during window update"));

    ui.groupBox_task->setTitle(tr("Task","task groupbox (add, remove, modify buttons) label"));
    ui.pushButton_add->setText(tr("add","add task button label"));
    ui.pushButton_add->setToolTip(tr("add task","add task button tooltip"));
    ui.pushButton_remove->setText(tr("remove","remove task button label"));
    ui.pushButton_remove->setToolTip(tr("remove highlighted task","remove task button tooltip"));
    ui.pushButton_edit->setText(tr("modify","modify task button label"));
    ui.pushButton_edit->setToolTip(tr("modify highlighted task","modify task button tooltip"));

    //ui.groupBox_operations -> setTitle(tr("Run","run groupbox label"));
    ui.pushButton_start->setText(tr("Run","start button label"));
    ui.pushButton_start->setToolTip(tr("Begin the execution of all included tasks","start button tooltip"));
    ui.AbortButton->setText(tr("Abort","Abort button label"));
    ui.AbortButton->setToolTip(tr("Stop the execution of running tasks NOW","Abort button tooltip"));
    ui.DoneButton->setText (tr("Done"));
    ui.DoneButton->setToolTip(tr("Execution of tasks finished","Done button tooltip"));
    ui.checkBox_DryRun->setText(tr("Dry","simulation checkbox label. Translate this as 'simulation'"));
    ui.checkBox_DryRun->setToolTip(tr("This will perform a <b>simulation run</b> that doesn't make any changes (and produces mostly the same output as a real run)","simulation checkbox tooltip - line1. Please leave tags <b> and </b> intact and surrounding 'simulation run'")+".<br>"+tr("NOTE","simulation checkbox tooltip - line2")+": "+tr("Progressbar update will not be realistic","simulation checkbox tooltip - line2"));

    ui.pushButton_shutdown->setText(tr("shutdown","shutdown button label"));
    ui.pushButton_shutdown->setToolTip(tr("Press down to shutdown the system when done","shutdown button tooltip"));
    
    ui.label_InformationWindow->setText(tr("Information window","information window title"));
    ui.pushButton_exit->setToolTip(tr("Exit","exit button tooltip. full phrase is: 'exit luckybackup'")+" "+appName);
    ui.pushButton_exit->setText(tr("EXIT","EXIT button label"));

    if (IsVisibleInfoWindow)
    {
        ui.pushButton_InfoCollapse->setToolTip(tr("Hide information window","show/hide information window button tooltip"));
    }
    else
    {
        ui.pushButton_InfoCollapse->setToolTip(tr("Show information window","show/hide information window button tooltip"));
    }

    ui.pushButton_minimizeToTray->setText(tr("minimize to tray"));
    ui.pushButton_minimizeToTray->setToolTip(tr("minimizes the window to the tray area"));
}

// createProfileCombo =============================================================================================================================
// fill the profile combo box with existing profiles.
// Also sets the currentProfileIndex to the index of the current profile
// Executes when the app starts & when the list of profiles in ~/.luckybackup/profiles changes
void luckyBackupWindow::createProfileCombo()
{
    GoBack = TRUE;	// the next line will execute function setCurrentProfile. set TRUE to avoid that
    ui.comboBox_profile -> clear();
    int currentProfileIndex = -1;
    QDir profiledir(profileDir);
    profiledir.setFilter(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot);
    profiledir.setSorting(QDir::Name | QDir::LocaleAware);
    QStringList profileNames = profiledir.entryList(QStringList("*.profile"));

    QString profilename="";
    for (count = 0; count < profileNames.size(); ++count)
    {
        profilename = profileNames[count];
        if (currentProfile == profileDir + profilename)	// set the currentProfileIndex to the index of the current profile
            currentProfileIndex = count;

        profilename.chop(8);

        GoBack = TRUE;	// the next line will execute function setCurrentProfile. set TRUE to avoid that
        ui.comboBox_profile -> addItem (profilename);
    }
    if (currentProfileIndex == -1)	// if no default profile exists
        currentProfileIndex = 0;

    GoBack = TRUE;	// the next line will execute function setCurrentProfile. set TRUE to avoid that
    ui.comboBox_profile -> setCurrentIndex(currentProfileIndex);
    GoBack = FALSE;

}

// createActions =============================================================================================================================
// create all main action
void luckyBackupWindow::createActions()
{
    actionHelp = new QAction(QIcon(":/luckyPrefix/book.png"), "Handbook", this);
    actionHelp -> setShortcut(tr("F1"));
    actionAbout = new QAction(QIcon(":/luckyPrefix/about.png"), "About", this);
    
    actionLockToolbars = new QAction("Lock Toolbars",this);
    actionLockToolbars -> setCheckable(TRUE);
    actionLockToolbars -> setChecked(AreToolbarsLocked);
    actionVisibleToolbarText = new QAction("Labels under icons",this);
    actionVisibleToolbarText -> setCheckable(TRUE);
    actionVisibleToolbarText -> setChecked(IsVisibleToolbarText);
    
    if (WINrunning)
    {
        actionSetWinPaths = new QAction("Set paths",this);
        connect( actionSetWinPaths, SIGNAL(triggered()), this, SLOT(setWinPaths()));      //menu action set paths
    }
    
    connect( actionHelp, SIGNAL(triggered()), this, SLOT(help()));		//menu action help
    connect( actionAbout, SIGNAL(triggered()), this, SLOT(about()));	//menu action about
    connect( actionLockToolbars, SIGNAL(triggered()), this, SLOT(setToolbarAttrs()));	//menu action lock toolbars
    connect( actionVisibleToolbarText, SIGNAL(triggered()), this, SLOT(setToolbarAttrs()));	//menu action visible toolbar text
}

// createMenus =============================================================================================================================
// create the main window menus
void luckyBackupWindow::createMenus()
{
    // settings menu ----------------------------------------------------------------------------------
    settingsMenu = menuBar() -> addMenu("Settings");

    // help menu ----------------------------------------------------------------------------------
    helpMenu = menuBar() -> addMenu("Help");
    helpMenu -> addAction(actionHelp);
    helpMenu -> addSeparator();
    helpMenu -> addAction(actionAbout);

    // toolbars actions -------------------------------------------------------------------------------
    toolbarsGroup = new QActionGroup(this);
    toolbarsMenu = settingsMenu -> addMenu("");
    
    visibleProfileComboToolbar = profileComboToolbar->toggleViewAction();
    toolbarsMenu -> addAction(visibleProfileComboToolbar);
    visibleProfileToolbar = profileToolbar->toggleViewAction();
    toolbarsMenu -> addAction(visibleProfileToolbar);
    toolbarsMenu -> addSeparator();
    toolbarsMenu -> addAction(actionLockToolbars);
    toolbarsMenu -> addAction(actionVisibleToolbarText);
    settingsMenu -> addSeparator();

    // language sub-menu -------------------------------------------------------------------------------
    languageGroup = new QActionGroup(this);
    languageMenu = settingsMenu -> addMenu("");
    connect(languageGroup, SIGNAL(triggered(QAction *)), this, SLOT( setLanguage( QAction *) )  );

    QStringList fileNames = transDir.entryList(QStringList("luckybackup_*.qm"));
    for (count = 0; count < fileNames.size(); ++count)
    {
        QString currentLocale = fileNames[count];
        currentLocale.remove(0, currentLocale.indexOf('_') + 1);
        currentLocale.chop(3);

        QTranslator translator;
        translator.load(fileNames[count], TransDir);
        QString language = translator.translate("luckyBackupWindow","English");
    
        action = new QAction(tr("&%1 %2").arg(count + 1).arg(language), this);
        action -> setCheckable(true);
        action -> setData(currentLocale);
    
        languageMenu -> addAction(action);
        languageGroup -> addAction(action);

        if (currentLocale == defaultLanguage)
        {
            action->setChecked(true);
            setLanguage(action);
        }
    }
    
    // Win-OS2 paths sub-menu -------------------------------------------------------------------------------
    if (WINrunning)
        settingsMenu -> addAction(actionSetWinPaths);
}
// createToolbar =============================================================================================================================
// create the tool bars
void luckyBackupWindow::createToolbar()
{
    profileComboToolbar = new QToolBar("current profile", this);
    profileToolbar = new QToolBar("actions", this);
    profileStartToolbar = new QToolBar("start", this);
    shutdownToolbar = new QToolBar("shutdown", this);
    errorsToolbar = new QToolBar("errors", this);
    
    this->addToolBar(Qt::TopToolBarArea, profileComboToolbar);
    this->addToolBar(Qt::TopToolBarArea, profileToolbar);
    this->addToolBar(Qt::TopToolBarArea, shutdownToolbar);
    this->addToolBar(Qt::TopToolBarArea, errorsToolbar);
    this->addToolBar(Qt::TopToolBarArea, profileStartToolbar);

    QSize ToolbarIconSize(22,22);
    profileToolbar->setIconSize(ToolbarIconSize);

    //Profile-------------------------------------------------------------------
    profileComboToolbar->addWidget(ui.comboBox_profile);	//profile drop-down list
    
    //Start & simulation buttons-------------------------------------------------------------------
    profileStartToolbar->addWidget(ui.groupBox_operations);//profile start toolbar
    
    //shutdown system button-------------------------------------------------------------------
    shutdownToolbar->addWidget(ui.pushButton_shutdown);//shutdown system toolbar
    
    // prev/next error buttons-------------------------------------------------------------------
    errorsToolbar->addWidget(ui.pushButton_previousError);    // errors toolbar
    errorsToolbar->addWidget(ui.pushButton_nextError);
    errorsToolbar->addWidget(ui.checkBox_onlyShowErrors);
    
    //Profile Actions-------------------------------------------------------------------
    profileToolbar -> addSeparator();			//---seperator---
    profileToolbar -> addAction(ui.actionSave);		//save
//	profileToolbar -> addAction(ui.actionDefault);		//default
//	profileToolbar -> addAction(ui.actionRename);		//rename
    profileToolbar -> addAction(ui.actionNew);		//new
    profileToolbar -> addAction(ui.actionDelete);		//delete
//	profileToolbar -> addSeparator();
//	profileToolbar -> addAction(ui.actionExport);
//	profileToolbar -> addAction(ui.actionImport);
    profileToolbar -> addSeparator();			//---seperator---
    profileToolbar -> addAction(ui.actionSchedule);		//schedule
    profileToolbar -> addAction(ui.actionEmail);     //email report
    profileToolbar -> addAction(ui.actionRefresh);		//refresh
    profileToolbar -> addSeparator();			//---seperator---
    profileToolbar -> addAction(ui.actionQuit);		//quit
    profileToolbar -> addSeparator();			//---seperator---

    profileComboToolbar -> setVisible (IsVisibleProfileComboToolbar);
    profileToolbar -> setVisible (IsVisibleProfileToolbar);
    
    setToolbarAttrs();
}



// checkOperationsList===============================================================================================================================
// Checks if the Operations list is ok to proceed
// calls global function checkTaskList()
bool luckyBackupWindow::checkOperationList()
{
    bool showBox = checkTaskList();

    if (ask)
    {
        message.prepend("<font color=red><b>" + tr("ERROR") + "</b></font><br>");
        if (showBox)
        {
            textDialog textdialogC ("QtCritical", message, this);
            textdialogC.exec();
        }
        
        ui.textBrowser_info -> setText(message);
        return FALSE;
    }
    return TRUE;
}

//checkDeclared ===================================================================================================================================
//Check if the declared data are ok by calling checkBackupDirs, checkSyncDirs accordingly
//This is called from the gui
void luckyBackupWindow::checkDeclared()
{
    int currentSelection = ui.listWidget_operations -> currentRow();	//keep the current selection
    checkDeclaredDirs(TRUE);

    currentOperation = 0;
    CheckedData = "";
    CheckedDataCLI = "";
    while (currentOperation < TotalOperations)
    {
        ui.listWidget_operations -> setCurrentRow(currentOperation);
        if (Operation[currentOperation] -> GetIncluded())	//if the operations is "included"
        {
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
        }
        else
            ui.listWidget_operations -> currentItem() -> setIcon(QIcon(":/luckyPrefix/about.png"));	
        currentOperation++;
    }
    
    if (currentSelection > -1)		// re-select the current selection (don't leave the last task selected)
    {
        currentOperation = currentSelection;
        ui.listWidget_operations -> setCurrentRow(currentOperation);
    }
}

// setCurrentprofile ================================================================================================================================
// function to set the currentProfile
void luckyBackupWindow::setCurrentProfile(QString currentProfileSet)
{
    if (notXnixRunning) // if OS2 or win is running and by mistake the path includes "/" instead of "\" 
        currentProfileSet.replace("/",SLASH);
    
    //current profile full absolut path
    currentProfile = currentProfileSet;

    //current profile QFile
    profile.setFileName(currentProfile);

    //current profile's name (QString)
    profileName = currentProfile;
    profileName = profileName.right(profileName.size() - profileName.lastIndexOf(SLASH) - 1);
    profileName.chop(8);
}

// loadCurrentprofile ================================================================================================================================
// function to load the current profile
// calls global function loadProfile
bool luckyBackupWindow::loadCurrentProfile()
{
    loadData = "";
    // Initialize arrays & window to zero values first
    ui.listWidget_operations -> clear();	//clear the operations list
    TotalOperations = 0;	//Set the operations list size to 0
    //taskAvailable -> ;					//clear operations array ?????????

    if (currentProfile == defaultProfile)
        loadData.append("<font color=blue><b>" + tr("loading default profile ...","information window message") + "</font></b><br>");
    else
        loadData.append("<font color=blue><b>" + tr("loading profile ...","information window message") + "</font></b><br>");

    int loadOK = loadProfile(currentProfile);	// try to load the currentProfile
    if (loadOK == 1)		// if it cannot open
    {
        loadData.append("<font color=red><b>" + tr("loading failed","information window message") + "</font></b><br>" +
                tr("Unable to open profile","information window message. full phrase is 'Unable to open profile <PROFIENAME>'")+" <b>" + profileName + "</b><br><font color=red>"
                + profile.errorString()) +"</font>";
        return FALSE;					//do nothing more
    }

    if (loadOK == 2)			// if it is not a valid profile
    {
        loadData.append("<font color=red><b>" + tr("loading failed","information window message") + "</font></b><br>" +
        tr("profile ","information window message. Full phrase is: 'profile <PROFILENAME> is not valid for luckybackup version:X.Y'. BEWARE of the whitespace in the end")
        + "<b>" + profileName + "</b> " + tr("is not valid for","information window message. Full phrase is: 'profile <PROFILENAME> is not valid for luckybackup version:X.Y") + " " + appName +", "+ tr("version:","information window message. Full phrase is: 'profile <PROFILENAME> is not valid for luckybackup version:X.Y") + countStr.setNum(appVersion));
        return FALSE;	//do nothing more
    }

    // if all went ok (profile loaded) - loadOK == 0
    savedProfile = TRUE;
    ui.actionSave -> setEnabled(FALSE);
    currentOperation = 0;
    while (currentOperation < TotalOperations)	// fill in the task list
    {
        ui.listWidget_operations -> addItem( Operation[currentOperation] -> GetName() );
        ui.listWidget_operations -> setCurrentRow(currentOperation);
        if (Operation[currentOperation] -> GetIncluded())
            ui.listWidget_operations -> currentItem() -> setCheckState (Qt::Checked);
        else
            ui.listWidget_operations -> currentItem() -> setCheckState (Qt::Unchecked);
        currentOperation++;
    }

    TotalOperations = ui.listWidget_operations -> count();	//Get the Operations list size
    checkDeclared();					// Check tasks & set icons
    loadData.append(tr("profile","info window message. full phrase: 'profile <PROFILENAME> loaded successfully'") + " <b>" + profileName + "</b> <font color=green>" + tr("loaded successfully","info window message. full phrase: 'profile <PROFILENAME> loaded successfully'") + " !!</font>");
    ui.listWidget_operations -> setSpacing(1);
    
    // Check to see if this profile is scheduled and inform user  ~~~~~~~~
    QString CronTab = "";
    QString profileCheckCron = profileName;
    profileCheckCron = profileCheckCron.replace(" ","\\ ");
    QFile cronFile (cronfilename);
    if (cronFile.open(QIODevice::ReadOnly | QIODevice::Text))		//open the cronFile
    {
        loadData.append("<br>"+tr("scheduled","this refers to a profile") + ": <b>");
        QTextStream in(&cronFile);
        while (!in.atEnd())
            CronTab.append(in.readLine());
        if (CronTab.contains(profileCheckCron, Qt::CaseInsensitive))
            loadData.append(tr("YES") + "</b>");
        else
            loadData.append(tr("NO") + "</b>");
    }
    
    //append the profile description if it exists
    if (profileDescription != "")
    {
        QString profileDescriptionDisplay = profileDescription;
        profileDescriptionDisplay.replace("\n","<br>");
        loadData.append("<br><br><b>" + tr("Description") + ":</b><br>" + profileDescriptionDisplay);
    }
    
    // Append a general directions message if the profile is empty
    if ( TotalOperations == 0 )
        loadData.append("<br><font color=magenta>" + tr("The task list is empty")+ "<br><b>" + tr("Use the \"add\" button on the right to get started","Please keep the add word inside quotes") + "</b></font><br>");
    
    return TRUE;	//profile loaded successfuly
}

// saveCurrentprofile ===============================================================================================================================
// function to save the current profile
// calls global function saveProfile()
bool luckyBackupWindow::saveCurrentProfile()
{
    saveData = "";
    TotalOperations = ui.listWidget_operations -> count();	//Get the Operations list size

    if (currentProfile == defaultProfile)
        saveData.append("<font color=blue><b>" + tr("saving default profile ...","Information window message") + "</font></b><br>");
    else
        saveData.append("<font color=blue><b>" + tr("saving profile ...","Information window message") + "</font></b><br>");

    if (!saveProfile(currentProfile))
    {
        saveData.append("<font color=red><b>" + tr("WARNING") + "</b></font><br>");
        if (currentProfile == defaultProfile)
            saveData.append(tr("default profile","Information window message. Full phrase: 'default profile <PROFILENAME> could not be saved'."));
        else
            saveData.append(tr("profile","Information window message. Full phrase: 'profile <PROFILENAME> could not be saved'"));
            
        saveData.append(" <b>" + profileName + "</b> "+ tr("could not be saved","Information window message. Full phrase: '(default) profile <PROFILENAME> could not be saved'") + "<br>" +	"<font color=red>"+ profile.errorString() + "</font>");
        savedProfile = FALSE;
        ui.actionSave -> setEnabled(TRUE);
        return FALSE;
    }

    saveData.append(tr("profile","Information window message. Full phrase: 'profile <PROFILENAME> saved successfully'") + " <b>" + profileName + "</b> <font color=green>" + tr("saved successfully","Information window message. Full phrase: 'profile <PROFILENAME> saved successfully'") + " !!</font>");

    // Check to see if this profile is scheduled and inform user  ~~~~~~~~
    QString CronTab = "";
    QFile cronFile (cronfilename);
    if (cronFile.open(QIODevice::ReadOnly | QIODevice::Text))		//open the cronFile
    {
        saveData.append("<br>"+tr("scheduled","this refers to a profile") + ": <b>");
        QTextStream in(&cronFile);
        while (!in.atEnd())
            CronTab.append(in.readLine());
        if (CronTab.contains(profileName, Qt::CaseInsensitive))
            saveData.append(tr("YES") + "</b>");
        else
            saveData.append(tr("NO") + "</b>");
    }
    
    //append the profile description if it exists
    if (profileDescription != "")
    {
        QString profileDescriptionDisplay = profileDescription;
        profileDescriptionDisplay.replace("\n","<br>");
        loadData.append("<br><br><b>" + tr("Description") + ":</b><br>" + profileDescriptionDisplay );
    }
    
    // if some tasks were deleted also delete the relevant .changes and log files
    for (int count = 0; count < deletedTaskNames.size(); ++count)
        arrangeLogSnap(0,"delete",deletedTaskNames.at(count));
    deletedTaskNames.clear();
    
    savedProfile = TRUE;			//change profile status to "saved"
    ui.actionSave -> setEnabled(FALSE);
    
    return TRUE;
}

// createCurrentprofile ===============================================================================================================================
// function to create the current profile with an empty task list
// calls global function saveProfile()
int luckyBackupWindow::createCurrentProfile()
{
    createData = "";
    if (!profile.exists())			//if the currentProfile does not exist, try to create it
    {
        TotalOperations = 0;	//Set the Operations list size to 0
        
        //Set email default options
        emailNever = 1;
        emailSubject = emailDefaultSubject;
        emailBody = emailDefaultBody;

        if (currentProfile == defaultProfile)
            createData.append("<font color=blue><b>" + tr("creating default profile ...","Information window message") + "</font></b><br>");
        else
            createData.append("<font color=blue><b>" + tr("creating profile ...","Information window message") + "</font></b><br>");

        if (!saveProfile(currentProfile))	//if the profile cannot be created
        {
            createData.append("<font color=red><b>" + tr("WARNING") + "</b></font><br>");
            if (currentProfile == defaultProfile)
                createData.append(tr("default profile","Information window message. Full phrase: 'default profile <PROFILENAME> could not be created'."));
            else
                createData.append(tr("profile","Information window message. Full phrase: 'profile <PROFILENAME> could not be created'."));
            createData.append(" <b>" + profileName + "</b> "+ tr("could not be created","Information window message. Full phrase: '(default) profile <PROFILENAME> could not be created'") + "<br>" + "<font color=red>"+ profile.errorString() + "</font>");
            return 2;	//profile could not be created
        }

        createData.append(tr("profile","Information window message. Full phrase: 'profile <PROFILENAME> created successfully'") + " <b>" + profileName + "</b> <font color=green>" + tr("created successfully","Information window message. Full phrase: 'profile <PROFILENAME> created successfully'") + " !!</font>");
        createData.append("<br><font color=magenta>" + tr("Use the \"add\" button on the right to get started","Please keep the add word inside quotes") + "</font><br>");
        createProfileCombo();	// update the profile combobox with all existing profiles
        savedProfile = TRUE;			//change profile status to "saved"
        ui.actionSave -> setEnabled(FALSE);
        return 1;		// Profile created successfully
    }
    return 0;	// profile already exists, just proceed
}

// isProfileSaved ====================================================================================================================================
//function to check if the current profile is saved and proceed or not
int luckyBackupWindow::isProfileSaved()
{
    if (!savedProfile)	//if the current profile is not saved, ask the user if he/she wants to, before proceeding
    {
        textDialog textdialogQ ("QtQuestion",
                    tr("Profile","Question dialog message. Full phrase: 'profile <PROFILENAME> is modified'")+" <b>" + profileName + "</b> " +
                    tr("is modified","Question dialog message. Full phrase: 'profile <PROFILENAME> is modified'")+ ".<br><br>" +
                    tr("Would you like to save it before proceeding ?"), this);
        textdialogQ.exec();
        
        if (textdialogQ.getGoOn() > 0)		//if user answers yes
        {
            if (!saveCurrentProfile())	// if it cannot be saved for any reason pop up a yes/no message box to go on or not
            {
                textDialog textdialogQ2 ("QtQuestion",
                    tr("Profile","Question dialog message. Full phrase: 'profile <PROFILENAME> could not be saved'")+" <b>" + profileName + "</b> " +tr("could not be saved","Question dialog message. Full phrase: 'profile <PROFILENAME> could not be saved'")
                        +"<br><font color=red>"+ profile.errorString()
                        + "</font><br><br>" + tr("Would you like to proceed anyway?"), this);
                textdialogQ2.exec();
                if (textdialogQ2.getGoOn() == 0)		//if user answers no
                {
                    int previousIndex = ui.comboBox_profile -> findText (profileName, Qt::MatchExactly);
                    GoBack = TRUE;	// the next line will execute  function profileComboChanged again. set TRUE to avoid that
                    ui.comboBox_profile -> setCurrentIndex(previousIndex);
                    return 0;	//profile could not be saved, user says DO NOT proceed
                }
                else
                    return 4;	//profile could not be saved, user wants to proceed
            }
            else
                return 2;		//profile save successfully, proceed
        }
        else
            return 3;	//user does not want to save profile, proceed
    }
    return 1;	// profile is already saved, just proceed
}

//saveSettings ===================================================================================================================================
//Saves various luckybackup settings such as the default profile (text mode after version 0.4.7)
bool luckyBackupWindow::saveSettings()
{
    QFile settingsfile(settingsFile);
    if (!settingsfile.open(QIODevice::WriteOnly))	// if the settings file cannot be saved (or fails to create)
    {
        settingsfile.close();
        return FALSE;
    }

    showOnlyErrors = ui.checkBox_onlyShowErrors -> isChecked();
    //write arrays to settings file
    QTextStream out(&settingsfile);
    
    out << "***************************** WARNING *****************************\n";
    out << "Do NOT edit this file directly, unless you REALLY know what you are doing !!\n\n\n";
    
    out << "[app_global]\n";
    out << "appName="                       << appName << "\n";                     //output the application name 
    out << "appVersion="                    << appVersion << "\n";                  //output the application version 
    out << "File_Type="                     << "luckybackup_settings_file" << "\n"; //output the application file type (?)
    
    out << "\n[settings_global]\n";
    out << "Main_window_width="             << mainWindowWidth << "\n";             //output the application main window width in pixels 
    out << "Main_window_height="            << mainWindowHeight << "\n";            //output the application main window height in pixels 
    out << "Are_toolbars_locked="           << AreToolbarsLocked << "\n";           //output the lock state of toolbars
    out << "Is_combo_toolbar_visible="      << IsVisibleProfileComboToolbar << "\n";//output the visible state of the combo toolbar
    out << "Is_profile_toolbar_visible="    << IsVisibleProfileToolbar << "\n";     //output the visible state of the profile toolbar
    out << "Is_toolbarText_visible="        << IsVisibleToolbarText << "\n";        //output the visible state of toolbar text
    out << "Default_Profile="               << defaultProfile << "\n";              //output the default profile full path
    out << "Default_Language="              << defaultLanguage << "\n";             //output the default language
    out << "Visible_info_window="           << IsVisibleInfoWindow << "\n";         //output the visibility state of the info window
    out << "Quite_mode_output="             << showOnlyErrors << "\n";              //output the quite mode state of the commands output window
    
    if (WINrunning)
    {
        out << "\n[settings_non_*nix]\n";
        out << "win_rsync_path="            << rsyncCommandPath << "\n";            //output the rsync path for windows or OS2
        out << "win_ssh_path="              << sshCommandPath << "\n";              //output the ssh path for windows or OS2
        out << "cygpath_path="              << cygpathCommand << "\n";
        out << "dosdev_path="               << dosdevCommand << "\n";
        out << "vshadowdir_path="           << vshadowDir << "\n";
        out << "tempdir_path="              << tempDirPath << "\n";
    }
    
    out << "\n[Settings_file_end]" << "\n";	

    settingsfile.close();
    return TRUE;
}

//loadSettings ===================================================================================================================================
//loads various luckybackup settings such as the default profile (text mode after version 0.4.7)
bool luckyBackupWindow::loadSettings()
{
    QFile settingsfile(settingsFile);
    if (!settingsfile.open(QIODevice::ReadOnly))        //if the settings file cannot be opened
    {
        settingsfile.close();
        return FALSE;
    }

    QTextStream in(&settingsfile);
    
    QString SettingsLine="";             //temp variable to import the settings line by line
    SettingsLine = in.readLine();
    
    // First check if the settings file is a text or data stream
    // if data, call loadSettingsQV
    if (SettingsLine !="***************************** WARNING *****************************")
    {
        settingsfile.close();
        return loadSettingsQV();
    }
    
    QString tempAppName = "asxeto";
    QString tempFileType = "asxeto";
    double tempAppVersion=0;
    bool IntOk;
    
    // Read all lines until the [settings_global] tag or end of file if invalid
    while ( !(SettingsLine.startsWith("[settings_global]")) && (!in.atEnd()) )
    {
        SettingsLine = in.readLine();
        
        //input the application name, version & file type --------------------------
        if (SettingsLine.startsWith("appName="))            tempAppName = SettingsLine.remove("appName=");
        if (SettingsLine.startsWith("appVersion="))         tempAppVersion = (SettingsLine.remove("appVersion=")).toDouble(&IntOk);
        if (SettingsLine.startsWith("File_Type="))          tempFileType = SettingsLine.remove("File_Type=");
    }

    //check if the file is a valid luckybackup settings file
    if ( (tempAppName != appName) || (tempAppVersion < validSettingsVersion) || (tempFileType != "luckybackup_settings_file") )
    {
        settingsfile.close();
        return FALSE;
    }

    // Read all lines until the [Settings_file_end] tag or end of file if invalid
    while ( !(SettingsLine.startsWith("[Settings_file_end]")) && (!in.atEnd()) )
    {
        SettingsLine = in.readLine();
        
        if (SettingsLine.startsWith("Main_window_width="))          mainWindowWidth = (SettingsLine.remove("Main_window_width=")).toInt(&IntOk,10);
        if (SettingsLine.startsWith("Main_window_height="))         mainWindowHeight = (SettingsLine.remove("Main_window_height=")).toInt(&IntOk,10);
        if (SettingsLine.startsWith("Are_toolbars_locked="))        AreToolbarsLocked = (SettingsLine.remove("Are_toolbars_locked=")).toInt(&IntOk,10);
        if (SettingsLine.startsWith("Is_combo_toolbar_visible="))   IsVisibleProfileComboToolbar = (SettingsLine.remove("Is_combo_toolbar_visible=")).toInt(&IntOk,10);
        if (SettingsLine.startsWith("Is_profile_toolbar_visible=")) IsVisibleProfileToolbar = (SettingsLine.remove("Is_profile_toolbar_visible=")).toInt(&IntOk,10);
        if (SettingsLine.startsWith("Is_toolbarText_visible="))     IsVisibleToolbarText = (SettingsLine.remove("Is_toolbarText_visible=")).toInt(&IntOk,10);
        if (SettingsLine.startsWith("Default_Profile="))            defaultProfile = SettingsLine.remove("Default_Profile=");
        if (SettingsLine.startsWith("Default_Language="))           defaultLanguage = SettingsLine.remove("Default_Language=");
        if (SettingsLine.startsWith("Visible_info_window="))        IsVisibleInfoWindow = (SettingsLine.remove("Visible_info_window=")).toInt(&IntOk,10);
        if (SettingsLine.startsWith("Quite_mode_output="))          showOnlyErrors = (SettingsLine.remove("Quite_mode_output=")).toInt(&IntOk,10);
        
        if (SettingsLine.startsWith("win_rsync_path="))             rsyncCommandPath = SettingsLine.remove("win_rsync_path=");
        if (SettingsLine.startsWith("win_ssh_path="))               sshCommandPath = SettingsLine.remove("win_ssh_path=");
        if (SettingsLine.startsWith("cygpath_path="))               cygpathCommand = SettingsLine.remove("cygpath_path=");
        if (SettingsLine.startsWith("dosdev_path="))                dosdevCommand = SettingsLine.remove("dosdev_path=");
        if (SettingsLine.startsWith("vshadowdir_path="))            vshadowDir = SettingsLine.remove("vshadowdir_path=");
        if (SettingsLine.startsWith("tempdir_path=") && !isTempDirPath) tempDirPath = SettingsLine.remove("tempdir_path=");
    }

    settingsfile.close();
    ui.checkBox_onlyShowErrors -> setChecked(showOnlyErrors);
    return TRUE;
}

//loadSettingsQV ===================================================================================================================================
//loads various luckybackup settings such as the default profile - data mode
bool luckyBackupWindow::loadSettingsQV()
{
    QFile settingsfile(settingsFile);
    if (!settingsfile.open(QIODevice::ReadOnly))        //if the settings file cannot be opened
    {
        settingsfile.close();
        return FALSE;
    }

    QDataStream in(&settingsfile);
    in.setVersion(QDataStream::Qt_4_3);

    QVariant v;                     //we will import everything as QVariant using this temp variable
    QString vString;                //temp variable to import "labels" of real data
    QString tempAppName = "asxeto";
    QString tempFileType = "asxeto";
    double tempAppVersion=0;
    in>>v;	if (v.toString()=="appName")
        in >> v;	tempAppName = v.toString();	//input the application name & version
    in>>v;	if (v.toString()=="appVersion")
        in >> v;	tempAppVersion = v.toDouble();
    in>>v;	if (v.toString()=="File_Type")
        in >> v;	tempFileType = v.toString();	//input the file type

    //check if the file is a valid luckybackup settings file
    if ( (tempAppName != appName) || (tempAppVersion < validSettingsVersion) || (tempFileType != "luckybackup_settings_file") )
    {
        settingsfile.close();
        return FALSE;
    }

    in>>v;	vString = v.toString();	in >> v;	//input a label in vString and real data in v
    while ( (vString != "Settings_file_end") && (!in.atEnd()) )
    {
        if (vString == "Main_window_width")         mainWindowWidth = v.toInt();
        if (vString == "Main_window_height")        mainWindowHeight = v.toInt();
        if (vString == "Are_toolbars_locked")       AreToolbarsLocked = v.toBool();
        if (vString == "Is_combo_toolbar_visible")  IsVisibleProfileComboToolbar = v.toBool();
        if (vString == "Is_profile_toolbar_visible")IsVisibleProfileToolbar = v.toBool();
        if (vString == "Is_toolbarText_visible")    IsVisibleToolbarText = v.toBool();
        if (vString == "Default_Profile")           defaultProfile = v.toString();
        if (vString == "Default_Language")          defaultLanguage = v.toString();
        if (vString == "Visible_info_window")       IsVisibleInfoWindow = v.toBool();

        if (vString == "win_rsync_path")            rsyncCommandPath = v.toString();
        if (vString == "win_ssh_path")              sshCommandPath = v.toString();
        
        in>>v;	vString = v.toString();
        if (vString!="Settings_file_end")
                in >> v;
    }
    settingsfile.close();
    
    saveSettings();     //save the settings file to text format
    
    return TRUE;
}

//arrangeLogSnap ===================================================================================================================================
//Rename-delete-copy logs & snaps when the current profile/task is renamed, deleted,duplicated
// if a task is deleted, this function is called from saveCurrentProfile()
// Returns TRUE if everything went ok
bool luckyBackupWindow::arrangeLogSnap(bool PorT,QString ActionTaken,QString NameToUse)
{
    // PorT is "1" for profile and "0" for task
    // ActionTaken can become "rename", "delete" ,"duplicate"
    // NameToUse is the new name of the current profile if rename/duplicate or the file to be deleted or the old name of the task that was renamed/deleted
    
    bool whatToReturn1 = FALSE, whatToReturn2 = FALSE;
    QStringList filtersSnapLog, snapListFiles, logsListFiles;
    if (PorT)       // we're talking about a profile
        filtersSnapLog << profileName + "-*";       // profileName is the old profile name
    else            // we're talking about a task   
        filtersSnapLog << profileName + "-" + NameToUse + "-*"; // NameToUse is the name of the task that was deleted/renamed (before it was renamed)
    
    // QSTringLists with all files to be manipulated
    QDir snapTempDir(snapChangesDir), logTempDir(logDir);
    snapListFiles = snapTempDir.entryList(filtersSnapLog,QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot,QDir::Name);
    logsListFiles = logTempDir.entryList(filtersSnapLog,QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot,QDir::Name);
    
    // actions for snap .changes files
    for (int count = 0; count < snapListFiles.size(); ++count)
    {
        snapfile.setFileName(snapChangesDir + snapListFiles.at(count));     // QFile
        snapchangesfilename = snapfile.fileName();                          // QString - old filename
        
        // the new snap .changes filename (QString) - replace either profilename or task name
        if (PorT)
            snapchangesfilename.replace(SLASH + profileName + "-" ,
                                        SLASH + NameToUse   + "-" ,Qt::CaseSensitive);  // QString - new filename (profile)
        else
            snapchangesfilename.replace(SLASH + profileName + "-" + NameToUse + "-",
                                        SLASH + profileName + "-" + Operation[currentOperation] -> GetName() + "-",Qt::CaseSensitive);  // QString - new filename (task)

        // and take some action
        if (ActionTaken == "delete")
            whatToReturn1 = snapfile.remove();
        if (ActionTaken == "rename")
            whatToReturn1 = snapfile.rename(snapchangesfilename);
        if (ActionTaken == "duplicate")     //only for profile. If a task is duplicated logs & snaps are reset
            whatToReturn1 = snapfile.copy(snapchangesfilename);
    }
    
    // actions for snap log files
    for (int count = 0; count < logsListFiles.size(); ++count)
    {
        logfile.setFileName(logDir + logsListFiles.at(count));     // QFile
        logfilename = logfile.fileName();                          // QString - old filename
        
        // the new log filename (QString) - replace either profilename or task name
        if (PorT)
            logfilename.replace(SLASH + profileName + "-",
                                SLASH + NameToUse   + "-",Qt::CaseSensitive);  // QString - new filename (profile)
        else
            logfilename.replace("-" + NameToUse +"-",
                                "-" + Operation[currentOperation] -> GetName() +"-",Qt::CaseSensitive);  // QString - new filename (task)

        // and take some action
        if (ActionTaken == "delete")
            whatToReturn2 = logfile.remove();
        if (ActionTaken == "rename")
            whatToReturn2 = logfile.rename(logfilename);
        if (ActionTaken == "duplicate")     //only for profile. If a task is duplicated logs & snaps are reset
            whatToReturn2 = logfile.copy(logfilename);
    }
    
    bool whatToReturn = whatToReturn1 && whatToReturn2; // return true if both snaps & log actions finished successfuly
    return whatToReturn;
}

// end of functions.cpp ---------------------------------------------------------------------------

