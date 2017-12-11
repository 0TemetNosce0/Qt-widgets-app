#-------------------------------------------------
#
# Project created by QtCreator 2015-01-28T20:26:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CustomToolTip
TEMPLATE = app


SOURCES += main.cpp\
    clabel.cpp \
    mainwidget.cpp \
    itemwidget.cpp \
    ctooltip.cpp

HEADERS  += mainwidget.h \
    itemwidget.h \
    ctooltip.h \
    global.h \
    clabel.h

FORMS    += mainwidget.ui

RESOURCES += \
    images.qrc
