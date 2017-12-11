/* ------------------ scheduleClass.h --------------------------------------------------------------------------------------
 header file for luckyBackup project

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

 developer          : luckyb 
 last modified      : 24 Jan 2011
===============================================================================================================================
===============================================================================================================================
*/



#ifndef SCHEDULECLASS_H
#define SCHEDULECLASS_H


//==============================================================================================================
//Declaration of schedule class (this is the class that holds profiles scheduling names & arguments)
class schedule 
{
    public:
        schedule()								//constructor
        {
            itsName= "";
            itsProfilePath = "";
            itsProfileName = "";
            itsMonth = 0;
            itsMonthDay = 0;
            itsWeekDay = 0;
            itsHour = 0;
            itsMinute = 0;
            itsSkipCritical = TRUE;
            itsConsoleMode = FALSE;
            itsReboot = FALSE;
            itsDelayReboot = 3;
        }
        ~schedule() {}								//destructor

        //Functions - get class operation data--------------------------------------------------------------------------------------
        QString GetName() const 		{return itsName;}
        QString GetProfilePath() const 		{return itsProfilePath;}
        QString GetProfileName() const 		{return itsProfileName;}

        int GetMonth () const           {return itsMonth;}
        int GetMonthDay () const        {return itsMonthDay;}
        int GetWeekDay () const         {return itsWeekDay;}
        int GetHour () const            {return itsHour;}
        int GetMinute () const          {return itsMinute;}
        bool GetSkipCritical() const    {return itsSkipCritical;}
        bool GetConsoleMode() const     {return itsConsoleMode;}
        bool GetReboot() const          {return itsReboot;}
        int GetDelayReboot () const     {return itsDelayReboot;}

        //Functions - set class operation data --------------------------------------------------------------------------------------
        void SetName(QString name) 				{itsName = name;}

        void SetProfilePath(QString ProfilePath) 		{itsProfilePath = ProfilePath;}
        void SetProfileName(QString ProfileName) 		{itsProfileName = ProfileName;}	

        void SetMonth(int month) 				{itsMonth = month;}
        void SetMonthDay(int monthDay) 				{itsMonthDay = monthDay;}
        void SetWeekDay(int weekDay) 				{itsWeekDay = weekDay;}
        void SetHour(int hour) 					{itsHour = hour;}
        void SetMinute(int minute) 				{itsMinute = minute;}
        void SetSkipCritical (bool SkipCritical)    {itsSkipCritical = SkipCritical;}
        void SetConsoleMode (bool ConsoleMode)      {itsConsoleMode = ConsoleMode;}
        void SetReboot (bool Reboot) 	 		    {itsReboot = Reboot;}
        void SetDelayReboot (int delayReboot)       {itsDelayReboot = delayReboot;}

    private:
        QString itsName;
        QString itsProfilePath;
        QString itsProfileName;
        int itsMonth;
        int itsMonthDay;
        int itsWeekDay;
        int itsHour;
        int itsMinute;
        bool itsSkipCritical;
        bool itsConsoleMode;
        bool itsReboot;
        int itsDelayReboot;
};

#endif

// end of scheduleClass.h--------------------------------------------------------------
