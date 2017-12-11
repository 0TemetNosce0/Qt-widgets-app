/* ---------------------------------- about.h ---------------------------------------------------------------------------
 header file used by about.cpp

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

 developer 		: luckyb 
 last modified 		: 20 Nov 2009
===============================================================================================================================
===============================================================================================================================
*/

#ifndef ABOUT_H
#define ABOUT_H

#include "ui_about.h"

//==============================================================================================================
//Declaration of aboutDialog class (this is the dialog displaying "about" information)

class aboutDialog : public QDialog
{
	Q_OBJECT
	
	public:
		aboutDialog (QUrl, QDialog *parent=0);

		void setTop();
		void setAbout();
		void setAuthor();
		void setThanks();
		void setLicense(QUrl);
		void setSupport();
		QString Text;

	private slots:
		void okay();

	private:
		Ui::aboutDialog uiA;
}; 

#endif

// end of about.h ---------------------------------------------------------------------------
