#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T11:29:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestTrackEditor03
TEMPLATE = app


SOURCES += main.cpp\
        trackeditor.cpp \
    track.cpp \
    trackmodel.cpp \
    trackdelegate.cpp

HEADERS  += trackeditor.h \
    track.h \
    trackmodel.h \
    trackdelegate.h

FORMS    += trackeditor.ui
