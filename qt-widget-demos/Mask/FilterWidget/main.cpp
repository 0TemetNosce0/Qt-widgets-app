#include "overlay.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Filter filter;
    QWidget widget;
    QHBoxLayout * layout = new QHBoxLayout(&widget);
    layout->addWidget(new QLabel("Foo"));
    layout->addWidget(new QLabel("Bar"));
    layout->addWidget(new QLabel("Baz"));

    foreach (QObject * obj, widget.children())
    {
        if (obj->isWidgetType()) obj->installEventFilter(&filter);
    }

    widget.show();

    return a.exec();
}
