/* ---------------------------------- textDialog.cpp --------------------------------------------------------------------------
 Class to display a simple go-noGo dialog

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
 last modified      : 30 Aug 2010

===============================================================================================================================
===============================================================================================================================
*/

#include "textDialog.h"

// class textDialog Constructor=================================================================================================
// Displays a simple dialog with text info, ok-cancel buttons and a lineEdit for user input
textDialog::textDialog (const QString type, const QString ReplaceInput, QWidget *parent) : QDialog (parent)
{
	uiT.setupUi(this);
	uiT.checkBox_select -> setVisible(FALSE);
	uiT.label_warning -> setVisible(FALSE);
	uiT.textEdit_userInput -> setVisible(FALSE);
	
	//connect okay & cancel pushButton SLOTs ----------------
	connect ( uiT.pushButton_ok, SIGNAL( clicked() ), this, SLOT( okay() ) );
 	connect ( uiT.pushButton_cancel, SIGNAL( clicked() ), this, SLOT( cancel() ) );

	GoOn = 0;
	Type = type;
	TextPassed = ReplaceInput;
	if (type == "NewProfile")
	{
		uiT.label_message 	-> setText(tr("Enter the name of the new profile :"));
		uiT.lineEdit_userInput 	-> setEchoMode (QLineEdit::Normal);
	}
	if (type == "RenameProfile")
	{
		uiT.label_message 	-> setText(tr("Enter the new name of the profile :"));
		uiT.lineEdit_userInput 	-> setEchoMode (QLineEdit::Normal);
		uiT.lineEdit_userInput 	-> setText(ReplaceInput);
		uiT.lineEdit_userInput 	-> selectAll();
	}
	if (type == "ProfileDescription")
	{
		uiT.lineEdit_userInput 	-> setVisible(FALSE);
		uiT.textEdit_userInput -> setVisible(TRUE);
		this -> resize(640, 480);
		uiT.label_message 	-> setText(tr("Profile description :"));
		uiT.textEdit_userInput 	-> setPlainText(ReplaceInput);
		uiT.textEdit_userInput	-> selectAll();
	}
	if (type == "ImportProfile")
	{
		uiT.label_message 	-> setText(tr("A profile with the same name already exists") + "<br>" +
			tr("Please enter a different name"));
		uiT.lineEdit_userInput 	-> setEchoMode (QLineEdit::Normal);
		uiT.lineEdit_userInput 	-> setText(ReplaceInput);
		uiT.lineEdit_userInput 	-> selectAll();
	}
	if (type == "password")
	{
		uiT.label_message 	-> setText(tr("Enter pasword :"));
		uiT.lineEdit_userInput 	-> setEchoMode (QLineEdit::Password);
	}
	if (type == "passphrase")
	{
		uiT.label_message 	-> setText(tr("Enter passphrase :"));
		uiT.lineEdit_userInput 	-> setEchoMode (QLineEdit::Password);
	}
	if (type == "CloneWarning")
	{
		uiT.checkBox_select -> setVisible(TRUE);
		uiT.label_warning -> setVisible(TRUE);
		uiT.checkBox_select -> setText (tr("Do not show this again for this task"));
		uiT.lineEdit_userInput 	-> setVisible(FALSE);
		uiT.label_message 	-> setText(tr("You have selected to \"Backup the contents of the source directory\"<br>together with the \"delete files on the destination\" option") +"<br><br>" + tr("BEWARE, if your intention is NOT to clone source to destination !!") +"<br><br>" + 
				tr("Are you sure you wish to proceed ??") + "<br><br>");
        resize(sizeHint());
	}
	if (type == "ValidateDialog")
	{
		uiT.lineEdit_userInput 	-> setVisible(FALSE);
		uiT.label_warning -> setVisible(TRUE);
		uiT.label_warning -> setPixmap(QPixmap(":/luckyPrefix/validate.png"));
		uiT.pushButton_cancel -> setText(tr("Copy command to clipboard"));
		uiT.pushButton_cancel -> setIcon(QIcon(":/luckyPrefix/copy.png"));
		uiT.label_message 	-> setText(ReplaceInput);
        resize(sizeHint());
	}
	if (type == "ViewCurrentCrontab")
	{
		this -> resize(640, 480);
		uiT.lineEdit_userInput 	-> setVisible(FALSE);
		uiT.pushButton_cancel -> setVisible(FALSE);
		uiT.label_message 	-> setText(ReplaceInput);
	}
	if (type == "emailOutput")
    {
        uiT.lineEdit_userInput  -> setVisible(FALSE);
        uiT.textEdit_userInput -> setVisible(TRUE);
        this -> resize(640, 480);
        uiT.label_message   -> setText(tr("eMail information"));
        uiT.textEdit_userInput  -> setPlainText(ReplaceInput);
        uiT.textEdit_userInput  -> setReadOnly(TRUE);
        uiT.pushButton_cancel   -> setVisible(FALSE);
    }
	
	// The next are used instead of standard Qt dialogs for translation reasons
	if (type == "QtInformation")
	{
		uiT.lineEdit_userInput 	-> setVisible(FALSE);
		uiT.label_warning 	-> setVisible(TRUE);
		uiT.label_warning 	-> setPixmap(QPixmap(":/luckyPrefix/validate.png"));
		uiT.label_message 	-> setText(ReplaceInput);
		
		uiT.pushButton_cancel 	-> setVisible(FALSE);
        resize(sizeHint());
	}
	if (type == "QtWarning")
	{
		uiT.lineEdit_userInput 	-> setVisible(FALSE);
		uiT.label_warning 	-> setVisible(TRUE);
		uiT.label_warning 	-> setPixmap(QPixmap(":/luckyPrefix/warning.png"));
		uiT.label_message 	-> setText(ReplaceInput);
		
		uiT.pushButton_cancel 	-> setVisible(FALSE);
        resize(sizeHint());
	}
	if (type == "QtCritical")
	{
		uiT.lineEdit_userInput 	-> setVisible(FALSE);
		uiT.label_warning 	-> setVisible(TRUE);
		uiT.label_warning 	-> setPixmap(QPixmap(":/luckyPrefix/cancel.png"));
		uiT.label_message 	-> setText(ReplaceInput);
		
		uiT.pushButton_cancel 	-> setVisible(FALSE);
        resize(sizeHint());
	}
	if (type == "QtQuestion")
	{
		uiT.lineEdit_userInput 	-> setVisible(FALSE);
		uiT.label_warning 	-> setVisible(TRUE);
		uiT.label_warning 	-> setPixmap(QPixmap(":/luckyPrefix/about.png"));
		uiT.label_message 	-> setText(ReplaceInput);
		
		uiT.pushButton_cancel 	-> setText(tr("No"));
		uiT.pushButton_ok 	-> setText(tr("Yes"));
        resize(sizeHint());
	}
}
// SLOTS-------------------------------------------------------------------------------------
// --------------------------------okay pressed------------------------------------------------
void textDialog::okay()
{
    GoOn = 1;
    userInput = uiT.lineEdit_userInput -> text();
    
    // Do not perform any further actions for the following categories:
    if ((Type == "password") || (Type == "passphrase"))
    {
        close();
        return;
    }
    if (Type == "ProfileDescription")
    {
        userInput = uiT.textEdit_userInput -> toPlainText();
        close();
        return;
    }

    //remove trailing or starting whitespaces and invalid characters
    QStringList invalid;
    invalid << "`" << "!" << "@" << "#" << "$" << "%" << "%" << "^" << "&" << "*" << "(" << ")" << "+" << "=" << "{" << "[" << "}"
        << "]" << ":" << ";" << "\"" << "'" << "|" << "\\" << "<" << "," << ">" << "?" << "/";
    for (int count=0; count<invalid.size(); ++count)
        userInput.replace(invalid.at(count),"");
    
    while ( (userInput.endsWith(" ")) || (userInput.endsWith(".")) )
        userInput.chop(1);
    while ( (userInput.startsWith(".")) || (userInput.startsWith(" ")) )
        userInput.remove(0,1);

    if (userInput == "")
        GoOn = 2;

    if (userInput == profileName)
        GoOn = 3;
    
    if (uiT.checkBox_select -> isChecked())		//"Do not show this again check box
        GoOn = 4;
    close();
}
// --------------------------------cancel pressed------------------------------------------------
void textDialog::cancel()
{
    //GoOn == 0
    if (Type == "ValidateDialog")
    {
        QString source, dest, Command_Clipboard;
    
        //copy command to clipboard		
        TextPassed = TextPassed.right(TextPassed.size()-TextPassed.indexOf("<font color=red>")); 	//remove all irrelevant text
        source = TextPassed.right(TextPassed.size()-TextPassed.indexOf("<font color=magenta>"));	//copy source & dest inside QString source
        TextPassed.remove(source);																	//remove source & dest from whole command
        dest = source.right(source.size()-source.lastIndexOf("<font color=magenta>"));				//copy dest inside QString dest
        source.remove(dest);																		//remove dest from source

        source.remove("<font color=magenta>",Qt::CaseSensitive);
        source.remove("</font>",Qt::CaseSensitive);
        source.remove("<br>",Qt::CaseSensitive);
        if (source.endsWith(" "))
            source.chop(1);
        source.replace(" ","\\ ");																	//replace whitespaces with " \"

        dest.remove("<font color=magenta>",Qt::CaseSensitive);
        dest.remove("</font>",Qt::CaseSensitive);
        dest.remove("<br>",Qt::CaseSensitive);
        dest.replace(" ","\\ ");	
        
        Command_Clipboard = TextPassed + source + " " + dest;
        Command_Clipboard.remove("<font color=red>",Qt::CaseSensitive);
        Command_Clipboard.remove("<font color=blue>",Qt::CaseSensitive);
        Command_Clipboard.remove("</font>",Qt::CaseSensitive);
        Command_Clipboard.remove("<br>",Qt::CaseSensitive);
        
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(Command_Clipboard);
    }
    else
        close();
}

void textDialog::closeEvent(QCloseEvent *event)
 {
	event->accept();
 }
// --------------------------------accessors-----------------------------------
int textDialog::getGoOn()
 {
	return GoOn ;
 }
QString textDialog::getUserInput()
 {
	return userInput;
 }

// end of textDialog.cpp ---------------------------------------------------------------------------

