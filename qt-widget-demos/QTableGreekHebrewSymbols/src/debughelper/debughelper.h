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
#ifndef DBGHELPER_H
#define DBGHELPER_H

#include <QtCore/QtDebug>

#ifdef OBV_NO_DEBUG_OUTPUT

#ifndef QT_NO_DEBUG
#define QT_NO_DEBUG
#endif

#ifndef QT_NO_DEBUG_OUTPUT
#define QT_NO_DEBUG_OUTPUT
#endif

#endif

#define myDebug() qDebug() << Q_FUNC_INFO << " "
#define myWarning() qWarning() << "W: "<< Q_FUNC_INFO << " "

/*#ifdef OBV_NO_DEBUG_OUTPUT
#define DEBUG_FUNC_NAME
#else*/
#define DEBUG_FUNC_NAME DbgHelper dbgHelper(Q_FUNC_INFO);
/*#endif*/


#include <QtCore/QString>
/**
 * DbgHelper is a debug helper, it shows the debug output more clearly
 */

class DbgHelper
{
public:
    DbgHelper(const QString &t);
    ~DbgHelper();
private:
    QString txt;
    static int indent;
    static int colorIndex;
    int myColor;
};
#endif
