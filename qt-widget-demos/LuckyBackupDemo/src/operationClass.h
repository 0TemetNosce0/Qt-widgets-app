/* ------------------ operationClass.h --------------------------------------------------------------------------------------
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


 project version    : Please see "main.cpp" for project version

 developer          : luckyb 
 last modified      : 11 Sep 2013
===============================================================================================================================
===============================================================================================================================
*/


#ifndef OPERATIONCLASS_H
#define OPERATIONCLASS_H
#include <QDateTime>

//==============================================================================================================
//Declaration of operation class (this is the class that holds operation's name & arguments)
class operation 
{
    public:
        operation()                                 //constructor
        {
            itsName = "";
            itsArguments.clear();   //itsArguments << "";
            itsDescription = "";
            itsSource = "";
            itsDestination = "";
            itsConnectRestore = "";
            itsLastExecutionErrors = -1;
            itsExclude = false;
            itsInclude = false;
            itsIncludeModeNormal = false;
            itsByPassWARNING = false;
            itsCloneWARNING = true;
            itsRepeatOnFail = 0;
            itsKeepSnapshots = 1;
            itsSnapshotsList.clear();
            itsOptionsFATntfs = false;
            itsOptionsSuper = false;
            itsOptionsNumericIDs = false;
            itsOptionsVss = false;
            itsOptionsRestorent = false;
            itsIncludeFromFile = false;
            itsExcludeFromFile = false;
            itsExcludeGVFS = false;
            itsExecuteBeforeList.clear();
            itsExecuteBeforeListState.clear();
            itsExecuteAfterList.clear();
            itsExecuteAfterListState.clear();
        }
        ~operation() {}                             //destructor

        //Functions - get class operation data--------------------------------------------------------------------------------------
        QString GetName() const                 {return itsName;}
        QString GetDescription() const          {return itsDescription;}
        QStringList GetArgs() const             {return itsArguments;}
        bool GetIncluded () const               {return itsIncluded;}
        bool GetCRITICAL () const               {return itsCRITICAL;}
        bool GetWARNING () const                {return itsWARNING;}
        bool GetOK () const                     {return itsOK;}
        bool GetDestMounted () const            {return itsDestMounted;}
        bool GetSourceMounted () const          {return itsSourceMounted;}
        bool GetSourcePerms() const             {return itsSourcePerms;}
        bool GetDestPerms () const              {return itsDestPerms;}
        bool GetPerform () const                {return itsPerform;}
        bool GetByPassWARNING () const          {return itsByPassWARNING;}
        bool GetCloneWARNING () const           {return itsCloneWARNING;}
        int GetRepeatOnFail() const             {return itsRepeatOnFail;}

        QDateTime GetLastExecutionTime() const  {return itsLastExecutionTime;}
        int GetLastExecutionErrors() const      {return itsLastExecutionErrors;}
        int GetSnapshotsListSize () const       {return itsSnapshotsList.size();}
        QStringList GetSnapshotsList () const   {return itsSnapshotsList;}
        QString GetSnapshotsListItem (int itemPosition) const {return itsSnapshotsList.value(itemPosition);}
        int GetKeepSnapshots () const           {return itsKeepSnapshots;}

        QString GetConnectRestore () const      {return itsConnectRestore;}

        bool GetTypeDirContents () const        {return itsTypeDirContents;}
        bool GetTypeDirName () const            {return itsTypeDirName;}
        bool GetTypeSync () const               {return itsTypeSync;}

        QString GetSource() const               {return itsSource;}
        QString GetDestination() const          {return itsDestination;}

        bool GetExclude() const                 {return itsExclude;}
        bool GetExcludeFromFile() const         {return itsExcludeFromFile;}
        QString GetExcludeFile() const          {return itsExcludeFile;}
        bool GetExcludeTemp() const             {return itsExcludeTemp;}
        bool GetExcludeCache () const           {return itsExcludeCache;}
        bool GetExcludeBackup () const          {return itsExcludeBackup;}
        bool GetExcludeMount() const            {return itsExcludeMount;}
        bool GetExcludeLostFound() const        {return itsExcludeLostFound;}
        bool GetExcludeSystem() const           {return itsExcludeSystem;}
        bool GetExcludeTrash() const            {return itsExcludeTrash;}
        bool GetExcludeGVFS() const             {return itsExcludeGVFS;}
        int GetExcludeListSize () const         {return itsExcludeList.size();}
        QString GetExcludeListItem (int itemPosition) const {return itsExcludeList.value(itemPosition);}

