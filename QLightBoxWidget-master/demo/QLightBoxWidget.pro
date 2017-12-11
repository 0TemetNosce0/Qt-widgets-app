#-------------------------------------------------
#
# Project created by QtCreator 2011-10-27T06:42:05
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4) {
	QT += widgets
}

TARGET = QLightBoxWidget
TEMPLATE = app

SRCDIR = ../src
INCLUDEPATH += $${SRCDIR}

SOURCES += main.cpp \
    $${SRCDIR}/qlightboxwidget.cpp \
    demowidget.cpp

HEADERS  += \
    $${SRCDIR}/qlightboxwidget.h \
    demowidget.h

RESOURCES += \
    resources.qrc
