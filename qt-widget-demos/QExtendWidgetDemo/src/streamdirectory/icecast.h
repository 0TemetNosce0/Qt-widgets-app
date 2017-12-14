#ifndef ICECAST_H
#define ICECAST_H

#include <QPointer>
#include <KIO/CopyJob>
#include <QDir>
#include "streamdirectorymodel.h"
#include "icecast_internalthread.h"

class icecast : public streamDirectoryModel
{
    Q_OBJECT

public:
    explicit icecast(QObject *parent);
    virtual ~icecast();

private:
    QDir m_tempdir;
    QPointer<KIO::CopyJob> m_copyjob;
    icecast_internalThread m_thread;

private slots:
    void process_file(KJob *job);
    void use_data(icecast_internalThread::streamEntryList list);
};

#endif
