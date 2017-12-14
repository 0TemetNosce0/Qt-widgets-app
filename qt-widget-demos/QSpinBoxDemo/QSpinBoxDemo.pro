#-------------------------------------------------
#
# Project created by QtCreator 2014-12-24T10:54:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSpinBoxDemo
TEMPLATE = app


include($(GLDRS)/Glodon/shared/GLD.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RC_FILE = icon.rc
