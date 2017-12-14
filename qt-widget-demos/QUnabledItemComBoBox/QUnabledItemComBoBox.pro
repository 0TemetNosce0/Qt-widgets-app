#-------------------------------------------------
#
# Project created by QtCreator 2015-03-04T15:18:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComBoBox
TEMPLATE = app


SOURCES += main.cpp\
    ccombobox.cpp \
    accountitem.cpp \
    mainwindow.cpp

HEADERS  += mainwindow.h \
    ccombobox.h \
    accountitem.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
