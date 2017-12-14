#-------------------------------------------------
#
# Project created by QtCreator 2015-05-15T14:39:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCSVExporterDemo
TEMPLATE = app


SOURCES += main.cpp \
    custommodel.cpp \
    csvexporterexample.cpp \
    csvexporter.cpp

HEADERS  += \
    custommodel.h \
    csvexporterexample.h \
    csvexporter.h

FORMS    += \
    csvexporterexample.ui \
    csvexporter.ui

RESOURCES += \
    csvexporterresource.qrc
