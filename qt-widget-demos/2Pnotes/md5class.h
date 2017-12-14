//File md5class.h
//Headerfile for the MD5 Message-Digest Algorithm derived from the RSA Data
//Security, Inc. Adapted to the Qt Framework.

#ifndef MD5CLASS_H
#define MD5CLASS_H


#include "md5hash.h"
#include <QString>
#include <QByteArray>

class md5class:private MD5Hash
{
    public:

        QByteArray md5FromStr(QString* string);
        QByteArray md5FromFile(QString * filename);
        void md5test(void);
};

#endif
