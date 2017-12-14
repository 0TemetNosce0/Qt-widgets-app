// File mmgmt.h
// Application 2Pnotes 2.0.5

#ifndef MMGMT_H
#define MMGMT_H

#include <QStringList>

class mmgmt
{
public:
    mmgmt();
    ~mmgmt();

    bool listIsEmpty(void);
    int countOfItems(void);
    void delAllContent(void);
    bool deleteRecord(int index);
    QString getBookmark(int index);
    QString getPassword(int index);
    QString getRemarks(int index);
    QString getListItem(int index);
    void appendListItem(QString item);
    void insertString(int index, int pos, QString c);
    int insertRecord(QString* b, QString* p, QString* r);
    int insertEditedRecord(int oldindex, QString* b, QString* p, QString* r);

private:
    QString sep;
    QStringList* slist;
};

#endif
