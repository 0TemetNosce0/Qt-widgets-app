#ifndef COPENSSLCIPHERCONTEXT_H
#define COPENSSLCIPHERCONTEXT_H

#include <QObject>
#include <QByteArray>

#include <openssl/evp.h>
#include <openssl/hmac.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <openssl/rand.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/x509v3.h>
#include <openssl/pkcs12.h>
#include <openssl/ssl.h>


#include "cciphercontext.h"

class COpensslCipherContext : public CCipherContext
{
    Q_OBJECT
public:
    COpensslCipherContext(const EVP_CIPHER *algorithm, const int pad, const QString &type,QObject *parent = 0);
    virtual ~COpensslCipherContext();


public:
    /**
     *  @brief aes加密解密的一次调用函数
     *
     */
    QByteArray process(Direction dir,const QByteArray &key, const QByteArray &iv,const QByteArray &a);
public://from CCipherContext
    void setup(Direction dir,const QByteArray &key,const QByteArray &iv);

    int blockSize() const;

    bool update(const QByteArray &in, QByteArray *out);

    bool final(QByteArray *out);

public:
signals:
    
public slots:

 protected:
    EVP_CIPHER_CTX m_context;
    const EVP_CIPHER *m_cryptoAlgorithm;
    Direction m_direction;
    int m_pad;
    
};

#endif // COPENSSLCIPHERCONTEXT_H
