#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T09:45:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Demo
TEMPLATE = app


SOURCES += main.cpp\
    custommodel.cpp \
    tableprinterexample.cpp

HEADERS  += \
    custommodel.h \
    tableprinterexample.h \
    tdpreviewdialog.h

FORMS += \
    tableprinterexample.ui \
    tdpreviewdialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-tableprinter-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/release/ -ltableprinter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-tableprinter-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/debug/ -ltableprinter

INCLUDEPATH += $$PWD/../build-tableprinter-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/debug
DEPENDPATH += $$PWD/../build-tableprinter-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-tableprinter-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/release/libtableprinter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-tableprinter-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/debug/libtableprinter.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-tableprinter-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/release/tableprinter.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-tableprinter-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Debug/debug/tableprinter.lib
