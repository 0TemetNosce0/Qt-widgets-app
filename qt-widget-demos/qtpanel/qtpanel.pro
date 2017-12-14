#-------------------------------------------------
#
# Project created by QtCreator 2015-05-11T12:30:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtpanel
TEMPLATE = app


SOURCES += main.cpp \
    x11support.cpp \
    trayapplet.cpp \
    textgraphicsitem.cpp \
    spacerapplet.cpp \
    panelwindow.cpp \
    panelapplication.cpp \
    iconloader.cpp \
    dpisupport.cpp \
    dockapplet.cpp \
    desktopapplications.cpp \
    demoapplet.cpp \
    clockapplet.cpp \
    applicationsmenuapplet.cpp \
    applet.cpp

HEADERS  += \
    x11support.h \
    trayapplet.h \
    textgraphicsitem.h \
    spacerapplet.h \
    panelwindow.h \
    panelapplication.h \
    iconloader.h \
    dpisupport.h \
    dockapplet.h \
    desktopapplications.h \
    demoapplet.h \
    clockapplet.h \
    applicationsmenuapplet.h \
    applet.h \
    animationutils.h

FORMS    += \
    panelapplicationsettings.ui
