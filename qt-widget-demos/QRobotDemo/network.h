#ifndef NETWORK
#define NETWORK

#include<QUrl>
#include<QNetworkRequest>
#include<QNetworkAccessManager>

class Network : public QObject
{
    Q_OBJECT

public:
    explicit Network();
    ~Network();

    static Network* instance();
    QNetworkReply* get(QString str);

signals:
    void finished(QNetworkReply*);

private:
    QNetworkAccessManager *manager;
};

#endif // NETWORK

