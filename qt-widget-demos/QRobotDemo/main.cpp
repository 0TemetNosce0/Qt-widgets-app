#include<QApplication>
#include"robot.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    Robot r;
    r.show();

    return app.exec();
}
