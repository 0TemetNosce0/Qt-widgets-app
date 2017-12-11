#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T09:05:21
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = ../GlDMaskWidget/bin

TARGET = GLDMaskWidget
TEMPLATE = app

include($(GLDRS)/Glodon/shared/GLD.pri)

greaterThan(QT_MAJOR_VERSION, 4): DEFINES += NOMINMAX

SOURCES += main.cpp\
        gldmaskwidget.cpp

HEADERS  += gldmaskwidget.h

#FORMS    += gldmaskwidget.ui

RESOURCES += \
    qrc.qrc
