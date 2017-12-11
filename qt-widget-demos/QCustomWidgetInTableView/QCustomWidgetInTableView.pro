#-------------------------------------------------
#
# Project created by QtCreator 2015-05-08T13:44:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CustomWidget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    installedappmodel.cpp \
    installedappdelegate.cpp \
    downloadingitem.cpp

HEADERS  += mainwindow.h \
    installedappmodel.h \
    installedappdelegate.h \
    downloadingitem.h

FORMS    += mainwindow.ui \
    downloadingitem.ui
