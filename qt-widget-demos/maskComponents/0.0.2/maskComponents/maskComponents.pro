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
    GLDMaskWidget.cpp \
    GLDNewGuideFacade.cpp \
    CustomNewGuideFacade.cpp \
    GLDMaskBox.cpp

HEADERS  += dialog.h \
    GLDMaskWidget.h \
    GLDNewGuideFacade.h \
    CustomNewGuideFacade.h \
    GLDMaskBox.h \
    commonutil.h

FORMS    += dialog.ui

RESOURCES += \
    res.qrc
