QT += core gui widgets printsupport

TEMPLATE += app
CONFIG += qt warn_on release
FORMS   += pbase.ui \
           enterKey.ui \
           AboutPbase.ui
HEADERS += pbase.h \
           mmgmt.h \
           rcsettings.h \
           blowfish.h \
           pbasedialog.h \
           text2printer.h
SOURCES += main.cpp \
           pbase.cpp \
           mmgmt.cpp \
           rcSettings.cpp \
           blowfish.cpp \
           dialogs.cpp \
           md5class.cpp \
           text2printer.cpp
RESOURCES += pbase-icons.qrc
TRANSLATIONS = 2Pnotes-2.0.5_de.ts
