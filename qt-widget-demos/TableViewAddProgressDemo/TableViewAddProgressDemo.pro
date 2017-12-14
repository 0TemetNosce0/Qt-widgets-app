#-------------------------------------------------
#
# Project created by QtCreator 2014-09-06T13:39:09
#
#-------------------------------------------------

QT       += core gui

CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TableViewAddProgressDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    progressbardelegate.cpp \
    tablemodel.cpp \
    tableview.cpp

HEADERS  += mainwindow.h \
    progressbardelegate.h \
    tablemodel.h \
    tableview.h
