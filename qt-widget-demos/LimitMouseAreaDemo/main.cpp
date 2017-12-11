#include "mainwindow.h"
#include <QApplication>
#include <windows.h>
#include <windef.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    RECT mainWinRect; //RECT��windef.h�б�����
    mainWinRect.left = (LONG)w.geometry().left();
    mainWinRect.right = (LONG)w.geometry().right();
    mainWinRect.top = (LONG)w.geometry().top();
    mainWinRect.bottom = (LONG)w.geometry().bottom();

    ClipCursor(&mainWinRect); //����Windows API
    /*****************************************************************************
     *  �������ȡ�����ƣ���ô���Ե���ClipCursor(NULL)���ͷŶ���������
     *
     *  ����Ҫע����ǣ�
     *  �ټ�����Ҫ���������xxWidget�ڣ�ֻ�ܵ�xxWidgetʵ��������֮�����������귶Χ
     *  �������������޵�ʱ���û�������Windows������ô��ǰ�Ĵ���ʧȥ��꣬������޻ᱻȡ��
     *****************************************************************************/

    return a.exec();
}