        bool GetInclude() const                 {return itsInclude;}
        bool GetIncludeFromFile() const         {return itsIncludeFromFile;}
        bool GetIncludeModeNormal() const       {return itsIncludeModeNormal;}
        QString GetIncludeFile() const          {return itsIncludeFile;}
        int GetIncludeListSize () const         {return itsIncludeList.size();}
        QString GetIncludeListItem (int itemPosition) const {return itsIncludeList.value(itemPosition);}

        bool GetRemote () const                 {return itsRemote;}
        bool GetRemoteModule () const           {return itsRemoteModule;}
        bool GetRemoteDestination () const      {return itsRemoteDestination;}
        bool GetRemoteSource () const           {return itsRemoteSource;}
        bool GetRemoteSSH () const              {return itsRemoteSSH;}
        QString GetRemoteHost () const          {return itsRemoteHost;}
        QString GetRemoteUser () const          {return itsRemoteUser;}
        QString GetRemotePassword () const      {return itsRemotePassword;}
        QString GetRemoteSSHPassword () const   {return itsRemoteSSHPassword;}
        QString GetRemoteSSHPasswordStr () const{return itsRemoteSSHPasswordStr;}
        QString GetRemoteSSHOptions () const    {return itsRemoteSSHOptions;}
        int GetRemoteSSHPort () const           {return itsRemoteSSHPort;}

        bool GetOptionsUpdate () const          {return itsOptionsUpdate;}
        bool GetOptionsDelete () const          {return itsOptionsDelete;}
        bool GetOptionsRecurse () const         {return itsOptionsRecurse;}
        bool GetOptionsOwnership () const       {return itsOptionsOwnership;}
        bool GetOptionsSymlinks () const        {return itsOptionsSymlinks;}
        bool GetOptionsPermissions () const     {return itsOptionsPermissions;}
        bool GetOptionsDevices () const         {return itsOptionsDevices;}
        bool GetOptionsCVS () const             {return itsOptionsCVS;}
        bool GetOptionsHardLinks () const       {return itsOptionsHardLinks;}
        bool GetOptionsFATntfs() const          {return itsOptionsFATntfs;}
        bool GetOptionsSuper() const            {return itsOptionsSuper;}
        bool GetOptionsNumericIDs() const       {return itsOptionsNumericIDs;}
        //windows related
        bool GetOptionsVss () const             {return itsOptionsVss;}
        bool GetOptionsRestorent () const       {return itsOptionsRestorent;}
        QString GetTempPath () const            {return itsTempPath;}
        QString GetLuckyBackupDir ( )           {return itsAppDir;}
        QString GetVshadowDir () const          {return itsVshadowDir;}
        QString GetRsyncCommand () const        {return itsRsyncCommand;}
        QString GetDosdevCommand () const       {return itsDosdevCommand;}
        QString GetCygpathCommand () const      {return itsCygpathCommand;}
        QString GetSshCommand () const          {return itsSshCommand;}
        // user options
        int GetOptionsListSize () const         {return itsOptionsList.size();}
        QString GetOptionsListItem (int itemPosition) const {return itsOptionsList.value(itemPosition);}

        int GetExecuteBeforeListSize () const   {return itsExecuteBeforeList.size();}
        QString GetExecuteBeforeListItem (int itemPosition) const {return itsExecuteBeforeList.value(itemPosition);}
        bool GetExecuteBeforeListItemState (int itemPosition) const {return itsExecuteBeforeListState.value(itemPosition);}
        int GetExecuteAfterListSize () const    {return itsExecuteAfterList.size();}
        QString GetExecuteAfterListItem (int itemPosition) const {return itsExecuteAfterList.value(itemPosition);}
        bool GetExecuteAfterListItemState (int itemPosition) const {return itsExecuteAfterListState.value(itemPosition);}

        //Functions - set class operation data --------------------------------------------------------------------------------------
        void SetName(QString name)                          {itsName = name;}
        void SetDescription(QString description)            {itsDescription = description;}

