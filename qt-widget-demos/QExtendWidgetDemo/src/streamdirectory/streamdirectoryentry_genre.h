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

#ifndef STREAMDIRECTORYENTRY_GENRE_H
#define STREAMDIRECTORYENTRY_GENRE_H

#include "streamdirectoryentry.h"

/** \brief Data type representing a stream.
*
* This data type represents a genre inside of a tree structure. */
class streamDirectoryEntry_genre : public streamDirectoryEntry
{
public:
    /** The constructor. */
    streamDirectoryEntry_genre();
    /** The destructor. */
    virtual ~streamDirectoryEntry_genre();
    virtual bool canFetchMore() const;
    virtual QVariant data(const int column) const;
    virtual void fetchMore();
    /** \returns whether there are streams for */
    virtual bool hasChildren() const;
    bool internal_canFetchMore;

private:
    bool streamFetchingHasTerminated;
    bool streamsHaveYetBeenRequested;
};

#endif
