#include "cciphercontext.h"

CCipherContext::CCipherContext(const QString &type,QObject *parent)
    : QObject(parent)
    , m_type(type)
{
}

CCipherContext::~CCipherContext()
{
}
