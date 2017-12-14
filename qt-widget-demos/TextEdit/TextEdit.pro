#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T21:08:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextEdit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mymdi.cpp

HEADERS  += mainwindow.h \
    mymdi.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
