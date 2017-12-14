#ifndef STREAMDIRECTORYENTRY_STREAM_H
#define STREAMDIRECTORYENTRY_STREAM_H

#include "streamdirectoryentry.h"

class streamDirectoryEntry_stream : public streamDirectoryEntry
{
  public:
    streamDirectoryEntry_stream();

    virtual ~streamDirectoryEntry_stream();

    enum type_of_stream
    {
      unknown,
      mp3,
      ogg,
      nsv,
      aac,
      aac_plus
    };

    quint64 bitrate;

    bool currentlyPlaying;

    virtual QVariant data(const int column) const;

    static QString formatedStreamType(const type_of_stream streamType);

    virtual bool hasChildren() const;

    QVariant rawData(const int column) const;

    type_of_stream streamType;
};

#endif
