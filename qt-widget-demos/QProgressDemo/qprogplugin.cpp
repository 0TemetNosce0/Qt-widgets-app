/***************************************************************************
 *   Copyright (C) 2008 - Giuseppe Cigala                                  *
 *   g_cigala@virgilio.it                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "qprog.h"
#include "qprogplugin.h"

#include <QtPlugin>

QProgPlugin::QProgPlugin(QObject *parent)
        : QObject(parent)
{
    initialized = false;
}

void QProgPlugin::initialize(QDesignerFormEditorInterface *)
{
    if (initialized)
        return;

    initialized = true;
}

bool QProgPlugin::isInitialized() const
{
    return initialized;
}

QWidget *QProgPlugin::createWidget(QWidget *parent)
{
    return new QProg(parent);
}

QString QProgPlugin::name() const
{
    return "QProg";
}

QString QProgPlugin::group() const
{
    return "Lab Widgets";
}

QIcon QProgPlugin::icon() const
{
    return QIcon(":/qprog.png");
}

QString QProgPlugin::toolTip() const
{
    return "";
}

QString QProgPlugin::whatsThis() const
{
    return "";
}

bool QProgPlugin::isContainer() const
{
    return false;
}

QString QProgPlugin::domXml() const
{
    return "<widget class=\"QProg\" name=\"qprog\">\n"
           " <property name=\"geometry\">\n"
           "  <rect>\n"
           "   <x>0</x>\n"
           "   <y>0</y>\n"
           "   <width>200</width>\n"
           "   <height>30</height>\n"
           "  </rect>\n"
           " </property>\n"
           " <property name=\"toolTip\" >\n"
           "  <string> Progress bar</string>\n"
           " </property>\n"
           " <property name=\"whatsThis\" >\n"
           "  <string>Progress bar</string>\n"
           " </property>\n"
           " </widget>\n";
}

QString QProgPlugin::includeFile() const
{
    return "qprog.h";
}

//Q_EXPORT_PLUGIN2(customwidgetplugin, QProgPlugin)
