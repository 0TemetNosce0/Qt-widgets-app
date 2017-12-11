#-------------------------------------------------
#
# Project created by QtCreator 2015-02-12T16:44:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BinaryTreeViewDemo
TEMPLATE = app

SOURCES += \
    src/AddValuesDialog.cpp \
    src/AddValuesWidget.cpp \
    src/Edge.cpp \
    src/main.cpp \
    src/Node.cpp \
    src/TreeManager.cpp \
    src/TreeScene.cpp \
    src/TreeView.cpp \
    src/ValueByIndexDialog.cpp \
    src/ViewerWindow.cpp

HEADERS += \
    include/AddValuesDialog.h \
    include/AddValuesWidget.h \
    include/Edge.h \
    include/Node.h \
    include/resource.h \
    include/TreeManager.h \
    include/TreeScene.h \
    include/TreeView.h \
    include/ValueByIndexDialog.h \
    include/ViewerWindow.h

FORMS    += \
    ui/addvaluesdialog.ui \
    ui/valuebyindexdialog.ui

RESOURCES += \
    resources.qrc

win32:RC_FILE = treeviewer.rc



