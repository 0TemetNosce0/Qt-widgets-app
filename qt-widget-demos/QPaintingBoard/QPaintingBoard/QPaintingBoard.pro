# -------------------------------------------------
# Project created by QtCreator 2010-02-05T10:11:52
# -------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = paint
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    paintarea.cpp \
    donewdialog.cpp

HEADERS += mainwindow.h \
    paintarea.h \
    donewdialog.h

FORMS += mainwindow.ui \
    donewdialog.ui

RESOURCES += myResource.qrc
