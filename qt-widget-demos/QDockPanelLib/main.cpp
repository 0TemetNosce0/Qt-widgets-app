#include "QDockManager.h"
#include "QDockFrame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDockManager* manager = new QDockManager(NULL);
    QDockFrame* frame = manager->getDockFrame();
    frame->resize(700, 500);
    frame->show();
    QWidget* widget1 = new QWidget;
    widget1->setAutoFillBackground(true);
    widget1->setPalette(QPalette(Qt::red));
    manager->addPanel(1, "test1111", QPoint(110, 110), QSize(200, 200), widget1);
    QWidget* widget2 = new QWidget;
    widget2->setAutoFillBackground(true);
    widget2->setPalette(QPalette(QColor(255, 97, 0)));
    manager->addPanel(2, "test2222", QPoint(120, 120), QSize(200, 200), widget2);
    QWidget* widget3 = new QWidget;
    widget3->setAutoFillBackground(true);
    widget3->setPalette(QPalette(Qt::yellow));
    manager->addPanel(3, "test3333", QPoint(130, 130), QSize(200, 200), widget3);
    QWidget* widget4 = new QWidget;
    widget4->setAutoFillBackground(true);
    widget4->setPalette(QPalette(Qt::green));
    manager->addPanel(4, "test4444", QPoint(140, 140), QSize(200, 200), widget4);
    QWidget* widget5 = new QWidget;
    widget5->setAutoFillBackground(true);
    widget5->setPalette(QPalette(Qt::blue));
    manager->addPanel(5, "test5555", QPoint(150, 150), QSize(200, 200), widget5);
    QWidget* widget6 = new QWidget;
    widget6->setAutoFillBackground(true);
    widget6->setPalette(QPalette(QColor(6, 82, 121)));
    manager->addPanel(6, "test6666", QPoint(160, 160), QSize(200, 200), widget6);
    QWidget* widget7 = new QWidget;
    widget7->setAutoFillBackground(true);
    widget7->setPalette(QPalette(QColor(255, 0, 255)));
    manager->addPanel(1, "test7777", QPoint(170, 170), QSize(200, 200), widget7);


    return a.exec();
}
