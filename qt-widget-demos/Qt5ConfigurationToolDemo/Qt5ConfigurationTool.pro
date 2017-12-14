#-------------------------------------------------
#
# Project created by QtCreator 2015-03-25T23:17:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets gui-private core-private

TARGET = qt5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tabpage.cpp \
    qt5ct.cpp \
    qsspage.cpp \
    qsseditordialog.cpp \
    paletteeditdialog.cpp \
    interfacepage.cpp \
    iconthemepage.cpp \
    fontspage.cpp \
    fontconfigdialog.cpp \
    appearancepage.cpp

HEADERS  += mainwindow.h \
    tabpage.h \
    qt5ct.h \
    qsspage.h \
    qsseditordialog.h \
    paletteeditdialog.h \
    interfacepage.h \
    iconthemepage.h \
    fontspage.h \
    fontconfigdialog.h \
    appearancepage.h

FORMS += \
    ui/qsspage.ui \
    ui/qsseditordialog.ui \
    ui/previewform.ui \
    ui/paletteeditdialog.ui \
    ui/mainwindow.ui \
    ui/interfacepage.ui \
    ui/iconthemepage.ui \
    ui/fontspage.ui \
    ui/fontconfigdialog.ui \
    ui/appearancepage.ui

RESOURCES += \
    translations/translations.qrc
