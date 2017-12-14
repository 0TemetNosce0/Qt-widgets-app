/* ---------------------------------- modifyDialog.cpp ---------------------------------------------------------------------------
Display a dialog. Adds a new or modifies an existing operation

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

#include "modifyDialog.h"

// class modifyDialog Constructor=================================================================================================
// modify or create an operation
modifyDialog::modifyDialog (int ItemNo, QDialog *parent) : QDialog (parent)
{
    uiM.setupUi(this);

    stdWindowWidth = 540;
    minWindowHeight = 245;
    maxWindowHeight = 565;
    uiM.tabWidget_advanced -> setVisible(FALSE);
    uiM.comboBox_Type -> setCurrentIndex(0);
    this -> resize(stdWindowWidth,minWindowHeight);
    ArrayPosition = ItemNo;
    validation = FALSE;
    listItemEditMode = FALSE;
        
    alsoExecuteTooltip = tr("Leave the box checked, to <b>STOP</b> the execution of running task if this command exits with an error");
    QString comLabel= tr("use boxes to <b>STOP</b> task execution on error", "Please leave the bold tags <b></b> intact and surrounding the word STOP translated");
    uiM.label_executeBeforeList -> setText ("<font color=red>" + comLabel + "</font>");
    uiM.label_executeAfterList -> setText ("<font color=red>" + comLabel + "</font>");
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Various gui initialization
    //uiM.toolBox_options         ->setItemEnabled (0,FALSE);    // different backend
    
    //Disable some stuff when windows is NOT running
    if (!WINrunning)
    {
        uiM.checkBox_vss        -> setVisible(FALSE);
        uiM.checkBox_restorent  -> setVisible(FALSE);
        uiM.lineEdit_sshPasswordStr -> setVisible(FALSE);
        uiM.lineEdit_sshOptions -> setVisible(FALSE);
    }
    else
        uiM.checkBox_vss        -> setEnabled(FALSE);   // disable VSS until a better solution is found
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //connections ----------------------------------------------------------------------------------------------------
    connect(uiM.pushButton_advanced, SIGNAL( toggled(bool) ), this, SLOT(advancedPressed(bool) ) );    //advanced pushButton
    connect(uiM.pushButton_cancel, SIGNAL( pressed() ), this, SLOT(cancelPressed() ) );        //cancel pushButton
    connect(uiM.pushButton_okay, SIGNAL( pressed() ), this, SLOT(okayPressed() ) );            //okay pushButton
    connect(uiM.pushButton_command, SIGNAL( pressed() ), this, SLOT(commandPressed() ) );        //show command pushButton
    connect(uiM.comboBox_Type, SIGNAL( currentIndexChanged(int) ), this, SLOT(TaskTypeChanged(int) ) ); //Actions when task type combo changes (hide/show stuff)

    //Connect all include tab stuff changes with the disableExcludeTab SLOT
    connect (uiM.checkBox_includeFile, SIGNAL (stateChanged(int) ), this , SLOT(disableExcludeTab()));
    connect (uiM.lineEdit_includeFile, SIGNAL (textChanged(QString) ), this , SLOT(disableExcludeTab()));
    connect (uiM.radioButton_includeOnly, SIGNAL (toggled(bool)), this , SLOT(disableExcludeTab()));
    connect (uiM.radioButton_includeNormal, SIGNAL (toggled(bool)), this , SLOT(disableExcludeTab()));
    
    //Connect all add list items buttons with the addListItem SLOT
    //Map all the pushButton signals and transmit a different integer depending on the pushbutton
    QSignalMapper *signalMapper2 = new QSignalMapper(this);
    signalMapper2 -> setMapping ( uiM.pushButton_excludeAdd, 0 );
    connect(uiM.pushButton_excludeAdd, SIGNAL( pressed() ), signalMapper2, SLOT(map() ) );    //excludAdd pushButton
    signalMapper2 -> setMapping ( uiM.pushButton_includeAdd, 1 );
    connect(uiM.pushButton_includeAdd, SIGNAL( pressed() ), signalMapper2, SLOT(map() ) );    //includeAdd pushButton
    signalMapper2 -> setMapping ( uiM.pushButton_optionsAdd, 2 );
    connect(uiM.pushButton_optionsAdd, SIGNAL( pressed() ), signalMapper2, SLOT(map() ) );    //optionsAdd pushButton
    signalMapper2 -> setMapping ( uiM.pushButton_executeBeforeAdd, 3 );
    connect(uiM.pushButton_executeBeforeAdd, SIGNAL( pressed() ), signalMapper2, SLOT(map() ) );    //executeBeforeAdd pushButton
    signalMapper2 -> setMapping ( uiM.pushButton_executeAfterAdd, 4 );
    connect(uiM.pushButton_executeAfterAdd, SIGNAL( pressed() ), signalMapper2, SLOT(map() ) );    //executeAftereAdd pushButton
    connect(signalMapper2, SIGNAL(mapped( const int)), this, SLOT( addListItem( const int) )  );

    //Connect all Remove list items buttons with the RemoveListItem SLOT
    //Map all the pushButton signals and transmit a different integer depending on the pushbutton
    QSignalMapper *signalMapper3 = new QSignalMapper(this);
    signalMapper3 -> setMapping ( uiM.pushButton_excludeRemove, 0 );
    connect(uiM.pushButton_excludeRemove, SIGNAL( pressed() ), signalMapper3, SLOT(map() ) );    //excludeRemove pushButton
    signalMapper3 -> setMapping ( uiM.pushButton_includeRemove, 1 );
    connect(uiM.pushButton_includeRemove, SIGNAL( pressed() ), signalMapper3, SLOT(map() ) );    //includeRemove pushButton
    signalMapper3 -> setMapping ( uiM.pushButton_optionsRemove, 2 );
    connect(uiM.pushButton_optionsRemove, SIGNAL( pressed() ), signalMapper3, SLOT(map() ) );    //optionsRemove pushButton
    signalMapper3 -> setMapping ( uiM.pushButton_executeBeforeRemove, 3 );
    connect(uiM.pushButton_executeBeforeRemove, SIGNAL( pressed() ), signalMapper3, SLOT(map() ) );    //executeBeforeRemove pushButton
    signalMapper3 -> setMapping ( uiM.pushButton_executeAfterRemove, 4 );
    connect(uiM.pushButton_executeAfterRemove, SIGNAL( pressed() ), signalMapper3, SLOT(map() ) );    //executeAfterRemove pushButton
    connect(signalMapper3, SIGNAL(mapped( const int)), this, SLOT( removeListItem( const int) )  );

    //Connect all edit list items buttons with the editListItem SLOT
    //Map all the pushButton signals and transmit a different integer depending on the pushbutton
    QSignalMapper *signalMapper5 = new QSignalMapper(this);
    signalMapper5 -> setMapping ( uiM.pushButton_editExclude, 0 );
    connect(uiM.pushButton_editExclude, SIGNAL( pressed() ), signalMapper5, SLOT(map() ) );  //EditExclude pushButton
    signalMapper5 -> setMapping ( uiM.pushButton_editInclude, 1 );
    connect(uiM.pushButton_editInclude, SIGNAL( pressed() ), signalMapper5, SLOT(map() ) );  //EditInclude pushButton
    signalMapper5 -> setMapping ( uiM.pushButton_editOptions, 2 );
    connect(uiM.pushButton_editOptions, SIGNAL( pressed() ), signalMapper5, SLOT(map() ) );  //EditOptiions pushButton
    signalMapper5 -> setMapping ( uiM.pushButton_editExecuteBefore, 3 );
    connect(uiM.pushButton_editExecuteBefore, SIGNAL( pressed() ), signalMapper5, SLOT(map() ) );    //EditExecuteBefore pushButton
    signalMapper5 -> setMapping ( uiM.pushButton_editExecuteAfter, 4 );
    connect(uiM.pushButton_editExecuteAfter, SIGNAL( pressed() ), signalMapper5, SLOT(map() ) ); //EditExecuteAfter pushButton
    connect(signalMapper5, SIGNAL(mapped( const int)), this, SLOT( editListItem( const int) )  );
    
    //Connect all "move up" list items buttons with the editListItem SLOT
    //Map all the pushButton signals and transmit a different integer depending on the pushbutton
    QSignalMapper *signalMapper6 = new QSignalMapper(this);
    signalMapper6 -> setMapping ( uiM.pushButton_moveUpExclude, 0 );
    connect(uiM.pushButton_moveUpExclude, SIGNAL( pressed() ), signalMapper6, SLOT(map() ) );
    signalMapper6 -> setMapping ( uiM.pushButton_moveUpInclude, 1 );
    connect(uiM.pushButton_moveUpInclude, SIGNAL( pressed() ), signalMapper6, SLOT(map() ) );
    signalMapper6 -> setMapping ( uiM.pushButton_moveUpOptions, 2 );
    connect(uiM.pushButton_moveUpOptions, SIGNAL( pressed() ), signalMapper6, SLOT(map() ) );
    signalMapper6 -> setMapping ( uiM.pushButton_moveUpExecuteBefore, 3 );
    connect(uiM.pushButton_moveUpExecuteBefore, SIGNAL( pressed() ), signalMapper6, SLOT(map() ) );
    signalMapper6 -> setMapping ( uiM.pushButton_moveUpExecuteAfter, 4 );
    connect(uiM.pushButton_moveUpExecuteAfter, SIGNAL( pressed() ), signalMapper6, SLOT(map() ) );
    connect(signalMapper6, SIGNAL(mapped( const int)), this, SLOT( moveListItemUp( const int) )  );
    
    //Connect all "move down" list items buttons with the editListItem SLOT
    //Map all the pushButton signals and transmit a different integer depending on the pushbutton
    QSignalMapper *signalMapper7 = new QSignalMapper(this);
    signalMapper7 -> setMapping ( uiM.pushButton_moveDownExclude, 0 );
    connect(uiM.pushButton_moveDownExclude, SIGNAL( pressed() ), signalMapper7, SLOT(map() ) );
    signalMapper7 -> setMapping ( uiM.pushButton_moveDownInclude, 1 );
    connect(uiM.pushButton_moveDownInclude, SIGNAL( pressed() ), signalMapper7, SLOT(map() ) );
    signalMapper7 -> setMapping ( uiM.pushButton_moveDownOptions, 2 );
    connect(uiM.pushButton_moveDownOptions, SIGNAL( pressed() ), signalMapper7, SLOT(map() ) );
    signalMapper7 -> setMapping ( uiM.pushButton_moveDownExecuteBefore, 3 );
    connect(uiM.pushButton_moveDownExecuteBefore, SIGNAL( pressed() ), signalMapper7, SLOT(map() ) );
    signalMapper7 -> setMapping ( uiM.pushButton_moveDownExecuteAfter, 4 );
    connect(uiM.pushButton_moveDownExecuteAfter, SIGNAL( pressed() ), signalMapper7, SLOT(map() ) );
    connect(signalMapper7, SIGNAL(mapped( const int)), this, SLOT( moveListItemDown( const int) )  );
    
    //Connect all toolButtons with the browse SLOT
    //Map all the toolButton signals and transmit a different integer depending on the toolbutton
    QSignalMapper *signalMapper = new QSignalMapper(this);
    signalMapper ->    setMapping ( uiM.toolButton_sourceBrowse, 0 );
    connect (uiM.toolButton_sourceBrowse, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiM.toolButton_destinationBrowse, 1 );
    connect (uiM.toolButton_destinationBrowse, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiM.toolButton_rsyncPassword, 4 );
    connect (uiM.toolButton_rsyncPassword, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiM.toolButton_sshPassword, 5 );
    connect (uiM.toolButton_sshPassword, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiM.toolButton_executeBeforeBrowse, 6 );
    connect (uiM.toolButton_executeBeforeBrowse, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiM.toolButton_executeAfterBrowse, 7 );
    connect (uiM.toolButton_executeAfterBrowse, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiM.toolButton_includeFile, 8 );
    connect (uiM.toolButton_includeFile, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiM.toolButton_excludeFile, 9 );
    connect (uiM.toolButton_excludeFile, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    connect(signalMapper, SIGNAL(mapped( const int)), this, SLOT( browse( const int) )  );

    //Connect all pattern toolButtons with the getPattern SLOT
    //Map all the toolButton signals and transmit a different integer depending on the toolbutton
    QSignalMapper *signalMapper4 = new QSignalMapper(this);
    signalMapper4 ->    setMapping ( uiM.toolButton_excludeAddPattern, 0 );
    connect (uiM.toolButton_excludeAddPattern, SIGNAL (clicked() ), signalMapper4 , SLOT (map()));
    signalMapper4 ->    setMapping ( uiM.toolButton_includeAddPattern, 1 );
    connect (uiM.toolButton_includeAddPattern, SIGNAL (clicked() ), signalMapper4 , SLOT (map()));
    connect(signalMapper4, SIGNAL(mapped( const int)), this, SLOT( getPattern( const int) )  );
    
    // ssh password file default value
    // I do not consider this a good idea, because the default option should be a blank field (no ssh key file)
    // If the user clicks the browse button , he/she will be transfered to the ~/.ssh dir as default
    /*
    if ( (uiM.lineEdit_sshPassword -> text() == "" ) && (!WINrunning) )
    {
        if (!WINrunning)
            uiM.lineEdit_sshPassword -> setText( myHome + SLASH +".ssh" + SLASH +"id_rsa");
        else
            uiM.lineEdit_sshPassword -> setText(luckyBackupDir+"id_rsa");
    }
    */
    
    if (ArrayPosition < TotalOperations)    //if modify is pressed fill the fields first with existing operation data
        fillModifyWindow(Operation[ArrayPosition]);
    
    disableExcludeTab();    // disable the exclude tab or nothing
    
    StdArguments << "-h" << "--progress" << "--stats";    //These are the standard arguments used by rsync

    //initialize a completer for the lineEdits
    QCompleter *completer = new QCompleter(this);
    completer                       -> setModel(new QDirModel(completer));
    uiM.lineEdit_source             -> setCompleter(completer);
    uiM.lineEdit_destination        -> setCompleter(completer);
    uiM.lineEdit_excludeAdd         -> setCompleter(completer);
    uiM.lineEdit_rsyncPassword      -> setCompleter(completer);
    uiM.lineEdit_sshPassword        -> setCompleter(completer);
    uiM.lineEdit_executeBeforeAdd   -> setCompleter(completer);
    uiM.lineEdit_executeAfterAdd    -> setCompleter(completer);
    uiM.lineEdit_excludeFile        -> setCompleter(completer);
    uiM.lineEdit_includeFile        -> setCompleter(completer);
}
//===================================================================================================================================================
//------------------------------------------------------------------SLOTS----------------------------------------------------------------------------
//===================================================================================================================================================

