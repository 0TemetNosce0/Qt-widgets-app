#-------------------------------------------------
#
# Project created by QtCreator 2015-12-02T20:26:51
#
#-------------------------------------------------
greaterThan(QT_MAJOR_VERSION, 4): QT += core-private widgets

TARGET = GLDMask
TEMPLATE = lib

CONFIG +=  debug_and_release

unix:QMAKE_CXXFLAGS += -std=c++11

CONFIG(debug, debug|release){
    contains(QMAKE_HOST.arch, x86_64) {
        DESTDIR = ../../bin/Debug/X64
    } else {
        DESTDIR = ../../bin/Debug/X86
    }
    unix:TARGET=$$join(TARGET,,,_debug)
    win32:TARGET=$$join(TARGET,,,d)
}

CONFIG(release, debug|release){
    contains(QMAKE_HOST.arch, x86_64) {
        DESTDIR = ../../bin/Release/X64
    } else {
        DESTDIR = ../../bin/Release/X86
    }
}

QMAKE_CXXFLAGS_RELEASE += /Zi
QMAKE_LFLAGS_RELEASE += /DEBUG

greaterThan(QT_MAJOR_VERSION, 4): DEFINES += NOMINMAX

DEFINES += GLDMASK_LIBRARY

win32-msvc|win32-msvc.net|win32-msvc2002|win32-msvc2003|win32-msvc2005|win32-msvc2008|win32-msvc2010|win32-msvc2012|win32-msvc2013 {
     LIBS += -loleaut32 -lole32
}

INCLUDEPATH += ../include

HEADERS += \
    ../include/CustomButton.h \
    ../include/GLDMask_Global.h \
    ../include/GLDMaskBox.h \
    ../include/IrregularForm.h

SOURCES += \
    CustomButton.cpp \
    GLDMaskBox.cpp \
    IrregularForm.cpp

