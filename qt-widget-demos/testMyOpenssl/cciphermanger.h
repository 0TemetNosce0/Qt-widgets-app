#ifndef CCIPHERMANGER_H
#define CCIPHERMANGER_H

#include <QObject>
#include <QStringList>

#include "cciphercontext.h"

class CCipherManger : public QObject
{
    Q_OBJECT
public:
    static CCipherManger* share();
    static void purgeShare();
public:
    QStringList features() const
    {
        QStringList list;
        list += "aes128-cbc-pkcs7";
        return list;
    }
public:
    CCipherContext *createContext(const QString &type);
private:
    explicit CCipherManger(QObject *parent = 0);
    ~CCipherManger();
    
signals:
    
public slots:

private:
    static CCipherManger* m_itself;
    
};

#endif // CCIPHERMANGER_H
