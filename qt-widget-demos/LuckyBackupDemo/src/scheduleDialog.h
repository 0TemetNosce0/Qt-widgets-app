/* ---------------------------------- scheduleDialog.h ---------------------------------------------------------------------------
 Header file for scheduleDialog.cpp

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
 last modified      : 09 Feb 2012
===============================================================================================================================
===============================================================================================================================
*/

#ifndef SCHEDULEDIALOG_H
#define SCHEDULEDIALOG_H

//include  header file that qmake produces from "*.ui" created with qt designer
#include "ui_scheduleDialog.h"


//==============================================================================================================
//Declaration of rsyncDialog class (this will execute rsync and show progress in a dialog)
class scheduleDialog : public QDialog
{
    Q_OBJECT
    
    public:
        scheduleDialog (QDialog *parent=0);

        QString schedulename;           // schedule file filename
        int TotalSchedule;              //The number of available profiles schedulesin "schedule list"- starts from 1
        int currentSchedule;            //this holds the current row from the "schedule list"- starts from 0
        void createCron();              //creates a cron file & updates the user's crontab
        QString CronTab;                //QString to hold the user's crontab
        int count;                      //simple count variable !!
        void clearScheduleDetails();    //function: when clear (schedule details) pushbutton pressed
        bool saveScheduleFile ();       //function to save the schedule-file
        QString scheduleText(QString,int,int,int,int,int,bool); //returns the text displayed at the schedule list (eg execute profile default at .... every...)


    private slots:
        void schedulePressed();     //SLOT when schedule buutton pressed
        void cancelPressed();       //SLOT when cancel pushbutton pressed

        void modifyPressed();       //SLOT when modify pushbutton pressed
        void addPressed();          //SLOT to add an item in the list
        void removePressed();       //SLOT to remove an item from the list
        void okaySchedulePressed(); //function to add ot modify a profile schedule
        void modifyCancelPressed(); //SLOT to initialize widget views
        void viewCrontab();         //SLOT to display the currenr crontab

        void fillDetails();         //SLOT to fill fields of schedule details
        void appendCrontabOutput(); //SLOT to read user's crontab to a QString

    private:
        Ui::scheduleDialog uiS;
        int currentProfileIndex;    //holds the current profile index inside the combobox
        bool noSchedules;           //becomes true when no schedules are declared
        bool changesMade;           //becomes true if changes are made but no cronIt is pressed
    

    protected:
        void closeEvent(QCloseEvent *event);	//when the close button of the dialog pressed

};

#endif

// end of scheduleDialog.h ---------------------------------------------------------------------------
