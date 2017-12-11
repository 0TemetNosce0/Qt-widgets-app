/****************************************************************************
    Copyright (C) VCreate Logic Private Limited, Bangalore
    Contact: info@vcreatelogic.com
    
    This file is developed by VCreate Logic Private Limited and used as part of the "luckyBackup" project
    It is distributed under the terms of the GNU General Public License
    It is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    It is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the luckyBackup project.  If not, see <http://www.gnu.org/licenses/>.

****************************************************************************/

#include "RsyncDirModel_p.h"

#include <QFileIconProvider>
#include <QPixmapCache>
#include <QDesktopServices>
#include <QDir>
#include <QIcon>
#include <QPixmap>
#include <QTextCodec>

///////////////////////////////////////////////////////////////////////////////
// RsyncEntry
///////////////////////////////////////////////////////////////////////////////

struct RsyncEntryData
{
    RsyncEntryData() : parent(0),
        childrenFetched(false),
        fetching(false) { }

    QUrlInfo urlInfo;

    RsyncEntry* parent;
    QList<RsyncEntry*> children;
    bool childrenFetched;
    bool fetching;
    QString path;
    QIcon icon;

};



RsyncEntry::RsyncEntry(const QUrlInfo& info)
{
    d = new RsyncEntryData;
    d->urlInfo = info;
    if(info.isDir())
        d->childrenFetched = false;
    else
        d->childrenFetched = true;

    if(info.isValid())
        d->icon = FileIconCache::instance().icon(info);
}

RsyncEntry::~RsyncEntry()
{
    qDeleteAll(d->children);
    delete d;
}

RsyncEntry* RsyncEntry::parentEntry() const
{
    return d->parent;
}

QList<RsyncEntry*> RsyncEntry::childEntries() const
{
    return d->children;
}

bool RsyncEntry::isChildrenFetched() const
{
    return d->childrenFetched;
}

bool RsyncEntry::isFetching() const
{
    return d->fetching;
}

QString RsyncEntry::path() const
{
    if(!d->path.isEmpty())
        return d->path;

    if(d->parent)
        d->path = d->parent->path();
    else
        d->path = "/";
        
    if(d->urlInfo.isDir())
        d->path += d->urlInfo.name() + "/";
    else
        d->path += d->urlInfo.name();

    return d->path;
}

QUrlInfo RsyncEntry::urlInfo() const
{
    return d->urlInfo;
}

QIcon RsyncEntry::icon() const
{
    return d->icon;
}

RsyncEntry* RsyncEntry::addUrlInfo(const QUrlInfo& urlInfo)
{
    if(d->children.count())
    {
        RsyncEntry* firstEntry = d->children.at(0);
        if(!firstEntry->urlInfo().isValid())
        {
            d->children.removeAt(0);
            delete firstEntry;
        }
    }

    RsyncEntry* childEntry = new RsyncEntry(urlInfo);
    d->children.append( childEntry );
    childEntry->d->parent = this;
    return childEntry;
}

void RsyncEntry::removeUrlInfo(const QUrlInfo& urlInfo)
{
    for(int i=0; i<d->children.count(); i++)
    {
        RsyncEntry* entry = d->children.at(i);
        if(entry->urlInfo() == urlInfo)
        {
            d->children.removeAt(i);
            delete entry;
            return;
        }
    }
}

void RsyncEntry::setChildrenFetched(bool val)
{
    if(!val && d->children.count())
        return;

    d->childrenFetched = val;
    if(val)
        d->fetching = false;
}

void RsyncEntry::clear()
{
    d->children.clear();
}

void RsyncEntry::setFetching(bool val)
{
    d->fetching = val;

    // Add a dummy URL info, until
    // children are fetched.
    addUrlInfo(QUrlInfo());
}

///////////////////////////////////////////////////////////////////////////////
// RsyncDirListerOperation
///////////////////////////////////////////////////////////////////////////////

struct RsyncDirListerOperationData
{
    RsyncDirListerOperationData()
            : parentEntry(0),
              executing(false),
              finished(false),
              success(false),
              RsyncCmdId(0) { }

