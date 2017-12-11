#ifndef UTIL_H
#define UTIL_H

#include <QString>

struct ToolUtil
{
    int parentId;
    int id;
    QString text;
    QString tooltip;
    QString toolicon;
};

class Util
{

public:
    static QString exePath();
    static QList<ToolUtil> parse(QString file_name);

};

#endif
