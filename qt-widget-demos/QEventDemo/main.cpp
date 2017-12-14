#include <QApplication>
#include "eventform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EventForm eventForm;
    eventForm.show();

    return a.exec();
}
