#include "dpisupport.h"

#include <QApplication>
#include <QDesktopWidget>

int adjustHardcodedPixelSize(int size)
{
    static int dpi = qApp->desktop()->logicalDpiX();
    return size*dpi / 96;
}
