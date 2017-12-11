#-------------------------------------------------
#
# Project created by QtCreator 2015-06-05T10:04:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudoku
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sudokutable.cpp \
    sudokudata.cpp \
    settingsdialog.cpp \
    cell.cpp

HEADERS  += mainwindow.h \
    sudokutable.h \
    sudokudata.h \
    settingsdialog.h \
    cell.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
