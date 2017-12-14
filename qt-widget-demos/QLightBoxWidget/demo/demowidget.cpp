#include "demowidget.h"
#include <qlightboxwidget.h>

#include <QLabel>
#include <QMovie>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>

DemoWidget::DemoWidget(QWidget* _parent)
    : QWidget(_parent)
{
    QLightBoxWidget* lightBox = new QLightBoxWidget(this);

    QLabel* text = new QLabel("Some information in <b>html</b> format<br/>"
                              "<ul><li>one</li><li>two</li><li>three</li></ul>");
    QLabel* image = new QLabel;
    image->setPixmap(QPixmap(":/image.jpg"));
    QPushButton* showLB = new QPushButton(tr("Show"));

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(text, 0, 0, Qt::AlignTop);
    mainLayout->addWidget(image, 0, 1);
    mainLayout->addWidget(showLB, 1, 1);

    this->setLayout(mainLayout);

    QLabel* lbTitle = new QLabel(tr("QLightBoxWidget"));
    lbTitle->setStyleSheet("font-size: 28px; font-weight: bold; color: white");
    QLabel* lbProgress = new QLabel;
    QMovie* progressMovie = new QMovie(":/loader.gif");
    lbProgress->setMovie(progressMovie);
    progressMovie->start();
    QLabel* lbDescription = new QLabel(tr("Example how to use QLightBoxWidget\n"
                                          "in your QtWidgets applications..."));
    lbDescription->setStyleSheet("color: white");
    QPushButton* lbClose = new QPushButton(tr("Close"));

    QGridLayout* lbLayout = new QGridLayout;
    lbLayout->setRowStretch(0, 1);
    lbLayout->setColumnStretch(0, 1);
    lbLayout->addWidget(lbTitle, 1, 1);
    lbLayout->addWidget(lbProgress, 1, 2, Qt::AlignRight);
    lbLayout->setColumnStretch(3, 1);
    lbLayout->addWidget(lbDescription, 2, 1, 1, 2);
    lbLayout->addWidget(lbClose, 3, 2);
    lbLayout->setRowStretch(4, 1);

    connect(showLB, SIGNAL(clicked()), lightBox, SLOT(show()));
    connect(lbClose, SIGNAL(clicked()), lightBox, SLOT(hide()));
    lightBox->setLayout(lbLayout);
}
