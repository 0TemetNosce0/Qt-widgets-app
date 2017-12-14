#include "player.h"
#include "skin.h"
#include "initialconfig.h"
#include "framelesshelper.h"
#include <QApplication>
#include <QStyleFactory>
#include <QTranslator>
#include <QLocale>
#include <QFile>
#include <QSettings>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Check if another instance has been started already
    QSharedMemory sharedMemory;
    sharedMemory.setKey("neu");

    if (!sharedMemory.create(1))
    {
        QMessageBox::warning(nullptr, QObject::tr("Warning!"), QObject::tr("An instance of this application is running!"));
        exit(0); // Exit process immediately
    }

    QSettings settings("neuPlayer.ini", QSettings::IniFormat);

    // Init Trad engine
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    //Load correct translation based on system locale
    translator.load("neuplayer_" + locale);
    a.installTranslator(&translator);
    //Setup actual window
    qApp->setStyle(QStyleFactory::create("Fusion")); //base theme fusion

    if(settings.value("skin", 1).toInt() == 1 || settings.value("skin", 1).toInt() == 3)
    {
        Skin HoloFusion(1, nullptr);
        HoloFusion.load();
    }

    else
    {
        Skin CleanFusion(0, nullptr);
        CleanFusion.load();
    }
    //Ready to show
    //Create the helper so it isn't destroyed right away
    NcFramelessHelper helper(nullptr);
    QFile fileHandler(".configdone"); //So you config before anything else
    if(!fileHandler.exists()) //If there is the config to do, the config will launch the app when done
    {
        QPointer <InitialConfig> config = new InitialConfig();
        config->show();
    }
    else
    {
        Player *neuPlayer = new Player(nullptr);
        if(settings.value("Additional_Features/framelessWindow", false).toBool())
        {
            if(settings.value("visibilite").toBool())
                helper.activateOn(neuPlayer, true);
            else
                helper.activateOn(neuPlayer);
        }
        neuPlayer->show();
    }
    fileHandler.close();

    return a.exec();
}
