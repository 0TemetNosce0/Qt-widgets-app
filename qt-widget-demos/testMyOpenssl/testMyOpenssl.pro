#-------------------------------------------------
#
# Project created by QtCreator 2014-09-20T13:17:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testMyOpenssl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cciphermanger.cpp \
    copensslciphercontext.cpp \
    cciphercontext.cpp

HEADERS  += mainwindow.h \
    cciphermanger.h \
    copensslciphercontext.h \
    copensslconfig.h \
    cciphercontext.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$quote($$PWD/openssl/include)
LIBS += -L$$quote($$PWD/openssl/lib)
LIBS += -llibeay32 -lssleay32
LIBS += -lgdi32 -lwsock32
