#-------------------------------------------------
#
# Project created by QtCreator 2011-09-19T12:48:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FancyTable
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    ccustomheaderview.cpp \
    ccustomheadermodel.cpp \
    ccustomtableview.cpp \
    cproxymodelwithheadermodels.cpp \
    ccheckboxitemdelegate.cpp \
    cdefaultitemdelegate.cpp \
    cheaderitemdelegate.cpp \
    crect.cpp

HEADERS  += dialog.h \
    ccustomheaderview.h \
    ccustomheadermodel.h \
    ccustomtableview.h \
    cproxymodelwithheadermodels.h \
    ccheckboxitemdelegate.h \
    cdefaultitemdelegate.h \
    cheaderitemdelegate.h \
    crect.h

FORMS    += dialog.ui