    QProcess* syncProcess;
    bool ProcReportedError;
    bool abort;
    QString errorMessage;
    RsyncDirLister* parent;
    RsyncEntry* parentEntry;
    bool executing;
    bool finished;
    bool success;
    int id;
    int RsyncCmdId;
    QUrl url;

    QList<QUrlInfo> urlInfoList;
};

static int UniqueId()
{
    static int id;
    return ++id;
}

RsyncDirListerOperation::RsyncDirListerOperation(RsyncDirLister* parent)
        : QObject(parent)
{
    d = new RsyncDirListerOperationData;
    d->parent = parent;
    d->id = UniqueId();
    d->url = QUrl(d->parent->url().path());
    d->syncProcess = new QProcess(this);
    connect(d->syncProcess, SIGNAL (finished(int, QProcess::ExitStatus)), this, SLOT(procFinished()));
    connect(d->syncProcess, SIGNAL (error(QProcess::ProcessError)), this, SLOT(procError()));
}

RsyncDirListerOperation::RsyncDirListerOperation(RsyncDirLister* parent,RsyncEntry* entry)
        : QObject(parent)
{
    d = new RsyncDirListerOperationData;
    d->parent = parent;
    d->parentEntry = entry;
    d->url = QUrl(d->parent->url().path()+d->parentEntry->path());
    d->parentEntry->setFetching(true);
    d->id = UniqueId();
    d->syncProcess = new QProcess(this);
    connect(d->syncProcess, SIGNAL (finished(int, QProcess::ExitStatus)), this, SLOT(procFinished()));
    connect(d->syncProcess, SIGNAL (error(QProcess::ProcessError)), this, SLOT(procError()));
}

RsyncDirListerOperation::~RsyncDirListerOperation()
{
    delete d;
}

void RsyncDirListerOperation::setParentEntry(RsyncEntry* entry)
{

        d->parentEntry = entry;
        d->url = QUrl(d->parent->url().path()+d->parentEntry->path());
        d->parentEntry->setFetching(true);
}

RsyncEntry* RsyncDirListerOperation::parentEntry() const
{
    return d->parentEntry;
}

int RsyncDirListerOperation::id() const
{
    return d->id;
}

bool RsyncDirListerOperation::isExecuting() const
{
    return d->executing;
}

bool RsyncDirListerOperation::isFinished() const
{
    return d->finished;
}

bool RsyncDirListerOperation::isSuccessfullyFinished() const
{
    return d->success;
}
QString RsyncDirListerOperation::path() const
{
    return d->url.path();
}
void RsyncDirListerOperation::execute()
{
    d->executing = true;
    QStringList tempArgs=d->parent->arguments();
    tempArgs << path();
    d->syncProcess -> start (d->parent->command(),tempArgs);   // execute rsync command with rsyncArguments
    if (!d->syncProcess->waitForStarted())
        abort();
}

void RsyncDirListerOperation::abort()
{
    if(d->executing)
    {
        d->syncProcess->kill();
        d->executing = false;
        d->finished = true;
        d->success = false;
        d->urlInfoList.clear();
//        emit aborted();
    }
}


