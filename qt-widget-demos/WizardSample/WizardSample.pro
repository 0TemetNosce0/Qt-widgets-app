#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T20:42:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WizardSample
TEMPLATE = app


SOURCES += main.cpp\
        wizardsample.cpp \
    somepage.cpp \
    assumptionpage.cpp \
    page.cpp

HEADERS  += wizardsample.h \
    somepage.h \
    assumptionpage.h \
    page.h

FORMS    += wizardsample.ui \
    somepage.ui \
    page.ui \
    assumptionpage.ui

RESOURCES += \
    wizardsample.qrc
