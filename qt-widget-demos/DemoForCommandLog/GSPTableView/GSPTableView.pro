#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T15:38:12
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core-private widgets-private

TARGET = GSPTableView
TEMPLATE = app

DESTDIR = ..\bin

include($(GLDRS)/Glodon/shared/GLD.pri)
include($(GLDRS)/Glodon/shared/GSP.pri)
include($(GLDRS)/Glodon/shared/VLD.pri)
include($(GLDRS)/Glodon/shared/GLDXLS.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
