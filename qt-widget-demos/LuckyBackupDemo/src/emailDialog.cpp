/* ---------------------------------- emailDialog.cpp ---------------------------------------------------------------------------
// Class to echedule an email report after a profile execution

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
 last modified      : 06 Feb 2014
===============================================================================================================================
===============================================================================================================================
*/

#include "emailDialog.h"

// class emailDialog Constructor===============================================================================================
// Displays a dialog to schedule email reports
emailDialog::emailDialog (QDialog *parent) : QDialog (parent)
{
    uiE.setupUi(this);
        
    fillWindow();
                
    //connect okay & cancel pushButton SLOTs ----------------
    connect ( uiE.pushButton_ok,        SIGNAL( clicked() ),    this, SLOT( okay() ) );
    connect ( uiE.pushButton_cancel,    SIGNAL( clicked() ),    this, SLOT( cancel() ) );
    connect ( uiE.pushButton_test,      SIGNAL( clicked() ),    this, SLOT( emailTest() ) );
    connect ( uiE.lineEdit_command,     SIGNAL( textEdited(QString) ),    this, SLOT( enableTLS() ) );
    connect ( uiE.checkBox_disable_tls, SIGNAL( stateChanged(int) ),    this, SLOT( enableTLS() ) );
    
    //Connect all "revert to default" toolButtons with the revertDefault SLOT
    //Map all the toolButton signals and transmit a different integer depending on the toolbutton
    QSignalMapper *signalMapper1 = new QSignalMapper(this);
    signalMapper1 ->    setMapping ( uiE.toolButton_default_command, 0 );
    connect (uiE.toolButton_default_command, SIGNAL (clicked() ), signalMapper1 , SLOT (map()));
    signalMapper1 ->    setMapping ( uiE.toolButton_default_subject, 1 );
    connect (uiE.toolButton_default_subject, SIGNAL (clicked() ), signalMapper1 , SLOT (map()));
    signalMapper1 ->    setMapping ( uiE.toolButton_default_body, 2 );
    connect (uiE.toolButton_default_body, SIGNAL (clicked() ), signalMapper1 , SLOT (map()));
    connect(signalMapper1, SIGNAL(mapped( const int)), this, SLOT( revertDefault( const int) )  );

    GoOn = 0;
}

// SLOTS-------------------------------------------------------------------------------------
// --------------------------------okay pressed------------------------------------------------
void emailDialog::okay()
{
    GoOn = 0;   // ok pressed -> Everything good
    fillVariables();
    
    if (!checkFields())
    {
        textDialog textdialogW ("QtWarning", warningMessage, this);
        textdialogW.exec();
        return; // do not proceed if something is wrong with the fields
    }
        
    
    close();    //emmit a QcloseEvent
}

// --------------------------------cancel pressed------------------------------------------------
void emailDialog::cancel()
{
    GoOn = 1;   // cancel pressed

    close();    //emmit a QcloseEvent
}

// -------------------------------- closeEvent emitted --------------------------------
void emailDialog::closeEvent(QCloseEvent *event)
{
    event -> accept();
}

// revertDefault ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//SLOT to revert a field to the default value
void emailDialog::revertDefault(const int field)
{
      switch (field)
    {
        //command
        case 0:
            if (WINrunning)
            {
                uiE.lineEdit_command        -> setText(emailDefaultWinCommand);
                uiE.lineEdit_arguments      -> setText(emailDefaultWinArguments);
            }
            else
            {
                uiE.lineEdit_command        -> setText(emailDefaultCommand);
                uiE.lineEdit_arguments      -> setText(emailDefaultArguments);
            }
            break;
        //subject
        case 1:
            uiE.lineEdit_arg_subject    -> setText(emailDefaultSubject);
            break;
        //body text
        case 2:
            uiE.textBrowser_arg_body    -> setText(emailDefaultBody);
            break;
    }
    enableTLS();
}

// Check if all fields are ok
bool emailDialog::checkFields()
{
    bool returnVal = TRUE;
    if (uiE.checkBox_conditionNever->isChecked())   // if the never condition is checked, just return. No email will be sent anyway
        return returnVal;
    
    warningMessage = "";
    
    if (uiE.lineEdit_command -> text() == "")
    {
        warningMessage.append(tr("The command field is empty") + "!! \n");
        returnVal = FALSE;
    }

    /* This is commented because a command with no arguments (eg a script) is possible to be used
    if (uiE.lineEdit_arguments -> text() == "")
    {
        warningMessage.append(tr("The command arguments field is empty") + "!! \n");
        returnVal = FALSE;
    }*/
    
    return returnVal ;
}

