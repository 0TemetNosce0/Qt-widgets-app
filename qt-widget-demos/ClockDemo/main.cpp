#include <QApplication>

#include "dialog.h"
#include "digiclock.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DigiClock clock;
    clock.show();

    return a.exec();
}
