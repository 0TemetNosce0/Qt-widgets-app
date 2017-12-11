#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T14:32:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCustomTableView
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    custommodel.cpp \
    customdelegate.cpp

HEADERS  += widget.h \
    custommodel.h \
    customdelegate.h
