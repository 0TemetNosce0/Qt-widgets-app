# =================================================
# * This file is part of the TTK StackedWidget project
# * Copyright (C) 2016 - 2017 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
#
# * You should have received a copy of the GNU General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# =================================================

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TTKStackedWidget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        animationstackedwidget.cpp

HEADERS  += mainwindow.h \
        animationstackedwidget.h

FORMS    += mainwindow.ui