// advanced button pressed=====================================================================================================
// hides or shows part of the widget
void modifyDialog::advancedPressed(bool advanced)
{
    int windowWidth = (this -> size()).width();
    if (advanced)
    {
        uiM.tabWidget_advanced -> setVisible(TRUE);
        uiM.pushButton_advanced -> setText(tr("simple"));
        this -> resize(windowWidth,maxWindowHeight);
    }
    else
    {
        uiM.tabWidget_advanced -> setVisible(FALSE);
        uiM.pushButton_advanced -> setText(tr("advanced"));
        this -> resize(windowWidth,minWindowHeight);
    }
}

// cancel button pressed=====================================================================================================
void modifyDialog::cancelPressed()
{
    modifyOK = FALSE;
    modifyConnected = FALSE;
    close();    //emmit a QcloseEvent
}

//window closebutton pressed or QcloseEvent emitted==========================================================================
void modifyDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
}

// browse button pressed=====================================================================================================
//opens a QFileDialog to browse for files/folders locally
void modifyDialog::browse(const int type)
{
    QString newLineEdit;
    switch (type)
    {
        //source browse button
        case 0:    newLineEdit = QFileDialog::getExistingDirectory (this, tr("Select source directory",
            "file selection dialog title"),uiM.lineEdit_source -> text());
            if (newLineEdit != "")    //if something is selected indeed
                uiM.lineEdit_source     -> setText(modifyOS2Slashes(newLineEdit));
            break;
        //destination browse button
        case 1: newLineEdit = QFileDialog::getExistingDirectory (this, tr("Select destination directory",
            "file selection dialog title"),uiM.lineEdit_destination -> text());
            if (newLineEdit != "")    //if something is selected indeed
                uiM.lineEdit_destination -> setText(modifyOS2Slashes(newLineEdit));
            break;
        //rsync password file browse button
        case 4:    newLineEdit = QFileDialog::getOpenFileName (this, tr("Select rsync password file",
            "file selection dialog title"), myHome);
            if (newLineEdit != "")    //if something is selected indeed
                uiM.lineEdit_rsyncPassword -> setText(modifyOS2Slashes(newLineEdit));
            break;
        //ssh password file browse button
        case 5:    if (!WINrunning)
                newLineEdit = QFileDialog::getOpenFileName (this, tr("Select ssh keyfile", "file selection dialog title"), myHome + SLASH +".ssh");
            else
                newLineEdit = QFileDialog::getOpenFileName (this, tr("Select ssh keyfile", "file selection dialog title"), luckyBackupDir);        
            if (newLineEdit != "")    //if something is selected indeed
                uiM.lineEdit_sshPassword -> setText(modifyOS2Slashes(newLineEdit));
            break;
        //execute before browse button
        case 6:    newLineEdit = QFileDialog::getOpenFileName (this, tr("Select command to be executed",
            "file selection dialog title"),SLASH);
            if (newLineEdit != "")    //if something is selected indeed
                uiM.lineEdit_executeBeforeAdd -> setText(modifyOS2Slashes(newLineEdit));
            break;
        //execute after browse button
        case 7:    newLineEdit = QFileDialog::getOpenFileName (this, tr("Select command to be executed",
            "file selection dialog title"),SLASH);
            if (newLineEdit != "")    //if something is selected indeed
                uiM.lineEdit_executeAfterAdd -> setText(modifyOS2Slashes(newLineEdit));
            break;
        //include from file browse button
        case 8:    newLineEdit = QFileDialog::getOpenFileName (this, tr("Select file to read include patterns",
            "file selection dialog title"),myHome);
            if (newLineEdit != "")    //if something is selected indeed
                uiM.lineEdit_includeFile -> setText(modifyOS2Slashes(newLineEdit));
            break;
        //exclude from file browse button
        case 9:    newLineEdit = QFileDialog::getOpenFileName (this, tr("Select file to read exclude patterns",
            "file selection dialog title"),myHome);
            if (newLineEdit != "")    //if something is selected indeed
                uiM.lineEdit_excludeFile -> setText(modifyOS2Slashes(newLineEdit));
            break;
    }

}

