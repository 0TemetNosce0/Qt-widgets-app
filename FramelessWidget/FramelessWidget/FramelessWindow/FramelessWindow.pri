
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include (.\Controls\controls.pri)

HEADERS += \
    $$PWD/XBorderPanel.h \
    $$PWD/Xc.h \
    $$PWD/XClientPanel.h \
    $$PWD/XFrame.h \
    $$PWD/XStyle.h \
    $$PWD/XStyleData.h \
    $$PWD/XTitlePanel.h \
    $$PWD/XWindow.h \
    $$PWD/XThemeHelper.h \
    $$PWD/XThemeWindow.h

SOURCES += \
    $$PWD/XBorderPanel.cpp \
    $$PWD/XClientPanel.cpp \
    $$PWD/XFrame.cpp \
    $$PWD/XStyle.cpp \
    $$PWD/XStyleData.cpp \
    $$PWD/XTitlePanel.cpp \
    $$PWD/XWindow.cpp \
    $$PWD/XThemeHelper.cpp \
    $$PWD/XThemeWindow.cpp

RESOURCES += \
    $$PWD/images/themeImages.qrc
