#-------------------------------------------------
#
# Project created by QtCreator 2013-08-22T08:22:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ListModel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tagmngrlistitem.cpp \
    tagmngrlistmodel.cpp \
    tagmngrlistview.cpp \
    ../../../dy-vp/videopro_win/gui/obs/UI/reclistwidget/reclistview.cpp \
    ../../../dy-vp/videopro_win/gui/obs/UI/reclistwidget/reclistviewmodel.cpp \
    ../../../dy-vp/videopro_win/gui/obs/UI/reclistwidget/reclistviewdelegate.cpp

HEADERS  += mainwindow.h \
    tagmngrlistitem.h \
    tagmngrlistmodel.h \
    tagmngrlistview.h \
    ../../../dy-vp/videopro_win/gui/obs/UI/reclistwidget/reclistview.h \
    ../../../dy-vp/videopro_win/gui/obs/UI/reclistwidget/reclistviewmodel.h \
    ../../../dy-vp/videopro_win/gui/obs/UI/reclistwidget/reclistviewdelegate.h