// pattern button pressed=====================================================================================================
//launches the pattern editor
void modifyDialog::getPattern(const int type)
{    
    if (uiM.lineEdit_source -> text() == "")    //if the source isn't defined yet
    {
        textDialog textdialogW ("QtWarning", tr("Please define the source before launching the pattern editor","message box, message")+" !!", this);
        textdialogW.exec();
        return;
    }

    modifyTrailing(); // first modify the trailing of the source & destination directories
    
    QString NewPattern = "";
    
    patternEditor patterneditor(uiM.lineEdit_source -> text(), this);
    patterneditor.exec();
    
    NewPattern = patterneditor.getPattern();
    if (NewPattern == "no pattern defined yet")    // cancel pressed at the pattern editor
        return;
    switch (type)
    {
        // insert the pattern to the exclude lineEdit
        case 0:    uiM.lineEdit_excludeAdd    -> setText(NewPattern);
                break;
        // insert the pattern to the incude lineEdit
        case 1:    uiM.lineEdit_includeAdd    -> setText(NewPattern);
                break;
    }
}
// okay button pressed=======================================================================================================
// Read all fields of modify operation dialog and fill appropriate variables
// ...after performing some checks & changes !!
void modifyDialog::okayPressed()
{
    modifyOK = TRUE;
    message = "";
    
    // Strip off invalid characters from task name
    uiM.lineEdit_name -> setText(stripInvalidCharacters(uiM.lineEdit_name -> text()));

    //if name or source or destination is missing do not proceed -----------------------------------------------------------
    if ( (uiM.lineEdit_name -> text() == "") || (uiM.lineEdit_destination -> text() == "") || (uiM.lineEdit_source -> text() == "")  )
    {
        modifyOK = FALSE;
        message.append("<b>"+tr("ERROR","message box message")+":</b> "+
                    tr("Please specify the following before proceeding:","message box, message"));
        if (uiM.lineEdit_name -> text() == "")
            message.append("<br>"+tr("Task name"));
        if (uiM.lineEdit_destination -> text() == "")
            message.append("<br>"+tr("Destination"));
        if (uiM.lineEdit_source -> text() == "")
            message.append("<br>"+tr("Source"));
        message.append("<br><br>");
    }

    //check if / is declared as source and backup dir by name as operation type ------------------------------------------------
    if ((uiM.lineEdit_source -> text() == "/") && (uiM.comboBox_Type -> currentIndex()==0) && (!uiM.checkBox_backupContents -> isChecked()))
    {
        modifyOK = FALSE;
        message.append("<b>"+tr("ERROR","message box message - line1")+":</b> "+
        tr("You have declared the '/' (root) directory as source and have NOT checked the 'Do NOT create extra directory' box","message box message - line1")+"<br>"+
                tr("That is not allowed because '/' does not have an actual name","message box message - line2")+" !!<br>"
                "..."+tr("Please check the relevant box before proceeding","message box message - line3")+"<br><br>");
    }
    //same for OS2 or win
    if (((uiM.lineEdit_source -> text()).endsWith(":\\")) && (uiM.comboBox_Type -> currentIndex()==0) && (!uiM.checkBox_backupContents -> isChecked())
        && (notXnixRunning) )
    {
        modifyOK = FALSE;
        message.append("<b>"+tr("ERROR","message box message - line1")+":</b> "+
        tr("You have declared the root directory of an entire partition as source and have NOT checked the 'Do NOT create extra directory' box","message box message - line1")+"<br>"+
                tr("That is not allowed because the root partition does not have an actual name","message box message - line2")+" !!<br>"
                "..."+tr("Please check the relevant box before proceeding","message box message - line3")+"<br><br>");
    }

    //check if the operation name already exists to proceed --------------------------------------------------------------------
    count=0;
    while (count < TotalOperations)
    {
        if ( ((uiM.lineEdit_name -> text()) == (Operation[count] -> GetName()) ) && (count != ArrayPosition) )
        {
            modifyOK = FALSE;
            message.append("<b>"+tr("ERROR","message box message - line1")+":</b> "+
            tr("The name of the task you requested already exists","message box message - line1")+" !!<br>"
                    "..."+tr("Please specify a different name before proceeding","message box message - line2")+"<br><br>");
            break;
        }
        count++;
    }

    modifyTrailing();    //do some changes according to radio button "operation type"

    //perform this if both source & destination are not empty
    if ( ((uiM.lineEdit_source -> text()) != "") && ((uiM.lineEdit_destination -> text()) != "" ) )
    {
        //check if source & destination are the same to proceed ------------------------------------------------------------------
        if ((( (uiM.lineEdit_source -> text()) == (uiM.lineEdit_destination -> text()) )    
        || ( (uiM.lineEdit_source -> text() + SLASH) == (uiM.lineEdit_destination -> text()) )    ) && (!uiM.groupBox_remote -> isChecked()) )
        {
            modifyOK = FALSE;
            message.append("<b>"+tr("ERROR","message box message - line1")+":</b> "+
            tr("The source you have declared is identical to the destination","message box message - line1")+" !!<br>"
                    "..."+tr("Please modify at least one of them","message box message - line2")+"<br><br>");
        }
        else    //check if the destination is part of the source directory structure ------------------------------------------------
        if (     ((uiM.lineEdit_destination -> text()).contains(uiM.lineEdit_source -> text(), Qt::CaseSensitive) )
        ||    ((uiM.lineEdit_destination -> text()).contains(uiM.lineEdit_source -> text() + SLASH, Qt::CaseSensitive))    )
                message.prepend("<b>"+tr("WARNING","message box message - line1")+":</b> "+
                    tr("You have declared a destination that is part of the source directory structure",
                       "message box message - line1")+"<br>"
                    +tr("<b>Do not forget</b> to define a directory at the 'exclude' groupbox that will contain the destination",
                    "message box message - line2. Please leave tag <b>,</b> intact and surrounding 'do not forget' translated")+"<br><br>");
    }

    //"recursive" has to be checked for --delete-after to operate -------------------------------------------------------------
    if ( (uiM.checkBox_deleteAfter -> isChecked()) && !(uiM.checkBox_recurse -> isChecked()) )
    {
        modifyOK = FALSE;
        message.append("<b>"+tr("ERROR","message box message - line1")+":</b> "+
        tr("You have checked the 'delete files on the destination' option","message box message - line2") + "<br>" +
                tr("without having checked 'Recurse into directories' which is required","message box message - line3")+"<br><br>");
    }

    //check if "remote" is checked and no hostname is declared -----------------------------------------------------------------
    if ( (uiM.groupBox_remote -> isChecked()) && (uiM.lineEdit_remoteHost -> text() == "") )
    {
        modifyOK = FALSE;
        message.append("<b>"+tr("ERROR","message box message - line1")+":</b>"+
                tr("'Remote Host' is checked, but no remote host name is declared","message box message - line2")+"<br>"+
                tr("Please specify a remote host name","message box message - line3")+"<br>"+
                tr("Otherwise uncheck 'Remote Host' to operate locally","message box message - line4")+"<br><br>");
    }

    bool tempCloneWarning = TRUE;
    //use this cause the next command will set CloneWARNING to TRUE by creating a new operation
    // only perform this if "modify is pressed, not "new/duplicate/restore" task
    if (!newTaskThisIs)
        tempCloneWarning = Operation[ArrayPosition] -> GetCloneWARNING ();
    
    Operation[ArrayPosition] = fillOperationArray();    //fill the operation array item with data from the modify dialog
    Operation[ArrayPosition] -> SetCloneWARNING (tempCloneWarning);

    if (!validation)         //if "done" pressed and not "validation check" 
    {
        if (modifyOK)        //if all "data filling" went ok
        {
            //check if the user has selected "delete files on the destination" & "backup the contents of a source directory" and WARN
            if ( (uiM.comboBox_Type -> currentIndex()==0) && (uiM.checkBox_deleteAfter -> isChecked()) &&
                (Operation[ArrayPosition] -> GetCloneWARNING()) && (uiM.checkBox_backupContents -> isChecked()) )
            {
                textDialog textdialog ("CloneWarning", "", this);
                textdialog.exec();
                if (textdialog.getGoOn() == 4)        //okay with "Do not show this again" checked
                {
                    Operation[ArrayPosition] -> SetCloneWARNING (FALSE);
                    close();
                }
                if (textdialog.getGoOn() == 2)        //okay with "Do not show this again" NOT checked
                    close();    //emmit a QcloseEvent
            }
            else
                close();    //emmit a QcloseEvent
        }
        else            //display a warning message
        {
            textDialog textdialogW ("QtWarning", message, this);
            textdialogW.exec();
        }
    }
}

// validate button pressed=======================================================================================================
// Pops up a dialog with the rsync command & arguments, also displays error messages
void modifyDialog::commandPressed()
{
    validation = TRUE;

    okayPressed();
    
    QStringList arguments = Operation[ArrayPosition] -> GetArgs(); QString tempArgs = ""; count=0; QString source, dest;
    source=arguments[arguments.size()-2];
    dest=arguments[arguments.size()-1];
    while (count < arguments.size()-2)
    {
        if (arguments[count].contains("-e "+sshCommandPath+" "))
        {
            tempArgs.append("-e \"" + arguments[count].remove(0,3) + "\" ");
        }
        else
            tempArgs.append(arguments[count]+" ");
        count++;
    }
    
    if (modifyOK)
        message.prepend(tr("All declared fields of the task properties window seem to be ok","message box message first line")+"<br><br>");
    else
        message.prepend("<b>"+tr("Errors have been found","message box message first line")+"...</b><br><br>");

    message.append("<b>"+tr("command to be executed","full phrase: command to be executed: <COMMAND>")+":</b><br>");
    
    textDialog textdialog ("ValidateDialog", message + "<font color=red>rsync </font><font color=blue>" + tempArgs +
        "</font><br><font color=magenta>"+ source + " </font><br><font color=magenta>" + dest + "</font><br>", this);
    textdialog.exec();

    validation = FALSE;
    //==========================================================================================================================
}

