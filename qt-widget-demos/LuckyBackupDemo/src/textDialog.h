// ---------------------------------- textDialogDialog.h ---------------------------------------------------------------------------
// header file used by textDialog.cpp

//===============================================================================================================================
//===============================================================================================================================
//     This file is part of "luckyBackup" project
//     Copyright, Loukas Avgeriou
//     luckyBackup is distributed under the terms of the GNU General Public License
//     luckyBackup is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
// 
//     luckyBackup is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
// 
//     You should have received a copy of the GNU General Public License
//     along with luckyBackup.  If not, see <http://www.gnu.org/licenses/>.


// project version	: Please see "main.cpp" for project version

// developer 		: luckyb 
// last modified 	: 06 Jan 2010
//===============================================================================================================================
//===============================================================================================================================

#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include "ui_textDialog.h"

//==============================================================================================================
//Declaration of textDialog class (this is a simple go -nogo dialog with a textdialog & 2 buttons)
// accessor function getGoOn returns TRUE or FALSE
class textDialog : public QDialog
{
	Q_OBJECT
	
	public:
		textDialog (const QString, const QString, QWidget *parent=0);
		int getGoOn();
		QString getUserInput();

	private slots:
		void okay();
		void cancel();

	private:
		Ui::textDialog uiT;
		int GoOn;
		QString userInput;
		QString Type;
		QString TextPassed;

	protected:
		void closeEvent(QCloseEvent*);
}; 

#endif

// end of textDialogDialog.h ---------------------------------------------------------------------------