        // Task state & general properties
        void SetIncluded(bool included)                     {itsIncluded = included;}
        void SetWARNING(bool warning)                       {itsWARNING = warning;}
        void SetCRITICAL(bool critical)                     {itsCRITICAL = critical;}
        void SetOK(bool ok)                                 {itsOK = ok;}
        void SetSourceMounted(bool mounted)                 {itsSourceMounted = mounted;}
        void SetDestMounted(bool mounted)                   {itsDestMounted = mounted;}
        void SetSourcePerms(bool sourceperms)               {itsSourcePerms = sourceperms;}
        void SetDestPerms(bool destperms)                   {itsDestPerms = destperms;}
        void SetPerform(bool perform)                       {itsPerform = perform;}
        void SetByPassWARNING(bool ByPassWARNING)           {itsByPassWARNING = ByPassWARNING;}
        void SetCloneWARNING(bool CloneWARNING)             {itsCloneWARNING = CloneWARNING;}
        void SetRepeatOnFail(int RepeatOnFail)              {itsRepeatOnFail = RepeatOnFail;}

        // last execution time & errors
        void SetLastExecutionTime(QDateTime lastTime)       {itsLastExecutionTime = lastTime;}
        void SetLastExecutionErrors(int LastExecutionErrors){itsLastExecutionErrors = LastExecutionErrors;}
        
        // snapshots list
        void SetSnapshotsList (QStringList snapslist)       {itsSnapshotsList = snapslist;}
        void AddSnapshotsListItem (QString itemText)        {itsSnapshotsList.append(itemText);}
        void ReplaceSnapshotsListItem (int position,QString text)   {itsSnapshotsList.replace(position,text);}
        void RemoveSnapshotsListItem  (int position)        {itsSnapshotsList.removeAt(position);}
        void ClearSnapshotsList ()                          {itsSnapshotsList.clear();}
        bool SnapshotsListIsEmpty ()                        {return itsSnapshotsList.isEmpty();}
        void SetKeepSnapshots(int keepsnapshots)            {itsKeepSnapshots = keepsnapshots;}

        // Arguments list
        void SetArgs (QStringList arguments)                {itsArguments = arguments;}
        void AppendArg (QString argument)                   {if (argument!="") itsArguments.append(argument);}
        void InsertDryRunArg ()                             {itsArguments.insert(itsArguments.size()-2,"--dry-run");}

        // connection with other task
        void SetConnectRestore (QString Connection)         {  itsConnectRestore = Connection;}

        // Task type
        void SetTypeDirContents (bool TypeDirContents)      { itsTypeDirContents = TypeDirContents;}
        void SetTypeDirName (bool TypeDirName)              { itsTypeDirName = TypeDirName;}
        void SetTypeSync (bool TypeSync)                    { itsTypeSync = TypeSync;}

        // source & destination
        void SetSource(QString source)                      {itsSource = source;}
        void SetDestination(QString destination)            {itsDestination = destination;}

        // Exclude ~~~~~~~~~~~
        // Exclude boolean
        void SetExclude()                      { if ( ((itsExcludeFromFile) && !(itsExcludeFile=="")) || (itsExcludeTemp)||(itsExcludeCache)||(itsExcludeBackup)||
                                    (itsExcludeMount)||(itsExcludeLostFound)||(itsExcludeSystem)||
                                    (itsExcludeTrash)||(itsExcludeGVFS)||(itsExcludeList.size()>0) )
                                        itsExclude = true;
                                    else     itsExclude = false; }
        // Exclude templates
        void SetExcludeTemp(bool ExcludeTemp)               { itsExcludeTemp = ExcludeTemp;}
        void SetExcludeCache (bool ExcludeCache)            { itsExcludeCache = ExcludeCache;}
        void SetExcludeBackup (bool ExcludeBackup)          { itsExcludeBackup = ExcludeBackup;}
        void SetExcludeMount(bool ExcludeMount)             { itsExcludeMount = ExcludeMount;}
        void SetExcludeLostFound(bool ExcludeLostFound)     { itsExcludeLostFound = ExcludeLostFound;}
        void SetExcludeSystem(bool ExcludeSystem)           { itsExcludeSystem = ExcludeSystem;}
        void SetExcludeTrash(bool ExcludeTrash)             { itsExcludeTrash = ExcludeTrash;}
        void SetExcludeGVFS(bool ExcludeGVFS)               { itsExcludeGVFS = ExcludeGVFS;}
        // Exclude from file
        void SetExcludeFromFile(bool ExcludeFromFile)       { itsExcludeFromFile = ExcludeFromFile;}
        void SetExcludeFile(QString ExcludeFile)            { itsExcludeFile = ExcludeFile;}
        //Exclude list - user defined
        void AddExcludeListItem (QString itemText)          { itsExcludeList.append(itemText);}

