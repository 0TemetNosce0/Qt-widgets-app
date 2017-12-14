#include "streamdirectoryentry.h"

streamDirectoryEntry::streamDirectoryEntry()
{
    parentItem = 0;
    self = this;
}

streamDirectoryEntry::~streamDirectoryEntry()
{
    foreach (streamDirectoryEntry *entry, childItems)
    {
        delete entry;
    }
}

int streamDirectoryEntry::childCount() const
{
    return childItems.size();
}

streamDirectoryEntry *streamDirectoryEntry::child(int row) const
{
    if (childItems.size() > row)
    {
        return childItems.value(row);
    }
    else
    {
        return 0;
    }
}

void streamDirectoryEntry::appendChild(streamDirectoryEntry *child)
{
    child->parentItem = this;
    childItems.append(child);
}

QVariant streamDirectoryEntry::rawData(const int column) const
{
    return data(column);
}

int streamDirectoryEntry::row() const
{
    if (parentItem)
    {
        return parentItem->childItems.indexOf(self);
    }
    else
    {
        return 0;
    };
}

QVariant streamDirectoryEntry::data(const int) const
{
    return QVariant();
}

streamDirectoryEntry *streamDirectoryEntry::parent() const
{
    return parentItem;
}

QString streamDirectoryEntry::name() const
{
    return entryName;
}

void streamDirectoryEntry::setName(const QString & name)
{
    entryName = name;
}

QUrl streamDirectoryEntry::value() const
{
    return entryValue;
}

void streamDirectoryEntry::setValue(const QUrl &value)
{
    entryValue = value;
}

bool streamDirectoryEntry::canFetchMore() const
{
    return false;
}

void streamDirectoryEntry::fetchMore()
{

}
