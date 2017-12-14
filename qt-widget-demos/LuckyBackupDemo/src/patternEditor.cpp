/* ---------------------------------- patternEditor.cpp ---------------------------------------------------------------------------
 Displays the pattern editor

===============================================================================================================================
===============================================================================================================================
     This file is part of "luckyBackup" project
     Copyright, Loukas Avgeriou
     luckyBackup is distributed under the terms of the GNU General Public License
     luckyBackup is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.
 
     luckyBackup is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
 
     You should have received a copy of the GNU General Public License
     along with luckyBackup.  If not, see <http://www.gnu.org/licenses/>.


 project version	: Please see "main.cpp" for project version

 developer 		: luckyb 
 last modified 	: 16 Jan 2012
===============================================================================================================================
===============================================================================================================================*/

#include "patternEditor.h"

// class patternEditor Constructor=================================================================================================
// Displays the pattern editor dialog
patternEditor::patternEditor (QString sourceRoot, QWidget *parent) : QDialog (parent)
{
    uiP.setupUi(this);
    uiP.groupBox_name -> setEnabled (FALSE);
    uiP.checkBox_pathAbsolute -> setEnabled (FALSE);
    uiP.checkBox_pathAny -> setEnabled (FALSE);
    uiP.spinBox_pathDeeper -> setEnabled (FALSE);
    uiP.label_pathDeeper -> setEnabled (FALSE);
    uiP.toolButton_browseFile -> setVisible(FALSE);
    uiP.checkBox_pathAbsolute -> setVisible(FALSE);
    uiP.label_browse -> setText(tr("directory :"));
    
    anchorSource="";
    itsPattern = "no pattern defined yet";
    SourceRoot = sourceRoot;
    if (!SourceRoot.endsWith(SLASH))
    {
        anchorSource = sourceRoot.right(sourceRoot.size()-sourceRoot.lastIndexOf(SLASH));
        SourceRoot.append(SLASH);
    }
    patternLine = "";
    
    //connect okay & cancel pushButton SLOTs ----------------
    connect ( uiP.pushButton_okay, SIGNAL( clicked() ), this, SLOT( okay() ) );
    connect ( uiP.pushButton_cancel, SIGNAL( clicked() ), this, SLOT( cancel() ) );
    connect ( uiP.pushButton_reset, SIGNAL( clicked() ), this, SLOT( resetFileds() ) );

    //Connect all toolButtons with the browse SLOT
    //Map all the toolButton signals and transmit a different integer depending on the toolbutton
    QSignalMapper *signalMapper = new QSignalMapper(this);
    signalMapper ->	setMapping ( uiP.toolButton_browseFile, 0 );
    connect (uiP.toolButton_browseFile, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    signalMapper ->	setMapping ( uiP.toolButton_browseDir, 1 );
    connect (uiP.toolButton_browseDir, SIGNAL (clicked() ), signalMapper , SLOT (map()));
    connect(signalMapper, SIGNAL(mapped( const int)), this, SLOT( browse( const int) )  );

    // connect all actions to fill-in the pattern at the lineEdit
    connect (uiP.radioButton_fileSpecific , SIGNAL(clicked(bool)), this, SLOT(fillPattern()));
    connect (uiP.radioButton_directorySpecific , SIGNAL(clicked(bool)), this, SLOT(fillPattern()));
    connect (uiP.radioButton_fileSet , SIGNAL(clicked(bool)), this, SLOT(fillPattern()));
    connect (uiP.radioButton_directorySet , SIGNAL(clicked(bool)), this, SLOT(fillPattern()));
    connect (uiP.lineEdit_browse , SIGNAL(textChanged(QString)), this, SLOT(fillPattern()));
    connect (uiP.spinBox_pathDeeper , SIGNAL(valueChanged(int)), this, SLOT(fillPattern()));
    connect (uiP.checkBox_directoryContents , SIGNAL(clicked(bool)), this, SLOT(fillPattern()));
    connect (uiP.lineEdit_nameIsExactly , SIGNAL(textChanged(QString)), this, SLOT(fillPattern()));
    connect (uiP.lineEdit_nameStartsWith , SIGNAL(textChanged(QString)), this, SLOT(fillPattern()));
    connect (uiP.lineEdit_nameEndsWith , SIGNAL(textChanged(QString)), this, SLOT(fillPattern()));
    connect (uiP.lineEdit_nameContains , SIGNAL(textChanged(QString)), this, SLOT(fillPattern()));
    connect (uiP.radioButton_fileSpecific , SIGNAL(toggled(bool)), this, SLOT(fileRadioChanged()));
    connect (uiP.checkBox_pathAny , SIGNAL(clicked(bool)), this, SLOT(fillPattern()));
    connect (uiP.checkBox_pathAbsolute , SIGNAL(clicked(bool)), this, SLOT(fillPattern()));
}
// SLOTS-------------------------------------------------------------------------------------
// --------------------------------okay pressed------------------------------------------------
void patternEditor::okay()
{
    itsPattern = uiP.lineEdit_patternFinal -> text();
    close();
}
// --------------------------------cancel pressed------------------------------------------------
void patternEditor::cancel()
{
    close();
}

void patternEditor::closeEvent(QCloseEvent *event)
 {
    event->accept();
 }
 
// --------------------------------reset pressed------------------------------------------------
//reset all fields to default values
void patternEditor::resetFileds()
{
    uiP.lineEdit_nameIsExactly -> setText("");
    uiP.lineEdit_nameStartsWith -> setText("");
    uiP.lineEdit_nameEndsWith -> setText("");
    uiP.lineEdit_nameContains -> setText("");
    uiP.groupBox_name -> setEnabled (FALSE);
    
    uiP.checkBox_pathAbsolute -> setCheckState(Qt::Unchecked);
    uiP.checkBox_pathAbsolute -> setEnabled (FALSE);
    uiP.checkBox_pathAbsolute -> setVisible(FALSE);
    
    uiP.checkBox_pathAny -> setCheckState(Qt::Unchecked);
    uiP.checkBox_pathAny -> setEnabled (FALSE);
    uiP.spinBox_pathDeeper -> setValue(0);
    uiP.spinBox_pathDeeper -> setEnabled (FALSE);
    uiP.label_pathDeeper -> setEnabled (FALSE);
    
    uiP.toolButton_browseFile -> setVisible(FALSE);
    
    uiP.checkBox_directoryContents -> setCheckState(Qt::Unchecked);
    uiP.radioButton_directorySpecific -> setChecked(TRUE);
    
    uiP.lineEdit_browse -> setText("");
    uiP.lineEdit_browse -> setEnabled (TRUE);
    uiP.lineEdit_patternFinal -> setText("");
    uiP.toolButton_browseDir -> setVisible(TRUE);
    uiP.label_browse -> setText(tr("directory :"));
} 
 // browse button pressed=====================================================================================================
//opens a QFileDialog to browse for files/folders locally
void patternEditor::browse(const int type)
{
    QString newLineEdit;
    switch (type)
    {
        //file browse button
        case 0:	newLineEdit = QFileDialog::getOpenFileName (this, tr("Select file"),SourceRoot);
            
            if (newLineEdit != "")	//if something is selected indeed (not cancel pressed)
            {
                if (notXnixRunning)
                    newLineEdit.replace("/",SLASH); // The OS2 filedialog captures path with *nix slashes. Change it to OS2 style
        
                if (!newLineEdit.startsWith(SourceRoot))
                {
                    textDialog textdialogW ("QtWarning", tr("Please choose a file within the source")+" :<br><br>" +
                        SourceRoot, this);
                    textdialogW.exec();
                }
                else
                    uiP.lineEdit_browse 	-> setText(newLineEdit);
            }
            break;
        //directory browse button
        case 1: newLineEdit = QFileDialog::getExistingDirectory (this, tr("Select directory"),SourceRoot);

            if (newLineEdit != "")	//if something is selected indeed (not cancel pressed)
            {
                if (notXnixRunning)
                    newLineEdit.replace("/",SLASH); // The OS2 filedialog captures path with *nix slashes. Change it to OS2 style
                    
                if (!newLineEdit.endsWith(SLASH))
                    newLineEdit.append(SLASH);
                    
                if (newLineEdit == "//")    // root selected - *nix
                        newLineEdit = "/";
                
                if (!newLineEdit.startsWith(SourceRoot))
                {
                    textDialog textdialogW ("QtWarning", tr("Please choose a directory within the source")+" :<br><br>" +
                        SourceRoot, this);
                    textdialogW.exec();
                }
                else
                    uiP.lineEdit_browse     -> setText(newLineEdit);
            }
            break;
    }

}
//fillPattern ====================================================================================================================
//SLOT to fill-in the pattern from the info in the dialog
void patternEditor::fillPattern()
{
    patternLine = "";
    
    // Use absolute path ----------------------------------------------------------------------------------------------------------
    if (uiP.checkBox_pathAbsolute -> isEnabled())
    {
        bool pathAbsoluteState = uiP.checkBox_pathAbsolute -> isChecked();
        uiP.lineEdit_browse -> setEnabled(pathAbsoluteState);
        uiP.toolButton_browseFile -> setEnabled(pathAbsoluteState);
        uiP.toolButton_browseDir -> setEnabled(pathAbsoluteState);
        uiP.label_pathDeeper -> setEnabled(pathAbsoluteState);
        uiP.spinBox_pathDeeper -> setEnabled(pathAbsoluteState);
        uiP.checkBox_pathAny -> setEnabled(pathAbsoluteState);
    }
    else
    {
        uiP.lineEdit_browse -> setEnabled(FALSE);
        uiP.toolButton_browseFile -> setEnabled(FALSE);
        uiP.toolButton_browseDir -> setEnabled(FALSE);
        uiP.label_pathDeeper -> setEnabled(FALSE);
        uiP.spinBox_pathDeeper -> setEnabled(FALSE);
        uiP.checkBox_pathAny -> setEnabled(FALSE);
    }
    
    if ( (uiP.radioButton_fileSpecific -> isChecked()) || (uiP.radioButton_directorySpecific -> isChecked()) )
    {
        uiP.lineEdit_browse -> setEnabled(TRUE);
        uiP.toolButton_browseFile -> setEnabled(TRUE);
        uiP.toolButton_browseDir -> setEnabled(TRUE);
    }
        
    // Read the path lineEdit
    if (uiP.lineEdit_browse -> isEnabled())
    {
        patternLine = uiP.lineEdit_browse -> text();	//first get the string from the path lineEdit
        if (patternLine.startsWith(SourceRoot))
            patternLine.replace (SourceRoot, anchorSource + SLASH);	// replace the starting source in the pattern with /
    }
    
    //go deeper in path ------------------- -------------------------------------------------------------------------------
    if ( (uiP.checkBox_pathAny->isEnabled()) && (uiP.checkBox_pathAny->isChecked()) )
        patternLine.append("**"+SLASH);
    else
    {
        count=0;
        while ( (count < uiP.spinBox_pathDeeper->value()) && (uiP.spinBox_pathDeeper->isEnabled()))
        {
            patternLine.append("*"+SLASH);
            count++;
        }
    }
    
    // groupbox NAME actions ------------------------------------------------------------------------------------------------
    if (uiP.lineEdit_nameIsExactly->text()=="")
    {
        uiP.lineEdit_nameStartsWith -> setEnabled(TRUE);
        uiP.lineEdit_nameEndsWith -> setEnabled(TRUE);
        uiP.lineEdit_nameContains -> setEnabled(TRUE);
    }
    else
    {
        uiP.lineEdit_nameStartsWith -> setEnabled(FALSE);
        uiP.lineEdit_nameEndsWith -> setEnabled(FALSE);
        uiP.lineEdit_nameContains -> setEnabled(FALSE);
    }
    
    if (uiP.lineEdit_nameIsExactly -> isEnabled())
        patternLine.append(uiP.lineEdit_nameIsExactly->text());
    
    if ( (uiP.lineEdit_nameStartsWith -> isEnabled()) && (!(uiP.lineEdit_nameStartsWith->text() == "")) )
        patternLine.append(uiP.lineEdit_nameStartsWith -> text() + "*");
    
    if ( (uiP.lineEdit_nameContains -> isEnabled()) && (!(uiP.lineEdit_nameContains -> text()=="")) )
    {
        if (uiP.lineEdit_nameStartsWith -> text()=="")
            patternLine.append("*");
        patternLine.append(uiP.lineEdit_nameContains -> text() + "*");
    }
    
    if ( (uiP.lineEdit_nameEndsWith->isEnabled()) && (!(uiP.lineEdit_nameEndsWith -> text()=="")) )
    {
        if ( (uiP.lineEdit_nameContains -> text()=="") && (uiP.lineEdit_nameStartsWith -> text()=="") )
            patternLine.append("*");
        patternLine.append( uiP.lineEdit_nameEndsWith->text());
    }

    // RADIO BUTTONS actions ----------------------------------------------------------------------------------------------------
    if (uiP.radioButton_fileSpecific -> isChecked())	// if file specific radio button is selected
    {
        uiP.label_browse -> setVisible(TRUE);

        uiP.label_browse -> setText(tr("file :"));
        if (patternLine.endsWith(SLASH))
            patternLine.chop(1);
    }
    if (uiP.radioButton_directorySpecific -> isChecked())	// if directory specific radio button is selected
    {
        uiP.label_browse -> setVisible(TRUE);
        uiP.label_browse -> setText(tr("directory :"));
        if ((!(patternLine.endsWith(SLASH))) && (!(patternLine == "")) )
            patternLine.append(SLASH);
    }
    if (uiP.radioButton_fileSet -> isChecked())		// if file set radio button is selected
    {
        uiP.checkBox_pathAbsolute -> setEnabled (TRUE);
        uiP.label_browse -> setVisible(FALSE);
        if (patternLine.endsWith(SLASH))
            patternLine.chop(1);
    }
    if (uiP.radioButton_directorySet -> isChecked())	// if directory set radio button is selected
    {
        uiP.checkBox_pathAbsolute -> setEnabled (TRUE);
        uiP.label_browse -> setVisible(FALSE);
        if ( (!(patternLine.endsWith(SLASH))) && (!(patternLine == "")) )
            patternLine.append(SLASH);
    }
    
    //just the contents of a directory -------------------------------------------------------------------------------
    if ( (uiP.checkBox_directoryContents->isChecked()) && (uiP.checkBox_directoryContents->isEnabled()) )
        patternLine.append("**");
    
    if (notXnixRunning)
        patternLine.replace(SLASH,"/"); // replace OS2 slashes with *nix ones -> OS2 uses *nix slashes for patterns

    uiP.lineEdit_patternFinal -> setText(patternLine);
}
//fileRadioChanged----------------------------------------------------------------------------
//actions when the file specific radio button is toggled
void patternEditor::fileRadioChanged()
{
    uiP.lineEdit_browse -> setText("");
}

 // --------------------------------accessors-----------------------------------
QString patternEditor::getPattern()
 {
    return itsPattern;
 }


// end of patternEditor.cpp ---------------------------------------------------------------------------

