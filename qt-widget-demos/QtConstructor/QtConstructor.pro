#-------------------------------------------------
#
# Project created by QtCreator 2014-11-24T09:02:50

#
#-------------------------------------------------


QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtFormBuilder
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    builder_wizard.cpp \
    model_template.cpp \
    stdfctl.cpp

HEADERS  += mainwindow.h \
    database.h \
    builder_wizard.h \
    model_template.h \
    stdfctl.h \
    mainwindow_includes.h

FORMS    += mainwindow.ui builder_wizard.ui

RESOURCES += \
    icones.qrc
