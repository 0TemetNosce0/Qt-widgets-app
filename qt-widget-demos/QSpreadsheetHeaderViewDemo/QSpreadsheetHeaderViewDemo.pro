#-------------------------------------------------
#
# Project created by QtCreator 2014-12-17T21:44:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSpreadsheetHeaderViewDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    QSpreadsheetHeaderView.cpp \
    tableview.cpp \
    tablemodel.cpp

HEADERS  += mainwindow.h \
    QSpreadsheetHeaderView.h \
    tableview.h \
    tablemodel.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
