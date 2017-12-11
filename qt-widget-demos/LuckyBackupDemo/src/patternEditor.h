// ---------------------------------- patternEditor.h ---------------------------------------------------------------------------
// header file used by patternEditor.cpp

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
// last modified 	: 26 Feb 2010
//===============================================================================================================================
//===============================================================================================================================

#ifndef PATTERNEDITOR_H
#define PATTERNEDITOR_H

#include "ui_patternEditor.h"

//==============================================================================================================
//Declaration of patternEditor class

class patternEditor : public QDialog
{
	Q_OBJECT
	
	public:
		patternEditor (QString, QWidget *parent=0);
		QString getPattern();

	private slots:
		void okay();
		void cancel();
		void resetFileds();
		void browse(const int);		//SLOT to browse for a directory or file
		void fillPattern();		//SLOT to fill-in the pattern from all the info from the dialog
		void fileRadioChanged();	//SLOT when the specific file radio button is toggled

	private:
		Ui::patternEditor uiP;
		QString itsPattern;
		QString SourceRoot;		//this holds the source of the task
		QString patternLine;	//this holds the final pattern to insert
		QString anchorSource;	//this holds the final directory of the source when "backup the entire source directory by name" is used
		int count;			//simple count variable

	protected:
		void closeEvent(QCloseEvent*);
}; 

#endif

// end of patternEditor.h ---------------------------------------------------------------------------
