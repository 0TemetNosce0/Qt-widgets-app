QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = NcFrameLessHelper
INCLUDEPATH += ./../src

SOURCES += \
    main.cpp \
    ./../src/NcFramelessHelper.cpp \
    Dialog.cpp

HEADERS += \
    ./../src/NcFramelessHelper.h \
    Dialog.h
