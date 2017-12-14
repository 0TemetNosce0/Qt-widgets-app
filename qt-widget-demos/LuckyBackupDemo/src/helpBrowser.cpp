// ---------------------------------- helpBrowser.cpp ---------------------------------------------------------------------------
// Class to display the project manual in a browser

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
// last modified 	: 17 Jan 2012
//===============================================================================================================================
//===============================================================================================================================

#include "helpBrowser.h"

// class helpBrowser Constructor=================================================================================================
// Displays a simple dialog for browsing manual/index.html
helpBrowser::helpBrowser (QUrl helpUrl, QWidget *parent) : QDialog (parent)
{
    uiB.setupUi(this);
    //connect okay pushButton SLOTs ----------------
    connect ( uiB.button_ok, SIGNAL( clicked() ), this, SLOT( okay() ) );
    uiB.browser -> setOpenLinks(TRUE);
    uiB.browser -> setOpenExternalLinks(FALSE);
    uiB.browser -> setSource(helpUrl);
}
// SLOTS-------------------------------------------------------------------------------------
// --------------------------------okay pressed------------------------------------------------
void helpBrowser::okay()
{
    close();
}

// end of helpBrowser.cpp ---------------------------------------------------------------------------

