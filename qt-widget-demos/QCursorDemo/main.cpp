#include "cursor.h"
#include <QApplication>
#include <QTranslator>

int main( int argc, char **argv )
{
    QFont font("ZYSong18030",12);
    QApplication::setFont(font);
    	
    QApplication a( argc, argv );
    QTranslator translator(0);
    translator.load("cursor_zh",".");
    a.installTranslator(&translator);    
    
    Cursor *cursor = new Cursor();
    cursor->show();
    return a.exec();
}
