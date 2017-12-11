#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QLocale>
#include <QString>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
     
#ifndef HAVE_QT5
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));
#endif

    QTranslator translator;
    QString locale = QLocale::system().name();

    if (translator.load(QString("qnetstatview_") + locale) == false)
    {
        translator.load(QString("/usr/share/qnetstatview/qnetstatview_") + locale);
    }
    app.installTranslator(&translator);

    MainWindow window;
    window.resize(800,600);
    window.show();

    return app.exec();
}