// List item Add button pressed=====================================================================================================
// adds an item in the excluded,included,options list
void modifyDialog::addListItem(const int type)
{
    QString text="", selectedText="";
    QList<QListWidgetItem*> temp;
    temp.clear();
    
    switch (type)
    {
        //exclude list add button
        case 0:    
            text = uiM.lineEdit_excludeAdd -> text();                               // This is the text in the lineEdit
            if (text == "")     // if there is nothing typed just return
                return;
            
            if (uiM.listWidget_exclude -> count() == 0) // if this is the first entry, just add it (to avoid segfault)
            {
                uiM.listWidget_exclude -> addItem(text);
                uiM.lineEdit_excludeAdd -> clear();
                return;
            }

            if (listItemEditMode)
                selectedText = (uiM.listWidget_exclude -> currentItem()) -> text();     // The selected list item text (used for listItemEdit)
            temp = uiM.listWidget_exclude -> findItems (text, Qt::MatchExactly) ;   // list with all other items that are the same with the lineedit
            
            // If the text in the lineedit already exists
            if ((temp.size() > 0) && (text != selectedText))
            {
                textDialog textdialogw ("QtWarning", tr("You have already added this exclude item","message box message")+" !!<br>" , this);
                textdialogw.exec();
                return;
            }
            
            if (listItemEditMode)
            {
                //change the value of the selected list item
                int selectedItem = uiM.listWidget_exclude -> currentRow(); 
                uiM.listWidget_exclude -> takeItem(selectedItem);               //take out the selected item from the list
                uiM.listWidget_exclude -> insertItem(selectedItem, text);       //insert a new one at the same position with the new text
                uiM.listWidget_exclude -> setCurrentRow(selectedItem);          //highlight this row

                // set the gui back to its original form
                uiM.pushButton_excludeAdd -> setText(origAddText);
                uiM.pushButton_excludeAdd -> setToolTip(origAddToolTip);
                uiM.pushButton_excludeAdd -> setIcon(QIcon(":/luckyPrefix/add.png"));
                uiM.pushButton_excludeRemove -> setText(origRemoveText);
                uiM.pushButton_excludeRemove -> setToolTip(origRemoveToolTip);
                uiM.pushButton_excludeRemove -> setIcon(QIcon(":/luckyPrefix/remove.png"));
                
                uiM.pushButton_editExclude -> setEnabled (TRUE);
                uiM.pushButton_moveUpExclude -> setEnabled (TRUE);
                uiM.pushButton_moveDownExclude -> setEnabled (TRUE);
                
                // set this bool var to FALSE - end of list edit mode
                listItemEditMode = FALSE;
            }
            else
                uiM.listWidget_exclude -> addItem(text);
            uiM.lineEdit_excludeAdd -> clear();
            
            break;
    
        //include list add button
        case 1:
            text = uiM.lineEdit_includeAdd -> text();
             if (text == "")     // if there is nothing typed just return
                return;
            
            if (uiM.listWidget_include -> count() == 0) // if this is the first entry, just add it (to avoid segfault)
            {
                    uiM.listWidget_include -> addItem(text);
                    uiM.lineEdit_includeAdd -> clear();
                    disableExcludeTab();    // disable the exclude tab or not
                    return;
            }

            if (listItemEditMode)
                selectedText = (uiM.listWidget_include -> currentItem()) -> text();     // The selected list item text (used for listItemEdit)
            temp = uiM.listWidget_include -> findItems (text, Qt::MatchExactly) ;   // list with all other items that are the same with the lineedit
            
            // If the text in the lineedit already exists
            if ((temp.size() > 0) && (text != selectedText))
            {
                textDialog textdialogw ("QtWarning", tr("You have already added this include item","message box message")+" !!<br>" , this);
                textdialogw.exec();                
                return;
            }

            if (listItemEditMode)
            {
                //change the value of the selected list item
                int selectedItem = uiM.listWidget_include -> currentRow(); 
                uiM.listWidget_include -> takeItem(selectedItem);               //take out the selected item from the list
                uiM.listWidget_include -> insertItem(selectedItem, text);       //insert a new one at the same position with the new text
                uiM.listWidget_include -> setCurrentRow(selectedItem);          //highlight this row

                // set the gui back to its original form
                uiM.pushButton_includeAdd -> setText(origAddText);
                uiM.pushButton_includeAdd -> setToolTip(origAddToolTip);
                uiM.pushButton_includeAdd -> setIcon(QIcon(":/luckyPrefix/add.png"));
                uiM.pushButton_includeRemove -> setText(origRemoveText);
                uiM.pushButton_includeRemove -> setToolTip(origRemoveToolTip);
                uiM.pushButton_includeRemove -> setIcon(QIcon(":/luckyPrefix/remove.png"));
                
                uiM.pushButton_editInclude -> setEnabled (TRUE);
                uiM.pushButton_moveUpInclude -> setEnabled (TRUE);
                uiM.pushButton_moveDownInclude -> setEnabled (TRUE);
                
                // set this bool var to FALSE - end of list edit mode
                listItemEditMode = FALSE;
            }
            else
                uiM.listWidget_include -> addItem(text);
            uiM.lineEdit_includeAdd -> clear();
            disableExcludeTab();    // disable the exclude tab or not
            break;
            
        //options list add button
        case 2:
            text = uiM.lineEdit_optionsAdd -> text();
            if (text == "")     // if there is nothing typed just return
                return;
            if (uiM.listWidget_options -> count() == 0) // if this is the first entry, just add it (to avoid segfault)
            {
                    uiM.listWidget_options -> addItem(text);
                    uiM.lineEdit_optionsAdd -> clear();
                    return;
            }
            
            if (listItemEditMode)
                selectedText = (uiM.listWidget_options -> currentItem()) -> text();     // The selected list item text (used for listItemEdit)
            temp = uiM.listWidget_options -> findItems (text, Qt::MatchExactly) ;   // list with all other items that are the same with the lineedit
            
            // If the text in the lineedit already exist
            if ((temp.size() > 0) && (text != selectedText))
            {
                textDialog textdialogW ("QtWarning", tr("You have already added this option","message box message")+" !!<br>", this);
                textdialogW.exec();
                return;
            }
            
            if (listItemEditMode)
            {
                //change the value of the selected list item
                int selectedItem = uiM.listWidget_options -> currentRow(); 
                uiM.listWidget_options -> takeItem(selectedItem); //take out the selected item from the list
                uiM.listWidget_options -> insertItem(selectedItem, text);       //insert a new one at the same position with the new text
                uiM.listWidget_options -> setCurrentRow(selectedItem);          //highlight this row

                // set the gui back to its original form
                uiM.pushButton_optionsAdd -> setText(origAddText);
                uiM.pushButton_optionsAdd -> setToolTip(origAddToolTip);
                uiM.pushButton_optionsAdd -> setIcon(QIcon(":/luckyPrefix/add.png"));
                uiM.pushButton_optionsRemove -> setText(origRemoveText);
                uiM.pushButton_optionsRemove -> setToolTip(origRemoveToolTip);
                uiM.pushButton_optionsRemove -> setIcon(QIcon(":/luckyPrefix/remove.png"));
                
                uiM.pushButton_editOptions -> setEnabled (TRUE);
                uiM.pushButton_moveUpOptions -> setEnabled (TRUE);
                uiM.pushButton_moveDownOptions -> setEnabled (TRUE);
                
                // set this bool var to FALSE - end of list edit mode
                listItemEditMode = FALSE;
            }
            else
                uiM.listWidget_options -> addItem(text);
            
            uiM.lineEdit_optionsAdd -> clear();

            break;
            
        //Execute before list add button
        case 3:
            text = uiM.lineEdit_executeBeforeAdd -> text();
            if (text != "")
            {
                if (listItemEditMode)
                {
                    //change the value of the selected list item
                    int selectedItem = uiM.listWidget_executeBefore -> currentRow(); 
                    uiM.listWidget_executeBefore -> takeItem(selectedItem); //take out the selected item from the list
                                //insert a new one at the same position with the new text
                    uiM.listWidget_executeBefore -> insertItem(selectedItem, text); 
                    uiM.listWidget_executeBefore -> setCurrentRow(selectedItem);        //highlight this row
                    uiM.listWidget_executeBefore -> currentItem() -> setCheckState(alsoExecuteState); // set its state to what it was
                    uiM.listWidget_executeBefore -> currentItem() -> setToolTip (alsoExecuteTooltip); // set the tooltip
    
                    // set the gui back to its original form
                    uiM.pushButton_executeBeforeAdd -> setText(origAddText);
                    uiM.pushButton_executeBeforeAdd -> setToolTip(origAddToolTip);
                    uiM.pushButton_executeBeforeAdd -> setIcon(QIcon(":/luckyPrefix/add.png"));
                    uiM.pushButton_executeBeforeRemove -> setText(origRemoveText);
                    uiM.pushButton_executeBeforeRemove -> setToolTip(origRemoveToolTip);
                    uiM.pushButton_executeBeforeRemove -> setIcon(QIcon(":/luckyPrefix/remove.png"));
                    
                    uiM.pushButton_editExecuteBefore -> setEnabled (TRUE);
                    uiM.pushButton_moveUpExecuteBefore -> setEnabled (TRUE);
                    uiM.pushButton_moveDownExecuteBefore -> setEnabled (TRUE);
                    
                    // set this bool var to FALSE - end of list edit mode
                    listItemEditMode = FALSE;
                }
                else
                {
                    uiM.listWidget_executeBefore -> addItem(text);
                    uiM.listWidget_executeBefore -> setCurrentRow(uiM.listWidget_executeBefore -> count()-1);
                    uiM.listWidget_executeBefore -> currentItem() -> setCheckState(Qt::Checked);
                    uiM.listWidget_executeBefore -> currentItem() -> setToolTip (alsoExecuteTooltip);
                }
                
                uiM.lineEdit_executeBeforeAdd -> clear();
            }
            break;
        //Execute after list add button
        case 4:
            text = uiM.lineEdit_executeAfterAdd -> text();
            if (text != "")
            {
                if (listItemEditMode)
                {
                    //change the value of the selected list item
                    int selectedItem = uiM.listWidget_executeAfter -> currentRow(); 
                    uiM.listWidget_executeAfter -> takeItem(selectedItem); //take out the selected item from the list
                                //insert a new one at the same position with the new text
                    uiM.listWidget_executeAfter -> insertItem(selectedItem, text); 
                    uiM.listWidget_executeAfter -> setCurrentRow(selectedItem);        //highlight this row
                    uiM.listWidget_executeAfter -> currentItem() -> setCheckState(alsoExecuteState); // set its state to what it was
                    uiM.listWidget_executeAfter -> currentItem() -> setToolTip (alsoExecuteTooltip);
    
                    // set the gui back to its original form
                    uiM.pushButton_executeAfterAdd -> setText(origAddText);
                    uiM.pushButton_executeAfterAdd -> setToolTip(origAddToolTip);
                    uiM.pushButton_executeAfterAdd -> setIcon(QIcon(":/luckyPrefix/add.png"));
                    uiM.pushButton_executeAfterRemove -> setText(origRemoveText);
                    uiM.pushButton_executeAfterRemove -> setToolTip(origRemoveToolTip);
                    uiM.pushButton_executeAfterRemove -> setIcon(QIcon(":/luckyPrefix/remove.png"));
                    
                    uiM.pushButton_editExecuteAfter -> setEnabled (TRUE);
                    uiM.pushButton_moveUpExecuteAfter -> setEnabled (TRUE);
                    uiM.pushButton_moveDownExecuteAfter -> setEnabled (TRUE);
                    
                    // set this bool var to FALSE - end of list edit mode
                    listItemEditMode = FALSE;
                }
                else
                {
                    uiM.listWidget_executeAfter -> addItem(text);
                    uiM.listWidget_executeAfter -> setCurrentRow(uiM.listWidget_executeAfter -> count()-1);
                    uiM.listWidget_executeAfter -> currentItem() -> setCheckState(Qt::Checked);
                    uiM.listWidget_executeAfter -> currentItem() -> setToolTip (alsoExecuteTooltip);
                }
                
                uiM.lineEdit_executeAfterAdd -> clear();
            }
            break;
    }
}

