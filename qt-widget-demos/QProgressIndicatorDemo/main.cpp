#include <QApplication>
#include <QMainWindow>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>

#include "QProgressIndicator.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    QMainWindow * mw = new QMainWindow;

    QProgressIndicator* pProgressIndicator = new QProgressIndicator();

    QFrame* frame = new QFrame;

    QVBoxLayout* pVLayout = new QVBoxLayout;

    QPushButton* startPb = new QPushButton("start spin");
    QObject::connect(startPb, SIGNAL(clicked(bool)), pProgressIndicator, SLOT(startAnimation()));

    QPushButton* stopPb = new QPushButton("stop spin");
    QObject::connect(stopPb, SIGNAL(clicked(bool)), pProgressIndicator, SLOT(stopAnimation()));

    QSlider* delaySlider = new QSlider;
    delaySlider->setRange(0, 100);
    delaySlider->setValue(pProgressIndicator->animationDelay());
    delaySlider->setOrientation(Qt::Horizontal);
    QObject::connect(delaySlider, SIGNAL(valueChanged(int)), pProgressIndicator, SLOT(setAnimationDelay(int)));

    pVLayout->addWidget(startPb);
    pVLayout->addWidget(stopPb);
    pVLayout->addWidget(delaySlider);

    QHBoxLayout* hbl = new QHBoxLayout(frame);
    hbl->addWidget(pProgressIndicator);
    hbl->addLayout(pVLayout);

    pProgressIndicator->startAnimation();

    mw->setCentralWidget(frame);

    mw->show();

    return app.exec();
}
