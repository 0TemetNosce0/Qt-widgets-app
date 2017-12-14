#include "cciphermanger.h"



#include "copensslciphercontext.h"

CCipherManger* CCipherManger::m_itself = NULL;

CCipherManger* CCipherManger::share()
{
    if(!m_itself)
    {
        m_itself = new CCipherManger();
    }
    return m_itself;
}

void CCipherManger::purgeShare()
{
    if(m_itself)
    {
        delete m_itself;
        m_itself = NULL;
    }
}

CCipherContext *CCipherManger::createContext(const QString &type)
{
    if ( type == "aes128-cbc-pkcs7" )
    {
        return new COpensslCipherContext( EVP_aes_128_cbc(), 1, type);
    }
    else
    {
        return NULL;
    }
}

CCipherManger::CCipherManger(QObject *parent) :
    QObject(parent)
{
    OpenSSL_add_all_algorithms();
}

CCipherManger::~CCipherManger()
{
    EVP_cleanup();
}