// List item Remove button pressed=====================================================================================================
// Removes an item from the excluded,included,options list
void modifyDialog::removeListItem(const int type)
{
    int selected;
    switch (type)
    {
        //exclude list remove button
        case 0:
            if (listItemEditMode)   // do not proceed further if this is just a cancel from list item edit mode
            {
                // set the gui back to its original form
                uiM.pushButton_excludeAdd -> setText(origAddText);
                uiM.pushButton_excludeAdd -> setToolTip(origAddToolTip);
                uiM.pushButton_excludeAdd -> setIcon(QIcon(":/luckyPrefix/add.png"));
                uiM.pushButton_excludeRemove -> setText(origRemoveText);
                uiM.pushButton_excludeRemove -> setToolTip(origRemoveToolTip);
                uiM.pushButton_excludeRemove -> setIcon(QIcon(":/luckyPrefix/remove.png"));
                uiM.pushButton_editExclude -> setEnabled (TRUE);
                uiM.pushButton_moveUpExclude -> setEnabled (TRUE);
                uiM.pushButton_moveDownExclude -> setEnabled (TRUE);
                listItemEditMode = FALSE;   // set this bool var to FALSE - end of list edit mode
                return;
            }
            
            selected = uiM.listWidget_exclude -> currentRow();            //current list row number
            if (selected < 0)                            //if nothing is selected do nothing
                return;
            uiM.listWidget_exclude-> takeItem(selected);
            break;
        //include list remove button
        case 1:
            if (listItemEditMode)   // do not proceed further if this is just a cancel from list item edit mode
            {
                // set the gui back to its original form
                uiM.pushButton_includeAdd -> setText(origAddText);
                uiM.pushButton_includeAdd -> setToolTip(origAddToolTip);
                uiM.pushButton_includeAdd -> setIcon(QIcon(":/luckyPrefix/add.png"));
                uiM.pushButton_includeRemove -> setText(origRemoveText);
                uiM.pushButton_includeRemove -> setToolTip(origRemoveToolTip);
                uiM.pushButton_includeRemove -> setIcon(QIcon(":/luckyPrefix/remove.png"));
                uiM.pushButton_editInclude -> setEnabled (TRUE);
                uiM.pushButton_moveUpInclude -> setEnabled (TRUE);
                uiM.pushButton_moveDownInclude -> setEnabled (TRUE);
                listItemEditMode = FALSE;   // set this bool var to FALSE - end of list edit mode
                return;
            }
            
            selected = uiM.listWidget_include -> currentRow();            //current list row number
            if (selected < 0)                            //if nothing is selected do nothing
                return;
            uiM.listWidget_include-> takeItem(selected);
            disableExcludeTab();    // disable the exclude tab or not
            break;
        //options list remove button
        case 2:
            if (listItemEditMode)   // do not proceed further if this is just a cancel from list item edit mode
            {
                // set the gui back to its original form
                uiM.pushButton_optionsAdd -> setText(origAddText);
                uiM.pushButton_optionsAdd -> setToolTip(origAddToolTip);
                uiM.pushButton_optionsAdd -> setIcon(QIcon(":/luckyPrefix/add.png"));
                uiM.pushButton_optionsRemove -> setText(origRemoveText);
                uiM.pushButton_optionsRemove -> setToolTip(origRemoveToolTip);
                uiM.pushButton_optionsRemove -> setIcon(QIcon(":/luckyPrefix/remove.png"));
                uiM.pushButton_editOptions -> setEnabled (TRUE);
                uiM.pushButton_moveUpOptions -> setEnabled (TRUE);
                uiM.pushButton_moveDownOptions -> setEnabled (TRUE);
                listItemEditMode = FALSE;   // set this bool var to FALSE - end of list edit mode
                return;
            }
            
            selected = uiM.listWidget_options -> currentRow();            //current list row number
            if (selected < 0)                            //if nothing is selected do nothing
                return;
            uiM.listWidget_options-> takeItem(selected);
            break;
        //execute before list remove button
        case 3:
            if (listItemEditMode)   // do not proceed further if this is just a cancel from list item edit mode
            {
                // set the gui back to its original form
                uiM.pushButton_executeBeforeAdd -> setText(origAddText);
                uiM.pushButton_executeBeforeAdd -> setToolTip(origAddToolTip);
                uiM.pushButton_executeBeforeAdd -> setIcon(QIcon(":/luckyPrefix/add.png"));
                uiM.pushButton_executeBeforeRemove -> setText(origRemoveText);
                uiM.pushButton_executeBeforeRemove -> setToolTip(origRemoveToolTip);
                uiM.pushButton_executeBeforeRemove -> setIcon(QIcon(":/luckyPrefix/remove.png"));
                uiM.pushButton_editExecuteBefore -> setEnabled (TRUE);
                uiM.pushButton_moveUpExecuteBefore -> setEnabled (TRUE);
                uiM.pushButton_moveDownExecuteBefore -> setEnabled (TRUE);
                listItemEditMode = FALSE;   // set this bool var to FALSE - end of list edit mode
                return;
            }
            
            selected = uiM.listWidget_executeBefore  -> currentRow();        //current list row number
            if (selected < 0)                            //if nothing is selected do nothing
                return;
            uiM.listWidget_executeBefore -> takeItem(selected);
            break;
        //execute after list remove button
        case 4:
            if (listItemEditMode)   // do not proceed further if this is just a cancel from list item edit mode
            {
                // set the gui back to its original form
                uiM.pushButton_executeAfterAdd -> setText(origAddText);
                uiM.pushButton_executeAfterAdd -> setToolTip(origAddToolTip);
                uiM.pushButton_executeAfterAdd -> setIcon(QIcon(":/luckyPrefix/add.png"));
                uiM.pushButton_executeAfterRemove -> setText(origRemoveText);
                uiM.pushButton_executeAfterRemove -> setToolTip(origRemoveToolTip);
                uiM.pushButton_executeAfterRemove -> setIcon(QIcon(":/luckyPrefix/remove.png"));
                uiM.pushButton_editExecuteAfter -> setEnabled (TRUE);
                uiM.pushButton_moveUpExecuteAfter -> setEnabled (TRUE);
                uiM.pushButton_moveDownExecuteAfter -> setEnabled (TRUE);
                listItemEditMode = FALSE;   // set this bool var to FALSE - end of list edit mode
                return;
            }
    
            selected = uiM.listWidget_executeAfter -> currentRow();            //current list row number
            if (selected < 0)                            //if nothing is selected do nothing
                return;
            uiM.listWidget_executeAfter -> takeItem(selected);
            break;
    }

}

// List item edit button pressed=====================================================================================================
// Edits an item from the excluded,included,options or "also execute" list
void modifyDialog::editListItem(const int type)
{
    int selected;
    QString selectedText = "";
    switch (type)
    {
        //exclude list
        case 0: selected = uiM.listWidget_exclude -> currentRow();              //current list row number
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            listItemEditMode = TRUE;
            origAddText = uiM.pushButton_excludeAdd -> text();
            origAddToolTip = uiM.pushButton_excludeAdd -> toolTip();
            origRemoveText = uiM.pushButton_excludeRemove -> text();
            origRemoveToolTip = uiM.pushButton_excludeRemove -> toolTip();
            uiM.pushButton_excludeAdd -> setText(tr("done"));
            uiM.pushButton_excludeAdd -> setToolTip(tr("done editing"));
            uiM.pushButton_excludeAdd -> setIcon(QIcon(":/luckyPrefix/okay.png"));
            uiM.pushButton_excludeRemove -> setText(tr("cancel"));
            uiM.pushButton_excludeRemove -> setToolTip(tr("cancel editing"));
            uiM.pushButton_excludeRemove -> setIcon(QIcon(":/luckyPrefix/cancel.png"));
            
            uiM.pushButton_editExclude -> setEnabled (FALSE);
            uiM.pushButton_moveUpExclude -> setEnabled (FALSE);
            uiM.pushButton_moveDownExclude -> setEnabled (FALSE);
            
            selectedText = (uiM.listWidget_exclude -> currentItem()) -> text();  //current list item text
            uiM.lineEdit_excludeAdd -> setText (selectedText);
            uiM.lineEdit_excludeAdd -> setFocus();
            uiM.lineEdit_excludeAdd -> selectAll();
            break;
        //include list
        case 1: selected = uiM.listWidget_include -> currentRow();          //current list row number
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            listItemEditMode = TRUE;
            origAddText = uiM.pushButton_includeAdd -> text();
            origAddToolTip = uiM.pushButton_includeAdd -> toolTip();
            origRemoveText = uiM.pushButton_includeRemove -> text();
            origRemoveToolTip = uiM.pushButton_includeRemove -> toolTip();
            uiM.pushButton_includeAdd -> setText(tr("done"));
            uiM.pushButton_includeAdd -> setToolTip(tr("done editing"));
            uiM.pushButton_includeAdd -> setIcon(QIcon(":/luckyPrefix/okay.png"));
            uiM.pushButton_includeRemove -> setText(tr("cancel"));
            uiM.pushButton_includeRemove -> setToolTip(tr("cancel editing"));
            uiM.pushButton_includeRemove -> setIcon(QIcon(":/luckyPrefix/cancel.png"));
            
            uiM.pushButton_editInclude -> setEnabled (FALSE);
            uiM.pushButton_moveUpInclude -> setEnabled (FALSE);
            uiM.pushButton_moveDownInclude -> setEnabled (FALSE);
            
            selectedText = (uiM.listWidget_include -> currentItem()) -> text();  //current list item text
            uiM.lineEdit_includeAdd -> setText (selectedText);
            uiM.lineEdit_includeAdd -> setFocus();
            uiM.lineEdit_includeAdd -> selectAll();
            break;
        //options list
        case 2: selected = uiM.listWidget_options -> currentRow();          //current list row number
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            listItemEditMode = TRUE;
            origAddText = uiM.pushButton_optionsAdd -> text();
            origAddToolTip = uiM.pushButton_optionsAdd -> toolTip();
            origRemoveText = uiM.pushButton_optionsRemove -> text();
            origRemoveToolTip = uiM.pushButton_optionsRemove -> toolTip();
            uiM.pushButton_optionsAdd -> setText(tr("done"));
            uiM.pushButton_optionsAdd -> setToolTip(tr("done editing"));
            uiM.pushButton_optionsAdd -> setIcon(QIcon(":/luckyPrefix/okay.png"));
            uiM.pushButton_optionsRemove -> setText(tr("cancel"));
            uiM.pushButton_optionsRemove -> setToolTip(tr("cancel editing"));
            uiM.pushButton_optionsRemove -> setIcon(QIcon(":/luckyPrefix/cancel.png"));
            
            uiM.pushButton_editOptions -> setEnabled (FALSE);
            uiM.pushButton_moveUpOptions -> setEnabled (FALSE);
            uiM.pushButton_moveDownOptions -> setEnabled (FALSE);
            
            selectedText = (uiM.listWidget_options -> currentItem()) -> text();  //current list item text
            uiM.lineEdit_optionsAdd -> setText (selectedText);
            uiM.lineEdit_optionsAdd -> setFocus();
            uiM.lineEdit_optionsAdd -> selectAll();
            break;
        //execute before list
        case 3: selected = uiM.listWidget_executeBefore  -> currentRow();       //current list row number
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            listItemEditMode = TRUE;
            origAddText = uiM.pushButton_executeBeforeAdd -> text();
            origAddToolTip = uiM.pushButton_executeBeforeAdd -> toolTip();
            origRemoveText = uiM.pushButton_executeBeforeRemove -> text();
            origRemoveToolTip = uiM.pushButton_executeBeforeRemove -> toolTip();
            uiM.pushButton_executeBeforeAdd -> setText(tr("done"));
            uiM.pushButton_executeBeforeAdd -> setToolTip(tr("done editing"));
            uiM.pushButton_executeBeforeAdd -> setIcon(QIcon(":/luckyPrefix/okay.png"));
            uiM.pushButton_executeBeforeRemove -> setText(tr("cancel"));
            uiM.pushButton_executeBeforeRemove -> setToolTip(tr("cancel editing"));
            uiM.pushButton_executeBeforeRemove -> setIcon(QIcon(":/luckyPrefix/cancel.png"));
            
            uiM.pushButton_editExecuteBefore -> setEnabled (FALSE);
            uiM.pushButton_moveUpExecuteBefore -> setEnabled (FALSE);
            uiM.pushButton_moveDownExecuteBefore -> setEnabled (FALSE);
            
            selectedText = (uiM.listWidget_executeBefore -> currentItem()) -> text();  //current list item text
            alsoExecuteState = uiM.listWidget_executeBefore -> currentItem() -> checkState();   // current list item check state
            uiM.lineEdit_executeBeforeAdd -> setText (selectedText);
            uiM.lineEdit_executeBeforeAdd -> setFocus();
            uiM.lineEdit_executeBeforeAdd -> selectAll();
            break;
        //execute after
        case 4: selected = uiM.listWidget_executeAfter -> currentRow();         //current list row number
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            listItemEditMode = TRUE;
            origAddText = uiM.pushButton_executeAfterAdd -> text();
            origAddToolTip = uiM.pushButton_executeAfterAdd -> toolTip();
            origRemoveText = uiM.pushButton_executeAfterRemove -> text();
            origRemoveToolTip = uiM.pushButton_executeAfterRemove -> toolTip();
            uiM.pushButton_executeAfterAdd -> setText(tr("done"));
            uiM.pushButton_executeAfterAdd -> setToolTip(tr("done editing"));
            uiM.pushButton_executeAfterAdd -> setIcon(QIcon(":/luckyPrefix/okay.png"));
            uiM.pushButton_executeAfterRemove -> setText(tr("cancel"));
            uiM.pushButton_executeAfterRemove -> setToolTip(tr("cancel editing"));
            uiM.pushButton_executeAfterRemove -> setIcon(QIcon(":/luckyPrefix/cancel.png"));
            
            uiM.pushButton_editExecuteAfter -> setEnabled (FALSE);
            uiM.pushButton_moveUpExecuteAfter -> setEnabled (FALSE);
            uiM.pushButton_moveDownExecuteAfter -> setEnabled (FALSE);
            
            selectedText = (uiM.listWidget_executeAfter -> currentItem()) -> text();  //current list item text
            alsoExecuteState = uiM.listWidget_executeAfter -> currentItem() -> checkState();   // current list item check state
            uiM.lineEdit_executeAfterAdd -> setText (selectedText);
            uiM.lineEdit_executeAfterAdd -> setFocus();
            uiM.lineEdit_executeAfterAdd -> selectAll();
            break;
    }
}

