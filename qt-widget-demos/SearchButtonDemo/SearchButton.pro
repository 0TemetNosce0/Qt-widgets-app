#-------------------------------------------------
#
# Project created by QtCreator 2011-10-27T11:29:01
#
#-------------------------------------------------

QT         += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = SearchButton
TEMPLATE    = app

DESTDIR     = bin
UI_DIR      = temp
MOC_DIR     = temp
OBJECTS_DIR = temp

SOURCES += main.cpp\
        Widget.cpp \
    SearchButton.cpp

HEADERS  += Widget.h \
    SearchButton.h

FORMS    += Widget.ui


