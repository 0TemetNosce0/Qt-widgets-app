#ifndef CCIPHERCONTEXT_H
#define CCIPHERCONTEXT_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include "copensslconfig.h"

class CCipherContext : public QObject
{
    Q_OBJECT
public:
    explicit CCipherContext(const QString &type,QObject *parent = 0);
    virtual ~CCipherContext();
signals:
    
public slots:
public:
    virtual void setup(Direction dir, const QByteArray &key, const QByteArray &iv) = 0;

    virtual int blockSize() const = 0;

    virtual bool update(const QByteArray &in, QByteArray *out) = 0;

    virtual bool final(QByteArray *out) = 0;
private:
    QString m_type;
    
};

#endif // CCIPHERCONTEXT_H
