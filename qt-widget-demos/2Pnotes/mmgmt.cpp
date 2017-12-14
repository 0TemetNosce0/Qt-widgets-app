// File mmgmt.cpp
// Memory management for 2Pnotes data

#include <stdio.h>
#include "mmgmt.h"

mmgmt::mmgmt()
{
    //separator for strings in the list
    sep = '\01';
    
    //Create an empty Stringlist
    slist = new QStringList();
}

mmgmt::~mmgmt()
{
    delete slist;
}

bool mmgmt::listIsEmpty(void)
{
    //return true is list is empty
    return slist->isEmpty();
}

int mmgmt::countOfItems(void)
{
    //return the number of items in the list
    return slist->size();
}

void mmgmt::delAllContent(void)
{
    //delete the content of the strlist, not the strlist itself
    slist->clear();
}

bool mmgmt::deleteRecord(int index)
{
    //return true, if record successful deleted
    
    if(!slist->isEmpty())
    {
        if(index>=0 && index<slist->size())
        {
            slist->removeAt(index);
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

QString mmgmt::getBookmark(int index)
{
    //return the bookmark or a null string
    
    if(!slist->isEmpty())
    {
        if(index>=0 && index<slist->size())
        {
            QStringList list;
            list = slist->at(index).split(sep);
            return list.at(0);
        }
        else
        {
            return QString();
        }
    }
    else
    {
        return QString();
    }
}

QString mmgmt::getPassword(int index)
{
    //return the password or a null string
    
    if(!slist->isEmpty())
    {
        if(index>=0 && index<slist->size())
        {
            QStringList list;
            list = slist->at(index).split(sep);
            return list.at(1);
        }
        else
        {
            return QString();
        }
    }
    else
    {
        return QString();
    }
}

QString mmgmt::getRemarks(int index)
{
    //return the remark or a null string
    if(!slist->isEmpty())
    {
        if(index>=0 && index<slist->size())
        {
            QStringList list;
            list = slist->at(index).split(sep);
            return list.at(2);
        }
        else
        {
            return QString();
        }
    }
    else
    {
        return QString();
    }
}

QString mmgmt::getListItem(int index)
{
    //return the full string at position item or a null string.
    //The string includes the parts bookmark, password, remarks and the separator char.
    //This function is usefull to copy the data into another Stringlist.
    
    if(!slist->isEmpty())
    {
        if(index >= 0 && index < slist->size())
        {
            return slist->at(index);
        }
        else
        {
            return QString();
        }
    }
    else
    {
        return QString();
    }
}

void mmgmt::appendListItem(QString item)
{
    //append the QString item at the end of the list.
    //The string must include the parts bookmark, password, remarks and the separator char.
    //This function is usefull to copy the data into another Stringlist.
    
    slist->append(item);
}

void mmgmt::insertString(int index, int pos, QString c)
{
    //insert QString c into QStringlist(index)at position pos.
    //pos=0 - bookmark, pos=1 - password, pos=2 - remarks
    
    if(!slist->isEmpty())
    {
        if(index < 0 || index > slist->size())
        {
            qWarning("Module mmgmt.cpp, func. insertString: index out of range.");
        }
        else
        {
            if(pos < 0 || pos > 2)
            {
                qWarning("Module mmgmt.cpp, func. insertString: pos out of range.");
            }
            else
            {
                QString i = slist->at(index);
                QStringList l = i.split(sep);

                l.removeAt(pos);
                l.insert(pos, c);
                i.clear();
                i = l.join(sep);
                slist->removeAt(index);
                slist->insert(index, i);
            }
        }
    }
    else
    {
        qWarning("Module mmgmt.cpp, func. insertString: QStringList slist is empty");
    }
}

int mmgmt::insertRecord(QString* b, QString* p, QString* r)
{
    /*insert a record into the list l (in alphbetical order),
    using the string b. Insert at first position if the list is empty
    if the content of *b exists into the list, a number is added to *b.
    return the index of the inserted string, */

    QStringList list;
    QString element, cp, ex;
    int i = 0, c, z = 2;
    
    cp = *b;
    
    if(!slist->isEmpty())
    {
        do
        {
            element = slist->at(i);
            list = element.split(sep);
            c = QString::localeAwareCompare(list.at(0), cp);
            
            if(c>0) //exit loop, insert record
            {
                break;
            }

            if(c == 0) //strings identical, append an extension to the new string
            {
                cp = *b;
                ex.clear();
                ex.setNum(z);
                ex.prepend(" - ");
                
                switch(z)
                {
                case 2:
                    ex += "nd";
                    break;
                case 3:
                    ex += "rd";
                    break;
                default:
                    ex += "th";
                }
                cp += ex;
                z++;
            }
            i++;
        }while(i<slist->size());
    }
    
    //insert, prepend or append the new record
    element.clear();
    element+=*b+ex+sep+*p+sep+*r;
    slist->insert(i, element);

    return i;
}

int mmgmt::insertEditedRecord(int oldindex, QString* b, QString* p, QString* r)
{
    slist->removeAt(oldindex);          // del old record
    return insertRecord(b, p, r);       // insert edited string like a new record
}
