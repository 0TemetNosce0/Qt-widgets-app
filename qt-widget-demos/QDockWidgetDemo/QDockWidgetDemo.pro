#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T12:03:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QDockWidgetDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myDockTitleBar.cpp

HEADERS  += mainwindow.h \
    myDockTitleBar.h

FORMS    += mainwindow.ui
