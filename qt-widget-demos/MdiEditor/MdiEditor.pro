#-------------------------------------------------
#
# Project created by QtCreator 2014-12-12T00:04:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MdiEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editor.cpp

HEADERS  += mainwindow.h \
    editor.h

FORMS    += mainwindow.ui

RESOURCES += \
    mdieditor.qrc
