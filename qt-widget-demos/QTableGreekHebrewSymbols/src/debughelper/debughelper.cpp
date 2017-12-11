/***************************************************************************
openBibleViewer - Bible Study Tool
Copyright (C) 2009-2011 Paul Walger
This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3 of the License, or (at your option)
any later version.
This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with
this program; if not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/
#include <debughelper.h>
#define NO_COLOR
#define DBGHELPER_USES_PRINTF

#ifdef DBGHELPER_USES_PRINTF
#include <stdio.h>
#else
#include <QtCore/QtDebug>
#endif

int DbgHelper::indent = 0;
int DbgHelper::colorIndex = 0;


static void DbgHelper_output(int color, int indent,
                             const QString &prefix, const QString &funcName)
{
    QString text = QString(4 * indent, ' ') + QString(prefix + " " + funcName);
    if(color >= 0) {
        text.prepend("\x1b[3" + QString::number(1 + color) + "m");
        text.append("\x1b[39m");
    }
#ifndef QT_NO_DEBUG_OUTPUT
	#ifndef DBGHELPER_USES_PRINTF
		qDebug() << text;
	#else
		fprintf(stderr, "%s\n", qPrintable(text));
	#endif
#endif
}

DbgHelper::DbgHelper(const QString &t)
{
    txt = t;
#ifdef NO_COLOR
    myColor = -1;
#else
    myColor = colorIndex;
    colorIndex = (colorIndex + 1) % 7;
#endif
    DbgHelper_output(myColor, indent, "BEGIN", txt);
    ++indent;
}

DbgHelper::~DbgHelper()
{
    --indent;
    DbgHelper_output(myColor, indent, "END", txt);
}
