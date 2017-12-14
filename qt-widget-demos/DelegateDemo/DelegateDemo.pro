#-------------------------------------------------
#
# Project created by QtCreator 2014-06-30T10:58:08
#
#-------------------------------------------------

#QT       += core gui xml printsupport
#greaterThan(QT_MAJOR_VERSION, 4): QT += core-private widgets-private
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets xml

QT       += core gui xml printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets widgets-private core-private

TARGET = DelegateDemo
TEMPLATE = app

DESTDIR = ../DelegateDemo/bin

SOURCES += main.cpp\
        DelegateDemo.cpp\
        $(GLDRS)/Glodon/include/GTF/GTFEngineUtils.cpp

HEADERS  += DelegateDemo.h\
         $(GLDRS)/Glodon/include/GTF/GTFEngineUtils.h

FORMS    += DelegateDemo.ui

include($(GLDRS)/Glodon/shared/GSP.pri)
include($(GLDRS)/Glodon/shared/GLDXLS.pri)
include($(GLDRS)/Glodon/shared/VLD.pri)

INCLUDEPATH += D:/workspace/GCR/trunk/GLDTechPlatform/include
INCLUDEPATH += D:/workspace/GCR/trunk/GLDTechPlatform/include/Intf
INCLUDEPATH += D:/workspace/GCR/trunk/GLDTechPlatform/include/Impl
