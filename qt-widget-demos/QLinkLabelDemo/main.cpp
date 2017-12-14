#include <QWidget>
#include <QHBoxLayout>
#include <QApplication>

#include "LinkLabel.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    LinkLabel *linkLabel = new LinkLabel;
    linkLabel->setLinkRange(0, 101);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(linkLabel);

    QWidget widget;
    widget.resize(700, 300);
    widget.setLayout(mainLayout);
    widget.show();

    return app.exec();
}
