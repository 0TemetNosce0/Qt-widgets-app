
QT += \
  gui\
  core\
  widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySysTray
TEMPLATE = app


SOURCES += \
  main.cpp\
  systray.cpp

HEADERS += \
  systray.h

FORMS += \
  systray.ui

RESOURCES += \
    icon.qrc
