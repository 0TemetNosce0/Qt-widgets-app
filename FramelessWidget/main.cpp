#include <QApplication>
#include "MainWidget.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QApplication a(argc, argv);

    CMainWidget *pWgt = new CMainWidget;
    pWgt->show();

    return a.exec();
}
