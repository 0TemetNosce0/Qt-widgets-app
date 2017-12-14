#-------------------------------------------------
#
# Project created by QtCreator 2015-02-12T11:12:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QExtendWidgetDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/console_reader.cpp \
    src/customizableheaderview.cpp \
    src/versionnumber.cpp \
    src/streamdirectory/icecast.cpp \
    src/streamdirectory/icecast_internalthread.cpp \
    src/streamdirectory/streamdirectoryentry.cpp \
    src/streamdirectory/streamdirectoryentry_genre.cpp \
    src/streamdirectory/streamdirectoryentry_root.cpp \
    src/streamdirectory/streamdirectoryentry_stream.cpp \
    src/streamdirectory/streamdirectorymodel.cpp \
    src/streamdirectory/streamdirectoryproxymodel.cpp

HEADERS  += mainwindow.h \
    src/console_reader.h \
    src/customizableheaderview.h \
    src/versionnumber.h \
    src/streamdirectory/icecast.h \
    src/streamdirectory/icecast_internalthread.h \
    src/streamdirectory/streamdirectoryentry.h \
    src/streamdirectory/streamdirectoryentry_genre.h \
    src/streamdirectory/streamdirectoryentry_root.h \
    src/streamdirectory/streamdirectoryentry_stream.h \
    src/streamdirectory/streamdirectorymodel.h \
    src/streamdirectory/streamdirectoryproxymodel.h

FORMS    += mainwindow.ui
