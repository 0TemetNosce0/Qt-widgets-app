#ifndef FILETREEITEMFACTORY_H
#define FILETREEITEMFACTORY_H

#include "WebItemDelegate.h"

class FileTreeItemFactory : public WebItemFactory
{
public:
    virtual QString pageHeader();
    virtual QString itemTemplate(const QModelIndex &index);
    virtual int itemHeight(const QModelIndex &index);
    virtual QStringList itemClasses(const QModelIndex &index);
};

#endif // FILETREEITEMFACTORY_H
