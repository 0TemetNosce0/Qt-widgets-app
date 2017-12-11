#include <QApplication>
#include "textedit.h"

#include <QSplashScreen>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/images/yafeilinux.gif");
    QSplashScreen splash(pixmap);//³ÌÐòÆô¶¯»­Ãæ
    for(qint64 i = 1111111 * 6; i > 0; i--)
    {
        splash.show();
    }

    TextEdit w;
    w.show();

    splash.finish(&w);

    return a.exec();
}