void RsyncDirListerOperation::procFinished()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextStream outputStream (new QString(codec->toUnicode(d->syncProcess -> readAllStandardOutput())));
    QString line;
    QList<RsyncEntry*> parentEntries;
    do {
        line =outputStream.readLine();
        QStringList data= line.split(" ",QString::SkipEmptyParts);
        if (data.isEmpty())
            continue;
        bool isDir=false;
        bool isFile=false;
        bool isLink=false;
        bool isExec=false;
        QString d1=data[0];
        //in data list 0: permisions, 1: size, 2: date, 3: hour, 4: name
        if (d1.at(0)=='d'){
               isExec=true;
               isDir=true;
        }
        else if(d1.at(0)=='l')
            isLink=true;
        else if(d1.at(0)=='-')
            isFile=true;
        else
            continue;
        d1=data[4];
        for (int i=5;i<data.size();i++)
            d1+=" "+data[i];
        if (d1[0]=='.')
            continue;
        if (d->parentEntry){
            d->parentEntry->addUrlInfo(QUrlInfo(d1,777,"root","root",data[1].toLong(), QDateTime::fromString(data[2]+" "+data[3],"yyyy/MM/dd HH:mm:ss"),
                                                          QDateTime::fromString(data[2]+" "+data[3],"yyyy/MM/dd HH:mm:ss"),
                                                          isDir,isFile,isLink,false,true,isExec));
        }else{
            parentEntries.append(new RsyncEntry(QUrlInfo(d1,777,"root","root",data[1].toLong(), QDateTime::fromString(data[2]+" "+data[3],"yyyy/MM/dd HH:mm:ss"),
                                                          QDateTime::fromString(data[2]+" "+data[3],"yyyy/MM/dd HH:mm:ss"),
                                                          isDir,isFile,isLink,false,true,isExec)));

        }


    }while (!line.isNull());
    d->executing = false;
    d->finished = true;
    d->success = true;
    if (d->parentEntry)
        d->parent->setChildrenFetched(d->parentEntry);
    else
        d->parent->setTopLevelEntries(parentEntries);
}

void RsyncDirListerOperation::procError()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    d->errorMessage = codec->toUnicode(d->syncProcess -> readAllStandardError());
    d->executing = false;
    d->finished = true;
    d->success = false;
}

///////////////////////////////////////////////////////////////////////////////
// RsyncDirLister
///////////////////////////////////////////////////////////////////////////////

struct RsyncDirListerData
{
    RsyncDirListerData() :
        topLevelEntriesFetched(false),
         currentParent(0) { }

//    QProcess *syncProcess;
//    bool ProcReportedError;
//    bool abort;
    QString errorMessage;
    QList<RsyncEntry*> topLevelEntries;
    bool topLevelEntriesFetched;
    QUrl url;

    RsyncEntry* currentParent;
    QString command;       //command to be executed. Normally this is "rsync"
    QStringList rsyncArguments;    // This stringList holds all arguments for the rsync command
    QList<RsyncDirListerOperation*> operationQueue;

};

RsyncDirLister::RsyncDirLister(QObject* parent)
:QObject(parent)
{
    d = new RsyncDirListerData;
    d->command="rsync";
    d->rsyncArguments << "--list-only";

}

RsyncDirLister::~RsyncDirLister()
{
    delete d;
}

void RsyncDirLister::setUrl(const QUrl& url)
{
    d->url = url;
}
void RsyncDirLister::setUrl(const QUrl& url,const QString& cpath)
{
    d->rsyncArguments.clear();
    d->url=url;
    d->command=cpath;

    d->rsyncArguments << "--list-only";
}
void RsyncDirLister::setUrl(const QUrl& url,const QString& cpath, const QStringList& cargs)
{
    d->rsyncArguments.clear();
    d->url=url;
    d->command=cpath;

    if (!cargs.isEmpty())
        d->rsyncArguments=cargs;
    d->rsyncArguments << "--list-only";

}

QUrl RsyncDirLister::url() const
{
    return d->url;
}

QString RsyncDirLister::command() const
{
    return d->command;
}

QStringList RsyncDirLister::arguments() const
{
    return d->rsyncArguments;
}

QList<RsyncEntry*> RsyncDirLister::topLevelEntries() const
{
    return d->topLevelEntries;
}

bool RsyncDirLister::topLevelEntriesFetched() const
{
    return d->topLevelEntriesFetched;
}

QString RsyncDirLister::lastError() const
{
    return d->errorMessage;
}

void RsyncDirLister::list()
{
    cleanOperations();
    // Create a list operation and queue it.
    RsyncDirListerOperation* listOper
            = new RsyncDirListerOperation(this);
      d->operationQueue.append(listOper);
      d->topLevelEntriesFetched = false;
      listOper->execute();

}

