/* ---------------------------------- winDialog.cpp --------------------------------------------------------------------------
Class to display a dialog and declare rsync and ssh paths

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
last modified      : 13 Jan 2013

===============================================================================================================================
===============================================================================================================================
*/

#include "winDialog.h"
#include "qdirdialog.h"
#include <QCompleter>
#include <QDirModel>

// class winDialog Constructor=================================================================================================
// Displays a simple dialog with text info, ok-cancel buttons and lineEdits for user input
winDialog::winDialog (QWidget *parent) : QDialog (parent)
{
    uiD.setupUi(this);
    
    uiD.lineEdit_rsyncPath -> setText(rsyncCommandPath);
    uiD.lineEdit_sshPath -> setText(sshCommandPath);
    uiD.lineEdit_cygpath -> setText(cygpathCommand);
    uiD.lineEdit_dosdev -> setText(dosdevCommand);
    uiD.lineEdit_vshadow -> setText(vshadowDir);
    uiD.lineEdit_tempdir -> setText(tempDirPath);
    uiD.lineEdit_appdir-> setText(luckyBackupDir);
    
    
    //connect okay & cancel pushButton SLOTs ----------------
    connect ( uiD.pushButton_ok, SIGNAL( clicked() ), this, SLOT( okay() ) );
    connect ( uiD.pushButton_cancel, SIGNAL( clicked() ), this, SLOT( cancel() ) );

    //Connect all toolButtons with the browse SLOT
    //Map all the toolButton signals and transmit a different integer depending on the toolbutton
    QSignalMapper *signalMapper = new QSignalMapper(this);
    signalMapper ->    setMapping ( uiD.toolButton_rsync, 0 );
    connect (uiD.toolButton_rsync, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiD.toolButton_ssh, 1 );
    connect (uiD.toolButton_ssh, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiD.toolButton_cygpath, 2 );
    connect (uiD.toolButton_cygpath, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiD.toolButton_dosdev, 3 );
    connect (uiD.toolButton_dosdev, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiD.toolButton_vshadow, 4 );
    connect (uiD.toolButton_vshadow, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiD.toolButton_tempdir, 5 );
    connect (uiD.toolButton_tempdir, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->    setMapping ( uiD.toolButton_appdir, 6 );
    connect (uiD.toolButton_appdir, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    connect(signalMapper, SIGNAL(mapped( const int)), this, SLOT( browse( const int) )  );
    
    //Connect all toolButtons with the useDefault SLOT
    //Map all the toolButton signals and transmit a different integer depending on the toolbutton
    QSignalMapper *signalMapper2 = new QSignalMapper(this);
    signalMapper2 ->    setMapping ( uiD.toolButton_defaultRsync, 0 );
    connect (uiD.toolButton_defaultRsync, SIGNAL (clicked() ), signalMapper2 , SLOT (map()));
    signalMapper2 ->    setMapping ( uiD.toolButton_defaultSsh, 1 );
    connect (uiD.toolButton_defaultSsh, SIGNAL (clicked() ), signalMapper2 , SLOT (map()));
    signalMapper2 ->    setMapping ( uiD.toolButton_defaultCygpath, 2 );
    connect (uiD.toolButton_defaultCygpath, SIGNAL (clicked() ), signalMapper2 , SLOT (map()));
    signalMapper2 ->    setMapping ( uiD.toolButton_defaultDosdev, 3 );
    connect (uiD.toolButton_defaultDosdev, SIGNAL (clicked() ), signalMapper2 , SLOT (map()));
    signalMapper2 ->    setMapping ( uiD.toolButton_defaultVshadow, 4 );
    connect (uiD.toolButton_defaultVshadow, SIGNAL (clicked() ), signalMapper2 , SLOT (map()));
    signalMapper2 ->    setMapping ( uiD.toolButton_defaultTempdir, 5 );
    connect (uiD.toolButton_defaultTempdir, SIGNAL (clicked() ), signalMapper2 , SLOT (map()));
    signalMapper2 ->    setMapping ( uiD.toolButton_defaultAppdir, 6 );
    connect (uiD.toolButton_defaultAppdir, SIGNAL (clicked() ), signalMapper2 , SLOT (map()));
    connect(signalMapper2, SIGNAL(mapped( const int)), this, SLOT( useDefault( const int) )  );
    
    //initialize a completer for the lineEdits
    QCompleter *completer = new QCompleter(this);
    completer                       -> setModel(new QDirModel(completer));
    uiD.lineEdit_rsyncPath          -> setCompleter(completer);
    uiD.lineEdit_sshPath            -> setCompleter(completer);
    uiD.lineEdit_cygpath            -> setCompleter(completer);
    uiD.lineEdit_dosdev             -> setCompleter(completer);
    uiD.lineEdit_vshadow            -> setCompleter(completer);
    uiD.lineEdit_tempdir            -> setCompleter(completer);
    uiD.lineEdit_appdir             -> setCompleter(completer);
}


// --------------------------------okay pressed------------------------------------------------
void winDialog::okay()
{
    rsyncCommandPath    = uiD.lineEdit_rsyncPath -> text();                
    sshCommandPath      = uiD.lineEdit_sshPath -> text();
    cygpathCommand      = uiD.lineEdit_cygpath -> text();
    dosdevCommand       = uiD.lineEdit_dosdev -> text();
    vshadowDir          = uiD.lineEdit_vshadow -> text();
    tempDirPath         = uiD.lineEdit_tempdir -> text();
    luckyBackupDir      =  uiD.lineEdit_appdir -> text();
//    if (!vshadowDir.endsWith(SLASH))
//      vshadowDir=vshadowDir+SLASH;
//    if (!tempDirPath.endsWith(SLASH))
//      tempDirPath=tempDirPath+SLASH;
    if (!luckyBackupDir.endsWith(SLASH))
        luckyBackupDir=luckyBackupDir+SLASH;
    setAppDir(luckyBackupDir);
    
    close();
}

// --------------------------------cancel pressed------------------------------------------------
void winDialog::cancel()
{
    close();
}

void winDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
}

// browse button pressed=====================================================================================================
//opens a QFileDialog to browse for files/folders locally
void winDialog::browse(const int type)
{
    QString newLineEdit;
    QDirDialog* fd;
    
    switch (type)
    {
        //rsync browse button
        case 0:    newLineEdit = QFileDialog::getOpenFileName (this, tr("Select rsync command",
            "file selection dialog title"),uiD.lineEdit_rsyncPath -> text(),tr("Executable Files (*.exe)"));
            if (newLineEdit != "")    //if something is selected indeed
                uiD.lineEdit_rsyncPath  -> setText(modifySlashes(newLineEdit));
            break;
        //ssh browse button
        case 1: newLineEdit = QFileDialog::getOpenFileName (this, tr("Select ssh command",
            "file selection dialog title"),uiD.lineEdit_sshPath -> text(),tr("Executable Files (*.exe)"));
            if (newLineEdit != "")    //if something is selected indeed
                uiD.lineEdit_sshPath -> setText(modifySlashes(newLineEdit));
            break;
        //cygpath browse button
        case 2:    newLineEdit = QFileDialog::getOpenFileName (this, tr("Select cygpath command",
            "file selection dialog title"),uiD.lineEdit_cygpath -> text(),tr("Executable Files (*.exe)"));
            if (newLineEdit != "")    //if something is selected indeed
                uiD.lineEdit_cygpath  -> setText(modifySlashes(newLineEdit));
            break;
        //dosdev browse button
        case 3:    newLineEdit = QFileDialog::getOpenFileName (this, tr("Select dosdev command",
          "file selection dialog title"),uiD.lineEdit_dosdev -> text(),tr("Executable Files (*.exe)"));
          if (newLineEdit != "")    //if something is selected indeed
              uiD.lineEdit_dosdev  -> setText(modifySlashes(newLineEdit));
          break;
        //vshadow browse button
        case 4:
            fd = new QDirDialog( ".exe", uiD.lineEdit_vshadow -> text(), this,
                 "Dir selection" );
            fd->setWindowTitle( "Select vshadow directory" );
            // show the dialog
            if( fd->exec() == QDialog::Accepted )
                       newLineEdit = (fd->directory()).absolutePath();
            if (newLineEdit != "")    //if something is selected indeed
                uiD.lineEdit_vshadow  -> setText(modifySlashes(newLineEdit));
            break;
        //temp browse button
        case 5:
           fd = new QDirDialog( "", uiD.lineEdit_tempdir -> text(), this,
                                                    "Dir selection" );
           fd->setWindowTitle( "Select temporary directory" );
          // show the dialog
          if( fd->exec() == QDialog::Accepted )
                     newLineEdit = (fd->directory()).absolutePath();
          if (newLineEdit != "")    //if something is selected indeed
              uiD.lineEdit_tempdir  -> setText(modifySlashes(newLineEdit));
          break;
          //luckybackup browse button
          case 6:
              fd = new QDirDialog( ".ini", uiD.lineEdit_appdir -> text(), this,
                   "Dir selection" );
              fd->setWindowTitle( "Select luckybackup directory" );
              // show the dialog
              if( fd->exec() == QDialog::Accepted )
                         newLineEdit = (fd->directory()).absolutePath();
              if (newLineEdit != "")    //if something is selected indeed
                  uiD.lineEdit_appdir  -> setText(modifySlashes(newLineEdit));
          break;
    }

}

// default button pressed=====================================================================================================
//opens a QFileDialog to browse for files/folders locally
//This dialog is possible only for non-*nix systems
void winDialog::useDefault(const int type)
{
    switch (type)
    {
        //rsync default button
        case 0:    if (WINrunning)
                        uiD.lineEdit_rsyncPath  -> setText(rsyncDefaultWinCommand);     // Default rsync path for windows (declared in global.h)
                   if (OS2running)
                        uiD.lineEdit_rsyncPath  -> setText(rsyncDefaultCommand);        // Default rsync path for OS2 (declared in global.h)
            break;
        //ssh default button
        case 1: if (WINrunning)
                        uiD.lineEdit_sshPath  -> setText(sshDefaultWinCommand);     // Default ssh path for windows (declared in global.h)
                if (OS2running)
                        uiD.lineEdit_sshPath  -> setText(sshDefaultCommand);        // Default ssh path for OS2 (declared in global.h)
            break;
        case 2:
              uiD.lineEdit_cygpath          -> setText(cygpathDefaultCommand);
              break;
        case 3:
            uiD.lineEdit_dosdev             -> setText(dosdevDefaultCommand);
            break;
        case 4:
            uiD.lineEdit_vshadow            -> setText(vshadowDefaultDir);
            break;
        case 5:
            uiD.lineEdit_tempdir            -> setText(tempDefaultDirPath);
            break;
        case 6:
          uiD.lineEdit_appdir               -> setText(luckyBackupDefaultDir);
          break;
    }
}

// modifySlashes ===========================================================================================================
// function to change / to \ for windows (normaly when file dialog is used)
QString winDialog::modifySlashes(QString pathToModify)
{    
    pathToModify.replace("/",SLASH);
    return pathToModify;
}

// end of winDialog.cpp ---------------------------------------------------------------------------

