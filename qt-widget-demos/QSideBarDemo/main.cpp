#include <QApplication>
#include "sidebar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SideBar w;

    w.addAction("Library", QIcon(":/icon/stripe.png"));
    w.addAction("Actors");
    w.addAction("Directors");
    w.addAction("Genres");
    w.addAction("Countries");
    w.addAction("Tags");

    w.show();

    return a.exec();
}
