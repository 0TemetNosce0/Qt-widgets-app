#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T09:28:33
#
#-------------------------------------------------

QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = tableprinter
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    tdpreviewdialog.cpp

HEADERS += \
    tdpreviewdialog.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    tdpreviewdialog.ui \
    tdtableprinter.ui

RESOURCES += \
    tableprinterresource.qrc
