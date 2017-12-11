#include "mrichtextedit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MRichTextEdit w;
    w.show();

    return a.exec();
}
