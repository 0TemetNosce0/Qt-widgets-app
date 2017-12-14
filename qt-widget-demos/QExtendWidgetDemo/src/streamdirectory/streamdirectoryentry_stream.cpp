/*
    Copyright (C) 2008-2009  Tim Fechtner < urwald at users dot sourceforge dot net >

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License or (at your option) version 3 or any later version
    accepted by the membership of KDE e.V. (or its successor approved
    by the membership of KDE e.V.), which shall act as a proxy
    defined in Section 14 of version 3 of the license.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "streamdirectoryentry_stream.h"

#include <QLocale>

streamDirectoryEntry_stream::streamDirectoryEntry_stream()
{
    name().clear();
    bitrate = 0;
    currentlyPlaying = false;
    streamType = unknown;
}

streamDirectoryEntry_stream::~streamDirectoryEntry_stream()
{

}

QString streamDirectoryEntry_stream::formatedStreamType(const type_of_stream streamType)
{
    switch (streamType)
    {
    case unknown:
        return QVariant("@info/plain type of the stream: unknown", "unknown");
    case mp3:
        return QVariant(
                    "@info/plain type of the stream: codec is MP3 (http://en.wikipedia.org/wiki/MP3)",
                    "MP3");
    case ogg:
        return QVariant(
                    "@info/plain type of the stream: container format is Ogg (http://en.wiki"
                    "pedia.org/wiki/Ogg)",
                    "Ogg");
    case nsv:
        return QVariant(
                    "@info/plain type of the stream: container format is NSV (http://en.wiki"
                    "pedia.org/wiki/Nullsoft_Streaming_Video)",
                    "NSV");
    case aac:
        return QVariant(
                    "@info/plain type of the stream: codec is AAC (http://en.wiki"
                    "pedia.org/wiki/Advanced_Audio_Coding)",
                    "AAC");
    case aac_plus:
        return QVariant(
                    "@info/plain type of the stream: codec is AACplus (http://en.wikipedia.org/wiki/AACplus)",
                    "AACplus");
    default:
        return QString();
    }
}

QVariant streamDirectoryEntry_stream::rawData(const int column) const
{
    if (column == 2)
    {
        return bitrate;
    }
    else
    {
        return data(column);
    }
}

QVariant streamDirectoryEntry_stream::data(const int column) const
{
    switch (column)
    {
    case 0:
        return name();
    case 1:
        return formatedStreamType(streamType);
    case 2:
        if (bitrate <= 0)
        {
            return QVariant();
        }
        else
        {
            return QVariant(
                        "@item This makes a nicly formated string for the bitrate of a stream - %1 is an "
                        "integer. WARNING: Unit has changed! It is now kbit instead of Kibit. "
                        "This means 1000 bit (NOT 1024).",
                        "%1 kbit/s",
                        "%1 kbit/s",
                        bitrate);
        }
    case 3:
        if (currentlyPlaying)
        {
            return QString("@item:intable Whether the stream provides (in its meta data) information "
                         "about the currently played song",
                         "yes");
        }
        else
        {
            return QString("@item:intable Whether the stream provides (in its meta data) information "
                         "about the currently played song",
                         "no");
        }
    case 4:
        return value().url();
    default:
        return QVariant();
    }
}

bool streamDirectoryEntry_stream::hasChildren() const
{
    return false;
}
