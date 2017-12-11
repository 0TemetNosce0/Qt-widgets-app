#-------------------------------------------------
#
# Project created by QtCreator 2014-12-12T09:44:27
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core-private widgets-private

TARGET = TreeView
TEMPLATE = app

HEADERS  += mainwindow.h \
        treeitem.h \
        treemodel.h \
        util.h \
        itemdelegate.h

SOURCES += main.cpp\
        mainwindow.cpp \
        treeitem.cpp \
        treemodel.cpp \
        util.cpp \
        itemdelegate.cpp

OTHER_FILES += \
    Bin/Resources/Style.qss

DESTDIR = $$PWD/Bin/

RC_FILE = TreeView.rc

CONFIG(debug, debug|release) {
    unix:TARGET=$$join(TARGET,,,_debug)
    win32:TARGET=$$join(TARGET,,,d)
} else {

}
