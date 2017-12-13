#include "builtindlg.h"
#include <QApplication>
#include <QTextCodec>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&app);
    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
        app.installTranslator(translator);
    }
    /*
    //QStringList environment = QProcess::systemEnvironment();
    //foreach(str, environment) {
    //    if(str.startsWith("QTDIR=")) {
    //        break;
    //    }
    //}
    bool bFinded = false;
    QString str = "QTDIR=/usr/share/qt4";
    str = str.mid(6);
    bFinded = translator.load("qt_" + QLocale::system().name(), str.append("/translations/"));
    if(bFinded) {
        qApp->installTranslator(&translator);
        qDebug() << QObject::tr("支持中文的Qt国际化翻译文件！");
    }
    else {
        qDebug() << QObject::tr("没有支持中文的Qt国际化翻译文件！");
    }
    */
    CBuiltinDlg w;
    w.show();

    return app.exec();
}
