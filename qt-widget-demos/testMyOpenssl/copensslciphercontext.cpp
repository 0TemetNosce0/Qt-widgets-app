#include "copensslciphercontext.h"


COpensslCipherContext::~COpensslCipherContext()
{
    EVP_CIPHER_CTX_cleanup(&m_context);
}

COpensslCipherContext::COpensslCipherContext(const EVP_CIPHER *algorithm, const int pad, const QString &type, QObject *parent)
   : CCipherContext(type,parent)
   , m_cryptoAlgorithm(algorithm)
   , m_direction(Unknowcode)
   , m_pad(pad)
{
    EVP_CIPHER_CTX_init(&m_context);
}

QByteArray COpensslCipherContext::process(Direction dir,const QByteArray &key, const QByteArray &iv,const QByteArray &a)
{
    setup(dir,key,iv);

    QByteArray updateOut;
    bool ok = update(a, &updateOut);
    if(!ok)
    {
        return QByteArray();
    }

    QByteArray finalOut;
    ok = final(&finalOut);
    if(!ok)
    {
        return QByteArray();
    }

    QByteArray out;
    out = updateOut + finalOut;
    return out;
}

void COpensslCipherContext::setup(Direction dir, const QByteArray &key, const QByteArray &iv)
{
    m_direction = dir;
    if ( ( m_cryptoAlgorithm == EVP_des_ede3() ) && (key.size() == 16) ) {
        // this is really a two key version of triple DES.
        m_cryptoAlgorithm = EVP_des_ede();
    }
    if (Encode == m_direction) {
        EVP_EncryptInit_ex(&m_context, m_cryptoAlgorithm, 0, 0, 0);
        EVP_CIPHER_CTX_set_key_length(&m_context, key.size());
        EVP_EncryptInit_ex(&m_context, 0, 0,
                   (const unsigned char*)(key.data()),
                   (const unsigned char*)(iv.data()));
    } else {
        EVP_DecryptInit_ex(&m_context, m_cryptoAlgorithm, 0, 0, 0);
        EVP_CIPHER_CTX_set_key_length(&m_context, key.size());
        EVP_DecryptInit_ex(&m_context, 0, 0,
                   (const unsigned char*)(key.data()),
                   (const unsigned char*)(iv.data()));
    }

    EVP_CIPHER_CTX_set_padding(&m_context, m_pad);
}

int COpensslCipherContext::blockSize() const
{
    return EVP_CIPHER_CTX_block_size(&m_context);
}

bool COpensslCipherContext::update(const QByteArray &in, QByteArray *out)
{
    // This works around a problem in OpenSSL, where it asserts if
    // there is nothing to encrypt.
    if ( 0 == in.size() )
        return true;

    out->resize(in.size()+blockSize());
    int resultLength;
    if (Encode == m_direction) {
        if (0 == EVP_EncryptUpdate(&m_context,
                       (unsigned char*)out->data(),
                       &resultLength,
                       (unsigned char*)in.data(),
                       in.size())) {
            return false;
        }
    } else {
        if (0 == EVP_DecryptUpdate(&m_context,
                       (unsigned char*)out->data(),
                       &resultLength,
                       (unsigned char*)in.data(),
                       in.size())) {
            return false;
        }
    }
    out->resize(resultLength);
    return true;
}

bool COpensslCipherContext::final(QByteArray *out)
{
    out->resize(blockSize());
    int resultLength;
    if (Encode == m_direction) {
        if (0 == EVP_EncryptFinal_ex(&m_context,
                         (unsigned char*)out->data(),
                         &resultLength)) {
            return false;
        }
    } else {
        if (0 == EVP_DecryptFinal_ex(&m_context,
                         (unsigned char*)out->data(),
                         &resultLength)) {
            return false;
        }
    }
    out->resize(resultLength);
    return true;
}
