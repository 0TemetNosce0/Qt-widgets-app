TARGET = example
TEMPLATE = app

MOC_DIR = .build
OBJECTS_DIR = .build
RCC_DIR = .build
UI_DIR = .build

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

INCLUDEPATH += ../src
VPATH = ../src

HEADERS = example.h \
          textprinter.h

SOURCES = main.cpp \
          example.cpp \
          textprinter.cpp
