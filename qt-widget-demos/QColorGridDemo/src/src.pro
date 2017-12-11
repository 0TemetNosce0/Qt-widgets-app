QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    colorgrid.h \
    colorpopup.h \
    colorbutton.h
    
SOURCES += \
    colorbutton.cpp \
    colorgrid.cpp \
    colorpopup.cpp


    
TEMPLATE = lib

DESTDIR = ../lib

INCLUDEPATH += ./ 

CONFIG += debug
CONFIG += release

CONFIG += staticlib

CONFIG(release, debug|release) {
    UI_DIR = release
    MOC_DIR = release
    OBJECTS_DIR = release
    TARGET = colorgrid
}

CONFIG(debug, debug|release) {
    UI_DIR = debug
    MOC_DIR = debug
    OBJECTS_DIR = debug
    TARGET = colorgridd
}
