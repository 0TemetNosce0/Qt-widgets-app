#-------------------------------------------------
#
# Project created by QtCreator 2015-04-09T14:05:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network webkit webkitwidgets

TARGET = QWebItemViewDemo
TEMPLATE = app


SOURCES += main.cpp\
        simplelistwidget.cpp \
    WebItemDelegate.cpp \
    filesystem.cpp \
    simplelistitemfactory.cpp \
    filetreeitemfactory.cpp

HEADERS  += simplelistwidget.h \
    WebItemDelegate.h \
    filesystem.h \
    simplelistitemfactory.h \
    filetreeitemfactory.h

FORMS    += simplelistwidget.ui
