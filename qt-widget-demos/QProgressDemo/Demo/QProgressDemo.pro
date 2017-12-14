#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T08:24:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QProgressDemo
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Qt/Qt5.1.1/5.1.1/msvc2010/plugins/designer/ -lqprogressplugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Qt/Qt5.1.1/5.1.1/msvc2010/plugins/designer/ -lqprogressplugind

INCLUDEPATH += $$PWD/../../../../Qt/Qt5.1.1/5.1.1/msvc2010/plugins/designer
DEPENDPATH += $$PWD/../../../../Qt/Qt5.1.1/5.1.1/msvc2010/plugins/designer

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Qt/Qt5.1.1/5.1.1/msvc2010/plugins/designer/qprogressplugin.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Qt/Qt5.1.1/5.1.1/msvc2010/plugins/designer/qprogressplugind.lib
