#include "DelegateDemo.h"
#include "GLDApplication.h"
#include <QApplication>
#include <QHash>

int main(int argc, char *argv[])
{
    GLDApplication a(argc, argv);
    DelegateDemo w;
    w.show();
    return a.exec();
}
