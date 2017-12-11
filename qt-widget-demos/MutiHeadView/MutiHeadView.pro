#-------------------------------------------------
#
# Project created by QtCreator 2014-12-17T18:01:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MutiHeadView
TEMPLATE = app


SOURCES += main.cpp\
        HierarchicalHeaderView.cpp\
        ProxyModelWithHeaderModels.cpp


HEADERS  +=\
        HierarchicalHeaderView.h\
        ProxyModelWithHeaderModels.h

FORMS    += mainwindow.ui
