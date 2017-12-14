#-------------------------------------------------
#
# Project created by QtCreator 2014-05-21T15:27:27
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = My2048
TEMPLATE = app


SOURCES += main.cpp\
    widget.cpp \
    GameWidget.cpp

HEADERS  += \
    widget.h \
    GameWidget.h

CONFIG += mobility
MOBILITY = 

