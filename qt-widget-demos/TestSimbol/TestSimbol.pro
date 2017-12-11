#-------------------------------------------------
#
# Project created by QtCreator 2014-10-29T16:21:52
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestSimbol
TEMPLATE = app
DESTDIR = ../TestSimbol/bin


include($(GLDRS)/Glodon/shared/GLD.pri)
include($(GLDRS)/Glodon/shared/GSP.pri)
include($(GLDRS)/Glodon/shared/GLDTechPlatform.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
