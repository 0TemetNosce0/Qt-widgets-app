#-------------------------------------------------
#
# Project created by QtCreator 2013-10-22T10:11:05
#
#-------------------------------------------------

QT       += core gui network widgets

TARGET = QQ
TEMPLATE = app

OTHER_FILES += \
    imsclient.rc

HEADERS += \
    workstation.h \
    uiweatherinfo.h \
    uitabwidget.h \
    uiloginscreen.h \
    uiinterfacemanager.h \
    uiimsbasedialog.h \
    uiapplicationmanager.h \
    tinyxml.h \
    tinystr.h \
    resource.h \
    imsresoursce.h \
    imsimagelineedit.h \
    imsimagelabel.h \
    imsimageaccount.h \
    imsdefine.h

SOURCES += \
    workstation.cpp \
    uiweatherinfo.cpp \
    uitabwidget.cpp \
    uiloginscreen.cpp \
    uiinterfacemanager.cpp \
    uiimsbasedialog.cpp \
    uiapplicationmanager.cpp \
    tinyxmlparser.cpp \
    tinyxmlerror.cpp \
    tinyxml.cpp \
    tinystr.cpp \
    main.cpp \
    imsresoursce.cpp \
    imsimagelineedit.cpp \
    imsimagelabel.cpp \
    imsimageaccount.cpp

FORMS += \
    uiweatherinfo.ui \
    uiloginscreen.ui \
    uiinterfacemanager.ui \
    uiapplicationmanager.ui \
    workstation.ui

RESOURCES += \
    workstation.qrc





