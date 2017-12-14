#include "icecast_internalthread.h"

#include <QFile>
#include <QMutexLocker>

icecast_internalThread::icecast_internalThread()
{

}

icecast_internalThread::~icecast_internalThread()
{
    wait();
}

void icecast_internalThread::run()
{
    QXmlStreamReader xml;
    QFile yp;
    QString tmpFile;

    filename_mutex.lock();
    tmpFile = filename;
    filename_mutex.unlock();
    yp.setFileName(tmpFile);
    yp.open(QIODevice::ReadOnly);
    xml.setDevice(&yp);
    streamList.clear();
    while (!xml.atEnd())
    {
        xml.readNext();
        if (xml.isStartElement() && (xml.name() == "entry"))
        {
            readStreamEntry(xml);
        }
    }
    emit streamlist_ready(streamList);
}

void icecast_internalThread::readStreamEntry(QXmlStreamReader & reader)
{
    streamDirectoryEntry_stream *streamEntry = new streamDirectoryEntry_stream();
    while (!((reader.isEndElement() && (reader.name() == "entry")) || reader.atEnd()))
    {
        reader.readNext();
        if (reader.isStartElement())
        {
            if (reader.name() == "server_name")
            {
                streamEntry->setName(reader.readElementText());
            }
            else if (reader.name() == "listen_url")
            {
                streamEntry->setValue(reader.readElementText());
            }
            else if (reader.name() == "server_type")
            {
                QString m_servertype = reader.readElementText();
                if (m_servertype == "audio/aacp")
                {
                    streamEntry->streamType = streamDirectoryEntry_stream::aac_plus;
                }
                else if (m_servertype == "audio/aac")
                {
                    streamEntry->streamType = streamDirectoryEntry_stream::aac;
                }
                else if (m_servertype == "audio/mpeg")
                {
                    streamEntry->streamType = streamDirectoryEntry_stream::mp3;
                }
                else if (m_servertype == "application/ogg")
                {
                    streamEntry->streamType =  streamDirectoryEntry_stream::ogg;
                }
                else if (m_servertype == "video/nsv")
                {
                    streamEntry->streamType =  streamDirectoryEntry_stream::nsv;
                }
                else
                {
                    streamEntry->streamType = streamDirectoryEntry_stream::unknown;
                }
            }
            else if (reader.name() == "bitrate")
            {
                streamEntry->bitrate = reader.readElementText().toULongLong();
                if (streamEntry->bitrate >= 1024)
                {
                    streamEntry->bitrate = streamEntry->bitrate / 1024;
                }
            }
            else if (reader.name() == "current_song")
            {
                streamEntry->currentlyPlaying = !(reader.readElementText().trimmed().isEmpty());
            }
        }
    }
    streamList.append(streamEntry);
}

void icecast_internalThread::setFilename(QString newFilename)
{
    QMutexLocker locker(&filename_mutex);
    filename = newFilename;
}
