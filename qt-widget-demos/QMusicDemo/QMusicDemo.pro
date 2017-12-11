#-------------------------------------------------
#
# Project created by QtCreator 2015-05-29T08:36:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMusicDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mtablemodel.cpp \
    mtabledelegate.cpp

HEADERS  += mainwindow.h \
    mtablemodel.h \
    mtabledelegate.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
