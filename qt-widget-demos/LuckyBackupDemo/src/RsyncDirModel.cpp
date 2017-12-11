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

#include "RsyncDirModel.h"
#include "RsyncDirModel_p.h"

#include <QIcon>
#include <QStyle>
#include <QApplication>
#include <QProcess>
#include <QTextStream>
#include <QString>
#include <QDebug>

struct RsyncDirModelData
{
//    QUrl url;
//    RsyncDirLister* lister;
    QList<RsyncEntry*> topLevelEntries;
    bool topLevelEntriesFetched;
//    QString command;     //command to be executed. Normally this is "rsync"
//    QStringList rsyncArguments;  // This stringList holds all arguments for the rsync command
//    QProcess *syncProcess;
//    bool ProcReportedError;
    RsyncDirLister* lister;
};

RsyncDirModel::RsyncDirModel(QObject* parent): QAbstractItemModel(parent)
{
    d = new RsyncDirModelData;
//    d->syncProcess = new QProcess(this);
//    d->rsyncArguments.clear();
//    d->rsyncArguments << "--list-only";
//    d->command = "rsync";
    d->lister = new RsyncDirLister;


//    connect(d->lister, SIGNAL(loginParamsRequest(QAuthenticator*)),
//            this, SIGNAL(loginParamsRequest(QAuthenticator*)));
    connect(d->lister, SIGNAL(listingDone(RsyncEntry*)),
            this, SLOT(slotListingDone(RsyncEntry*)));
//    connect(syncProcess, SIGNAL (finished(int, QProcess::ExitStatus)), this, SLOT(procFinished()));
//    connect(syncProcess, SIGNAL (error(QProcess::ProcessError)), this, SLOT(procError()));

//    d->ProcReportedError = FALSE;      // This might change as soon as syncprocess will start ()
}

RsyncDirModel::~RsyncDirModel()
{
    delete d;
}

void RsyncDirModel::setUrl(const QUrl& url,const QString& cpath)
{
    d->lister->setUrl(url,cpath);
    d->lister->list();
}

void RsyncDirModel::setUrl(const QUrl& url,const QString& cpath, const QStringList& cargs)
{
    d->lister->setUrl(url,cpath,cargs);

    d->lister->list();
}

void RsyncDirModel::setUrl(const QUrl& url)
{
    d->lister->setUrl(url);
    d->lister->list();
}

QUrl RsyncDirModel::url() const
{
    return d->lister->url();
}

QUrl RsyncDirModel::url(const QModelIndex& index) const
{
    QString path = this->path(index);

    QUrl url = d->lister->url();
    url.setPath(path);
    return url;
}

QString RsyncDirModel::path(const QModelIndex& index) const
{
    RsyncEntry* entry = (RsyncEntry*)index.internalPointer();
    if(!entry)
        return QString();

    QString rootPath = d->lister->url().path();
    QString pathStr = rootPath + entry->path();
    return pathStr;
}

QModelIndex RsyncDirModel::index(const QString& path) const
{
    if(!d->topLevelEntries.count())
        return QModelIndex();

    // Remove the root path name from the input
    // if given
    QString path2 = path;
    QUrl url = d->lister->url();
    QString rootPath = url.path();
    if(path2.startsWith(rootPath))
        path2.remove(0, rootPath.length());

    // Break the path name into directory/file names.
    QStringList comps = path2.split("/", QString::SkipEmptyParts);
    
    // Scan entries and look for the path
    QList<RsyncEntry*> entryList = d->topLevelEntries;
    RsyncEntry* entry = 0;
    for(int i=0; i<comps.count(); i++)
    {
        for(int i=0; i<entryList.count(); i++)
        {
            entry = 0;

            RsyncEntry* e = entryList.at(i);
            if(e->urlInfo().name() == comps.at(i))
            {
                entry = e;
                break;
            }
        }

        if(!entry)
            return QModelIndex();

        entryList = entry->childEntries();
    }

    if(entry)
        return index(entry);

    return QModelIndex();
}

void RsyncDirModel::refresh(const QModelIndex& index)
{
    if(index.isValid())
    {
        RsyncEntry* entry = (RsyncEntry*)index.internalPointer();
        entry->setChildrenFetched(false);
        d->lister->list(entry);
    }
    else
    {
        d->topLevelEntries.clear();
        d->lister->list();

        beginResetModel();
        endResetModel();
    }
}

int RsyncDirModel::rowCount(const QModelIndex& parent) const
{
    if(!parent.isValid())
    {
        if(d->topLevelEntries.count())
            return d->topLevelEntries.count();

        // Return one row to show that entries are being fetched.
        // Or that entries cant be fetched.
        return 1;
    }

    if(!d->topLevelEntries.count())
        return 0;
        
    RsyncEntry* entry = (RsyncEntry*)parent.internalPointer();
    if(entry)
    {
        if(entry->isChildrenFetched())
            return entry->childEntries().count();

        return 1;
    }

    return 0;
}

int RsyncDirModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    if(d->topLevelEntries.count())
        return 3;

    // Return one row to show that entries are being fetched.
    // Or that entries cant be fetched.
    return 1;
}

QVariant RsyncDirModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(!d->topLevelEntries.count())
    {
        if(!index.row() && !index.column() && role == Qt::DisplayRole)
        {
            if(d->topLevelEntriesFetched)
                return QString("Could not fetch %1").arg(d->lister->url().toString());
            else
                return QString("Fetching %1...").arg(d->lister->url().toString());
        }
        return QVariant();
    }

    RsyncEntry* entry = (RsyncEntry*)index.internalPointer();
    if(!entry->urlInfo().isValid())
    {
        if(!index.column() && role == Qt::DisplayRole)
            return "Fetching...";

        return QVariant();
    }

    switch(index.column())
    {
    case 0: // Name
        if(role == Qt::DisplayRole)
        {
            return entry->urlInfo().name();
        }
        
        if(role == Qt::DecorationRole)
            return entry->icon();

        if(role == Qt::ToolTipRole)
            return entry->path();

        break;

    case 1: // Last Modified
        if(role == Qt::DisplayRole)
            return entry->urlInfo().lastModified().toString();

        break;

    case 2: // Size
        if(role == Qt::DisplayRole)
        {
            if(!entry->urlInfo().isDir())         
                return entry->urlInfo().size();
        }

        break;
    }

    return QVariant();
}

QModelIndex RsyncDirModel::index(int row, int col, const QModelIndex& parent) const
{
    if(!parent.isValid())
    {
        if(!d->topLevelEntries.count())
            return QAbstractItemModel::createIndex(row, col);

        if(row < 0 || row >= d->topLevelEntries.count())
            return QModelIndex();
                 
        RsyncEntry* entry = d->topLevelEntries.at(row);
        return createIndex(row, col, entry);
    }
        
    RsyncEntry* entry = (RsyncEntry*)parent.internalPointer();
    if(!entry->isChildrenFetched())
        d->lister->list(entry);

    if(row < 0 || row >= entry->childEntries().count())
        return QModelIndex();
    
    RsyncEntry* childEntry = entry->childEntries().at(row);
    return createIndex(row, col, childEntry);
}

QModelIndex RsyncDirModel::parent(const QModelIndex& index) const
{
    if(!index.isValid() || !d->topLevelEntries.count())
        return QModelIndex();

    RsyncEntry* entry = (RsyncEntry*)index.internalPointer();
    RsyncEntry* parentRowEntry = entry->parentEntry();

    if(!parentRowEntry)
        return QModelIndex();

    int idx = d->topLevelEntries.indexOf(parentRowEntry);
    if(idx >= 0)
        return createIndex(idx, 0, parentRowEntry);

    RsyncEntry* grantParent = parentRowEntry->parentEntry();
    idx = grantParent->childEntries().indexOf(parentRowEntry);
    return createIndex(idx, 0, parentRowEntry);
}

QVariant RsyncDirModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole || orientation != Qt::Horizontal )
        return QVariant();

    if(!d->topLevelEntries.count())
        return QString();

    switch(section)
    {
        case 0:
            return "Name";
        case 1:
            return "Last Modified";
        case 2:
            return "Size";
        default:
            break;
    }

    return QVariant();    
}

Qt::ItemFlags RsyncDirModel::flags(const QModelIndex& index) const
{
    RsyncEntry* entry = (RsyncEntry*)index.internalPointer();
    if(entry && entry->urlInfo().isValid())
        return Qt::ItemIsSelectable|Qt::ItemIsEnabled;

    return Qt::ItemIsEnabled;
}

QModelIndex RsyncDirModel::index(RsyncEntry* entry) const
{
    // Confirm that this entry belongs to us
    if(!d->topLevelEntries.count())
        return QModelIndex();

    RsyncEntry* e2 = entry;
    while(e2->parentEntry())
        e2 = e2->parentEntry();

    if(!d->topLevelEntries.contains(e2))
        return QModelIndex();

    RsyncEntry* parent = entry->parentEntry();
    if(parent)
        return createIndex(parent->childEntries().indexOf(entry), 0, entry);

    return createIndex(d->topLevelEntries.indexOf(entry), 0, entry);
}

void RsyncDirModel::slotListingDone(RsyncEntry* entry)
{
    if(entry)
    {
        QModelIndex index = this->index(entry);
        if(!index.isValid())
            return;

        beginRemoveRows(index, 0, 1);
        // Do nothing
        endRemoveRows();

        beginInsertRows(index, 0, entry->childEntries().count());
        // Do nothing
        endInsertRows();
    }
    else
    {
        d->topLevelEntries = d->lister->topLevelEntries();
        d->topLevelEntriesFetched = true;

        beginResetModel();
        endResetModel();
    }
}


 
