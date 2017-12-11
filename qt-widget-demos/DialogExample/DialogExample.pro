#-------------------------------------------------
#
# Project created by QtCreator 2014-12-23T23:20:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DialogExample
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    customdlg.cpp \
    inputdlg.cpp \
    msgboxdlg.cpp

HEADERS  += dialog.h \
    customdlg.h \
    inputdlg.h \
    msgboxdlg.h

FORMS    += dialog.ui
