#-------------------------------------------------
#
# Project created by QtCreator 2015-03-02T17:06:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComboboxDelegate
TEMPLATE = app


SOURCES += main.cpp\
        ItemDelegate.cpp \
        Widget.cpp

HEADERS  += Widget.h \
         ItemDelegate.h

FORMS    += Widget.ui

RESOURCES += \
    Resource.qrc
