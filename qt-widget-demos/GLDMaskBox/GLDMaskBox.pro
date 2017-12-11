#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T15:42:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GLDMaskBox
TEMPLATE = app

DESTDIR = ../GlDMaskBox/bin

greaterThan(QT_MAJOR_VERSION, 4): DEFINES += NOMINMAX

include($(GLDRS)/Glodon/shared/GLD.pri)

SOURCES += main.cpp\
           GLDMaskBox.cpp \
           CustomDialog.cpp \
    CustomPushButton.cpp

HEADERS  += GLDMaskBox.h \
            CommonUtil.h \
            CustomDialog.h \
    CustomPushButton.h
