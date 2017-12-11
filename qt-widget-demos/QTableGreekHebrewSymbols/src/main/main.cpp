#include <QApplication>
#include "mainwindow.h"

#include "defines.h"

#include <QTranslator>
#include <QLocale>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName(GL_PROG_NAME);

    MainWindow w;
    w.show();

    return a.exec();
}
