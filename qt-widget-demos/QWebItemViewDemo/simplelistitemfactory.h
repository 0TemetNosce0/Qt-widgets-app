#ifndef SIMPLELISTITEMFACTORY_H
#define SIMPLELISTITEMFACTORY_H

#include "WebItemDelegate.h"

class SimpleListItemFactory : public WebItemFactory
{
public:
    virtual QString pageHeader();
    virtual QString itemTemplate(const QModelIndex &index);
    virtual int itemHeight(const QModelIndex &index);
    virtual bool recreateItemOnDataChange(const QModelIndex& index) const;
};

#endif // SIMPLELISTITEMFACTORY_H