// List item move up button pressed=====================================================================================================
// Moves an item within list, up one position
void modifyDialog::moveListItemUp(const int type)
{
    int selected;
    QListWidgetItem *tempItem;
    switch (type)
    {
        //exclude list
        case 0: selected = uiM.listWidget_exclude -> currentRow();          //current list row number
            if (selected < 0)                         //if nothing is selected do nothing
                return;
            if (selected > 0)                       //if this is not the first row proceed with swapping items
            {
                tempItem = uiM.listWidget_exclude -> takeItem(selected);
                uiM.listWidget_exclude -> insertItem (selected-1, tempItem);
                uiM.listWidget_exclude -> setCurrentRow (selected-1);
            }
            break;
        //include list
        case 1: selected = uiM.listWidget_include -> currentRow();          //current list row number
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            if (selected > 0)                       //if this is not the first row proceed with swapping items
            {
                tempItem = uiM.listWidget_include -> takeItem(selected);
                uiM.listWidget_include -> insertItem (selected-1, tempItem);
                uiM.listWidget_include -> setCurrentRow (selected-1);
            }
            break;
        //options list
        case 2: selected = uiM.listWidget_options -> currentRow();          //current list row number
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            if (selected > 0)                       //if this is not the first row proceed with swapping items
            {
                tempItem = uiM.listWidget_options -> takeItem(selected);
                uiM.listWidget_options -> insertItem (selected-1, tempItem);
                uiM.listWidget_options -> setCurrentRow (selected-1);
            }
            break;
        //execute before
        case 3: selected = uiM.listWidget_executeBefore  -> currentRow();   //current list row number
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            if (selected > 0)                       //if this is not the first row proceed with swapping items
            {
                tempItem = uiM.listWidget_executeBefore -> takeItem(selected);
                uiM.listWidget_executeBefore -> insertItem (selected-1, tempItem);
                uiM.listWidget_executeBefore -> setCurrentRow (selected-1);
            }
            break;
        //execute after
        case 4: selected = uiM.listWidget_executeAfter -> currentRow();         //current list row number
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            if (selected > 0)                       //if this is not the first row proceed with swapping items
            {
                tempItem = uiM.listWidget_executeAfter -> takeItem(selected);
                uiM.listWidget_executeAfter -> insertItem (selected-1, tempItem);
                uiM.listWidget_executeAfter -> setCurrentRow (selected-1);
            }
            break;
    }

}

// List item move down button pressed=====================================================================================================
// Moves an item within list, down one position
void modifyDialog::moveListItemDown(const int type)
{
    int selected, totalListItems;
    QListWidgetItem *tempItem;
    switch (type)
    {
        //exclude list
        case 0: selected = uiM.listWidget_exclude -> currentRow();          //current list row number
            totalListItems = uiM.listWidget_exclude -> count();             //total no of list items
            if (selected < 0)                         //if nothing is selected do nothing
                return;
            if (selected < totalListItems-1)                       //if this is not the last row proceed with swapping items
            {
                tempItem = uiM.listWidget_exclude -> takeItem(selected);
                uiM.listWidget_exclude -> insertItem (selected+1, tempItem);
                uiM.listWidget_exclude -> setCurrentRow (selected+1);
            }
            break;
        //include list
        case 1: selected = uiM.listWidget_include -> currentRow();          //current list row number
            totalListItems = uiM.listWidget_include -> count();             //total no of list items
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            if (selected < totalListItems-1)                       //if this is not the last row proceed with swapping items
            {
                tempItem = uiM.listWidget_include -> takeItem(selected);
                uiM.listWidget_include -> insertItem (selected+1, tempItem);
                uiM.listWidget_include -> setCurrentRow (selected+1);
            }
            break;
        //options list
        case 2: selected = uiM.listWidget_options -> currentRow();          //current list row number
            totalListItems = uiM.listWidget_options -> count();             //total no of list items
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            if (selected < totalListItems-1)                       //if this is not the last row proceed with swapping items
            {
                tempItem = uiM.listWidget_options -> takeItem(selected);
                uiM.listWidget_options -> insertItem (selected+1, tempItem);
                uiM.listWidget_options -> setCurrentRow (selected+1);
            }
            break;
        //execute before
        case 3: selected = uiM.listWidget_executeBefore  -> currentRow();       //current list row number
            totalListItems = uiM.listWidget_executeBefore -> count();             //total no of list items
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            if (selected < totalListItems-1)                       //if this is not the last row proceed with swapping items
            {
                tempItem = uiM.listWidget_executeBefore -> takeItem(selected);
                uiM.listWidget_executeBefore -> insertItem (selected+1, tempItem);
                uiM.listWidget_executeBefore -> setCurrentRow (selected+1);
            }
            break;
        //execute after
        case 4: selected = uiM.listWidget_executeAfter -> currentRow();         //current list row number
            totalListItems = uiM.listWidget_executeAfter -> count();             //total no of list items
            if (selected < 0)                           //if nothing is selected do nothing
                return;
            if (selected < totalListItems-1)                       //if this is not the last row proceed with swapping items
            {
                tempItem = uiM.listWidget_executeAfter -> takeItem(selected);
                uiM.listWidget_executeAfter -> insertItem (selected+1, tempItem);
                uiM.listWidget_executeAfter -> setCurrentRow (selected+1);
            }
            break;
    }

}

// Task type combobox changed=====================================================================================================
// Enable/disable the "keep snapshots" spinbox
void modifyDialog::TaskTypeChanged(int type)
{
    if (type == 1)
    {
        uiM.label_snapshotsKeep -> setVisible(FALSE);
        uiM.spinBox_snapshotsKeep -> setVisible(FALSE);
        uiM.checkBox_backupContents -> setVisible(FALSE);
        uiM.checkBox_deleteAfter -> setEnabled (FALSE);
    }
    else
    {
        uiM.label_snapshotsKeep -> setVisible(TRUE);
        uiM.spinBox_snapshotsKeep -> setVisible(TRUE);
        uiM.checkBox_backupContents -> setVisible(TRUE);
        uiM.checkBox_deleteAfter -> setEnabled (TRUE);
    }
}
// Include tab stuff  changed=====================================================================================================
// Enable/disable the "exclude" tab
void modifyDialog::disableExcludeTab()
{
    bool enableIt = TRUE;
    
    // conditions to disable the exclude tab
    if ( ( (uiM.listWidget_include -> count() > 0) || 
       ((uiM.checkBox_includeFile->isChecked()) && ((uiM.lineEdit_includeFile->text()).size() >0)) ) &&
       (uiM.radioButton_includeOnly -> isChecked()) )
       
       enableIt = FALSE;

    uiM.toolBox_exclude -> setEnabled (enableIt);
}

//===================================================================================================================================================
//------------------------------------------------------------------FUNCTIONS------------------------------------------------------------------------
//===================================================================================================================================================

