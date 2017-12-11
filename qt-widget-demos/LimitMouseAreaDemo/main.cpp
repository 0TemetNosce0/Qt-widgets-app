#include "mainwindow.h"
#include <QApplication>
#include <windows.h>
#include <windef.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    RECT mainWinRect; //RECT在windef.h中被定义
    mainWinRect.left = (LONG)w.geometry().left();
    mainWinRect.right = (LONG)w.geometry().right();
    mainWinRect.top = (LONG)w.geometry().top();
    mainWinRect.bottom = (LONG)w.geometry().bottom();

    ClipCursor(&mainWinRect); //这是Windows API
    /*****************************************************************************
     *  如果你想取消限制，那么可以调用ClipCursor(NULL)来释放对鼠标的限制
     *
     *  另外要注意的是：
     *  ①假如你要限制鼠标在xxWidget内，只能等xxWidget实例被构建之后才能限制鼠标范围
     *  ②如果在鼠标受限的时候，用户按下了Windows键，那么当前的窗口失去鼠标，鼠标受限会被取消
     *****************************************************************************/

    return a.exec();
}
