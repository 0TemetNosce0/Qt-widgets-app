#-------------------------------------------------
#
# Project created by QtCreator 2015-01-12T22:52:48
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VM6000
TEMPLATE = app


SOURCES += main.cpp\
    excelhelper.cpp \
    frmconfig.cpp \
    frminputbox.cpp \
    frmipc.cpp \
    frmmain.cpp \
    frmmessagebox.cpp \
    frmnvr.cpp \
    frmpollconfig.cpp \
    iconhelper.cpp \
    myapp.cpp \
    switchbutton.cpp

HEADERS  += \
    excelhelper.h \
    frmconfig.h \
    frminputbox.h \
    frmipc.h \
    frmmain.h \
    frmmessagebox.h \
    frmnvr.h \
    frmpollconfig.h \
    iconhelper.h \
    myapp.h \
    myhelper.h \
    switchbutton.h

FORMS    += \
    frmmessagebox.ui \
    frmmain.ui \
    frminputbox.ui \
    frmconfig.ui \
    frmnvr.ui \
    frmipc.ui \
    frmpollconfig.ui

INCLUDEPATH 	+= $$PWD

MOC_DIR         = temp/moc
RCC_DIR         = temp/rcc
UI_DIR          = temp/ui
OBJECTS_DIR     = temp/obj
DESTDIR         = bin

win32:RC_FILE   = main.rc

RESOURCES += \
    rc.qrc

