#include "streamdirectoryentry_root.h"

streamDirectoryEntry_root::streamDirectoryEntry_root()
{

}

streamDirectoryEntry_root::~streamDirectoryEntry_root()
{

}

bool streamDirectoryEntry_root::hasChildren() const
{
    return (childCount() > 0);
}
