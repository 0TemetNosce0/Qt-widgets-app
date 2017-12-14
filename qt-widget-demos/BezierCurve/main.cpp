#include "gui.h"
#include <QApplication>

using namespace std;

int main( int argc, char* argv[])
{
        QApplication a(argc, argv);
        gui fenster;
        
        fenster.show();
        
        return a.exec();
}

