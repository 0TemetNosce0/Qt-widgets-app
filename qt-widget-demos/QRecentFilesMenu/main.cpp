#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setOrganizationName("QtApp");
    QApplication::setApplicationName("Recent Files Example");

    MainWindow *mainWin = new MainWindow;
    mainWin->show();
    return app.exec();
}
