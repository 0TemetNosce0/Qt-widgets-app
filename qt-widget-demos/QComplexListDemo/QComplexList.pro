#-------------------------------------------------
#
# Project created by QtCreator 2015-04-01T13:12:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QComplexList
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    layertablemodel.cpp \
    layeritemdelegate.cpp \
    layertableview.cpp

HEADERS  += mainwindow.h \
    layertablemodel.h \
    layeritemdelegate.h \
    layertableview.h

FORMS    += mainwindow.ui
