#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T23:00:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HistoryCurveTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    TreeItem.cpp \
    TagTreeModel.cpp

HEADERS  += mainwindow.h \
    TreeItem.h \
    TagTreeModel.h

RESOURCES += \
    res.qrc

