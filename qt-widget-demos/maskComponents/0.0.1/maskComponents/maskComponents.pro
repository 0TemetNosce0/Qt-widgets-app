#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T16:52:31
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = maskComponents
TEMPLATE = app

DESTDIR = ../maskComponents/bin

greaterThan(QT_MAJOR_VERSION, 4): DEFINES += NOMINMAX

include($(GLDRS)/Glodon/shared/GLD.pri)

SOURCES += main.cpp\
        dialog.cpp \
    GLDHintWidget.cpp \
    GLDMaskWidget.cpp \
    GLDNewGuideFacade.cpp \
    CustomNewGuideFacade.cpp

HEADERS  += dialog.h \
    GLDHintWidget.h \
    GLDMaskWidget.h \
    GLDNewGuideFacade.h \
    CustomNewGuideFacade.h

FORMS    += dialog.ui

RESOURCES += \
    res.qrc
