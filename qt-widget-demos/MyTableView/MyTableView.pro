#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T17:31:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyTableView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    VHeaderView.cpp \
    VHeaderModel.cpp \
    tableview.cpp \
    SortFilterModel.cpp \
    NodeManager.cpp \
    HHeaderView.cpp \
    HHeaderModel.cpp \
    HHeaderItemDelegate.cpp \
    DrawGantt.cpp \
    DataTreeView.cpp \
    DataTreeDelegate.cpp \
    DataNode.cpp \
    DataModel.cpp

HEADERS  += mainwindow.h \
    VHeaderView.h \
    VHeaderModel.h \
    tableview.h \
    SortFilterModel.h \
    NodeManager.h \
    HHeaderView.h \
    HHeaderModel.h \
    HHeaderItemDelegate.h \
    DrawGantt.h \
    DataTreeView.h \
    DataTreeDelegate.h \
    DataNode.h \
    DataModel.h \
    Const.h

FORMS    += mainwindow.ui

RESOURCES += \
    mytableview.qrc
