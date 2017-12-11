#-------------------------------------------------
#
# Project created by QtCreator 2015-02-28T14:49:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = QLabelDemo
TEMPLATE = app


SOURCES += main.cpp\
        labelsound.cpp \
    label.cpp

HEADERS  += labelsound.h \
    label.h

FORMS    += labelsound.ui

RESOURCES += \
    res.qrc
