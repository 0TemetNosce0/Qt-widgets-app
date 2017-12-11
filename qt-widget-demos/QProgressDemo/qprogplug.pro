TARGET = qprogressplugin
TEMPLATE = lib

QT += core gui designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += plugin debug_and_release

TARGET = $$qtLibraryTarget($$TARGET)
DESTDIR = $$[QT_INSTALL_PLUGINS]/designer

HEADERS = qprog.h \
          qprogplugin.h

SOURCES = qprog.cpp \
          qprogplugin.cpp

sources.files = $$SOURCES $$HEADERS *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/designer/qprogplugin

INSTALLS += target sources

RESOURCES += qprog.qrc

OTHER_FILES += \
    qprogplugin.json
