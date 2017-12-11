#-------------------------------------------------
#
# Project created by QtCreator 2014-12-21T21:42:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlyBird
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    barrier.cpp \
    bird.cpp \
    gamecontroller.cpp \
    roaditem.cpp

HEADERS  += mainwindow.h \
    barrier.h \
    bird.h \
    define.h \
    gamecontroller.h \
    roaditem.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
