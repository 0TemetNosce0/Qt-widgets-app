#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Student s1(20, "zhxxx", 411, "158xxxxx", "jsj", "dec");
    Student s2(21, "zhxxx", 411, "158xxxxx", "jsj", "dec");
    Student s3(22, "zhxxx", 411, "158xxxxx", "jsj", "dec");
    Student s4(23, "zhxxx", 411, "158xxxxx", "jsj", "dec");
    Student s5(24, "zhxxx", 411, "158xxxxx", "jsj", "dec");
    Student s6(25, "zhxxx", 411, "158xxxxx", "jsj", "dec");
    Student s7(26, "zhxxx", 411, "158xxxxx", "jsj", "dec");

    QList<Student> students;
    students << s1 << s2 << s3 << s4 << s5 << s6 << s7;

    MainWindow w;
    w.setUpData(students);
    w.setFixedWidth(756);
    w.show();

    return a.exec();
}
