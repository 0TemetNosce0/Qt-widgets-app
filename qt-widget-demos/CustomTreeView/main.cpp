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
    font.setFamily(QStringLiteral("΢���ź�"));
    app.setFont(font);

    // ����QSS��ʽ��
    QString strFile = QCoreApplication::applicationDirPath() + "/Resources/Style.qss";
    QFile qss(strFile);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    return app.exec();
}
