#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T08:35:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QComboboxStyle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        $(GLDRS)/Glodon/include/GTF/GTFEngineUtils.cpp \
    proxystyle.cpp

HEADERS  += mainwindow.h \
$(GLDRS)/Glodon/include/GTF/GTFEngineUtils.h \
    proxystyle.h

FORMS    += mainwindow.ui
