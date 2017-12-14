#include "overlaywidget.h"

#include <QLabel>
#include <QMainWindow>
#include <QApplication>
#include <QGraphicsBlurEffect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //    QMainWindow w;
    //    w.resize(900, 600);
    //    new LoadingOverlay(&w);
    //    w.show();

    ContainerWidget base;
    QLabel l("Dewey, Cheatem and Howe, LLC.", &base);
    l.setFont(QFont("times,times new roman", 32));
    l.setAlignment(Qt::AlignCenter);
    l.setGraphicsEffect(new QGraphicsBlurEffect);
    LoadingOverlay overlay(&base);
    base.show();

    return a.exec();
}