void RsyncDirLister::list(RsyncEntry* entry)
{
    // If the entry is already being fetched,
    // dont sweat
    cleanOperations();
    if(entry->isChildrenFetched() || entry->isFetching())
        return;

    // Verify whether entry belongs to us
    RsyncEntry* e2 = entry;
    while(e2->parentEntry())
        e2 = e2->parentEntry();
    if(!d->topLevelEntries.contains(e2))
        return;

    // Create a list operation and queue it.
    RsyncDirListerOperation* listOper
            = new RsyncDirListerOperation(this,entry);
//    listOper->setParentEntry(entry);
    d->operationQueue.append(listOper);
    listOper->execute();
}

void RsyncDirLister::refresh()
{
    abort();
    qDeleteAll(d->topLevelEntries);
    d->topLevelEntries.clear();
    list();
}

void RsyncDirLister::refresh(RsyncEntry* entry)
{
    if(entry->isFetching())
        return;

    entry->setChildrenFetched(false);
    list(entry);
}

void RsyncDirLister::cleanOperations()
{
  Q_FOREACH(RsyncDirListerOperation* oper, d->operationQueue)
  {
      if(oper->isFinished())
          d->operationQueue.removeOne(oper);
  }
}

void RsyncDirLister::abort()
{
    QList<RsyncDirListerOperation*> queue = d->operationQueue;
    d->operationQueue.clear();

    Q_FOREACH(RsyncDirListerOperation* oper, queue)
    {
        if(oper->isExecuting())
            oper->abort();
    }

    qDeleteAll(queue);
}

void RsyncDirLister::setTopLevelEntries(const QList<RsyncEntry*>& entries)
{
    d->topLevelEntries = entries;
    d->topLevelEntriesFetched = true;
    emit listingDone(NULL);
}

void RsyncDirLister::setChildrenFetched(RsyncEntry* entry)
{
    entry->setChildrenFetched(true);
    emit listingDone(entry);
}


///////////////////////////////////////////////////////////////////////////////
// RsyncDirLister
///////////////////////////////////////////////////////////////////////////////



struct FileIconCacheData
{
    QFileIconProvider iconProvider;
    QString tempDir;

    QString suffix(const QString& fileName);
    QString createTempFile(const QString& name);
};

FileIconCache& FileIconCache::instance()
{
    static FileIconCache theInstance;
    return theInstance;
}

FileIconCache::FileIconCache()
{
    d = new FileIconCacheData;

    QDir tempDir = QDir::tempPath();
    tempDir.mkdir("FileIconCache");
    d->tempDir = tempDir.absoluteFilePath("FileIconCache");
}

FileIconCache::~FileIconCache()
{
    delete d;
}

QIcon FileIconCache::icon(const QUrlInfo& info) const
{
    QIcon icon;

    if(info.isDir())
        icon = d->iconProvider.icon(QFileIconProvider::Folder);
    else
    {
        QString suffix = d->suffix(info.name());
        QPixmap pixmap;
        if(QPixmapCache::find(suffix, pixmap))
            return QIcon(pixmap);

        if(suffix.isEmpty())
            icon = d->iconProvider.icon(QFileIconProvider::File);
        else
        {
            // Create an empty file with the same name as info.name()
            // in the temporary folder
            QString file = d->createTempFile(info.name());
            if(file.isEmpty())
                icon = d->iconProvider.icon(QFileIconProvider::File);
            else
                icon = d->iconProvider.icon(QFileInfo(file));
            QFile::remove(file);
        }

        if(icon.isNull())
            icon = d->iconProvider.icon(QFileIconProvider::File);

        QPixmapCache::insert(suffix, icon.pixmap(32,32));
    }

    return icon;
}

QString FileIconCacheData::suffix(const QString& fileName)
{
    QStringList comps = fileName.split(".");
    comps.removeFirst();

    QString suffix = comps.join(".");
    return suffix;
}

QString FileIconCacheData::createTempFile(const QString& name)
{
    QString completeName = QString("%1/%2").arg(tempDir).arg(name);

    QFile file(completeName);
    if(!file.open(QFile::WriteOnly))
        return QString();

    file.write(completeName.toLatin1());
    file.close();

    return completeName;
}
 
