#-------------------------------------------------
#
# Project created by QtCreator 2015-03-04T15:55:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSimpleSheetDemo
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    Dialogs/SortDialog.cpp \
    Dialogs/NewFileDialog.cpp \
    Dialogs/MySpinBox.cpp \
    Dialogs/InsertRCDialog.cpp \
    Dialogs/GraphicPropertiesDialog.cpp \
    Dialogs/FunctionListDialog.cpp \
    Dialogs/FindDialog.cpp \
    Table.cpp \
    QSimplesheet.cpp \
    PictureGraphic.cpp \
    ItemDelegate.cpp \
    Graphic.cpp \
    Commands.cpp \
    Cell.cpp \
    Calculator.cpp

HEADERS  += mainwindow.h \
    Dialogs/SortDialog.h \
    Dialogs/NewFileDialog.h \
    Dialogs/MySpinBox.h \
    Dialogs/InsertRCDialog.h \
    Dialogs/GraphicPropertiesDialog.h \
    Dialogs/FunctionListDialog.h \
    Dialogs/FindDialog.h \
    Table.h \
    QSimplesheet.h \
    PictureGraphic.h \
    ItemDelegate.h \
    Graphic.h \
    Commands.h \
    Cell.h \
    Calculator.h

FORMS += \
    Dialogs/SortDialog.ui \
    Dialogs/NewFileDialog.ui \
    Dialogs/InsertRCDialog.ui \
    Dialogs/GraphicPropertiesDialog.ui \
    Dialogs/FunctionListDialog.ui \
    Dialogs/FindDialog.ui

RESOURCES += \
    resources.qrc
