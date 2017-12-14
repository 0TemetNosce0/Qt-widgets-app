#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T19:15:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTableView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    proxystyle.cpp \
    nofocusdelegate.cpp \
    centeredcheckboxwidget.cpp \
    booleandelegate.cpp \
    scrollproxystyle.cpp

HEADERS  += mainwindow.h \
    proxystyle.h \
    nofocusdelegate.h \
    centeredcheckboxwidget.h \
    booleandelegate.h \
    scrollproxystyle.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

