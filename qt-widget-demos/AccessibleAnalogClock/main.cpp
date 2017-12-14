#include "analogclock.h"
#include "accessibleclock.h"
#include <QAccessible>
#include <QApplication>

QAccessibleInterface *clockFactory(const QString &classname, QObject *object)
{
    QAccessibleInterface *interface = 0;

    if (object && object->isWidgetType())
    {
        interface = new AccessibleClock(static_cast<QWidget *>(object));
    }

    return interface;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QAccessible::installFactory(clockFactory);
    AnalogClock analogClock;
    analogClock.show();
    return a.exec();
}
