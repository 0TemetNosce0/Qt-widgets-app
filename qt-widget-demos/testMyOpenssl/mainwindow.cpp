#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>
#include "copensslciphercontext.h"
#include "cciphermanger.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
    OpenSSL_add_all_algorithms();

    QString type = "aes128-cbc-pkcs7";
    COpensslCipherContext temp ( EVP_aes_128_cbc(), 1, type);

    QByteArray key("1234567890123456");
    QByteArray iv(key);

    QByteArray s = "zhangjunhua4101132";
    QByteArray  encryptedData = temp.process(Encode,key,iv,s);


    QByteArray decryptedData = temp.process(Decode,key,iv,encryptedData);


    EVP_cleanup();
    */

    COpensslCipherContext* temp = NULL;
    temp = static_cast<COpensslCipherContext*>(CCipherManger::share()->createContext("aes128-cbc-pkcs7"));


    QByteArray s = "zhangjunhua4101132";
    if(temp)
    {
        //key 和 iv 必须为16位
        QByteArray key("1234567890123456");
        QByteArray iv(key);
        QByteArray  encryptedData = temp->process(Encode,key,iv,s);
        qDebug() << "encryptedData:" << encryptedData;
        QByteArray decryptedData = temp->process(Decode,key,iv,encryptedData);
        qDebug() << "decryptedData:" << decryptedData;

        delete temp;
        temp = NULL;
    }

}

MainWindow::~MainWindow()
{
    CCipherManger::purgeShare();
    delete ui;
}
