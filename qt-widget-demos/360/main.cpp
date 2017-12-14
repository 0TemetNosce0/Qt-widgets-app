#include "src/test/mainwidget.h"
#include "src/main/mainwindow.h"

#include <QFile>
#include <QTextCodec>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":/qss/default");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

#ifdef MAIN_TEST
    MainWidget w;
    w.show();
#else
    MainWindow *w = new MainWindow;
    w->show();
#endif

    return a.exec();
}
