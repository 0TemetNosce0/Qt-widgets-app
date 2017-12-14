/*-------------------------commandline.h------------------------------------------
	header file for commandline.cpp

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
 last modified 		: 03 Mar 2010
===============================================================================================================================
===============================================================================================================================

 runs luckybackup in command line mode
*/

#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <iostream>

using namespace std;

//==============================================================================================================
//Declaration of commandline class (this is the class that runs luckybackup in command line mode)
class commandline
{
	public:
		commandline ();
		~commandline();

		void rsyncIT();		//perform rsync execution
		void thats_all();	//display a "finished" message
		int result();		//executes all necessary function & returns an integer

		int count;		//simple count variable !!
		QString CheckedData;	//String holding the ok - notOK message after the backup dirs check
		
	private:
		char* profileNameArg;	//holds the profile as given at the command line
		void intro();		//display an intro message
		int errorCount;		// error counter for a specific task execution

};

#endif
// end of commandline.h---------------------------------------------------------
 
