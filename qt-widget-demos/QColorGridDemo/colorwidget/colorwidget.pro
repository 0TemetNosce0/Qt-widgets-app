QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


SOURCES += main.cpp \
           colorwidget.cpp

HEADERS += colorwidget.h

FORMS += \
    colorwidget.ui

TEMPLATE = app

TARGET = colorwidget

LIBPATH = ../lib

INCLUDEPATH += ./ ../src

CONFIG += debug
CONFIG += release

CONFIG(release, debug|release) {
    UIC_DIR = release
    MOC_DIR = release
    OBJECTS_DIR = release
    LIBS += -lcolorgrid
}

CONFIG(debug, debug|release) {
    UIC_DIR = debug
    MOC_DIR = debug
    OBJECTS_DIR = debug
    LIBS += -lcolorgridd
}
