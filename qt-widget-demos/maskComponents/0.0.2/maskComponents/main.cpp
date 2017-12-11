#include "dialog.h"
#include "CustomNewGuideFacade.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog w;
    w.show();

    CustomNewGuideFacade::execute(&w);

    return a.exec();
}
