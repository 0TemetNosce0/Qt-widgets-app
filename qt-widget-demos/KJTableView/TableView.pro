#-------------------------------------------------
#
# Project created by QtCreator 2014-07-23T16:42:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TableView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    kjmodel.cpp \
    kjstyleditemdelegate.cpp \
    kjconversationwidget.cpp

HEADERS  += mainwindow.h \
    kjmodel.h \
    kjstyleditemdelegate.h \
    kjconversationwidget.h

FORMS    += mainwindow.ui \
    kjconversationwidget.ui