        // Include ~~~~~~~~~~~~~
        // Include boolean
        void SetInclude()                      {  if ( ((itsIncludeFromFile) && !(itsIncludeFile=="")) || 
                                            (itsIncludeList.size()>0) )
                                        itsInclude = true;
                                    else    itsInclude = false;}
        // Include from file
        void SetIncludeFromFile(bool IncludeFromFile)       { itsIncludeFromFile = IncludeFromFile;}
        // Include mode
        void SetIncludeModeNormal(bool IncludeModeNormal)   { itsIncludeModeNormal = IncludeModeNormal;}
        
        void SetIncludeFile(QString IncludeFile)            { itsIncludeFile = IncludeFile;}
        // Include list
        void AddIncludeListItem (QString itemText)          { itsIncludeList.append(itemText);}

        // Remote
        void SetRemote (bool Remote)                        { itsRemote = Remote;}
        void SetRemoteModule (bool RemoteModule)            { itsRemoteModule = RemoteModule;}
        void SetRemoteDestination (bool RemoteDestination)  { itsRemoteDestination = RemoteDestination;}
        void SetRemoteSource (bool RemoteSource)            { itsRemoteSource = RemoteSource;}
        void SetRemoteSSH (bool RemoteSSH)                  { itsRemoteSSH = RemoteSSH;}
        void SetRemoteHost (QString RemoteHost)             { itsRemoteHost = RemoteHost;}
        void SetRemoteUser (QString RemoteUser)             { itsRemoteUser = RemoteUser;}
        void SetRemotePassword (QString RemotePassword)     { itsRemotePassword = RemotePassword;}
        void SetRemoteSSHPassword (QString RemoteSSHPassword) { itsRemoteSSHPassword = RemoteSSHPassword;}
        void SetRemoteSSHPasswordStr (QString RemoteSSHPassword) { itsRemoteSSHPasswordStr = RemoteSSHPassword;}
        void SetRemoteSSHOptions (QString RemoteSSHOptions) { itsRemoteSSHOptions = RemoteSSHOptions;}
        void SetRemoteSSHPort (int RemoteSSHPort)           { itsRemoteSSHPort = RemoteSSHPort;}

        // Command options - templates
        void SetOptionsUpdate (bool OptionsUpdate)          { itsOptionsUpdate = OptionsUpdate;}
        void SetOptionsDelete (bool OptionsDelete)          { itsOptionsDelete = OptionsDelete;}
        void SetOptionsRecurse (bool OptionsRecurse)        { itsOptionsRecurse = OptionsRecurse;}
        void SetOptionsOwnership (bool OptionsOwnership)    { itsOptionsOwnership = OptionsOwnership;}
        void SetOptionsSymlinks (bool OptionsSymlinks)      { itsOptionsSymlinks = OptionsSymlinks;}
        void SetOptionsPermissions (bool OptionsPermissions){ itsOptionsPermissions = OptionsPermissions;}
        void SetOptionsDevices (bool OptionsDevices)        { itsOptionsDevices = OptionsDevices;}
        void SetOptionsCVS (bool OptionsCVS)                { itsOptionsCVS = OptionsCVS;}
        void SetOptionsHardLinks (bool OptionsHardLinks)    { itsOptionsHardLinks = OptionsHardLinks;}
        void SetOptionsFATntfs (bool OptionsFATntfs)        { itsOptionsFATntfs = OptionsFATntfs;}
        void SetOptionsSuper (bool OptionsSuper)            { itsOptionsSuper = OptionsSuper;}
        void SetOptionsNumericIDs (bool OptionsNumeriIDs)   { itsOptionsNumericIDs = OptionsNumeriIDs;}
        // windows related options
        void SetOptionsRestorent (bool Options)             { itsOptionsRestorent = Options;}
        void SetOptionsVss (bool Options)                   { itsOptionsVss = Options;}
        void SetTempPath (QString s)                        {itsTempPath = s;}
        void SetLuckyBackupDir (QString s)                  { itsAppDir = s; }
        void SetVshadowDir (QString s)                      {itsVshadowDir = s;}
        void SetRsyncCommand (QString s)                    {itsRsyncCommand = s;}
        void SetDosdevCommand (QString s)                   {itsDosdevCommand = s;}
        void SetCygpathCommand (QString s)                  {itsCygpathCommand = s;}
        void SetSshCommand (QString s)                      {itsSshCommand = s;}
        // Command options list - user defined
        void AddOptionsListItem (QString itemText)          { itsOptionsList.append(itemText);}

