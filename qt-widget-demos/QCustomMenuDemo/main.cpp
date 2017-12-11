#include "custommenu.h"
#include <QApplication>

#include "customstyle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CCustomStyle* pStyle = new CCustomStyle;
    pStyle->setIconSize(QSize(12, 12));
    a.setStyle(pStyle);

    TestDialog w;
    w.show();

    return a.exec();
}
