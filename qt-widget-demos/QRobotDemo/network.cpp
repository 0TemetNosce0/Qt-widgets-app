#include"network.h"

Network::Network()
    : manager(new QNetworkAccessManager())
{
    connect(manager, SIGNAL(finished(QNetworkReply*))
            , this, SIGNAL(finished(QNetworkReply*)));
}

Network::~Network()
{
    delete manager;
}

Network *Network::instance()
{
    static Network net;
    return &net;
}

QNetworkReply *Network::get(QString str)
{
    return manager->get(QNetworkRequest(QUrl(str)));
}
