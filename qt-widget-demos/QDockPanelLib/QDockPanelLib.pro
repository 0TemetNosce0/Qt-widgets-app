#-------------------------------------------------
#
# Project created by QtCreator 2015-05-11T12:06:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QDockPanelLib
TEMPLATE = app


SOURCES += main.cpp \
    QDockTabWidget.cpp \
    QDockTabBar.cpp \
    QDockSideButton.cpp \
    QDockSideBar.cpp \
    QDockPanelComponents.cpp \
    QDockPanel.cpp \
    QDockNode.cpp \
    QDockMaskWidget.cpp \
    QDockManager.cpp \
    QDockFrame.cpp \
    QDockArrows.cpp \
    IAcceptDrop.cpp

HEADERS  += \
    QDockTabWidget.h \
    QDockTabBar.h \
    QDockSideButton.h \
    QDockSideBar.h \
    QDockPanelComponents.h \
    QDockPanel.h \
    QDockNode.h \
    QDockMaskWidget.h \
    QDockManager.h \
    QDockFrame.h \
    QDockCommon.h \
    QDockArrows.h \
    IAcceptDrop.h

FORMS    +=

RESOURCES += \
    DockResource.qrc
