#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T17:13:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = ../GLDMaskDemo/bin

TARGET = GLDMaskDemo
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): DEFINES += NOMINMAX

include($(GLDRS)/Glodon/shared/GLD.pri)
include($(GLDRS)/Glodon/shared/GLDMask.pri)
include($(GLDRS)/Glodon/shared/VLD.pri)

SOURCES += main.cpp\
           CustomDialog.cpp \
           LogoinWidget.cpp

HEADERS += CustomDialog.h \
           LogoinWidget.h \

RESOURCES +=
