#-------------------------------------------------
#
# Project created by QtCreator 2015-03-13T19:08:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuiMock
TEMPLATE = app


SOURCES += main.cpp\
    draglabel.cpp \
    dragwidget.cpp \
    droplabel.cpp

HEADERS  += \
    draglabel.h \
    dragwidget.h \
    droplabel.h

FORMS    +=  mainwindow.ui

#DISTFILES += \
#    mainwindow.ui

RESOURCES += \
    images.qrc
