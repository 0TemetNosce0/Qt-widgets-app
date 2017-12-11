#include "icecast.h"
#include <KIO/CopyJob>
#include <QUrl>

icecast::icecast(QObject *parent)
    : streamDirectoryModel(parent)
{
    qRegisterMetaType<icecast_internalThread::streamEntryList>();
    m_copyjob = KIO::copy(QUrl("http://dir.xiph.org/yp.xml"),
                          QUrl::fromLocalFile(m_tempdir.dirName()),
                          KIO::HideProgressInfo);
    connect(m_copyjob, SIGNAL(result(KJob *)), this, SLOT(process_file(KJob *)));
}

icecast::~icecast()
{
    if (!m_copyjob.isNull())
    {
        m_copyjob->kill();
    }
}

void icecast::process_file(KJob *job)
{
    if (job->error() == 0)
    {
        connect(&m_thread,
                SIGNAL(streamlist_ready(icecast_internalThread::streamEntryList)),
                this,
                SLOT(use_data(icecast_internalThread::streamEntryList)));
        m_thread.setFilename(m_tempdir.name() + "/yp.xml");
        m_thread.start();
    }
}

void icecast::use_data(icecast_internalThread::streamEntryList list)
{
    m_tempdir.unlink();
    beginInsertRows(QModelIndex(), 0, list.count() - 1);
    foreach (streamDirectoryEntry_stream *entry, list)
    {
        rootEntry->appendChild(entry);
    }
    endInsertRows();
    disconnect(this, SLOT(use_data(icecast_internalThread::streamEntryList)));
}
