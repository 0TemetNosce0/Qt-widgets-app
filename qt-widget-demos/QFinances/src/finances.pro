QT += widgets sql printsupport

TEMPLATE = app
CONFIG += warn_on \
    thread \
    qt \
 release

TARGET = bin/finances
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build

SOURCES += main.cpp \
    finances.cpp \
    dockwidg.cpp \
    fdatabase.cpp \
    misc.cpp \
    topheader.cpp \
    mystatusbar.cpp \
    filterdlgimpl.cpp \
    helpbrowser.cpp \
    titlebar.cpp \
    mortgagordlgimpl.cpp \
    mytransactionslist.cpp \
    parametersdlgimpl.cpp \
    transactiondlgimpl.cpp \
    accountpanelimpl.cpp \
    preferencesdlgImpl.cpp \
    querytable.cpp

HEADERS += finances.h \
    dockwidg.h \
    fdatabase.h \
    misc.h \
    topheader.h \
    mystatusbar.h \
    filterdlgimpl.h \
    helpbrowser.h \
    titlebar.h \
    mortgagordlgimpl.h \
    mytransactionslist.h \
    parametersdlgimpl.h \
    transactiondlgimpl.h \
    preferencesdlgImpl.h \
    querytable.h \
    accountpanelimpl.h

RESOURCES += application.qrc
RC_FILE = winicon.rc

TRANSLATIONS += lang/Ukrainian.ts \
 lang/German.ts \
 lang/Russian.ts

target.path = ../../myFinances
documentation.path = ../../myFinances/doc
documentation.files = doc/*
translation.path = ../../myFinances/lang
translation.files = lang/*.qm
data_css.path = ../../myFinances
data_css.files = data/*.*

INSTALLS += target \
    documentation \
    data_css \
    translation

FORMS += \
    parameters.ui \
    preferences.ui \
    transaction.ui \
    account.ui \
    mortgagordialog.ui \
    mortgagors.ui