        // Execute before/after list
        void AddExecuteBeforeListItem (QString itemText)    { itsExecuteBeforeList.append(itemText);}
        void AddExecuteBeforeListItemState (bool itemState) { itsExecuteBeforeListState.append(itemState);}
        void AddExecuteAfterListItem (QString itemText)     { itsExecuteAfterList.append(itemText);}
        void AddExecuteAfterListItemState (bool itemState)  { itsExecuteAfterListState.append(itemState);}

    private:
        QString itsName;
        QStringList itsArguments;
        QString itsDescription;
        bool itsIncluded;
        bool itsCRITICAL;
        bool itsWARNING;
        bool itsOK;
        bool itsSourceMounted;
        bool itsDestMounted;
        bool itsSourcePerms;
        bool itsDestPerms;
        bool itsPerform;
        bool itsByPassWARNING;
        bool itsCloneWARNING;
        int itsRepeatOnFail;
        QDateTime itsLastExecutionTime;
        int itsLastExecutionErrors;
        QStringList itsSnapshotsList;
        int itsKeepSnapshots;

        QString itsConnectRestore;

        bool itsTypeDirName;
        bool itsTypeDirContents;
        bool itsTypeSync;

        QString itsDestination;
        QString itsSource;

        bool itsExclude;
        bool itsExcludeTemp;
        bool itsExcludeCache;
        bool itsExcludeBackup;
        bool itsExcludeMount;
        bool itsExcludeLostFound;
        bool itsExcludeSystem;
        bool itsExcludeTrash;
        bool itsExcludeGVFS;
        bool itsExcludeFromFile;
        QString itsExcludeFile;
        QStringList itsExcludeList;

        bool itsInclude;
        bool itsIncludeFromFile;
        bool itsIncludeModeNormal;
        QString itsIncludeFile;
        QStringList itsIncludeList;

        bool itsRemote;
        bool itsRemoteModule;
        bool itsRemoteDestination;
        bool itsRemoteSource;
        bool itsRemoteSSH;
        QString itsRemoteHost;
        QString itsRemoteUser;
        QString itsRemotePassword;
        QString itsRemoteSSHPassword;
        QString itsRemoteSSHPasswordStr;
        QString itsRemoteSSHOptions;
        int itsRemoteSSHPort;

        bool itsOptionsUpdate;
        bool itsOptionsDelete;
        bool itsOptionsRecurse;
        bool itsOptionsOwnership;
        bool itsOptionsSymlinks;
        bool itsOptionsPermissions;
        bool itsOptionsDevices;
        bool itsOptionsCVS;
        bool itsOptionsHardLinks;
        bool itsOptionsFATntfs;
        bool itsOptionsSuper;
        bool itsOptionsNumericIDs;
        //windows related variables
        bool itsOptionsVss;
        bool itsOptionsRestorent;
        QString itsTempPath;
        QString itsAppDir;
        QString itsVshadowDir;
        QString itsRsyncCommand;
        QString itsDosdevCommand;
        QString itsCygpathCommand;
        QString itsSshCommand;
        //user defined options list
        QStringList itsOptionsList;

        QStringList itsExecuteBeforeList;
        QList<bool> itsExecuteBeforeListState;
        QStringList itsExecuteAfterList;
        QList<bool> itsExecuteAfterListState;
};

#endif

// end of operationClass.h--------------------------------------------------------------
