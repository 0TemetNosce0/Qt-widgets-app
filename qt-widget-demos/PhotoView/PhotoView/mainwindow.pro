#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T14:38:40
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mainwindow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    toolbar.cpp \
    photoinfo.cpp \
    about.cpp \
    mirroreditem.cpp \
    mirrorview.cpp \
    slideshow.cpp

HEADERS  += mainwindow.h \
    toolbar.h \
    photoinfo.h \
    about.h \
    mirroreditem.h \
    mirrorview.h \
    slideshow.h

FORMS    += mainwindow.ui \
    photoinfo.ui \
    about.ui \
    mirrorview.ui \
    slideshow.ui

RESOURCES += \
    mainwindow.qrc


TRANSLATIONS += photoview_zh.ts \
    photoview_en.ts

RC_ICONS = photoview.ico

