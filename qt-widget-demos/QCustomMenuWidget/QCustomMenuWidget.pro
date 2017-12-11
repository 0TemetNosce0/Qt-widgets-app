#-------------------------------------------------
#
# Project created by QtCreator 2014-05-06T12:06:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HoverMenuItem
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    customaction.cpp \
    customactionwidget.cpp

HEADERS  += mainwidget.h \
    customaction.h \
    customactionwidget.h

FORMS    += mainwidget.ui
