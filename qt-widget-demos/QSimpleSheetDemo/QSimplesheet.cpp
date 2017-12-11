// +-------------------------------------------------------------------------+
// | QSimpleSheet simple spreadsheet                                         |
// | Copyright (C) 2008 Shahab <shahab.sh.70@gmail.com>                      |
// +-------------------------------------------------------------------------+
// | License:                                                                |
// |                                                                         |
// | QSimpleSheet is free software; you can redistribute it and/or modify    |
// | it under the terms of the GNU General Public License as published by    |
// | the Free Software Foundation; either version 2 of the License, or       |
// | (at your option) any later version.                                     |
// |                                                                         |
// | QSimpleSheet is distributed in the hope that it will be useful,         |
// | but WITHOUT ANY WARRANTY; without even the implied warranty of          |
// | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            |
// | GNU General Public License for more details.                            |
// |                                                                         |
// | You should have received a copy of the GNU General Public License       |
// | along with QSimpleSheet; if not, write to the Free Software             |
// | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA|
// |                                                                         |
// +-------------------------------------------------------------------------+
// | Author:  Shahab Shirazi <shahab.sh.70@gmail.com>                        |
// +-------------------------------------------------------------------------+

#include <QApplication>
#include <QStringList>
#include <QSplashScreen>
#include <QPixmap>
#include "QSimplesheet.h"
#include "MainWindow.h"

int main(int argc, char *argv[]) 
{
   QApplication app(argc, argv);

   QSplashScreen *splash = new QSplashScreen;
   splash->setPixmap(QPixmap(":/images/splashscreen.png"));
   splash->show();

   QStringList args = app.arguments();
   MainWindow mainWindow;

   if (args.count() > 1)
   {
       mainWindow.open(args[1]);
   }

   mainWindow.show();
   
   splash->finish(&mainWindow);
   delete splash;
      
   return app.exec();
}
