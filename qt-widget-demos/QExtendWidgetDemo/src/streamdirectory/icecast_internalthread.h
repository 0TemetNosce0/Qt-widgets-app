#ifndef ICECAST_INTERNALTHREAD_H
#define ICECAST_INTERNALTHREAD_H

#include <QList>
#include <QMutex>
#include <QThread>
#include <QXmlStreamReader>
#include "streamdirectoryentry_stream.h"

class icecast_internalThread : public QThread
{
    Q_OBJECT

public:
    typedef QList<streamDirectoryEntry_stream *> streamEntryList;

    icecast_internalThread();
    virtual ~icecast_internalThread();

    void setFilename(QString newFilename);

signals:
    void streamlist_ready(icecast_internalThread::streamEntryList list);

protected:
    virtual void run();

private:
    QString filename;
    QMutex filename_mutex;
    void readStreamEntry(QXmlStreamReader & reader);
    streamEntryList streamList;

};

Q_DECLARE_METATYPE(icecast_internalThread::streamEntryList)

#endif
