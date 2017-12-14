QT += widgets

HEADERS       = mainwindow.h \
    customiconstyle.h
SOURCES       = mainwindow.cpp \
                main.cpp \
    customiconstyle.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/menus
INSTALLS += target

RESOURCES += \
    res.qrc
