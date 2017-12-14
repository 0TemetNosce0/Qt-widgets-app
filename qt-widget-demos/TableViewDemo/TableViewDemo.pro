#-------------------------------------------------
#
# Project created by QtCreator 2014-03-10T17:41:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TableViewDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    student.cpp \
    customdelegate.cpp \
    insertwidget.cpp

HEADERS  += mainwindow.h \
    student.h \
    customdelegate.h \
    insertwidget.h

FORMS    += mainwindow.ui \
    insertwidget.ui
