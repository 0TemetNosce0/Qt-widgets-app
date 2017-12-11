#-------------------------------------------------
#
# Project created by QtCreator 2015-07-23T12:27:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtControlDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customprogressbar.cpp \
    custombattery.cpp \
    customcoolbar.cpp \
    customlcdnumber.cpp \
    customindicator.cpp \
    customgauge.cpp

HEADERS  += mainwindow.h \
    customprogressbar.h \
    custombattery.h \
    customcoolbar.h \
    customindicator.h \
    customlcdnumber.h \
    customgauge.h

FORMS    += mainwindow.ui
