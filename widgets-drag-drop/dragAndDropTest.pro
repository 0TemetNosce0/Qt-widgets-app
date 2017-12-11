#-------------------------------------------------
#
# Project created by QtCreator 2010-09-06T22:51:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DragAndDrop_test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cdragablecontainer.cpp \
    cverticalcontainer.cpp

HEADERS  += mainwindow.h \
    cdragablecontainer.h \
    cverticalcontainer.h

FORMS    += mainwindow.ui \
    cdragablecontainer.ui

