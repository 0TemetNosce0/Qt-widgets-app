#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T15:51:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core-private widgets-private

TARGET = MyDateTimeEdit
TEMPLATE = app

include($(GLDRS)/Glodon/shared/GLD.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
