//File md5class.cpp
//MD5 Message-Digest Algorithm derived from the RSA Data
//Security, Inc. Adapted to the Qt Framework.
//This class produced safe hashvalues for strings and files.

#include "md5class.h"
#include "md5.cpp"


QByteArray md5class::md5FromStr(QString* string)
{
    // Return the MD5 hash of the referred string. 
    // The return value is null terminated.
    //  string is converted to Utf8. It works with all unicode symbols.

    QByteArray m(33, 0);
    QByteArray r(16, 0);

    QByteArray a = string->toLatin1();

    MD5String(a.data(), (unsigned int)a.size(), (unsigned char*)r.data());
    MD52hex(m.data(), (unsigned char*)r.data());

    return m;
}

QByteArray md5class::md5FromFile(QString * filename)
{
    // Return the MD5 hash of the referred filename.
    // The return value is null terminated.
    // filename is converted from unicode to ascii.

    QByteArray m(33, 0);
    QByteArray r(16, 0);

    QByteArray f = filename->toLatin1();
    MD5File(f.data(), (unsigned char*)r.data());
    MD52hex(m.data(), (unsigned char*)r.data());

    return m;
}

void md5class::md5test(void)
{
    MD5TestSuite();
}
