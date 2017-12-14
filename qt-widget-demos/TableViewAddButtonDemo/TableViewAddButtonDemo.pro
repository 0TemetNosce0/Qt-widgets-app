#-------------------------------------------------
#
# Project created by QtCreator 2014-09-06T13:39:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TableViewAddButtonDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablemodel.cpp \
    tableview.cpp \
    buttondelegate.cpp

HEADERS  += mainwindow.h \
    tablemodel.h \
    tableview.h \
    buttondelegate.h

RESOURCES += \
    res.qrc