// fillOperationArray =====================================================================================================
//function to fill the data of an operation array item from the window fields
operation *modifyDialog::fillOperationArray()
{
    operation *pTask = new operation;
    
    //Before doing any changes, inherit last execution time & error as well as snapshots list from the existing task
    //if this is not a new task (modify task. NOT new/duplicate/restore task)
    if (!newTaskThisIs)
    {
        pTask -> SetLastExecutionTime (Operation[ArrayPosition] -> GetLastExecutionTime());
        pTask -> SetLastExecutionErrors (Operation[ArrayPosition] -> GetLastExecutionErrors());
        pTask -> SetSnapshotsList (Operation[ArrayPosition] -> GetSnapshotsList());
    }
    
    //set operation name --------------------------------------------------------------------------------------------------------
    pTask -> SetName        ( uiM.lineEdit_name -> text() );

    // set connection ----------------------------------------------------------------------------
    pTask -> SetConnectRestore    ("");
    
    //set task description --------------------------------------------------------------------------------------------------------
    pTask -> SetDescription ( uiM.textEdit_Description -> toPlainText() );

    // set operation type ------------------------------------------------------------------------------
    if (uiM.comboBox_Type -> currentIndex()==0)
    {
        if (uiM.checkBox_backupContents -> isChecked())
        {
            pTask -> SetTypeDirContents    ( TRUE );
            pTask -> SetTypeDirName        ( FALSE );
            pTask -> SetTypeSync        ( FALSE );
        }
        else
        {
            pTask -> SetTypeDirContents    ( FALSE );
            pTask -> SetTypeDirName        ( TRUE );
            pTask -> SetTypeSync        ( FALSE );
        }
    }
    if (uiM.comboBox_Type -> currentIndex()==1)
    {
        pTask -> SetTypeDirContents    ( FALSE );
        pTask -> SetTypeDirName        ( FALSE );
        pTask -> SetTypeSync        ( TRUE );
        uiM.spinBox_snapshotsKeep -> setValue (1);    // also set the keep snapshots spinbox to "1" if it is a sync task
    }
    
    // also set the keep snapshots spinbox to "1" if remote destination is used
    // Commended bacause remote snapshots are now supported - safely delete this
    //if ( (uiM.groupBox_remote -> isChecked()) && (uiM.radioButton_remoteDestination -> isChecked()) )
    //    uiM.spinBox_snapshotsKeep -> setValue (1);

    //set source & destination ------------------------------------------------------------------------------------------------
    pTask -> SetSource        ( uiM.lineEdit_source -> text() );
    pTask -> SetDestination        ( uiM.lineEdit_destination -> text() );

    //set number of snapshots ------------------------------------------------------------------------------------------------
    pTask -> SetKeepSnapshots    ( uiM.spinBox_snapshotsKeep -> value() );
    
    //set exclude groupbox & all the info in there -----------------------------------------------------------------------------
    pTask -> SetExcludeTemp        ( uiM.checkBox_excludeTemp -> isChecked() );
    pTask -> SetExcludeFromFile    ( uiM.checkBox_excludeFile -> isChecked() );
    pTask -> SetExcludeFile        ( uiM.lineEdit_excludeFile -> text() );
    pTask -> SetExcludeCache    ( uiM.checkBox_excludeCache -> isChecked() );
    pTask -> SetExcludeBackup    ( uiM.checkBox_excludeBackup -> isChecked() );
    pTask -> SetExcludeMount    ( uiM.checkBox_excludeMount -> isChecked() );
    pTask -> SetExcludeLostFound    ( uiM.checkBox_excludeLostFound -> isChecked() );
    pTask -> SetExcludeSystem    ( uiM.checkBox_excludeSystem -> isChecked() );
    pTask -> SetExcludeTrash    ( uiM.checkBox_excludeTrash -> isChecked() );
    pTask -> SetExcludeGVFS     ( uiM.checkBox_excludeGVFS -> isChecked() );

    count = 0;    //read exclude list one by one
    while ( count < (uiM.listWidget_exclude -> count()) )
    {
        uiM.listWidget_exclude -> setCurrentRow(count);
        pTask -> AddExcludeListItem((uiM.listWidget_exclude -> currentItem()) -> text());
        count++;
    }
    pTask -> SetExclude ();

    //set include groupbox & all the info in there -----------------------------------------------------------------------------
    pTask -> SetIncludeFromFile    ( uiM.checkBox_includeFile -> isChecked() );
    pTask -> SetIncludeFile        ( uiM.lineEdit_includeFile -> text() );
    pTask -> SetIncludeModeNormal  ( uiM.radioButton_includeNormal -> isChecked() );
    count = 0;    //read include list one by one
    while ( count < (uiM.listWidget_include -> count()) )
    {
        uiM.listWidget_include -> setCurrentRow(count);
        pTask -> AddIncludeListItem((uiM.listWidget_include -> currentItem()) -> text());
        count++;
    }
    pTask -> SetInclude();

    //set remote groupbox & all the info in there -----------------------------------------------------------------------------
    pTask -> SetRemote              ( uiM.groupBox_remote -> isChecked() );
    pTask -> SetRemoteModule        ( uiM.checkBox_remoteModule -> isChecked() );
    pTask -> SetRemoteDestination   ( uiM.radioButton_remoteDestination -> isChecked() );
    pTask -> SetRemoteSource        ( uiM.radioButton_remoteSource -> isChecked() );
    pTask -> SetRemoteHost          ( uiM.lineEdit_remoteHost -> text() );
    pTask -> SetRemoteUser          ( uiM.lineEdit_remoteUser -> text() );
    pTask -> SetRemotePassword      ( uiM.lineEdit_rsyncPassword -> text() );
    pTask -> SetRemoteSSH           ( uiM.checkBox_ssh -> isChecked() );
    pTask -> SetRemoteSSHPassword   ( uiM.lineEdit_sshPassword -> text() );
    pTask -> SetRemoteSSHPort       ( (uiM.lineEdit_sshPort -> text()).toInt() );
    pTask -> SetRemoteSSHPasswordStr( uiM.lineEdit_sshPasswordStr -> text());
    pTask -> SetRemoteSSHOptions    ( uiM.lineEdit_sshOptions -> text());
    
    //set rsync options checkboxes -----------------------------------------------------------------------------------------------
    pTask -> SetOptionsUpdate       ( uiM.checkBox_update -> isChecked() );
    pTask -> SetOptionsOwnership    ( uiM.checkBox_ownership -> isChecked() );
    pTask -> SetOptionsSymlinks     ( uiM.checkBox_symlinks -> isChecked() );
    pTask -> SetOptionsPermissions  ( uiM.checkBox_permissions -> isChecked() );
    pTask -> SetOptionsDevices      ( uiM.checkBox_devices -> isChecked() );
    pTask -> SetOptionsCVS          ( uiM.checkBox_cvs -> isChecked() );
    pTask -> SetOptionsHardLinks    ( uiM.checkBox_hardLinks -> isChecked() );
    pTask -> SetOptionsFATntfs      ( uiM.checkBox_FATntfs -> isChecked() );
    pTask -> SetOptionsDelete       ( uiM.checkBox_deleteAfter -> isChecked() );
    pTask -> SetOptionsRecurse      ( uiM.checkBox_recurse -> isChecked() );
    pTask -> SetOptionsSuper        ( uiM.checkBox_super -> isChecked() );
    pTask -> SetOptionsNumericIDs   ( uiM.checkBox_numericIDs -> isChecked() );
    // windows related rsync options
    pTask -> SetOptionsRestorent    ( uiM.checkBox_restorent -> isChecked() );
    pTask -> SetOptionsVss          ( uiM.checkBox_vss -> isChecked() );
    pTask -> SetTempPath(tempDirPath);
    pTask -> SetLuckyBackupDir      (luckyBackupDir);
    pTask -> SetVshadowDir          (vshadowDir);
    pTask -> SetDosdevCommand       (dosdevCommand);
    pTask -> SetCygpathCommand      (cygpathCommand);
    pTask -> SetRsyncCommand        (rsyncCommandPath);
    pTask -> SetSshCommand          (sshCommandPath);
    
    count = 0;    //read options list one by one
    while ( count < (uiM.listWidget_options -> count()) )
    {
        uiM.listWidget_options -> setCurrentRow(count);
        pTask -> AddOptionsListItem((uiM.listWidget_options -> currentItem()) -> text());
        count++;
    }
    count = 0;    //read execute before list one by one
    bool tempState;
    while ( count < (uiM.listWidget_executeBefore -> count()) )
    {
        uiM.listWidget_executeBefore -> setCurrentRow(count);
        pTask -> AddExecuteBeforeListItem((uiM.listWidget_executeBefore -> currentItem()) -> text());
        if ((uiM.listWidget_executeBefore -> currentItem()) -> checkState() == Qt::Checked)
            tempState = TRUE;   else tempState = FALSE;
        pTask -> AddExecuteBeforeListItemState(tempState);
        count++;
    }
    count = 0;    //read execute after list one by one
    while ( count < (uiM.listWidget_executeAfter -> count()) )
    {
        uiM.listWidget_executeAfter -> setCurrentRow(count);
        pTask -> AddExecuteAfterListItem((uiM.listWidget_executeAfter -> currentItem()) -> text());
        if ((uiM.listWidget_executeAfter -> currentItem()) -> checkState() == Qt::Checked)
            tempState = TRUE;   else tempState = FALSE;
        pTask -> AddExecuteAfterListItemState(tempState);
        count++;
    }
    pTask -> SetByPassWARNING   ( uiM.checkBox_byPassWarning -> isChecked() );
    pTask -> SetRepeatOnFail    ( uiM.spinBox_repeatOnFail -> value() );

    //append aguments -----------------------------------------------------------------------------------------------------------
    pTask -> SetArgs ( AppendArguments(pTask) );

    return pTask;
}

