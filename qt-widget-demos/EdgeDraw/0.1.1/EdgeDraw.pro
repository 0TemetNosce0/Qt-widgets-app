#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T17:13:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = ../0.1.1/bin

TARGET = EdgeDraw
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): DEFINES += NOMINMAX
include($(GLDRS)/Glodon/shared/GLD.pri)

SOURCES += main.cpp\
    GLDMaskBox.cpp \
    CustomDialog.cpp \
    irregularform.cpp

HEADERS  += GLDMaskBox.h \
            CustomDialog.h \
            CommonUtil.h \
            irregularform.h

RESOURCES +=
