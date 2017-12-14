#-------------------------------------------------
#
# Project created by QtCreator 2015-01-04T15:33:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
qtHaveModule(printsupport): QT += printsupport

TARGET = ImageProcessorDemo
TEMPLATE = app


SOURCES += main.cpp\
        imgprocessor.cpp \
    showwidget.cpp

HEADERS  += imgprocessor.h \
    showwidget.h

FORMS    += imgprocessor.ui

RESOURCES += \
    res.qrc