// fillModifyWindow =======================================================================================================
//function to fill the window fields from the data of an operation array item
void modifyDialog::fillModifyWindow(operation *pTask)
{
    uiM.lineEdit_name         -> setText    (pTask -> GetName() );
    
    uiM.textEdit_Description     -> setPlainText    (pTask    -> GetDescription() );

    if (pTask -> GetTypeDirContents())
    {
        uiM.comboBox_Type -> setCurrentIndex(0);
        uiM.checkBox_backupContents -> setCheckState(Qt::Checked);
        uiM.checkBox_deleteAfter -> setEnabled (TRUE);
    }
    if (pTask -> GetTypeDirName())
    {
        uiM.comboBox_Type -> setCurrentIndex(0);
        uiM.checkBox_backupContents -> setCheckState(Qt::Unchecked);
        uiM.checkBox_deleteAfter -> setEnabled (TRUE);
    }
    if (pTask -> GetTypeSync())
    {
        uiM.comboBox_Type -> setCurrentIndex(1);
        uiM.checkBox_deleteAfter -> setEnabled (FALSE);
    }

    uiM.lineEdit_source             -> setText    (pTask -> GetSource() );
    uiM.lineEdit_destination        -> setText    (pTask -> GetDestination() );
    
    uiM.spinBox_snapshotsKeep       -> setValue    (pTask -> GetKeepSnapshots());

    uiM.checkBox_excludeFile        -> setChecked    (pTask -> GetExcludeFromFile() );
    uiM.lineEdit_excludeFile        -> setText    (pTask -> GetExcludeFile() );
    uiM.checkBox_excludeTemp        -> setChecked    (pTask -> GetExcludeTemp() );
    uiM.checkBox_excludeCache       -> setChecked    (pTask -> GetExcludeCache() );
    uiM.checkBox_excludeBackup      -> setChecked    (pTask -> GetExcludeBackup() );
    uiM.checkBox_excludeMount       -> setChecked    (pTask -> GetExcludeMount() );
    uiM.checkBox_excludeLostFound   -> setChecked    (pTask -> GetExcludeLostFound() );
    uiM.checkBox_excludeSystem      -> setChecked    (pTask -> GetExcludeSystem() );
    uiM.checkBox_excludeTrash       -> setChecked    (pTask -> GetExcludeTrash() );
    uiM.checkBox_excludeGVFS        -> setChecked    (pTask -> GetExcludeGVFS() );
    count=0;
    while ( count < (pTask -> GetExcludeListSize()) )
    {
        uiM.listWidget_exclude      -> addItem    (pTask -> GetExcludeListItem(count));
        count++;
    }

    uiM.checkBox_includeFile        -> setChecked    (pTask -> GetIncludeFromFile() );
    uiM.radioButton_includeNormal     -> setChecked    (pTask -> GetIncludeModeNormal() );
    uiM.radioButton_includeOnly     -> setChecked    (!pTask -> GetIncludeModeNormal() );
    uiM.lineEdit_includeFile        -> setText        (pTask -> GetIncludeFile() );
    count=0;
    while ( count < (pTask -> GetIncludeListSize()) )
    {
        uiM.listWidget_include      -> addItem    (pTask -> GetIncludeListItem(count));
        count++;
    }

    uiM.groupBox_remote             -> setChecked    (pTask -> GetRemote() );
    uiM.checkBox_remoteModule       -> setChecked    (pTask -> GetRemoteModule() );
    uiM.radioButton_remoteDestination-> setChecked    (pTask -> GetRemoteDestination() );
    uiM.radioButton_remoteSource    -> setChecked    (pTask -> GetRemoteSource() );
    uiM.lineEdit_remoteHost         -> setText    (pTask -> GetRemoteHost() );
    uiM.lineEdit_remoteUser         -> setText    (pTask -> GetRemoteUser() );
    uiM.lineEdit_rsyncPassword      -> setText    (pTask -> GetRemotePassword() );
    uiM.checkBox_ssh                -> setChecked    (pTask -> GetRemoteSSH() );
    uiM.lineEdit_sshPassword        -> setText    (pTask -> GetRemoteSSHPassword() );
    uiM.lineEdit_sshPasswordStr     -> setText    (pTask -> GetRemoteSSHPasswordStr() );
    uiM.lineEdit_sshOptions         -> setText    (pTask -> GetRemoteSSHOptions() );
    if (pTask -> GetRemoteSSHPort() == 0)
        uiM.lineEdit_sshPort        -> setText    ("");
    else
        uiM.lineEdit_sshPort        -> setText    (countStr.setNum(pTask -> GetRemoteSSHPort()) );

    uiM.checkBox_update             -> setChecked    (pTask -> GetOptionsUpdate() );
    uiM.checkBox_deleteAfter        -> setChecked    (pTask -> GetOptionsDelete() );
    uiM.checkBox_recurse            -> setChecked    (pTask -> GetOptionsRecurse() );
    uiM.checkBox_ownership          -> setChecked    (pTask -> GetOptionsOwnership() );
    uiM.checkBox_symlinks           -> setChecked    (pTask -> GetOptionsSymlinks() );
    uiM.checkBox_permissions        -> setChecked    (pTask -> GetOptionsPermissions() );
    uiM.checkBox_devices            -> setChecked    (pTask -> GetOptionsDevices() );
    uiM.checkBox_cvs                -> setChecked    (pTask -> GetOptionsCVS() );
    uiM.checkBox_hardLinks          -> setChecked    (pTask -> GetOptionsHardLinks() );
    uiM.checkBox_FATntfs            -> setChecked    (pTask -> GetOptionsFATntfs() );
    uiM.checkBox_super              -> setChecked    (pTask -> GetOptionsSuper() );
    uiM.checkBox_numericIDs         -> setChecked    (pTask -> GetOptionsNumericIDs() );
    
    uiM.checkBox_vss                -> setChecked    (pTask -> GetOptionsVss() );
    uiM.checkBox_restorent          -> setChecked    (pTask -> GetOptionsRestorent() );
    
    count=0;
    while ( count < (pTask -> GetOptionsListSize()) )
    {
        uiM.listWidget_options    -> addItem    (pTask -> GetOptionsListItem(count));
        count++;
    }
    count=0;
    while ( count < (pTask -> GetExecuteBeforeListSize()) )
    {
        uiM.listWidget_executeBefore -> addItem    (pTask -> GetExecuteBeforeListItem(count));
        uiM.listWidget_executeBefore -> setCurrentRow(uiM.listWidget_executeBefore -> count()-1);
        uiM.listWidget_executeBefore -> currentItem() -> setToolTip (alsoExecuteTooltip);
        if (pTask -> GetExecuteBeforeListItemState(count) == TRUE)
            uiM.listWidget_executeBefore -> currentItem() -> setCheckState(Qt::Checked);
        else
            uiM.listWidget_executeBefore -> currentItem() -> setCheckState(Qt::Unchecked);
        count++;
    }
    count=0;
    while ( count < (pTask -> GetExecuteAfterListSize()) )
    {
        uiM.listWidget_executeAfter -> addItem    (pTask -> GetExecuteAfterListItem(count));
        uiM.listWidget_executeAfter -> setCurrentRow(uiM.listWidget_executeAfter -> count()-1);
        uiM.listWidget_executeAfter -> currentItem() -> setToolTip (alsoExecuteTooltip);
        if (pTask -> GetExecuteAfterListItemState(count) == TRUE)
            uiM.listWidget_executeAfter -> currentItem() -> setCheckState(Qt::Checked);
        else
            uiM.listWidget_executeAfter -> currentItem() -> setCheckState(Qt::Unchecked);
        count++;
    }
    uiM.checkBox_byPassWarning      -> setChecked   ( pTask -> GetByPassWARNING() );
    uiM.spinBox_repeatOnFail        -> setValue     ( pTask -> GetRepeatOnFail() );
}

// modifyTrailing ===========================================================================================================
// adds or removes a trailing "/" at the source & destination directory
void modifyDialog::modifyTrailing()
{   
    // SLASH is "/" for *nix and windows and "\\" for OS2
    
    QString sourceDir   = uiM.lineEdit_source -> text();
    QString destDir     = uiM.lineEdit_destination -> text();
    
    // Check if a drive letter is declared at OS/2 or win (eg c:) and add a trailing slash
    if (notXnixRunning)
    {
        if (sourceDir.endsWith(":"))    sourceDir.append(SLASH);
        if (destDir.endsWith(":"))      destDir.append(SLASH);
    }

    //Directory by contents - trailing slash at source & dest paths
    if ((uiM.comboBox_Type -> currentIndex()==0) && (uiM.checkBox_backupContents -> isChecked()))
    {
        if ( (!sourceDir.endsWith(XnixSLASH)) && (!sourceDir.endsWith(SLASH)) && (sourceDir != ""))
        {
            if (uiM.groupBox_remote -> isChecked() && uiM.radioButton_remoteSource -> isChecked())
                sourceDir.append(XnixSLASH);
            else
                sourceDir.append(SLASH);
        }
        if ( (!destDir.endsWith(XnixSLASH)) &&(!destDir.endsWith(SLASH)) && (destDir != ""))
        {
            if (uiM.groupBox_remote -> isChecked() && uiM.radioButton_remoteDestination -> isChecked())
                destDir.append(XnixSLASH);
            else
                destDir.append(SLASH);
        }
    }

    //Directory by name - trailing slash only at  dest path not source
    if ((uiM.comboBox_Type -> currentIndex()==0) && (!uiM.checkBox_backupContents -> isChecked()))
    {
        if (notXnixRunning) //OS2 & win
        {
            if ( (sourceDir.endsWith(SLASH)) && (!sourceDir.endsWith(":"+SLASH)) )      sourceDir.chop(1);
            if ( (!destDir.endsWith(XnixSLASH)) && (!destDir.endsWith(SLASH)) && (destDir != "") )
            {
                if (uiM.groupBox_remote -> isChecked() && uiM.radioButton_remoteDestination -> isChecked())
                    destDir.append(XnixSLASH);
                else
                    destDir.append(SLASH);
            }
        }
        else        //linux-unix
        {
            if ( (sourceDir.endsWith(SLASH)) && (sourceDir != SLASH) )            sourceDir.chop(1);
            if ( (!destDir.endsWith(SLASH)) && (destDir != "") )                  destDir.append(SLASH);
        }
    }

    if (uiM.comboBox_Type -> currentIndex()==1)        //sync Directories - both paths have to have a trailing slash
    {
       if ((!sourceDir.endsWith(XnixSLASH)) && (!sourceDir.endsWith(SLASH)) && (sourceDir != ""))
       {
            if (uiM.groupBox_remote -> isChecked() && uiM.radioButton_remoteSource -> isChecked())
                sourceDir.append(XnixSLASH);
            else
                sourceDir.append(SLASH);
        }
        if ( (!destDir.endsWith(XnixSLASH)) &&(!destDir.endsWith(SLASH)) && (destDir != ""))
        {
            if (uiM.groupBox_remote -> isChecked() && uiM.radioButton_remoteDestination -> isChecked())
                destDir.append(XnixSLASH);
            else
                destDir.append(SLASH);
        }
        
        uiM.checkBox_deleteAfter    -> setChecked    (FALSE);
        uiM.checkBox_update         -> setChecked    (TRUE);
        uiM.checkBox_ownership      -> setChecked    (TRUE);
        uiM.checkBox_permissions    -> setChecked    (TRUE);
    }
    
    /*if (WINrunning)     // some more adjustments for windows when the user wants to declare directly paths with "/" instead of "\" (normally for remote)
    {      
        if (sourceDir.contains("/"))    sourceDir.replace(SLASH,"/");
        if (sourceDir.endsWith("//"))   sourceDir.chop(1);
        if (destDir.contains("/"))      destDir.replace(SLASH,"/");
        if (destDir.endsWith("//"))     destDir.chop(1);
    }*/
    
    uiM.lineEdit_source -> setText(sourceDir);
    uiM.lineEdit_destination -> setText(destDir);
}

// modifyOS2Slashes ===========================================================================================================
// function to change / to \ for OS2 (normaly when file dialog is used)
QString modifyDialog::modifyOS2Slashes(QString pathToModify)
{    
    if ( (notXnixRunning) && !pathToModify.startsWith("/") )
        pathToModify.replace("/",SLASH);
    
    return pathToModify;
}


// stripInvalidCharacters =============================================================================================================================
// Replaces all invalid filename characters from a QString with "-"
QString modifyDialog::stripInvalidCharacters(QString stringToStrip)
{
    QString stripedString = stringToStrip;
    QStringList invalidChars;
    invalidChars << "/" << "\\" << ":" << "*" << "?" << "\"" << "<" << ">" << "|";
    
    foreach (QString charToRemove, invalidChars)
        stripedString.replace(charToRemove, "", Qt::CaseSensitive);

    return stripedString;
}
// end of modifyDialog.cpp ---------------------------------------------------------------------------

