#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.resize(800, 600);
    mainWindow.show();

    QFont font = app.font();
    font.setFamily(QStringLiteral("微软雅黑"));
    app.setFont(font);

    // 加载QSS样式表
    QString strFile = QCoreApplication::applicationDirPath() + "/Resources/Style.qss";
    QFile qss(strFile);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    return app.exec();
}
