#-------------------------------------------------
#
# Project created by QtCreator 2012-12-31T11:41:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += core gui

TARGET = QTableGreekHebrewSymbols
TEMPLATE = app


PROJECTNAME = QTableGreekHebrewSymbols

DESTDIR     = build/bin
OBJECTS_DIR = build/obj
MOC_DIR     = build/moc
RCC_DIR     = build/rc
UI_DIR      = build/ui


INCLUDEPATH = \
    src \
    src/gui/dialogs/about \
    src/gui/hebrewpanel \
    src/gui/greekpanel \
    src/main \
    src/other \
    src/defines \
    src/debughelper

DEPENDPATH += \
    src/main \
    src/gui/dialogs/about \
    src/gui/hebrewpanel \
    src/gui/greekpanel \
    src/other/ \
    src/defines

SOURCES += \
    src/main/mainwindow.cpp \
    src/main/main.cpp \
    src/gui/dialogs/about/about.cpp \
    src/gui/greekpanel/greekpanel.cpp \
    src/gui/hebrewpanel/hebrewpanel.cpp

HEADERS  += \
    src/main/mainwindow.h \
    src/gui/dialogs/about/about.h \
    src/gui/greekpanel/greekpanel.h \
    src/gui/hebrewpanel/hebrewpanel.h \
    src/defines/defines.h \
    src/debughelper/debughelper.h

FORMS    += \
    src/main/mainwindow.ui \
    src/gui/dialogs/about/about.ui \
    src/gui/greekpanel/greekpanel.ui \
    src/gui/hebrewpanel/hebrewpanel.ui

