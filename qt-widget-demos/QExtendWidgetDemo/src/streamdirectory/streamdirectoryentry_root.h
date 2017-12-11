#ifndef STREAMDIRECTORYENTRY_ROOT_H
#define STREAMDIRECTORYENTRY_ROOT_H

#include "streamdirectoryentry.h"

class streamDirectoryEntry_root : public streamDirectoryEntry
{
public:
    streamDirectoryEntry_root();
    virtual ~streamDirectoryEntry_root();
    virtual bool hasChildren() const;
};

#endif
