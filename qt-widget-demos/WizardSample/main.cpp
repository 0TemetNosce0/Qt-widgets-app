#include "wizardsample.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WizardSample w;
    w.show();
    return a.exec();
}
