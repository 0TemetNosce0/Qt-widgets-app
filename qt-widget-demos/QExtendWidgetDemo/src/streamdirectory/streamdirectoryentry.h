#ifndef STREAMDIRECTORYENTRY_H
#define STREAMDIRECTORYENTRY_H

#include <QUrl>
#include <QList>
#include <QString>
#include <QVariant>

class streamDirectoryEntry
{

public:
    streamDirectoryEntry();
    virtual ~streamDirectoryEntry();

    void appendChild(streamDirectoryEntry *child);
    virtual bool canFetchMore() const;
    streamDirectoryEntry *child(int row) const;
    int childCount() const;
    virtual QVariant data(const int column) const;
    virtual void fetchMore();
    virtual bool hasChildren() const = 0;
    QString name() const;
    streamDirectoryEntry *parent() const;
    virtual QVariant rawData(const int column) const;
    int row() const;
    void setName(const QString & name);
    void setValue(const QUrl & value);
    QUrl value() const;

private:
    QList<streamDirectoryEntry *> childItems;
    QString entryName;
    QUrl entryValue;
    streamDirectoryEntry *parentItem;
    streamDirectoryEntry *self;
};

#endif
