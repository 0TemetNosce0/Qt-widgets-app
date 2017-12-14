#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T17:13:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = ../GLDMaskBox/bin

TARGET = GLDMaskBox
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): DEFINES += NOMINMAX

include($(GLDRS)/Glodon/shared/GLD.pri)
include($(GLDRS)/Glodon/shared/VLD.pri)

SOURCES += main.cpp\
           GLDMaskBox.cpp \
           CustomDialog.cpp \
           IrregularForm.cpp \
           LogoinWidget.cpp \
           CustomButton.cpp

HEADERS += GLDMaskBox.h \
           CustomDialog.h \
           CommonUtil.h \
           IrregularForm.h \
           LogoinWidget.h \
           CustomButton.h

RESOURCES +=