// fillWindow
// Fill gui fields from variables
void emailDialog::fillWindow()
{
    uiE.lineEdit_command            -> setText(emailCommand);
    uiE.lineEdit_arguments          -> setText(emailArguments);
    uiE.lineEdit_arg_from           -> setText(emailFrom);
    uiE.lineEdit_arg_to             -> setText(emailTo);
    uiE.lineEdit_arg_subject        -> setText(emailSubject);
    uiE.lineEdit_arg_smtp           -> setText(emailSMTP);
    uiE.textBrowser_arg_body        -> setText(emailBody);
    uiE.checkBox_conditionNever     -> setChecked(emailNever);
    uiE.checkBox_conditionError     -> setChecked(emailError);
    uiE.checkBox_conditionSchedule  -> setChecked(emailSchedule);
    uiE.checkBox_disable_tls        -> setChecked(emailTLS);
    enableTLS();
}

// fillVariables
// Fill variables from gui fields 
void emailDialog::fillVariables()
{
    emailCommand    = uiE.lineEdit_command -> text();
    emailArguments  = uiE.lineEdit_arguments -> text();
    emailFrom       = uiE.lineEdit_arg_from -> text();
    emailTo         = uiE.lineEdit_arg_to -> text();
    emailSubject    = uiE.lineEdit_arg_subject -> text();
    if (WINrunning)
    {
        QStringList smtpSrv = (uiE.lineEdit_arg_smtp -> text()).split(":");
        emailSMTP       = smtpSrv.first();
        QString smtpPort = "25";
        if (smtpSrv.length()>1)
            smtpPort=smtpSrv.at(1);
        //QString smtpUser = uiE.lineEdit_arg_smtp_user->text();    // security issues ?
        //QString smtpPass = uiE.lineEdit_arg_smtp_pass->text();    // security issues ?
    }
    else
        emailSMTP       = uiE.lineEdit_arg_smtp -> text();
    emailBody       = uiE.textBrowser_arg_body -> toPlainText();
    emailNever      = uiE.checkBox_conditionNever -> isChecked();
    emailError      = uiE.checkBox_conditionError -> isChecked();
    emailSchedule   = uiE.checkBox_conditionSchedule -> isChecked();
    emailTLS        = uiE.checkBox_disable_tls -> isChecked();
    
// Windows TESTING purposes for Juan TESTING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*  if (WINrunning)
    {
        // Execute the email command
        QProcess *emailProcess;                         emailProcess = new QProcess;
        emailProcess -> setProcessChannelMode(QProcess::MergedChannels);
        QDir::setCurrent(luckyBackupDir);
        emailProcess -> setWorkingDirectory(luckyBackupDir);
        QStringList args;
        if (!smtpUser.isEmpty() && !smtpPass.isEmpty())
        {
            args << "-install" << emailSMTP << emailFrom <<"2" << smtpPort <<"-" << smtpUser << smtpPass;
            emailProcess -> start ("blat.exe",args);
            emailProcess -> waitForFinished(10000);
        }

        // Build the return string ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //QString errorOccured = emailProcess -> errorString();
    }*/
    // WINDOWS TESTING END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

// emailTest
// Send an email now, using current gui field values
void emailDialog::emailTest()
{
    fillVariables();
    
    if (!checkFields())
    {
        textDialog textdialogW ("QtWarning", warningMessage, this);
        textdialogW.exec();
        return; // do not proceed if something is wrong with the fields (eg command is empty)
    }
    
    warningMessage = sendEmailNow(TRUE);
        
    textDialog textdialogW ("emailOutput",warningMessage, this);
    textdialogW.exec();
}

// enableTLS
// enable/disable the TLS option
void emailDialog::enableTLS()
{
    QString tlsArgument= "-o tls=no";
    QString tempEmailArguments  = uiE.lineEdit_arguments -> text();
    tempEmailArguments.remove(tlsArgument +" ");
    tempEmailArguments.remove(" " + tlsArgument);
    
    //hide or show the "disable TLS" option if "sendemail" is used as command
    if (uiE.lineEdit_command -> text() == emailDefaultCommand)
    {
        uiE.checkBox_disable_tls -> setEnabled(TRUE);
        if (uiE.checkBox_disable_tls -> isChecked())
            tempEmailArguments.prepend(tlsArgument + " ");
    }
    else
        uiE.checkBox_disable_tls -> setEnabled(FALSE);
    
    uiE.lineEdit_arguments          -> setText(tempEmailArguments);
}
// --------------------------------accessors-----------------------------------
// Return an integer according to different status
int emailDialog::getGoOn()
{
    return GoOn ;
}


// end of emailDialog.cpp ---------------------------------------------------------------------------

