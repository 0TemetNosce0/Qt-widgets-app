#-------------------------------------------------
#
# Project created by QtCreator 2015-01-09T10:08:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QGridLayoutDemo
TEMPLATE = app


SOURCES += main.cpp\
           dialog.cpp \
           hexspinbox.cpp \
           $(GLDRS)/Glodon/include/GTF/GTFEngineUtils.cpp \
           searchbutton.cpp \
           widget.cpp

HEADERS  += dialog.h \
            hexspinbox.h \
            searchbutton.h \
            $(GLDRS)/Glodon/include/GTF/GTFEngineUtils.h \
            widget.h

FORMS    += dialog.ui \
            widget.ui
