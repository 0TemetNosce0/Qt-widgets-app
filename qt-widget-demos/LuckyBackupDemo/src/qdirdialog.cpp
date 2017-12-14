/**********************************************************************
** Author: Nicolas Remy
** Copyright (C) 2002-2004 The Board of Trustees of the Leland Stanford Junior
**   University
** All rights reserved.
**
** This file is part of the luckybackup project
**
** This file may be distributed and/or modified under the terms of the 
** license defined by the Stanford Center for Reservoir Forecasting and 
** appearing in the file LICENSE.XFREE included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.gnu.org/copyleft/gpl.html for GPL licensing information.
**
** Contact the Stanford Center for Reservoir Forecasting, Stanford University
** if any conditions of this licensing are not clear to you.
**
**********************************************************************/

#include "qdirdialog.h"


QDirDialog::QDirDialog( const QString& extension, 
                        const QString& dirName, QWidget* parent,
                        const char* name, 
                        QFileDialog::FileMode mode,
                        bool modal )
  : QFileDialog( parent, QString::null, dirName),
    extension_( extension ) {

  if(name)
    setObjectName(name);

  setModal(modal);
  init_dialog( mode );
}

QDirDialog::QDirDialog( const QString& extension, 
                        QWidget* parent,
                        const char* name, 
                        QFileDialog::FileMode mode,
                        bool modal )
  : QFileDialog( parent, Qt::Dialog),
    extension_( extension ) {

  setModal(modal);
  if(name)
    setObjectName(name);
  
  init_dialog( mode );
}


void QDirDialog::check_selected_directory( const QString& dirName ) {
  if( !dirName.endsWith( extension_, Qt::CaseInsensitive) ) return;

  selected_directory_ = dirName;
  this->accept();
}


void QDirDialog::init_dialog( QFileDialog::FileMode mode ) {
  setFileMode( mode );

  QObject::connect( this, SIGNAL( directoryEntered( const QString& ) ),
                    this, SLOT( check_selected_directory( const QString& ) ) );

}


void QDirDialog::accept() {
  QDialog::accept();
  QStringList sl = selectedFiles();
  if( selected_directory_.isEmpty() ) {
    selected_directory_ = sl[0];
  }
}
